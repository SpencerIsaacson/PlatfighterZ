using Engine;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using static Engine.Global;
using static Game;

class GameplayDemo : IGameState
{
    bool view_debug = false;

    //Game World
    Transform camera = new Transform();
    float field_of_view = 3 / 8f * Tau;
    Transform[] transforms;
    readonly Player[] players = new Player[PLAYER_COUNT];
    readonly Animator[] animators = new Animator[PLAYER_COUNT];
    readonly Color[] player_colors = new Color[] { Color.Red, Color.Green, Color.Blue, Color.Purple };

    //Play variables
    const int PLAYER_COUNT = 4; //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players
    int winner = 0;
    bool game_over = false;
    float initial_time = 99;
    float time_remaining;
    float max_health = 10;

    //physics
    readonly float gravity = 10;

    Hitbox[] attackboxes =
    {
        new Hitbox(){transform_index = 14, radius = .2f},
        new Hitbox(){transform_index = 15, radius = .2f},
    };

    public GameplayDemo()
    {
        ResetGame();
    }

    public unsafe void Update()
    {
        //Update
        {
            if (!game_over)
            {
                for (int player_index = 0; player_index < PLAYER_COUNT; player_index++)
                {
                    fixed (Transform* playerEntity = &(transforms[players[player_index].entity_ID]))
                    {
                        Vector3 velocity = Vector3.Zero;
                        if ((*playerEntity).position.y > 0)
                            players[player_index].y_velocity -= gravity * time_step;

                        KeyFrame[] first_curve_frames = animators[player_index].current_animation.curves[0].keyframes;
                        float ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;

                        if (!players[player_index].defeated)
                        {
                            bool moving = false;

                            if (animators[player_index].current_animation.curves != AvatarDemo.punch_curves) //TODO use animation, not just curves
                            {
                                if (Input.ButtonDown(player_index, Buttons.LEFT))
                                {
                                    (*playerEntity).rotation.y = -1 / 4f * Tau;
                                    moving = true;
                                }

                                if (Input.ButtonDown(player_index, Buttons.RIGHT))
                                {
                                    (*playerEntity).rotation.y = 1 / 4f * Tau;
                                    moving = true;
                                }

                                if (moving)
                                {
                                    animators[player_index].current_animation = AvatarDemo.walk_animation;
                                    var rotation = (*playerEntity).rotation;
                                    var playerSpeed = 5f;
                                    velocity.x = TransformVector(Rotation(rotation.x, rotation.y, rotation.z), Vector3.Forward).x * playerSpeed;
                                }
                                else
                                    animators[player_index].current_animation = AvatarDemo.idle_animation;

                                if ((*playerEntity).position.y == 0 && Input.ButtonDown(player_index, Buttons.JUMP))
                                    players[player_index].y_velocity = 10;

                                if (Input.ButtonDown(player_index, Buttons.PUNCH))
                                {
                                    animators[player_index].current_animation = AvatarDemo.punch_animation;
                                    animators[player_index].current_frame = 1;
                                }
                            }
                            else if(animators[player_index].current_frame >= ending_frame )
                            {
                                animators[player_index].current_animation = AvatarDemo.idle_animation;
                                animators[player_index].current_frame = 1;
                            }
                        }

                        //Animate Player
                        {
                            Animator animator = animators[player_index];
                            if (animator.current_frame >= ending_frame)
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

                            for (int attackbox_index = 0; attackbox_index < attackboxes.Length; attackbox_index++)
                            {
                                if(animator.current_animation.attackbox_keys != null)
                                for (int i = 0; i < animator.current_animation.attackbox_keys.Length; i++)
                                {
                                    if (animator.current_frame == animator.current_animation.attackbox_keys[i])
                                    {
                                        attackboxes[attackbox_index].active = animator.current_animation.attackbox_values[i];
                                    }
                                }
                            }

                            animator.current_frame ++;

                            animators[player_index] = animator;
                        }

                        //Move Player
                        {
                            velocity.y = players[player_index].y_velocity;
                            velocity *= time_step;
                            (*playerEntity).position += velocity;

                            if ((*playerEntity).position.y < 0)
                            {
                                (*playerEntity).position.y = 0;
                                players[player_index].y_velocity = 0;
                            }

                            transforms[players[player_index].entity_ID] = (*playerEntity);
                        }

                    }
                    ////Hurt Player
                    //{
                    //    players[player_id].health -= time_step * ((player_id + 1));

                    //    if (players[player_id].health <= 0)
                    //    {
                    //        players[player_id].stock--;
                    //        if (players[player_id].stock > 0)
                    //            players[player_id].health = max_health;
                    //        else
                    //            players[player_id].defeated = true;
                    //    }
                    //}
                }

                //Update Camera
                {
                    float average_x = 0;
                    foreach (var player in players)
                    {
                        average_x += transforms[player.entity_ID].position.x;
                    }
                    average_x /= PLAYER_COUNT;

                    camera.position.x = camera.position.x + time_step * (average_x - camera.position.x);
                }

                //Check if the game is ongoing
                {
                    int remaining_players = 0;

                    //Check Winner
                    {

                        for (int i = 0; i < PLAYER_COUNT; i++)
                        {
                            if (!players[i].defeated)
                            {
                                winner = i + 1;
                                remaining_players++;
                                if (remaining_players != 1)
                                    winner = 0;
                            }
                        }
                    }

                    //Check Match Complete
                    {
                        game_over = winner != 0 || remaining_players == 0;
                        time_remaining -= time_step;
                        if (time_remaining <= 0)
                        {
                            game_over = true;
                        }
                    }
                }
            }

            //Get Debug Input
            {
                if (Input.KeyDownFresh(Keys.G))
                    view_debug = !view_debug;

                if (Input.KeyDownFresh(Keys.R))
                    ResetGame();

                if (Input.KeyDownFresh(Keys.F))
                    fixed_framerate = !fixed_framerate;
            }
        }

        //Render
        {
            //Prep
            {
                graphics.SmoothingMode = SmoothingMode.HighQuality;
                graphics.Clear(Color.Black);
            }
            

            //Draw Scene
            {
                //get camera matrix
                Transform inverted_camera = Transform.Default();
                inverted_camera.position = -camera.position;
                inverted_camera.rotation = -camera.rotation;
                Matrix4x4 world_to_camera = GetMatrix(inverted_camera);
                Vector3[] positions = new Vector3[transforms.Length];

                //Draw Transforms
                {
                    for (int i = 1; i < transforms.Length; i++)
                    {
                        Matrix4x4 local_to_world = WorldSpaceMatrix(transforms[i], transforms);
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

                        positions[i] = position;
                    }

                    for (int i = 1; i < positions.Length; i++)
                    {
                        var position = positions[i];
                        var parent_position = position;

                        if (transforms[i].parent != 0 && transforms[i].parent != -1)
                            parent_position = positions[transforms[i].parent];

                        float d = camera.position.z - position.z;
                        float width = 300 / (d);
                        float half_width = width / 2;

                        Pen player_pen = new Pen(player_colors[i / GetSkeleton().Length]);
                        graphics.DrawLine(player_pen, position.x, position.y, parent_position.x, parent_position.y);
                        graphics.DrawEllipse(player_pen, position.x - half_width, position.y - half_width, width, width);
                    }

                    //Draw Hitboxes - TODO
                    {
                        for (int i = 0; i < attackboxes.Length; i++)
                        {
                            if (attackboxes[i].active)
                            {
                                Transform t = transforms[attackboxes[i].transform_index];
                                Matrix4x4 m = WorldSpaceMatrix(t, transforms);

                                Vector3 center = positions[attackboxes[i].transform_index];

                                float width = attackboxes[i].radius * 2 * PIXELS_PER_UNIT;
                                float half = width / 2f;
                                Color color = Color.Red;
                                graphics.FillEllipse(new SolidBrush(color), center.x - 4, center.y - 4, 8, 8);
                                graphics.FillEllipse(new SolidBrush(Color.FromArgb(30, color)), center.x - half, center.y - half, width, width);
                                graphics.DrawEllipse(new Pen(Color.FromArgb(color.R / 2, color.G / 2, color.B / 2), 2f), center.x - half, center.y - half, width, width);
                            }
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
                    }
                }
                

            }
        }
    }

    Transform[] skeleton;
    Transform[] GetSkeleton()
    {
        if (skeleton == null)
            skeleton = LoadHierarchy("Assets/avatar");
        return skeleton;
    }

    void ResetGame()
    {
        game_over = false;
        time_remaining = initial_time;
        List<Transform> list_entities = new List<Transform>();
        Transform[] skeleton = GetSkeleton();

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
            entity.scale = Vector3.One;
            entity.rotation.y = 1 / 4f * Tau;

            players[i].health = max_health;
            players[i].defeated = false;
            players[i].entity_ID = i * skeleton.Length;
            players[i].stock = 5;
            players[i].y_velocity = 0;
            list_entities[player_root_index] = entity;
        }
        this.transforms = list_entities.ToArray();

        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            Animator new_animator = new Animator();
            new_animator.current_animation = AvatarDemo.idle_animation;
            new_animator.current_frame = 1;
            animators[i] = new_animator;
        }

        camera.position = new Vector3(0, 0, -20);
        camera.scale = Vector3.One;
    }
}
