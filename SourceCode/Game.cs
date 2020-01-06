using Engine;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

using static DrawingLibrary;
using static Engine.Global;
using static Game;

class Game
{
    //Resolution
    public static int PIXELS_PER_UNIT = 64;
    public static int WIDTH = 1024;
    public static int HEIGHT = 576;

    //GUI
    public static System.Windows.Forms.Form window = new System.Windows.Forms.Form();
    public static BufferedGraphics buffered_graphics;
    public static Graphics graphics;

    //Timing
    public const float TIME_RECALCULATION_INTERVAL = 1;
    public const float TARGET_FRAMERATE = 60;
    public const float STANDARD_TIMESTEP = 1 / TARGET_FRAMERATE;
    public static Stopwatch stopwatch = new Stopwatch();
    public static float previous_time;
    public static float delta_time;
    public static float time_since_last_frame;
    public static float time_scale = 1f;
    public static float frames_per_second;
    public static float time_since_timing_recalculated;
    public static bool fixed_framerate = false;
    public static int frames_since_last_second;

    public static GameStates current_game_state;

    SplashScreen splash_screen = new SplashScreen();
    SkinnedMeshDemo skinned_demo = new SkinnedMeshDemo();
    GameplayState play_state = new GameplayState();
    MeshDemo mesh_demo = new MeshDemo();

    public enum GameStates
    {
        Splash,
        SkinnedMesh,
        Mesh,
        Gameplay
    }

    int state_count = 4;
    public static int game_state_index = 0;

    static void Main()
    {
        try
        {
            new Game();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            Console.ReadLine();
        }
    }

    Game()
    {
        //Setup Window
        {
            window.ClientSize = new Size(WIDTH, HEIGHT);
            window.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            window.MaximizeBox = false;
            window.Text = "Platfighter Z";
            window.Icon = new Icon(Global.GetAssetStream("icon.ico"));
            //Cursor.Hide();
        }

        //Initialize Graphics
        {
            DrawingLibrary.InitGraphics();
        }
        
        Input.InitKeyboard(Input.keys_down, Input.keys_stale, Input.keyboard_state);

        //Start Game Loop
        {
            System.Windows.Forms.Application.Idle += GameLoop;
            stopwatch.Start();
            System.Windows.Forms.Application.Run(window);
        }
    }


    void GameLoop(object sender, EventArgs e)
    {
        while (WindowIsIdle())
        {
            if (!fixed_framerate || time_since_last_frame > STANDARD_TIMESTEP)
            {
                //Tick
                {
                    //Update Input Devices
                    {
                        Input.PollKeyboard();
                    }

                    //Cycle Through GameStates
                    {
                        if (Input.KeyDownFresh(Engine.Keys.Tab))
                        {
                            game_state_index = (game_state_index + 1) % state_count;
                        }

                        else if (Input.KeyDownFresh(Engine.Keys.Z))
                        {
                            game_state_index--;
                            if (game_state_index < 0)
                                game_state_index += state_count;
                        }

                        current_game_state = (GameStates)game_state_index;
                    }

                    frames_since_last_second++;

                   switch(current_game_state)
                   {
                        case GameStates.Splash:
                            splash_screen.Update();
                            break;
                        case GameStates.SkinnedMesh:
                            skinned_demo.SkinnedMeshDemo_Update(); 
                            break;
                        case GameStates.Gameplay:
                            play_state.Update(); 
                            break;
                        case GameStates.Mesh:
                            mesh_demo.Update();   
                            break;                     
                   }

                    buffered_graphics.Render();
                    
                    time_since_last_frame = 0;
                }
            }

            //Update Timing
            {
                float elapsed = (float)(stopwatch.Elapsed.TotalSeconds - previous_time);
                time_since_last_frame += elapsed;
                time_since_timing_recalculated += elapsed;

                delta_time = (fixed_framerate) ? STANDARD_TIMESTEP : (time_since_last_frame * time_scale);

                if (time_since_timing_recalculated >= TIME_RECALCULATION_INTERVAL)
                {
                    frames_per_second = frames_since_last_second / time_since_timing_recalculated;
                    time_since_timing_recalculated = frames_since_last_second = 0;
                }
                previous_time = (float)stopwatch.Elapsed.TotalSeconds;
            }
        }
    }

    bool WindowIsIdle()
    {
#if Windows
        return PeekMessage(out NativeMessage result, IntPtr.Zero, 0, 0, 0) == 0;
#else
        return false;
#endif
    }

#if Windows
    //Imports a native Win32 function for checking the windows message queue
    [DllImport("User32.dll")]
    static extern int PeekMessage(out NativeMessage message, IntPtr handle, uint filterMin, uint filterMax, uint remove);

    struct NativeMessage
    {
        IntPtr Handle;
        uint Message;
        IntPtr WParameter;
        IntPtr LParameter;
        uint Time;
        Point Location;
    }
#endif
}


class MeshDemo : IGameState
{
    static Mesh mesh = LoadMesh("teapot.obj");
    static Transform camera = new Transform() { position = Vector3.Forward * -30, scale = Vector3.One };
    static Transform cube_transform = new Transform() { position = Vector3.Forward * 10f, scale = Vector3.One };
    static float field_of_view = Tau / 4;
    static Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);

    
    public void Update()
    {
        Temp(mesh);
        OutputRender();
    }

    static unsafe void Temp(Mesh mesh)
    {
        C_Mesh c_mesh = new C_Mesh();
        fixed (Vector3* vec_p = mesh.vertices)
        fixed (int* ind_p = mesh.indices)
        {
            c_mesh.vertices = vec_p;
            c_mesh.indices = ind_p;
            c_mesh.indices_length = mesh.indices.Length;
            c_mesh.vertices_length = mesh.vertices.Length;
        }
        cube_transform = RunMeshDemo(c_mesh, cube_transform,camera, delta_time);
        DrawString("FPS: " + frames_per_second, 16, 16);
    }
    
    [DllImport("SGL.dll")]
    static extern Transform RunMeshDemo(C_Mesh mesh, Transform cube_transform, Transform camera, float delta_time);

}

class SkinnedMeshDemo
{
    Mesh mesh;
    uint[] body_poly_colors;

    Transform[] skeleton;
    Matrix4x4[] bind_matrices;
    Vector4[] weights;
    Weight_Index[] weight_indices;
    Dictionary<int, Vector3>[] morphs = new Dictionary<int, Vector3>[5];
    float[] morph_weights = new float[5];
    Vector3[] transformed_vertices;
    Transform camera = new Transform() { position = Vector3.Forward * -50, scale = Vector3.One };

    bool has_a_face = true;
    bool animate_face = false;
    int facial_index_offset = 266;
    bool fill_toggle;

    float frame;
    float animation_length = 32;
    float rotation_y = Tau / 2;
    bool animation_play = false;
    bool rotation_play = false;
    bool view_debug;
    bool view_fps;
    float facial_time = 0;

    public SkinnedMeshDemo()
    {
        BuildGuy();
    }

    void BuildGuy()
    {
        mesh = LoadMesh("skin_translated.obj");
        skeleton = LoadHierarchy("avatar");


        if (has_a_face)
        {
            //load face
            Mesh face = LoadMesh("face.obj");
            Mesh smile = LoadMesh("smile.obj");
            Mesh angry_eyes = LoadMesh("angry_eyes.obj");

            //adjust head vertices
            {
                mesh.vertices[08].z -= .3f;
                mesh.vertices[01].z -= .2f;
                mesh.vertices[21].z -= .2f;

                mesh.vertices[07].z -= .3f;
                mesh.vertices[22].z -= .3f;
                mesh.vertices[14].z -= .3f;
                mesh.vertices[19].z -= .3f;
                mesh.vertices[29].z -= .3f;
                mesh.vertices[32].z -= .3f;
            }

            //Attach face
            mesh = AppendMesh(mesh, face);

            //build facial morph targets
            {
                morphs[0] = new Dictionary<int, Vector3>();
                for (int i = 0; i < smile.vertices.Length; i++)
                {
                    if (smile.vertices[i] - face.vertices[i] != Vector3.Zero)
                    {
                        morphs[0].Add(i, smile.vertices[i]);
                    }
                }

                morphs[1] = new Dictionary<int, Vector3>();
                for (int i = 0; i < angry_eyes.vertices.Length; i++)
                {
                    if (angry_eyes.vertices[i] - face.vertices[i] != Vector3.Zero)
                    {
                        morphs[1].Add(i, angry_eyes.vertices[i]);
                    }
                }
            }
        }

        //TODO replace with files to load
        body_poly_colors = LoadPolygonColors("skin_poly_colors");
        SetWeights();

        //build bind matrices
        {
            bind_matrices = new Matrix4x4[skeleton.Length];
            Transform[] bind_transforms = new Transform[skeleton.Length];

            for (int i = 0; i < bind_matrices.Length; i++)
            {
                bind_transforms[i] = InvertTransform(skeleton[i]);
                bind_matrices[i] = WorldSpaceMatrix(i, bind_transforms);
            }
        }

        transformed_vertices = new Vector3[mesh.vertices.Length];
        skeleton[0].position.y = -1;
    }



    void SetWeights()
    {
        weights = new Vector4[mesh.vertices.Length];
        weight_indices = new Weight_Index[mesh.vertices.Length];

        for (int i = 0; i < mesh.vertices.Length; i++)
            weights[i] = new Vector4(1, 0, 0, 0);

        Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(GetAssetPathPrefix() + "weight_indices");
        using (BinaryReader reader = new BinaryReader(stream))
        {
            List<Weight_Index> weight_index_list = new List<Weight_Index>();
            while (reader.BaseStream.Position != reader.BaseStream.Length)
            {
                Weight_Index w = new Weight_Index();
                w.bone1 = reader.ReadInt32();
                w.bone2 = reader.ReadInt32();
                w.bone3 = reader.ReadInt32();
                w.bone4 = reader.ReadInt32();
                weight_index_list.Add(w);
            }

           weight_indices = weight_index_list.ToArray();
        }
    }


    public unsafe void SkinnedMeshDemo_Update()
    {
        //Input
        {
            float delta = 5 * delta_time;
            if (Input.KeyDownFresh(Keys.Y))
                view_fps = !view_fps;

            if (Input.KeyDownFresh(Keys.G))
                view_debug = !view_debug;
            if (Input.KeyDown(Keys.W))
                camera.position.y -= delta;
            if (Input.KeyDown(Keys.S))
                camera.position.y += delta;
            if (Input.KeyDown(Keys.A))
                camera.position.x += delta;
            if (Input.KeyDown(Keys.D))
                camera.position.x -= delta;

            if (Input.KeyDown(Keys.Up))
                camera.position.z += delta * 10;
            else if (Input.KeyDown(Keys.Down))
                camera.position.z -= delta * 10;

            if (Input.KeyDownFresh(Keys.T))
            {
                animation_play = !animation_play;
            }

            if (Input.KeyDownFresh(Keys.Q))
            {
                animate_face = !animate_face;
            }

            if (Input.KeyDownFresh(Keys.F))
            {
                has_a_face = !has_a_face;
                BuildGuy();
            }

            if (Input.KeyDownFresh(Keys.R))
            {
                rotation_play = !rotation_play;
            }

            if (Input.KeyDownFresh(Keys.F4))
                DrawingLibrary.ToggleFullScreen();
            if(Input.KeyDownFresh(Keys.Space))
                fill_toggle = !fill_toggle;
        }

        //Animate
        {
            if (rotation_play)
            {
                rotation_y += delta_time;
                skeleton[0].rotation.y = rotation_y;
            }

            if (animation_play)
            {
                //Animate Skeleton
                {
                    foreach (AnimationCurve curve in DefinedAnimations.walk_animation.curves)
                    {
                        KeyFrame[] keyframes = curve.keyframes;
                        int transform_index = curve.transform_index;

                        fixed (Transform* p = &skeleton[transform_index])
                        {
                            float* f = &(*p).position.x + curve.property_tag;

                            AnimateProperty(keyframes, frame, f);
                        }
                    }
                }
            }

            Matrix4x4[] skeleton_matrices = new Matrix4x4[skeleton.Length];

            //Get Skeleton Matrices
            {
                for (int i = 0; i < skeleton_matrices.Length; i++)
                {
                    skeleton_matrices[i] = WorldSpaceMatrix(i, skeleton);
                }
            }

            //Apply Mesh Skinning
            {
                for (int i = 0; i < mesh.vertices.Length; i++)
                {
                    Vector3 v_a = bind_matrices[weight_indices[i].bone1] * skeleton_matrices[weight_indices[i].bone1] * mesh.vertices[i];
                    Vector3 v_b = bind_matrices[weight_indices[i].bone2] * skeleton_matrices[weight_indices[i].bone2] * mesh.vertices[i];
                    Vector3 v_c = bind_matrices[weight_indices[i].bone3] * skeleton_matrices[weight_indices[i].bone3] * mesh.vertices[i];
                    Vector3 v_d = bind_matrices[weight_indices[i].bone4] * skeleton_matrices[weight_indices[i].bone4] * mesh.vertices[i];

                    transformed_vertices[i] = (v_a * weights[i].x) + (v_b * weights[i].y) + (v_c * weights[i].z) + (v_d * weights[i].w);
                }
            }

            //Apply Facial Morph Targets
            {
                if (has_a_face && animate_face)
                {
                    Vector3[] deltas = new Vector3[259];
                    for (int morph_index = 0; morph_index < morphs.Length; morph_index++)
                    {
                        if (morphs[morph_index] != null)
                        {
                            var current_morph = morphs[morph_index];

                            foreach (var entry in current_morph)
                            {
                                int key = entry.Key;
                                Vector3 point = entry.Value;
                                int vertex_index = key + facial_index_offset;
                                Weight_Index weight_index = weight_indices[vertex_index];
                                Vector4 weight = weights[key];

                                Vector3 v_a = bind_matrices[weight_index.bone1] * skeleton_matrices[weight_index.bone1] * point;
                                Vector3 v_b = bind_matrices[weight_index.bone2] * skeleton_matrices[weight_index.bone2] * point;
                                Vector3 v_c = bind_matrices[weight_index.bone3] * skeleton_matrices[weight_index.bone3] * point;
                                Vector3 v_d = bind_matrices[weight_index.bone4] * skeleton_matrices[weight_index.bone4] * point;

                                Vector3 skinned_morph = (v_a * weight.x) + (v_b * weight.y) + (v_c * weight.z) + (v_d * weight.w);

                                deltas[key] += (skinned_morph - transformed_vertices[vertex_index]) * morph_weights[morph_index];
                            }
                        }
                    }

                    for (int i = 0; i < deltas.Length; i++)
                    {
                        int vertex_index = i + facial_index_offset;
                        transformed_vertices[vertex_index] += deltas[i];
                    }
                }

                morph_weights[0] = ((float)Math.Cos(facial_time * 2) + 1) / 2;
                morph_weights[1] = ((float)Math.Sin(facial_time * 2) + 1) / 2;

                facial_time += delta_time;
            }

            //Advance Animation Time
            {
                frame += TARGET_FRAMERATE * delta_time;
                frame %= animation_length;
            }
        }

        C_Mesh c_mesh = new C_Mesh();
        fixed (Vector3* vec_p = transformed_vertices)
        fixed (int* ind_p = mesh.indices)
        {
            c_mesh.vertices = vec_p;
            c_mesh.indices = ind_p;
            c_mesh.indices_length = mesh.indices.Length;
            c_mesh.vertices_length = transformed_vertices.Length;
        }

        Render(c_mesh, body_poly_colors, camera, (fill_toggle)?1:0);
        
        if (view_fps)
            DrawString($"FPS: {frames_per_second:F3}", 32, 32);
        
        OutputRender();
    }

    [DllImport("SGL.dll")]
    static extern unsafe void Render(C_Mesh mesh, uint[] body_poly_colors, Transform camera, int fill_toggle);
}

class GameplayState : IGameState
{
    bool view_debug = false;

    //Game World
    Transform camera = new Transform();
    float field_of_view = 3 / 8f * Tau;
    Transform[] transforms;
    public static readonly Player[] players = new Player[PLAYER_COUNT];
    readonly Animator[] animators = new Animator[PLAYER_COUNT];
    public static readonly uint[] player_colors = new uint[] { red, 0xFF008000, blue, purple };
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

                                        AnimateProperty(keyframes, frame, f);
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

                                        Vector3 v = Transform_v3(a, Vector3.Zero);
                                        Vector3 w = Transform_v3(b, Vector3.Zero);

                                        var dist = Vector3.Distance(v, w);
                                        bool intersects = (dist <= (players[other_player].defendboxes[your_defend].radius + players[player_index].attackboxes[my_attack].radius));

                                        if (intersects)
                                        {
                                            players[other_player].current_health -= 10 * delta_time;
                                            if (players[other_player].current_health <= 0)
                                            {
                                                players[other_player].stock--;
                                                if (players[other_player].stock > 0)
                                                    players[other_player].current_health = max_health;
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
            FillVerticalGradient(cyan, 0xFF_00_44_AA);

            //Draw Scene
            {
                //get camera matrix
                Matrix4x4 world_to_camera = GetMatrix(InvertTransform(camera));


                //Draw Blocks
                {
                    for (int i = 0; i < blocks.Length; i++)
                    {
                        Matrix4x4 local_to_world = WorldSpaceMatrix(i, blocks);
                        Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);
                        Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

                        Vector4 position = new Vector4(-.5f, .5f, 0, 1);
                        position = Transform_Vector4(local_to_clip, position);

                        if (position.w != 0)
                            position /= position.w;

                        //place origin at center of screen
                        position.x++;
                        position.y++;

                        //scale space to fill screen
                        position.x *= WIDTH / 2;
                        position.y *= HEIGHT / 2;

                        Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
                        position2 = Transform_Vector4(local_to_clip, position2);

                        if (position2.w != 0)
                            position2 /= position2.w;

                        //place origin at center of screen
                        position2.x++;
                        position2.y++;

                        //scale space to fill screen
                        position2.x *= WIDTH / 2;
                        position2.y *= HEIGHT / 2;

                        float width = position2.x - position.x;
                        float height = position2.y - position.y;
                        FillRectangle(brown, position.x, position.y, width, height);
                    }
                }

                Vector3[] transformed_positions = new Vector3[transforms.Length];

                //Draw Transforms
                {
                    for (int i = 0; i < transforms.Length; i++)
                    {
                        Matrix4x4 local_to_world = WorldSpaceMatrix(i, transforms);
                        Matrix4x4 local_to_camera = local_to_world * world_to_camera;

                        Vector3 position = Transform_v3(local_to_camera, Vector3.Zero);

                        Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);

                        var v4 = new Vector4(position.x, position.y, position.z, 1);
                        v4 = Transform_Vector4(camera_to_clip, v4);

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

                        DrawLine(player_colors[i / GetSkeleton().Length], position.x, position.y, parent_position.x, parent_position.y);
                        Draw_Circle(player_colors[i / GetSkeleton().Length], position.x, position.y, -half_width, 1);
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
                                    DrawHitbox(center, red, width);
                                }
                            }

                            for (int i = 0; i < players[player_index].defendboxes.Length; i++)
                            {

                                if (players[player_index].defendboxes[i].active)
                                {
                                    Vector3 center = transformed_positions[players[player_index].defendboxes[i].transform_index];
                                    float d = camera.position.z - center.z;
                                    float width = 30 * (players[player_index].defendboxes[i].radius * 2 * PIXELS_PER_UNIT) / (d);
                                    DrawHitbox(center, blue, -width);
                                }
                            }
                        }
                    }

                    //Draw Colliders
                    {
                        for (int i = 0; i < blocks.Length; i++)
                        {
                            Matrix4x4 local_to_world = WorldSpaceMatrix(i, blocks);
                            Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);
                            Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

                            Vector4 position = new Vector4(-.5f, .5f, 0, 1);
                            position = Transform_Vector4(local_to_clip, position);

                            if (position.w != 0)
                                position /= position.w;

                            //place origin at center of screen
                            position.x++;
                            position.y++;

                            //scale space to fill screen
                            position.x *= WIDTH / 2;
                            position.y *= HEIGHT / 2;

                            Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
                            position2 = Transform_Vector4(local_to_clip, position2);

                            if (position2.w != 0)
                                position2 /= position2.w;

                            //place origin at center of screen
                            position2.x++;
                            position2.y++;

                            //scale space to fill screen
                            position2.x *= WIDTH / 2;
                            position2.y *= HEIGHT / 2;

                            DrawRectangle(blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
                        }

                        for (int i = 0; i < players.Length; i++)
                        {
                            Matrix4x4 local_to_world = WorldSpaceMatrix(players[i].entity_ID, transforms);
                            Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);
                            Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

                            Vector4 position = new Vector4(-.5f, .5f, 0, 1);
                            position = Transform_Vector4(local_to_clip, position);

                            if (position.w != 0)
                                position /= position.w;

                            //place origin at center of screen
                            position.x++;
                            position.y++;

                            //scale space to fill screen
                            position.x *= WIDTH / 2;
                            position.y *= HEIGHT / 2;

                            Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
                            position2 = Transform_Vector4(local_to_clip, position2);

                            if (position2.w != 0)
                                position2 /= position2.w;

                            //place origin at center of screen
                            position2.x++;
                            position2.y++;

                            //scale space to fill screen
                            position2.x *= WIDTH / 2;
                            position2.y *= HEIGHT / 2;

                            DrawRectangle(blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
                        }
                    }
                }
            }

            //Draw Heads-Up Display (HUD)
            {
                var available_space = WIDTH / PLAYER_COUNT;
                int indent_x = 30;
                int indent_y = 10;
                int max_width = available_space - indent_x * 2;
                int health_height = 15;
                int padding = 4;
                int half_padding = padding / 2;
                for (int player = 0; player < PLAYER_COUNT; player++)
                {
                    //Draw HealthBar
                    {
                        float portion = players[player].current_health / max_health;
                        int current_width = (int)(portion * max_width);
                        int x_pos = indent_x + available_space * player;
                        int padded_height = health_height - padding;
                        int padded_x_pos = x_pos + half_padding;
                        int padded_y_pos = indent_y + half_padding;

                        FillRectangle(black, x_pos, indent_y, max_width, health_height);
                        FillRectangle(red, padded_x_pos, padded_y_pos, max_width - padding, padded_height);
                        FillRectangle(green, padded_x_pos, padded_y_pos, current_width - padding, padded_height);
                    }

                    //Draw Stocks
                    {
                        for (int stock = 0; stock < players[player].stock; stock++)
                        {
                            FillCircle(player_colors[player], available_space * player + indent_x + 10 + (stock * (20+5)), 40, 10);
                            Draw_Circle(black, available_space * player + indent_x + 10 + (stock * (25)), 40, 10, 3f);
                        }
                    }
                }

                //Draw Timer
                {
                    int char_sprite_size = 8;
                    DrawString($"{time_remaining:F0}", WIDTH / 2 - char_sprite_size * (((int)time_remaining).ToString().Length - 1), char_sprite_size * 2);
                }

                if (game_over)
                {
                    //Draw Game End Message
                    {
                        int offset_x = WIDTH / 2, offset_y = HEIGHT / 2;

                        string message = (winner == 0) ? "TIE!" : ("PLAYER " + winner + " WINS!");
                        DrawString(message, offset_x - 5, offset_y - 5);
                        DrawString(message, offset_x, offset_y);
                    }
                }
            }

            if (view_debug)
            {
                //Display Game Stats
                {
                    DrawString($"FPS: {frames_per_second:F2}", PIXELS_PER_UNIT / 2, 50);
                    DrawString($"delta_time: {delta_time:F9}", PIXELS_PER_UNIT / 2, 65);
                }
            }

            Flatten();
            OutputRender();
        }
    }

    static void DrawHitbox(Vector3 center, uint color, float width)
    {
        float half = width / 2f;
        uint transparent_color = (color ^ black) | 0x5E000000;
        Blend_Circle(transparent_color, center.x, center.y, half);
        Draw_Circle(Darker(color), center.x, center.y, half, 2);
        FillCircle(color, center.x, center.y, 4);
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
        skeleton = GetSkeleton();
        skeleton[1].position.y = 2;

        transforms = new Transform[skeleton.Length*PLAYER_COUNT];

        float distance_apart = 3.5f;
        float leftmost_position = -(PLAYER_COUNT - 1) * distance_apart / 2;

        for (int i = 0; i < PLAYER_COUNT; i++)
        {
            int player_root_index = i * skeleton.Length;


            for (int bone = 0; bone < skeleton.Length; bone++)
            {
                Transform joint = skeleton[bone];
                if(joint.parent > -1)
                    joint.parent += player_root_index;
                transforms[player_root_index + bone] = joint;
            }

            Transform entity = transforms[player_root_index];

            entity.position.x = leftmost_position + i * distance_apart;
            entity.rotation.y = 1 / 4f * Tau;

            players[i].current_health = max_health;
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

            transforms[player_root_index] = entity;
        }


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
