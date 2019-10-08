using Engine;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

using static Engine.Global;
using static Game;

class GameplayState : IGameState
{
    bool view_debug = false;

    //Game World
    Transform camera = new Transform();
    float field_of_view = 3 / 8f * Tau;
    Transform[] transforms;
    public static readonly Player[] players = new Player[PLAYER_COUNT];
    readonly Animator[] animators = new Animator[PLAYER_COUNT];
    public static readonly Color[] player_colors = new Color[] { Color.Red, Color.Green, Color.Blue, Color.Purple };
    Transform[] blocks = new Transform[30];

    //Play variables
    public const int PLAYER_COUNT = 4; //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players
    int winner = 0;
    bool game_over = false;
    float initial_time = 99;
    float time_remaining;
    float max_health = 10;

    //physics
    readonly float gravity = 10;

    public GameplayState()
    {
        ResetGame();
        for (int i = 0; i < blocks.Length; i++)
        {
            blocks[i] = Transform.Default();
            blocks[i].position.x = (i % 10) - 5;
        }

        for (int i = 0; i < 10; i++)
        {
            blocks[i].position.y = 4f;
        }

        for (int i = 10; i < 20; i++)
        {
            blocks[i].position.y = -2f;
        }

        for (int i = 20; i < 30; i++)
        {
            blocks[i].position.y = -3f;
        }

        blocks[17].position.y = -1;
        blocks[15].position.y = -1;
        blocks[15].position.x -= .25f;
        blocks[18].scale.x = 50f;
        blocks[29].scale.x = 10f;
        blocks[29].position = new Vector3(-10, 1, 0);
    }

    public unsafe void Update()
    {
        //Update
        {
            graphics.Clear(Color.Black);
            //Get Debug Input
            {
                if (Input.KeyDownFresh(Keys.G))
                    view_debug = !view_debug;

                if (Input.KeyDownFresh(Keys.R))
                    ResetGame();

                if (Input.KeyDownFresh(Keys.F))
                    fixed_framerate = !fixed_framerate;
            }

            if (!game_over)
            {
                for (int player_index = 0; player_index < PLAYER_COUNT; player_index++)
                {
                    fixed (Transform* playerTransform = &(transforms[players[player_index].entity_ID]))
                    {
                        //Animate Player
                        {
                            KeyFrame[] first_curve_frames = animators[player_index].current_animation.curves[0].keyframes;
                            float ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;

                            if (!players[player_index].defeated)
                            {
                                //Set Animation State
                                {
                                    bool moving = false;

                                    if (animators[player_index].current_animation.curves != DefinedAnimations.punch_curves) //TODO use animation, not just curves
                                    {
                                        if (Input.ButtonDown(player_index, Buttons.LEFT))
                                        {
                                            (*playerTransform).rotation.y = -1 / 4f * Tau;
                                            moving = true;
                                        }

                                        if (Input.ButtonDown(player_index, Buttons.RIGHT))
                                        {
                                            (*playerTransform).rotation.y = 1 / 4f * Tau;
                                            moving = true;
                                        }

                                        if (moving)
                                        {
                                            animators[player_index].current_animation = DefinedAnimations.walk_animation;
                                            var rotation = (*playerTransform).rotation;
                                        }
                                        else
                                            animators[player_index].current_animation = DefinedAnimations.idle_animation;

                                        if (Input.ButtonDown(player_index, Buttons.PUNCH))
                                        {
                                            animators[player_index].current_animation = DefinedAnimations.punch_animation;
                                            animators[player_index].current_frame = 1;
                                        }
                                    }
                                    else if (animators[player_index].current_frame >= ending_frame)
                                    {
                                        animators[player_index].current_animation = DefinedAnimations.idle_animation;
                                        animators[player_index].current_frame = 1;
                                    }
                                }
                            }

                            //Play Animation
                            {
                                Animator animator = animators[player_index];
                                if (animator.current_animation.looped && animator.current_frame >= ending_frame)
                                    animator.current_frame = 1;


                                float frame = animators[player_index].current_frame;

                                foreach (AnimationCurve curve in animator.current_animation.curves)
                                {
                                    KeyFrame[] keyframes = curve.keyframes;
                                    int transform_index = curve.transform_index + player_index * skeleton.Length;

                                    fixed (Transform* p = &transforms[transform_index])
                                    {
                                        float* f = &(*p).position.x + curve.property_tag;

                                        AnimateProperty(keyframes, frame, ref *f);
                                    }
                                }

                                for (int attackbox_index = 0; attackbox_index < players[player_index].attackboxes.Length; attackbox_index++)
                                {
                                    if (animator.current_animation.attackbox_keys != null)
                                        for (int i = 0; i < animator.current_animation.attackbox_keys[attackbox_index].Length; i++)
                                        {
                                            if (frame > animator.current_animation.attackbox_keys[attackbox_index][i])
                                            {
                                                players[player_index].attackboxes[attackbox_index].active = animator.current_animation.attackbox_values[attackbox_index][i];
                                            }
                                        }
                                }

                                for (int defendbox_index = 0; defendbox_index < players[player_index].defendboxes.Length; defendbox_index++)
                                {
                                    if (animator.current_animation.defendbox_keys != null)
                                        for (int i = 0; i < animator.current_animation.defendbox_keys[defendbox_index].Length; i++)
                                        {
                                            if (frame > animator.current_animation.defendbox_keys[defendbox_index][i])
                                            {
                                                players[player_index].defendboxes[defendbox_index].active = animator.current_animation.defendbox_values[defendbox_index][i];
                                            }
                                        }
                                }

                                animator.current_frame += TARGET_FRAMERATE * delta_time;

                                animators[player_index] = animator;
                            }
                        }

                        //Move Player
                        {
                            float acceleration = 100f;
                            float jump_speed = 8;
                            float max_speed = 5;
                            float slide_coefficient = 0;
                            bool no_horizontal_input = false;
                            float ground_fall_velocity = -.01f;

                            if (!players[player_index].defeated)
                            {
                                if (Input.ButtonDown(player_index, Buttons.RIGHT))
                                    players[player_index].velocity.x += acceleration * delta_time;
                                else if (Input.ButtonDown(player_index, Buttons.LEFT))
                                    players[player_index].velocity.x -= acceleration * delta_time;
                                else
                                    no_horizontal_input = true;
                            }

                            if (players[player_index].velocity.x > max_speed)
                                players[player_index].velocity.x = max_speed;
                            else if (players[player_index].velocity.x < -max_speed)
                                players[player_index].velocity.x = -max_speed;

                            if (players[player_index].grounded)
                            {
                                players[player_index].velocity.y = ground_fall_velocity;

                                if (no_horizontal_input)
                                    players[player_index].velocity.x *= slide_coefficient;

                                if (!players[player_index].defeated && Input.ButtonDown(player_index, Buttons.JUMP))
                                    players[player_index].velocity.y = jump_speed;
                            }
                            else
                            {
                                players[player_index].velocity.y -= gravity * delta_time;
                            }

                            float ax_half = transforms[players[player_index].entity_ID].scale.x / 2;
                            float ay_half = transforms[players[player_index].entity_ID].scale.y / 2;


                            var old_x = transforms[players[player_index].entity_ID].position.x;
                            transforms[players[player_index].entity_ID].position.x += players[player_index].velocity.x * delta_time;

                            for (int i = 0; i < blocks.Length; i++)
                            {
                                var b = blocks[i];
                                if (Intersect(transforms[players[player_index].entity_ID], b))
                                {
                                    if (old_x < b.position.x)
                                        transforms[players[player_index].entity_ID].position.x -= (transforms[players[player_index].entity_ID].position.x + (transforms[players[player_index].entity_ID].scale.x / 2)) - (b.position.x - (b.scale.x / 2));
                                    else if (old_x > b.position.x)
                                        transforms[players[player_index].entity_ID].position.x += (b.position.x + (b.scale.x / 2)) - (transforms[players[player_index].entity_ID].position.x - (transforms[players[player_index].entity_ID].scale.x / 2));
                                }
                            }

                            var old_y = transforms[players[player_index].entity_ID].position.y;
                            transforms[players[player_index].entity_ID].position.y += players[player_index].velocity.y * delta_time;

                            players[player_index].grounded = false;

                            for (int i = 0; i < blocks.Length; i++)
                            {
                                var b = blocks[i];
                                if (Intersect(transforms[players[player_index].entity_ID], b))
                                {
                                    if (old_y < b.position.y)
                                    {
                                        transforms[players[player_index].entity_ID].position.y -= (transforms[players[player_index].entity_ID].position.y + (transforms[players[player_index].entity_ID].scale.y / 2)) - (b.position.y - (b.scale.y / 2));
                                        players[player_index].velocity.y = 0;
                                    }
                                    else if (old_y > b.position.y)
                                    {
                                        transforms[players[player_index].entity_ID].position.y += (b.position.y + (b.scale.y / 2)) - (transforms[players[player_index].entity_ID].position.y - (transforms[players[player_index].entity_ID].scale.y / 2));
                                        players[player_index].grounded = true;
                                    }
                                }
                            }

                            if (transforms[players[player_index].entity_ID].position.Magnitude() > 50)
                            {
                                transforms[players[player_index].entity_ID].position = Vector3.Zero;
                                players[player_index].stock--;
                            }
                        }

                    }

                    //Hurt Player --TODO fix. also make sure only applies the first time on the first frame of an intersection with first defendbox. Is currently be multiple damaging.
                    {
                        for (int my_attack = 0; my_attack < players[player_index].attackboxes.Length; my_attack++)
                        {
                            if (players[player_index].attackboxes[my_attack].active)
                                for (int other_player = 0; other_player < PLAYER_COUNT; other_player++)
                                {
                                    if (other_player == player_index)
                                        continue;
                                    for (int your_defend = 0; your_defend < players[other_player].defendboxes.Length; your_defend++)
                                    {
                                        var a = WorldSpaceMatrix(players[player_index].attackboxes[my_attack].transform_index, transforms);
                                        var b = WorldSpaceMatrix(players[other_player].defendboxes[your_defend].transform_index, transforms);

                                        Vector3 v = TransformVector(a, Vector3.Zero);
                                        Vector3 w = TransformVector(b, Vector3.Zero);

                                        var dist = Vector3.Distance(v, w);
                                        bool intersects = (dist <= (players[other_player].defendboxes[your_defend].radius + players[player_index].attackboxes[my_attack].radius));

                                        if (intersects)
                                        {
                                            players[other_player].health -= 10 * delta_time;
                                            if (players[other_player].health <= 0)
                                            {
                                                players[other_player].stock--;
                                                if (players[other_player].stock > 0)
                                                    players[other_player].health = max_health;
                                                else if (!players[other_player].defeated)
                                                {
                                                    players[other_player].defeated = true;
                                                    animators[other_player].current_animation = DefinedAnimations.die_animation;
                                                    animators[other_player].current_frame = 1;
                                                }
                                            }
                                        }
                                    }
                                }
                        }
                    }
                }

                //Update Camera
                {
                    //TODO actual frustum check to keep players on screen
                    float min_x = float.MaxValue;
                    float min_y = float.MaxValue;

                    float max_x = -float.MaxValue;
                    float max_y = -float.MaxValue;

                    foreach (var player in players)
                    {
                        var x = transforms[player.entity_ID].position.x;
                        var y = transforms[player.entity_ID].position.y;

                        if (x < min_x)
                            min_x = x;
                        if (x > max_x)
                            max_x = x;

                        if (y < min_y)
                            min_y = y;
                        if (y > max_y)
                            max_y = y;
                    }

                    camera.position.x = (max_x + min_x) / 2;
                    camera.position.y = (max_y + min_y) / 2;
                    camera.position.z = -20 - (max_x - min_x);

                }

                //Check Match Complete
                {
                    int remaining_players = 0;

                    for (int i = 0; i < PLAYER_COUNT; i++)
                    {
                        if (!players[i].defeated)
                        {
                            remaining_players++;
                            winner = i + 1;
                        }
                    }

                    if (remaining_players != 1)
                        winner = 0;

                    time_remaining -= delta_time;
                    game_over = winner != 0 || remaining_players == 0 || time_remaining <= 0;
                }
            }
        }

        //Render
        {
            //Draw Scene
            {
                //get camera matrix
                Matrix4x4 world_to_camera = GetMatrix(InvertTransform(camera));


                //Draw Blocks
                {
                    graphics.SmoothingMode = SmoothingMode.None;

                    for (int i = 0; i < blocks.Length; i++)
                    {
                        Matrix4x4 local_to_world = WorldSpaceMatrix(i, blocks);
                        Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view);
                        Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

                        Vector4 position = new Vector4(-.5f, .5f, 0, 1);
                        position = TransformVector(local_to_clip, position);

                        if (position.w != 0)
                            position /= position.w;

                        //place origin at center of screen
                        position.x++;
                        position.y++;

                        //scale space to fill screen
                        position.x *= WIDTH / 2;
                        position.y *= HEIGHT / 2;

                        Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
                        position2 = TransformVector(local_to_clip, position2);

                        if (position2.w != 0)
                            position2 /= position2.w;

                        //place origin at center of screen
                        position2.x++;
                        position2.y++;

                        //scale space to fill screen
                        position2.x *= WIDTH / 2;
                        position2.y *= HEIGHT / 2;

                        graphics.FillRectangle(Brushes.Brown, position.x, position.y, position2.x - position.x, position2.y - position.y);
                    }
                }


                Vector3[] transformed_positions = new Vector3[transforms.Length];

                //Draw Transforms
                {
                    graphics.SmoothingMode = SmoothingMode.HighQuality;

                    for (int i = 0; i < transforms.Length; i++)
                    {
                        Matrix4x4 local_to_world = WorldSpaceMatrix(i, transforms);
                        Matrix4x4 local_to_camera = local_to_world * world_to_camera;

                        Vector3 position = TransformVector(local_to_camera, Vector3.Zero);

                        Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view);

                        var v4 = new Vector4(position.x, position.y, position.z, 1);
                        v4 = TransformVector(camera_to_clip, v4);

                        position = new Vector3(v4.x, v4.y, v4.z);

                        if (v4.w != 0)
                            position /= v4.w;

                        //place origin at center of screen
                        position.x++;
                        position.y++;

                        //scale space to fill screen
                        position.x *= WIDTH / 2;
                        position.y *= HEIGHT / 2;

                        transformed_positions[i] = position;
                    }

                    for (int i = 0; i < transformed_positions.Length; i++)
                    {
                        var position = transformed_positions[i];
                        var parent_position = position;

                        if (transforms[i].parent != -1)
                            parent_position = transformed_positions[transforms[i].parent];

                        float d = camera.position.z - position.z;
                        float width = 450 / (d);
                        float half_width = width / 2;

                        Pen player_pen = new Pen(player_colors[i / GetSkeleton().Length]);
                        graphics.DrawLine(player_pen, position.x, position.y, parent_position.x, parent_position.y);
                        graphics.DrawEllipse(player_pen, position.x - half_width, position.y - half_width, width, width);
                    }


                }

                if (view_debug)
                {
                    //Draw Hitboxes
                    {
                        for (int player_index = 0; player_index < PLAYER_COUNT; player_index++)
                        {
                            for (int attackbox_index = 0; attackbox_index < players[player_index].attackboxes.Length; attackbox_index++)
                            {
                                if (players[player_index].attackboxes[attackbox_index].active)
                                {
                                    Vector3 center = transformed_positions[players[player_index].attackboxes[attackbox_index].transform_index];
                                    float width = players[player_index].attackboxes[attackbox_index].radius * 2 * PIXELS_PER_UNIT;
                                    DrawHitbox(center, Color.Red, width);
                                }
                            }

                            for (int i = 0; i < players[player_index].defendboxes.Length; i++)
                            {

                                if (players[player_index].defendboxes[i].active)
                                {
                                    Vector3 center = transformed_positions[players[player_index].defendboxes[i].transform_index];
                                    float d = camera.position.z - center.z;
                                    float width = 30 * (players[player_index].defendboxes[i].radius * 2 * PIXELS_PER_UNIT) / (d);
                                    DrawHitbox(center, Color.Blue, width);
                                }
                            }
                        }
                    }

                    //Draw Colliders
                    {
                        for (int i = 0; i < blocks.Length; i++)
                        {
                            Matrix4x4 local_to_world = WorldSpaceMatrix(i, blocks);
                            Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view);
                            Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

                            Vector4 position = new Vector4(-.5f, .5f, 0, 1);
                            position = TransformVector(local_to_clip, position);

                            if (position.w != 0)
                                position /= position.w;

                            //place origin at center of screen
                            position.x++;
                            position.y++;

                            //scale space to fill screen
                            position.x *= WIDTH / 2;
                            position.y *= HEIGHT / 2;

                            Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
                            position2 = TransformVector(local_to_clip, position2);

                            if (position2.w != 0)
                                position2 /= position2.w;

                            //place origin at center of screen
                            position2.x++;
                            position2.y++;

                            //scale space to fill screen
                            position2.x *= WIDTH / 2;
                            position2.y *= HEIGHT / 2;

                            graphics.DrawRectangle(Pens.Blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
                        }

                        for (int i = 0; i < players.Length; i++)
                        {
                            Matrix4x4 local_to_world = WorldSpaceMatrix(players[i].entity_ID, transforms);
                            Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view);
                            Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

                            Vector4 position = new Vector4(-.5f, .5f, 0, 1);
                            position = TransformVector(local_to_clip, position);

                            if (position.w != 0)
                                position /= position.w;

                            //place origin at center of screen
                            position.x++;
                            position.y++;

                            //scale space to fill screen
                            position.x *= WIDTH / 2;
                            position.y *= HEIGHT / 2;

                            Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
                            position2 = TransformVector(local_to_clip, position2);

                            if (position2.w != 0)
                                position2 /= position2.w;

                            //place origin at center of screen
                            position2.x++;
                            position2.y++;

                            //scale space to fill screen
                            position2.x *= WIDTH / 2;
                            position2.y *= HEIGHT / 2;

                            graphics.DrawRectangle(Pens.Blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
                        }
                    }
                }
            }

            //Draw Heads-Up Display
            {
                var available_space = WIDTH / PLAYER_COUNT;
                Point indent = new Point(30, 10);
                Pen stroke = new Pen(Color.Black, 3f);
                int healthWidth = available_space - indent.X * 2;
                int healthHeight = 15;

                for (int player = 0; player < PLAYER_COUNT; player++)
                {
                    //Draw HealthBar
                    {
                        float percent = (float)(players[player].health) / max_health;
                        int myWidth = (int)(percent * (float)healthWidth);
                        Rectangle rect = new Rectangle(indent.X, indent.Y, healthWidth, healthHeight);

                        graphics.FillRectangle(Brushes.Red, rect);
                        rect.Width = myWidth;
                        graphics.FillRectangle(Brushes.Green, rect);
                        rect.Width = healthWidth;
                        graphics.DrawRectangle(stroke, rect);
                    }

                    //Draw Stocks
                    {
                        Rectangle rect = new Rectangle(indent.X, 30, 20, 20);

                        for (int stock = 0; stock < players[player].stock; stock++)
                        {
                            graphics.FillEllipse(new SolidBrush(player_colors[player]), rect);
                            graphics.DrawEllipse(stroke, rect);
                            graphics.FillEllipse(new SolidBrush(ControlPaint.Light(player_colors[player])), rect.X + 4, rect.Y + 4, 10, 10);
                            rect.X += 25;
                        }
                    }

                    graphics.TranslateTransform(available_space, 0);
                }

                graphics.ResetTransform();

                //Draw Timer
                {
                    Font font = new Font(SystemFonts.DefaultFont.FontFamily, 25, FontStyle.Regular);
                    graphics.DrawString(string.Format("{0:F0}", time_remaining), font, Brushes.White, WIDTH / 2, 25, centered_format);
                }

                if (game_over)
                {
                    //Draw Game End Message
                    {
                        Point offset = new Point(WIDTH / 2, HEIGHT / 2);

                        string message = (winner == 0) ? "TIE!" : ("PLAYER " + winner + " WINS!");
                        Font font = new Font(SystemFonts.DefaultFont.FontFamily, 50, FontStyle.Regular);
                        graphics.DrawString(message, font, Brushes.Red, offset.X - 5, offset.Y - 5, centered_format);
                        graphics.DrawString(message, font, Brushes.Yellow, offset.X, offset.Y, centered_format);
                    }
                }
            }

            if (view_debug)
            {
                //Draw Grid
                {
                    var pen = new Pen(Color.FromArgb(90, 50, 50, 50));
                    for (int x = 0; x < WIDTH / PIXELS_PER_UNIT; x++)
                        graphics.DrawLine(pen, x * PIXELS_PER_UNIT, 0, x * PIXELS_PER_UNIT, HEIGHT);
                    for (int y = 0; y < HEIGHT / PIXELS_PER_UNIT; y++)
                        graphics.DrawLine(pen, 0, y * PIXELS_PER_UNIT, WIDTH, y * PIXELS_PER_UNIT);
                }

                //Display Game Stats
                {
                    graphics.DrawString(string.Format("FPS: {0:F2}", frames_per_second), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 50);
                    graphics.DrawString(string.Format("delta_time: {0:F9}", delta_time), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 65);
                    graphics.DrawString(string.Format("entities: {0}", transforms.Length), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 95);

                    for (int i = 0; i < PLAYER_COUNT; i++)
                    {
                        graphics.DrawString($"position: {transforms[players[i].entity_ID].position:F9}", Control.DefaultFont, Brushes.Yellow, i * WIDTH / 4, 128);
                        graphics.DrawString($"velocity: {players[i].velocity.y:F9}", Control.DefaultFont, Brushes.Yellow, i * WIDTH / 4, 128 + 16);
                    }
                }
            }
        }
    }



    private static unsafe void DrawHitbox(Vector3 center, Color color, float width)
    {
        float half = width / 2f;
        graphics.FillEllipse(new SolidBrush(color), center.x - 4, center.y - 4, 8, 8);
        graphics.FillEllipse(new SolidBrush(Color.FromArgb(30, color)), center.x - half, center.y - half, width, width);
        graphics.DrawEllipse(new Pen(Color.FromArgb(color.R / 2, color.G / 2, color.B / 2), 2f), center.x - half, center.y - half, width, width);
    }

    Transform[] skeleton;
    Transform[] GetSkeleton()
    {
        if (skeleton == null)
            skeleton = LoadHierarchy("avatar");
        return skeleton;
    }

    void ResetGame()
    {
        game_over = false;
        time_remaining = initial_time;
        List<Transform> list_entities = new List<Transform>();
        skeleton = GetSkeleton();
        skeleton[1].position.y = 2;

        float distance_apart = 3.5f;
        float leftmost_position = -(PLAYER_COUNT - 1) * distance_apart / 2;

        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            list_entities.AddRange(skeleton);
            int player_root_index = i * skeleton.Length;

            for (int index = 1; index < skeleton.Length; index++)
            {
                var joint = list_entities[index + player_root_index];
                joint.parent += player_root_index;
                list_entities[index + player_root_index] = joint;
            }

            Transform entity = list_entities[player_root_index];

            entity.position.x = leftmost_position + i * distance_apart;
            entity.rotation.y = 1 / 4f * Tau;

            players[i].health = max_health;
            players[i].defeated = false;
            players[i].entity_ID = i * skeleton.Length;
            players[i].stock = 5;
            players[i].velocity.y = 0;
            players[i].defendboxes = new Hitbox[]
            {
                new Hitbox() { transform_index = 6, radius = .2f, active = true },
                new Hitbox() { transform_index = 4, radius = .2f, active = true },
                new Hitbox() { transform_index = 1, radius = .3f, active = true },
                new Hitbox() { transform_index = 2, radius = .4f, active = true },
                new Hitbox() { transform_index = 3, radius = .2f, active = true },
            };

            players[i].attackboxes = new Hitbox[]
            {
                new Hitbox() { transform_index = 14, radius = .2f },
                new Hitbox() { transform_index = 15, radius = .2f },
            };

            for (int o = 0; o < players[i].attackboxes.Length; o++)
            {
                players[i].attackboxes[o].transform_index += skeleton.Length * i;
            }

            for (int o = 0; o < players[i].defendboxes.Length; o++)
            {
                players[i].defendboxes[o].transform_index += skeleton.Length * i;
            }

            list_entities[player_root_index] = entity;
        }

        transforms = list_entities.ToArray();

        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            Animator new_animator = new Animator();
            new_animator.current_animation = DefinedAnimations.idle_animation;
            new_animator.current_frame = 1;
            animators[i] = new_animator;
        }

        camera.position = new Vector3(0, 0, -20);
        camera.scale = Vector3.One;
    }
}
