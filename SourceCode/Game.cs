using Engine;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

using static DrawingLibrary;
using static Engine.Global;
using static Game;
using static System.Math;

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
        SkinnedMesh,
        Splash,
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
            font_set = LoadFontSet("font_set");
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
                            SkinnedMeshDemo_Update(skinned_demo); 
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

public unsafe void SkinnedMeshDemo_Update(SkinnedMeshDemo skinned_demo)
{
    //Input
    {
        float delta = 5 * delta_time;
        if (Input.KeyDownFresh(Keys.Y))
            skinned_demo.view_fps = !skinned_demo.view_fps;

        if (Input.KeyDownFresh(Keys.G))
            skinned_demo.view_debug = !skinned_demo.view_debug;
        if (Input.KeyDown(Keys.W))
            skinned_demo.camera.position.y -= delta;
        if (Input.KeyDown(Keys.S))
            skinned_demo.camera.position.y += delta;
        if (Input.KeyDown(Keys.A))
            skinned_demo.camera.position.x += delta;
        if (Input.KeyDown(Keys.D))
            skinned_demo.camera.position.x -= delta;

        if (Input.KeyDown(Keys.Up))
            skinned_demo.camera.position.z += delta * 10;
        else if (Input.KeyDown(Keys.Down))
            skinned_demo.camera.position.z -= delta * 10;

        if (Input.KeyDownFresh(Keys.T))
        {
            skinned_demo.animation_play = !skinned_demo.animation_play;
        }

        if (Input.KeyDownFresh(Keys.Q))
        {
            skinned_demo.animate_face = !skinned_demo.animate_face;
        }

        if (Input.KeyDownFresh(Keys.F))
        {
            skinned_demo.has_a_face = !skinned_demo.has_a_face;
            skinned_demo.BuildGuy();
        }

        if (Input.KeyDownFresh(Keys.R))
        {
            skinned_demo.rotation_play = !skinned_demo.rotation_play;
        }

        if (Input.KeyDownFresh(Keys.F4))
            DrawingLibrary.ToggleFullScreen();
        if(Input.KeyDownFresh(Keys.Space))
            skinned_demo.fill_toggle = !skinned_demo.fill_toggle;
    }

    //Animate
    {
        if (skinned_demo.rotation_play)
        {
            skinned_demo.rotation_y += delta_time;
            skinned_demo.skeleton[0].rotation.y = skinned_demo.rotation_y;
        }

        if (skinned_demo.animation_play)
        {
            //Animate Skeleton
            {
                foreach (AnimationCurve curve in DefinedAnimations.walk_animation.curves)
                {
                    KeyFrame[] keyframes = curve.keyframes;
                    int transform_index = curve.transform_index;

                    fixed (Transform* p = &skinned_demo.skeleton[transform_index])
                    {
                        float* f = &(*p).position.x + curve.property_tag;

                        AnimateProperty(keyframes, skinned_demo.frame, f);
                    }
                }
            }
        }

        Matrix4x4[] skeleton_matrices = new Matrix4x4[skinned_demo.skeleton.Length];

        //Get Skeleton Matrices
        {
            for (int i = 0; i < skeleton_matrices.Length; i++)
            {
                skeleton_matrices[i] = WorldSpaceMatrix(i, skinned_demo.skeleton);
            }
        }

        //Apply Mesh Skinning
        {
            for (int i = 0; i < skinned_demo.mesh.vertices.Length; i++)
            {
                Vector3 v_a = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone1] * skeleton_matrices[skinned_demo.weight_indices[i].bone1] * skinned_demo.mesh.vertices[i];
                Vector3 v_b = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone2] * skeleton_matrices[skinned_demo.weight_indices[i].bone2] * skinned_demo.mesh.vertices[i];
                Vector3 v_c = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone3] * skeleton_matrices[skinned_demo.weight_indices[i].bone3] * skinned_demo.mesh.vertices[i];
                Vector3 v_d = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone4] * skeleton_matrices[skinned_demo.weight_indices[i].bone4] * skinned_demo.mesh.vertices[i];

                skinned_demo.transformed_vertices[i] = (v_a * skinned_demo.weights[i].x) + (v_b * skinned_demo.weights[i].y) + (v_c * skinned_demo.weights[i].z) + (v_d * skinned_demo.weights[i].w);
            }
        }

        //Apply Facial Morph Targets
        {
            if (skinned_demo.has_a_face && skinned_demo.animate_face)
            {
                Vector3[] deltas = new Vector3[259];
                for (int morph_index = 0; morph_index < skinned_demo.morphs.Length; morph_index++)
                {
                    if (skinned_demo.morphs[morph_index] != null)
                    {
                        var current_morph = skinned_demo.morphs[morph_index];

                        foreach (var entry in current_morph)
                        {
                            int key = entry.Key;
                            Vector3 point = entry.Value;
                            int vertex_index = key + skinned_demo.facial_index_offset;
                            Weight_Index weight_index = skinned_demo.weight_indices[vertex_index];
                            Vector4 weight = skinned_demo.weights[key];

                            Vector3 v_a = skinned_demo.bind_matrices[weight_index.bone1] * skeleton_matrices[weight_index.bone1] * point;
                            Vector3 v_b = skinned_demo.bind_matrices[weight_index.bone2] * skeleton_matrices[weight_index.bone2] * point;
                            Vector3 v_c = skinned_demo.bind_matrices[weight_index.bone3] * skeleton_matrices[weight_index.bone3] * point;
                            Vector3 v_d = skinned_demo.bind_matrices[weight_index.bone4] * skeleton_matrices[weight_index.bone4] * point;

                            Vector3 skinned_morph = (v_a * weight.x) + (v_b * weight.y) + (v_c * weight.z) + (v_d * weight.w);

                            deltas[key] += (skinned_morph - skinned_demo.transformed_vertices[vertex_index]) * skinned_demo.morph_weights[morph_index];
                        }
                    }
                }

                for (int i = 0; i < deltas.Length; i++)
                {
                    int vertex_index = i + skinned_demo.facial_index_offset;
                    skinned_demo.transformed_vertices[vertex_index] += deltas[i];
                }
            }

            skinned_demo.morph_weights[0] = ((float)Math.Cos(skinned_demo.facial_time * 2) + 1) / 2;
            skinned_demo.morph_weights[1] = ((float)Math.Sin(skinned_demo.facial_time * 2) + 1) / 2;

            skinned_demo.facial_time += delta_time;
        }

        //Advance Animation Time
        {
            skinned_demo.frame += TARGET_FRAMERATE * delta_time;
            skinned_demo.frame %= skinned_demo.animation_length;
        }
    }

    C_Mesh c_mesh = new C_Mesh();
    fixed (Vector3* vec_p = skinned_demo.transformed_vertices)
    fixed (int* ind_p = skinned_demo.mesh.indices)
    {
        c_mesh.vertices = vec_p;
        c_mesh.indices = ind_p;
        c_mesh.indices_length = skinned_demo.mesh.indices.Length;
        c_mesh.vertices_length = skinned_demo.transformed_vertices.Length;
    }

    Render(c_mesh, skinned_demo.body_poly_colors, skinned_demo.camera, (skinned_demo.fill_toggle) ? 1 : 0);
    
    if (skinned_demo.view_fps)
        DrawString($"FPS: {frames_per_second:F3}", 32, 32);
    OutputRender();
}

[DllImport("SGL.dll")]
static extern unsafe void Render(C_Mesh mesh, uint[] body_poly_colors, Transform camera, int fill_toggle);

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
    public Mesh mesh;
    public uint[] body_poly_colors;

    public Transform[] skeleton;
    public Matrix4x4[] bind_matrices;
    public Vector4[] weights;
    public Weight_Index[] weight_indices;
    public Dictionary<int, Vector3>[] morphs = new Dictionary<int, Vector3>[5];
    public float[] morph_weights = new float[5];
    public Vector3[] transformed_vertices;
    public Transform camera = new Transform() { position = Vector3.Forward * -50, scale = Vector3.One };

    public bool has_a_face = true;
    public bool animate_face = false;
    public int facial_index_offset = 266;
    public bool fill_toggle;

    public float frame;
    public float animation_length = 32;
    public float rotation_y = Tau / 2;
    public bool animation_play = false;
    public bool rotation_play = false;
    public bool view_debug;
    public bool view_fps;
    public float facial_time = 0;

    public SkinnedMeshDemo()
    {
        BuildGuy();
    }

    public void BuildGuy()
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



    public void SetWeights()
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

namespace Engine
{
    /// <summary>
    /// Contains engine-level functionality used throughout the game
    /// </summary>
    public unsafe struct C_Mesh
    {
        public Vector3* vertices;
        public int* indices;
        public int vertices_length;
        public int indices_length;
    }

    enum Keys
    {
        Tab = 9, 
        Space = 32,
        Left = 37, Up, Right, Down,
        Delete = 46, 
        A = 65,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, 
        F4 = 115, 
        NumPad0 = 96, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
    }

    public struct Weight_Index
    {
        public int bone1, bone2, bone3, bone4;

        public Weight_Index(int bone1, int bone2, int bone3, int bone4)
        {
            this.bone1 = bone1;
            this.bone2 = bone2;
            this.bone3 = bone3;
            this.bone4 = bone4;
        }
    }

    public struct Player
    {
        public int entity_ID;
        public int selected_character;
        public bool defeated;
        public int stock;
        public float current_health;
        public Hitbox[] attackboxes;
        public Hitbox[] defendboxes;
        public Vector2 velocity;
        public bool grounded;
    }


    public struct Fighter
    {
        public string name;
        public Bitmap icon;
    }


    public struct Animator
    {
        public float current_frame;
        public Animation current_animation;
    }


    public struct Animation
    {
        public bool looped;
        public List<AnimationCurve> curves;
        public int[][] defendbox_keys;
        public bool[][] defendbox_values;
        public int[][] attackbox_keys;
        public bool[][] attackbox_values;
    }


    public struct AnimationCurve
    {
        public int transform_index;
        public byte property_tag;
        public KeyFrame[] keyframes;
    }


    public struct KeyFrame
    {
        public float frame;
        public float value;
        public float left_handle_x;
        public float left_handle_y;
        public float right_handle_x;
        public float right_handle_y;
    }


    public struct Hitbox
    {
        public int transform_index;
        public float radius;
        public bool active;
    }


    public struct Transform
    {
        public int parent;
        public Vector3 position;
        public Vector3 rotation;
        public Vector3 scale;

        public static Transform Default()
        {
            return new Transform()
            {
                parent = -1,
                position = Vector3.Zero,
                rotation = Vector3.Zero,
                scale = Vector3.One
            };
        }


    }


    public struct Vector2
    {
        public float x, y;

        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public static readonly Vector2 Right = new Vector2 { x = 1, y = 0 };
        public static readonly Vector2 Left = new Vector2 { x = -1, y = 0 };
        public static readonly Vector2 Up = new Vector2 { x = 0, y = 1 };
        public static readonly Vector2 Down = new Vector2 { x = 0, y = -1 };
        public static readonly Vector2 Zero = new Vector2 { x = 0, y = 0 };
        public static readonly Vector2 One = new Vector2 { x = 1, y = 1 };

        public static Vector2 operator +(Vector2 a, Vector2 b) { return new Vector2 { x = a.x + b.x, y = a.y + b.y }; }
        public static Vector2 operator -(Vector2 a, Vector2 b) { return new Vector2 { x = a.x - b.x, y = a.y - b.y }; }
        public static Vector2 operator *(Vector2 v, float s) { return new Vector2 { x = v.x * s, y = v.y * s }; }
        public static Vector2 operator /(Vector2 v, float s) { return new Vector2 { x = v.x / s, y = v.y / s }; }

        public static float Distance(Vector2 a, Vector2 b) { return (a - b).Magnitude(); }
        public float Magnitude() { return (float)Sqrt(x * x + y * y); }
    }


    public struct Vector3
    {
        public float x, y, z;

        public Vector3(float x, float y, float z) { this.x = x; this.y = y; this.z = z; }

        public static readonly Vector3 Right = new Vector3 { x = 1, y = 0, z = 0 };
        public static readonly Vector3 Left = new Vector3 { x = -1, y = 0, z = 0 };
        public static readonly Vector3 Up = new Vector3 { x = 0, y = 1, z = 0 };
        public static readonly Vector3 Down = new Vector3 { x = 0, y = -1, z = 0 };
        public static readonly Vector3 Forward = new Vector3 { x = 0, y = 0, z = 1 };
        public static readonly Vector3 Backward = new Vector3 { x = 0, y = 0, z = -1 };
        public static readonly Vector3 Zero = new Vector3 { x = 0, y = 0, z = 0 };
        public static readonly Vector3 One = new Vector3 { x = 1, y = 1, z = 1 };

        public static Vector3 operator -(Vector3 v) { return new Vector3 { x = -v.x, y = -v.y, z = -v.z }; }
        public static Vector3 operator +(Vector3 a, Vector3 b) { return new Vector3 { x = a.x + b.x, y = a.y + b.y, z = a.z + b.z }; }
        public static Vector3 operator -(Vector3 a, Vector3 b) { return new Vector3 { x = a.x - b.x, y = a.y - b.y, z = a.z - b.z }; }
        public static Vector3 operator *(Vector3 v, float s) { return new Vector3 { x = v.x * s, y = v.y * s, z = v.z * s }; }
        public static Vector3 operator /(Vector3 v, float s) { return new Vector3 { x = v.x / s, y = v.y / s, z = v.z / s }; }
        public static bool operator ==(Vector3 a, Vector3 b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
        public static bool operator !=(Vector3 a, Vector3 b) { return a.x != b.x || a.y != b.y || a.z != b.z; }
        public override bool Equals(object a)
        {
            return this == (Vector3)a;
        }

        public override int GetHashCode () { return -1; /*TODO implement?*/ }

        public Vector3 Normalized() { return this / Magnitude(); }

        public float Magnitude() { return (float)Sqrt(x * x + y * y + z * z); }

        public static float Distance(Vector3 a, Vector3 b) { return (a - b).Magnitude(); }

        public static float DotProduct(Vector3 a, Vector3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

        public static Vector3 CrossProduct(Vector3 a, Vector3 b)
        {
            return new Vector3()
            {
                x = a.y * b.z - a.z * b.y,
                y = a.z * b.x - a.x * b.z,
                z = a.x * b.y - a.y * b.x,
            };
        }


        public override string ToString()
        {
            return $"[{x:F2}, {y:F2}, {z:F2}]";
        }
    }


    public struct Vector4
    {
        public float x, y, z, w;

        public Vector4(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public static Vector4 operator /(Vector4 v, float s) { return new Vector4(v.x / s, v.y / s, v.z / s, v.w / s); }

        public override string ToString()
        {
            return $"[{x:F2}, {y:F2}, {z:F2}, {w:F2}]";
        }
    }


    public struct Matrix4x4
    {
        public float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

        public Matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
        {
            this.m11 = m11;
            this.m12 = m12;
            this.m13 = m13;
            this.m14 = m14;
            this.m21 = m21;
            this.m22 = m22;
            this.m23 = m23;
            this.m24 = m24;
            this.m31 = m31;
            this.m32 = m32;
            this.m33 = m33;
            this.m34 = m34;
            this.m41 = m41;
            this.m42 = m42;
            this.m43 = m43;
            this.m44 = m44;
        }

        public static readonly Matrix4x4 identity = new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

        public static Vector3 operator *(Matrix4x4 m, Vector3 v) { return Global.Transform_v3(m, v); }

        public static Vector3 operator *(Vector3 v, Matrix4x4 m) { return Global.Transform_v3(m, v); }

        public static Matrix4x4 operator *(Matrix4x4 a, Matrix4x4 b)
        {
            return Global.Concatenate(a, b);
        }

        public override string ToString()
        {
            return $"{m11:F2}, {m12:F2}, {m13:F2}, {m14:F2}, \n{m21:F2}, {m22:F2}, {m23:F2}, {m24:F2}, \n{m31:F2}, {m32:F2}, {m33:F2}, {m34:F2}, \n{m41:F2}, {m42:F2}, {m43:F2}, {m44:F2}\n";
        }
    }


    public struct Mesh
    {
        public Vector3[] vertices;
        public int[] indices;
    }

    public struct Texture
    {
        public readonly int width, height;
        public readonly uint[] pixels;

        public Texture(int width, int height)
        {
            this.width = width;
            this.height = height;
            pixels = new uint[width * height];
        }
    }

    public struct CharSprite
    {
        public byte
            row1,
            row2,
            row3,
            row4,
            row5,
            row6,
            row7,
            row8;
    }

    interface IGameState
    {
        void Update();
    }

    public static class Global
    {
        public const float Tau = 6.28318530717958f;
        public const float Pi = Tau / 2;

        #region Linear Algebra

        [DllImport("SGL.dll")]
        public static extern Transform InvertTransform(Transform t);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 GetMatrix(Transform t);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 WorldSpaceMatrix(int index, Transform[] hierarchy);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Concatenate(Matrix4x4 a, Matrix4x4 b);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Transpose(Matrix4x4 m);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Translation(float x, float y, float z);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Scale(float x, float y, float z);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Rotation(float x, float y, float z);

        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Perspective(float near, float far, float field_of_view, float width, float height);

        [DllImport("SGL.dll")]
        public static extern Vector3 Transform_v3(Matrix4x4 m, Vector3 v);

        [DllImport("SGL.dll")]
        public static extern Vector4 Transform_Vector4(Matrix4x4 m, Vector4 v);

        #endregion

        #region Mesh Operations

        public static Mesh AppendMesh(Mesh a, Mesh b)
        {
            List<Vector3> vertices = new List<Vector3>(a.vertices);
            List<int> indices = new List<int>(a.indices);
            for (int i = 0; i < b.indices.Length; i++)
            {
                b.indices[i] += a.vertices.Length;
            }
            vertices.AddRange(b.vertices);
            indices.AddRange(b.indices);

            return new Mesh { vertices = vertices.ToArray(), indices = indices.ToArray() };
        }

        #endregion
        
        #region Animation
        //[DllImport("SGL.dll")]
        public static unsafe void AnimateProperty(KeyFrame[] curve, float frame, float* property)
        {
            for (int i = 0; i < curve.Length - 1; i++)
            {
                KeyFrame a = curve[i];
                KeyFrame b = curve[i + 1];
                if (frame >= a.frame && frame <= b.frame)
                {
                    *property = Sample(a, b, frame);
                    return;
                }
            }
        }

        [DllImport("SGL.dll")]
        public static extern float Sample(KeyFrame a, KeyFrame b, float frame);

        #endregion

        #region Collision Detection
        [DllImport("SGL.dll")]
        public static extern bool Intersect(Transform a, Transform b);
        #endregion

        #region FileIO

        public static Stream GetAssetStream(string path)
        {
            return Assembly.GetExecutingAssembly().GetManifestResourceStream(GetAssetPathPrefix() + path);
        }

        
        /* 
         * For some reason, when I build the application through visual studio, embedded resources have the folder name automatically prepended to the path, but not when I build the app from the command line.
         * This function acts as a workaround to have the correct path for each build until I can figure out what controls how the resource path is set in the build
        */
        public static string GetAssetPathPrefix()
        {
            #if vs_build
                return "PlatfighterZ.Assets.";
            #else
                return "";
            #endif
        }

        public static Mesh LoadMesh(string path)
        {
            Stream stream = GetAssetStream(path);

            using (StreamReader reader = new StreamReader(stream))
            {
                List<Vector3> vertexList = new List<Vector3>();
                List<int> indexList = new List<int>();

                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    var subs = line.Split(' ');

                    switch (subs[0])
                    {
                        case "v":
                            vertexList.Add(new Vector3 { x = float.Parse(subs[1]), y = float.Parse(subs[2]), z = float.Parse(subs[3]) });
                            break;
                        case "f":
                            indexList.Add(int.Parse(subs[1]) - 1);
                            indexList.Add(int.Parse(subs[2]) - 1);
                            indexList.Add(int.Parse(subs[3]) - 1);
                            break;
                    }
                }

                return new Mesh() { vertices = vertexList.ToArray(), indices = indexList.ToArray() };
            }
        }

        public static uint[] LoadPolygonColors(string path)
        {
            Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(GetAssetPathPrefix() + path);
            using (BinaryReader reader = new BinaryReader(stream))
            {
                List<uint> polygon_colors = new List<uint>();
                while (reader.BaseStream.Position != reader.BaseStream.Length)
                {
                    polygon_colors.Add(reader.ReadUInt32());
                }

                return polygon_colors.ToArray();
            }

        }
        
        public static void SaveKeyFrames(string path, KeyFrame[] curve)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(path, FileMode.Create)))
            {
                for (int i = 0; i < curve.Length; i++)
                {
                    writer.Write(curve[i].frame);
                    writer.Write(curve[i].value);
                    writer.Write(curve[i].left_handle_x);
                    writer.Write(curve[i].left_handle_y);
                    writer.Write(curve[i].right_handle_x);
                    writer.Write(curve[i].right_handle_y);
                }
            }
        }

        public static KeyFrame[] LoadKeyFrames(string path)
        {
            Stream stream = GetAssetStream(path);
            using (BinaryReader reader = new BinaryReader(stream))
            {
                List<KeyFrame> curve = new List<KeyFrame>();
                while (reader.BaseStream.Position != reader.BaseStream.Length)
                {
                    var keyframe = new KeyFrame();
                    keyframe.frame = reader.ReadSingle();
                    keyframe.value = reader.ReadSingle();
                    keyframe.left_handle_x = reader.ReadSingle();
                    keyframe.left_handle_y = reader.ReadSingle();
                    keyframe.right_handle_x = reader.ReadSingle();
                    keyframe.right_handle_y = reader.ReadSingle();
                    curve.Add(keyframe);
                }
                return curve.ToArray();
            }
        }

        public static void SaveHierarchy(string path, Transform[] hierarchy)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(path, FileMode.Create)))
            {
                for (int i = 0; i < hierarchy.Length; i++)
                {
                    writer.Write(hierarchy[i].parent);
                    writer.Write(hierarchy[i].position.x);
                    writer.Write(hierarchy[i].position.y);
                    writer.Write(hierarchy[i].position.z);
                    writer.Write(hierarchy[i].rotation.x);
                    writer.Write(hierarchy[i].rotation.y);
                    writer.Write(hierarchy[i].rotation.z);
                    writer.Write(hierarchy[i].scale.x);
                    writer.Write(hierarchy[i].scale.y);
                    writer.Write(hierarchy[i].scale.z);
                }
            }
        }

        public static Transform[] LoadHierarchy(string path)
        {
            Stream stream = GetAssetStream(path);
            using (BinaryReader reader = new BinaryReader(stream))
            {
                List<Transform> hierarchy = new List<Transform>();
                while (reader.BaseStream.Position != reader.BaseStream.Length)
                {
                    Transform transform = new Transform();
                    transform.parent = reader.ReadInt32();
                    transform.position.x = reader.ReadSingle();
                    transform.position.y = reader.ReadSingle();
                    transform.position.z = reader.ReadSingle();
                    transform.rotation.x = reader.ReadSingle();
                    transform.rotation.y = reader.ReadSingle();
                    transform.rotation.z = reader.ReadSingle();
                    transform.scale.x = reader.ReadSingle();
                    transform.scale.y = reader.ReadSingle();
                    transform.scale.z = reader.ReadSingle();
                    hierarchy.Add(transform);
                }
                return hierarchy.ToArray();
            }
        }

        public static CharSprite[] LoadFontSet(string path)
        {
            Stream stream = GetAssetStream(path);
            using (BinaryReader reader = new BinaryReader(stream))
            {
                List<CharSprite> char_sprites = new List<CharSprite>();
                while (reader.BaseStream.Position != reader.BaseStream.Length)
                {
                    CharSprite sprite = new CharSprite();
                    sprite.row1 = reader.ReadByte();
                    sprite.row2 = reader.ReadByte();
                    sprite.row3 = reader.ReadByte();
                    sprite.row4 = reader.ReadByte();
                    sprite.row5 = reader.ReadByte();
                    sprite.row6 = reader.ReadByte();
                    sprite.row7 = reader.ReadByte();
                    sprite.row8 = reader.ReadByte();
                    char_sprites.Add(sprite);
                }
                return char_sprites.ToArray();
            }
        }
        
        public static void SaveFontSet(string path, CharSprite[] font_set)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(path, FileMode.Create)))
            {
                for (int i = 0; i < font_set.Length; i++)
                {
                    writer.Write(font_set[i].row1);
                    writer.Write(font_set[i].row2);
                    writer.Write(font_set[i].row3);
                    writer.Write(font_set[i].row4);
                    writer.Write(font_set[i].row5);
                    writer.Write(font_set[i].row6);
                    writer.Write(font_set[i].row7);
                    writer.Write(font_set[i].row8);
                }
            }
        }

        #endregion
    }




    public enum Buttons
    {
        LEFT,
        RIGHT,
        DOWN,
        JUMP,
        PUNCH
    }

    class Input
    {
        //Input
        public static byte[] keys_down = new byte[256];
        public static byte[] keys_stale = new byte[256]; //whether a key has been pressed for more than one consecutive frame
        public static byte[] keyboard_state = new byte[256];

        public static Keys[,] control_mappings = //each row represents a player's control scheme
        {
            {Keys.A,       Keys.D ,       Keys.S,        Keys.W,       Keys.Q},
            {Keys.J,       Keys.L,        Keys.K,        Keys.I,       Keys.U},
            {Keys.Left,    Keys.Right,    Keys.Down,     Keys.Up,      Keys.Delete},
            {Keys.NumPad4, Keys.NumPad6,  Keys.NumPad5,  Keys.NumPad8, Keys.NumPad7}
        };

        [DllImport("SGL.dll")]
        public static extern bool ButtonDown(int player, Buttons action);
        [DllImport("SGL.dll")]
        public static extern bool ButtonDownFresh(int player, Buttons action);
        [DllImport("SGL.dll")]
        public static extern bool KeyDownFresh(Keys key);
        [DllImport("SGL.dll")]
        public static extern bool KeyDown(Keys key);
        [DllImport("SGL.dll")]
        public static extern void PollKeyboard();
        [DllImport("SGL.dll")]        
        public static extern void InitKeyboard(byte[] keys_down, byte[] keys_stale, byte[] keyboard_state);
    }

}

static class DrawingLibrary
{
    public static bool maximized = false;

    public static uint[] pixels;
    public static GCHandle pixel_handle;
    public static Bitmap rendered_image;


    public const uint red = 0xFF_FF_00_00;
    public const uint green = 0xFF_00_FF_00;
    public const uint blue = 0xFF_00_00_FF;

    public const uint cyan = green | blue;
    public const uint magenta = red | blue;
    public const uint yellow = red | green;

    public const uint black = 0xFF_00_00_00;
    public const uint white = red | green | blue;

    public const uint brown = 0xFF_A5_2A_2A;
    public const uint purple = 0xFF_80_00_80;

    [DllImport("SGL.dll")]
    public static extern void InitMeshDemo(float field_of_view, int WIDTH, int HEIGHT, uint[] pixels); //TODO rename
    [DllImport("SGL.dll")]
    public static unsafe extern void FillVerticalGradient(uint color1, uint color2);
    [DllImport("SGL.dll")]
    public static extern uint Darker(uint color);
    [DllImport("SGL.dll")]
    public static extern void Flatten();
    [DllImport("SGL.dll")]
    public static extern void FillRectangle_Blend(uint color, int x, int y, int width, int height);
    [DllImport("SGL.dll")]
    public static extern void  DrawHorizontal_Blend(uint color, int y);
    [DllImport("SGL.dll")]
    public static extern void DrawVertical_Blend(uint color, int x);
    [DllImport("SGL.dll")]
    public static extern void DrawLine(uint color, float x1, float y1, float x2, float y2);
    [DllImport("SGL.dll")]
    public static extern uint BlendColor(uint s, uint d);
    [DllImport("SGL.dll")]
    public static extern void DrawHorizontal(uint color, int y);
    [DllImport("SGL.dll")]
    public static extern void DrawVertical(uint color, int x);
    [DllImport("SGL.dll")]
    public static extern void DrawGrid_ScreenSpace(int unit_size);
    [DllImport("SGL.dll")]
    public static extern void DrawHorizontalSegment(uint color, int y, int x1, int x2);
    [DllImport("SGL.dll")]
    public static extern void DrawVerticalSegment(uint color, int x, int y1, int y2);
    [DllImport("SGL.dll")]
    public static extern void DrawRectangle(uint color, float x, float y, float width, float height);
    [DllImport("SGL.dll")]
    public static extern void FillRectangle(uint color, float x, float y, float width, float height);
    [DllImport("SGL.dll")]
    public static extern void Draw_Circle(uint color, float x, float y, float radius, float stroke);
    [DllImport("SGL.dll")]
    public static extern void FillCircle(uint color, float x, float y, float radius);
    [DllImport("SGL.dll")]
    public static extern void Blend_Circle(uint color, float x, float y, float radius);    
    [DllImport("SGL.dll")]
    public static extern void FillTriangle(uint color, int x1, int y1, int x2, int y2, int x3, int y3);
    [DllImport("SGL.dll")]
    public static extern void PutPixel(uint color, int x, int y);
    [DllImport("SGL.dll")]
    public static extern void PutPixel_ByIndex(uint color, int i);

    public static void ToggleFullScreen()
    {
        maximized = !maximized;
        if (maximized)
            ToFullScreenView();
        else
            ToWindowedView();
    }
    
    public static void ToFullScreenView()
    {
        WIDTH = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Width;
        HEIGHT = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Height;
        window.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
        window.WindowState = System.Windows.Forms.FormWindowState.Maximized;
        InitGraphics();
    }

    public static void ToWindowedView()
    {
        WIDTH = 1024;
        HEIGHT = 576;
        window.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
        window.WindowState = System.Windows.Forms.FormWindowState.Normal;
        InitGraphics();
    }

    public static void InitGraphics()
    {
        window.ClientSize = new Size(WIDTH, HEIGHT);
        pixels = new uint[WIDTH * HEIGHT];
        if (pixel_handle.IsAllocated)
            pixel_handle.Free();
        pixel_handle = GCHandle.Alloc(pixels, GCHandleType.Pinned);
        rendered_image = new Bitmap(WIDTH, HEIGHT, WIDTH * 4, PixelFormat.Format32bppPArgb, pixel_handle.AddrOfPinnedObject());
        buffered_graphics = BufferedGraphicsManager.Current.Allocate(window.CreateGraphics(), window.DisplayRectangle);
        graphics = buffered_graphics.Graphics;
        InitMeshDemo(Global.Tau / 4, WIDTH, HEIGHT, pixels);
    }

    public static void OutputRender()
    {
        graphics.DrawImage(rendered_image, 0, 0); //TODO find something faster than this! Perhaps you can access the contents of the GDI drawing surface directly?
    }

    #region Text

    static char[] char_dict = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ', '.', ':', ',', '_', '[', ']', '-', };
    public static CharSprite[] font_set = new CharSprite[44]; //TODO don't rely on this magic number, at least until you've verified it will stay the same

    public static void DrawString(string s, int x, int y)
    {
        s = s.ToLower();
        for (int i = 0; i < s.Length; i++)
        {
            for(int o = 0; o < char_dict.Length; o++)
            {
                if(s[i] == char_dict[o])
                    DrawCharacter(font_set[o], x + i * 9, y);
            }
        }
    }

    public static unsafe void DrawCharacter(CharSprite sprite, int x, int y)
    {
        byte* p = &sprite.row1;
        for (int row = 0; row < 8; row++, p++)
        {
            for (int col = 0; col < 8; col++)
            {
                bool pixel_active = ((*p << col) & 0b10000000) == 0b10000000;
                if (pixel_active)
                    PutPixel(white, col + x, row + y);
            }
        }
    }

    #endregion
}

static class DefinedAnimations
{
    public static List<AnimationCurve> idle_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 2 },
                    new KeyFrame {frame = 30, value = 1.93f },
                    new KeyFrame {frame = 60, value = 2 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 1, //core
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .3f },
                    new KeyFrame {frame = 60, value = .3f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 2, //chest
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .0f },
                    new KeyFrame {frame = 30, value = .3f },
                    new KeyFrame {frame = 60, value = .0f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/5f },
                    new KeyFrame {frame = 60, value = Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/6f },
                    new KeyFrame {frame = 30, value = Tau/8f },
                    new KeyFrame {frame = 60, value = Tau/6f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 5,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/3f },
                    new KeyFrame {frame = 60, value = Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 30, value = -Tau/5f },
                    new KeyFrame {frame = 60, value = -Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/6f },
                    new KeyFrame {frame = 30, value = -Tau/8f },
                    new KeyFrame {frame = 60, value = -Tau/6f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 7,
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 30, value = -Tau/3f },
                    new KeyFrame {frame = 60, value = -Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 8,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = -0.3f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 9,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0.6f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 11,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0.3f },
                    new KeyFrame {frame = 30, value = 0.0f },
                    new KeyFrame {frame = 60, value = 0.3f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 12,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0.6f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },
        };
    public static List<AnimationCurve> walk_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 2 },
                    new KeyFrame {frame = 8, value = 1.75f },
                    new KeyFrame {frame = 16, value = 2 },
                    new KeyFrame {frame = 24, value = 1.75f },
                    new KeyFrame {frame = 32, value = 2 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 2, //chest 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = +0.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4, //left shoulder 
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/6 },
                    new KeyFrame {frame = 32, value = Tau/6 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4, //left shoulder 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = 0.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 5, //left elbow 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .5f },
                    new KeyFrame {frame = 60, value = .5f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6, //right shoulder 
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/6 },
                    new KeyFrame {frame = 32, value = -Tau/6 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6, //right shoulder 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = 0.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 7, //right elbow 
                property_tag = 4,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -.5f },
                    new KeyFrame {frame = 32, value = -.5f },
                },
            },
            new AnimationCurve()
            {
                transform_index = 8, //left hip 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -.5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = .5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 9, //left knee 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 16, value = .5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 11, //right hip 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = .5f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = -.5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 12, //right knee 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = 0 },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = .5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },
        };
    public static List<AnimationCurve> punch_curves = new List<AnimationCurve>
    {
        new AnimationCurve()
        {
            transform_index = 1, //core 
            property_tag = 1,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 2 },
                new KeyFrame {frame = 30, value = 2 },
            },
        },
        new AnimationCurve()
        {
            transform_index = 1, //core
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = .3f },
                new KeyFrame {frame = 30, value = .3f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 2, //chest
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = .0f },
                new KeyFrame {frame = 15, value = -.9f },
                new KeyFrame {frame = 30, value = .0f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 4,
            property_tag = 5,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = Tau/4f },
                new KeyFrame {frame = 30, value = Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 4,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = Tau/6f },
                new KeyFrame {frame = 15, value = -Tau/9f },
                new KeyFrame {frame = 30, value = Tau/6f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 5,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = Tau/4f },
                new KeyFrame {frame = 30, value = Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 6,
            property_tag = 5,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = -Tau/4f },
                new KeyFrame {frame = 15, value = 0 },
                new KeyFrame {frame = 30, value = -Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 6,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = -Tau/6f },
                new KeyFrame {frame = 15, value = -Tau/4 },
                new KeyFrame {frame = 30, value = -Tau/6f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 7,
            property_tag = 4,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = -Tau/4f },
                new KeyFrame {frame = 15, value = 0 },
                new KeyFrame {frame = 30, value = -Tau/4f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 8,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0f },
                new KeyFrame {frame = 30, value = 0f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 9,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0f },
                new KeyFrame {frame = 30, value = 0f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 11,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0.3f },
                new KeyFrame {frame = 30, value = 0.3f },
            },
        },
        new AnimationCurve()
        {
            transform_index = 12,
            property_tag = 3,
            keyframes = new KeyFrame[]
            {
                new KeyFrame {frame = 01, value = 0f },
                new KeyFrame {frame = 30, value = 0f },
            },
        },
    };
    public static List<AnimationCurve> jump_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 27, value = -0.75f },
                    new KeyFrame {frame = 30, value = -0.5f },
                    new KeyFrame {frame = 45, value = 0f },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 8,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = -0.5f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 9,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = 1f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 11,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = -0.5f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 12,
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = 1f },
                    new KeyFrame {frame = 40, value = 0 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_index = 4,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 1/4f*Tau },
                    new KeyFrame {frame = 30, value = 1/8f*Tau },
                    new KeyFrame {frame = 40, value = 1/4f*Tau },
                    new KeyFrame {frame = 60, value = 1/4f*Tau },
                },
            },
            new AnimationCurve()
            {
                transform_index = 6,
                property_tag = 5,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -1/4f*Tau },
                    new KeyFrame {frame = 30, value = -1/8f*Tau },
                    new KeyFrame {frame = 40, value = -1/4f*Tau },
                    new KeyFrame {frame = 60, value = -1/4f*Tau },
                },
            },
        };

    public static Animation idle_animation = new Animation() { looped = true, curves = idle_curves };
    public static Animation walk_animation = new Animation() { looped = true, curves = walk_curves };
    public static Animation punch_animation = new Animation()
    {
        looped = true,
        curves = punch_curves,
        attackbox_keys = new int[][]
        {
            new int[] { 1 },
            new int[] { 1, 5, 20 },
        },
        attackbox_values = new bool[][]
        {
            new bool[]{ false },
            new bool[]{ false, true, false },
        }
    };
    public static Animation jump_animation = new Animation() { curves = jump_curves };
    public static Animation die_animation = new Animation()
    {
        curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 2 },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },

            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 3,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 60, value = 1.6f },
                },
            },
        }
    };
}

class SplashScreen : IGameState
{
    bool splash_screen_started = false;
    bool splash_screen_ended = false;
    float splash_screen_time;
    float splash_screen_alpha;
    Bitmap logo = (Bitmap)Image.FromStream(GetAssetStream("VikingStudios.png"));

    public void Update()
    {
        if (splash_screen_time > 10)
        {
            if (!splash_screen_ended)
            {
                game_state_index++;
                splash_screen_ended = true;
            }
            else
            {
                splash_screen_time = 0;
                splash_screen_ended = false;
            }
        }

        if (!splash_screen_started)
        {
            System.Media.SoundPlayer player = new System.Media.SoundPlayer(GetAssetStream("preparations.wav"));
            player.Play();
            splash_screen_started = true;
        }

        ImageAttributes imageAttributes = new ImageAttributes();
        int width = logo.Width;
        int height = logo.Height;

        float[][] colorMatrixElements = {
                    new float[] {1,  0,  0,  0, 0},        // red scaling factor of 1
                    new float[] {0,  1,  0,  0, 0},        // green scaling factor of 1
                    new float[] {0,  0,  1,  0, 0},        // blue scaling factor of 1
                    new float[] {0,  0,  0,  splash_screen_alpha, 0},        // alpha scaling factor of 1
                    new float[] {0,  0,  0,  0, 1}};    // translations

        ColorMatrix colorMatrix = new ColorMatrix(colorMatrixElements);

        imageAttributes.SetColorMatrix(colorMatrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);

        graphics.Clear(Color.Black);
        graphics.DrawImage(logo, new Rectangle(0, 0, WIDTH, HEIGHT), 0, 0, 1920, 1080, GraphicsUnit.Pixel, imageAttributes);

        splash_screen_time += delta_time;
        if (splash_screen_time > 2 && splash_screen_time < 7 && splash_screen_alpha < .9)
            splash_screen_alpha += delta_time / 5;

        if (splash_screen_time > 8)
            splash_screen_alpha -= delta_time;

        if (splash_screen_alpha < 0)
            splash_screen_alpha = 0;
    }
}