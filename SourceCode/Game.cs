using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

using static Engine.DrawingLibrary;
using static Engine.Global;
using static Engine.Game;
using static System.Math;

namespace Engine
{
    class Game
    {
        //Resolution
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
        GameplayState play_state = new GameplayState();
        MeshDemo mesh_demo = new MeshDemo();


        public enum GameStates
        {
            Splash,
            Mesh,
            SkinnedMesh,
            Gameplay,
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

        unsafe Game()
        {
            //Setup Window
            {
                window.ClientSize = new Size(WIDTH, HEIGHT);
                window.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
                window.MaximizeBox = false;
                window.Text = "Platfighter Z";
                window.Icon = new Icon(GetAssetStream("icon.ico"));
                //System.Windows.Forms.Cursor.Hide();
            }

            SkinnedMeshDemo_Init();
            InitMeshDemo();
            //Initialize Graphics
            {
                InitGraphics();
                font_set = LoadFontSet("font_set");
                fixed (CharSprite* p = font_set)
                {
                    FillSprites(p, font_set.Length);
                }
            }

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

                        if (Input.KeyDownFresh(Keys.F4))
                        {
                            ToggleFullScreen();
                        }

                        //Cycle Through GameStates
                        {
                            if (Input.KeyDownFresh(Keys.Tab))
                            {
                                game_state_index = (game_state_index + 1) % state_count;
                            }

                            else if (Input.KeyDownFresh(Keys.Z))
                            {
                                game_state_index--;
                                if (game_state_index < 0)
                                    game_state_index += state_count;
                            }

                            current_game_state = (GameStates)game_state_index;
                        }

                        frames_since_last_second++;

                        switch (current_game_state)
                        {
                            case GameStates.Splash:
                                splash_screen.Update();
                                break;
                            case GameStates.SkinnedMesh:
                                SkinnedMeshDemo_Update(delta_time);
                                OutputRender();
                                break;
                            case GameStates.Gameplay:
                                UpdateGameplay(play_state);
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
            return PeekMessage(out NativeMessage result, IntPtr.Zero, 0, 0, 0) == 0;
        }
        [DllImport("SGL.dll")]
        static extern void InitMeshDemo();
        [DllImport("SGL.dll")]
        public static extern void GameplayState_Init(GameplayState state);
        [DllImport("SGL.dll")]
        public static extern void ResetGame(GameplayState state);
        [DllImport("SGL.dll")]
        public static unsafe extern void UpdateGameplay(GameplayState state);
        [DllImport("SGL.dll")]
        static extern unsafe void FillSprites(CharSprite* sprites, int count);
        [DllImport("SGL.dll")]
        public static extern void RunMeshDemo(C_Mesh mesh, Transform camera, float delta_time, float frames_per_second);
        [DllImport("SGL.dll")]
        static extern void SkinnedMeshDemo_Init();
        [DllImport("SGL.dll")]
        static extern unsafe void SkinnedMeshDemo_Update(float delta_time);
        [DllImport("SGL.dll")]
        static unsafe extern void Render(C_Mesh mesh, uint* body_poly_colors, Transform camera, byte fill_toggle);
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
    }

    class MeshDemo
    {
        static Mesh mesh = LoadMesh("cube.obj");
        static Transform camera = new Transform() { position = Vector3.Forward * -30, scale = Vector3.One };


        public unsafe void Update()
        {
            C_Mesh c_mesh = new C_Mesh();
            fixed (int* i = mesh.indices)
            fixed (Vector3* v = mesh.vertices)
            {
                c_mesh.indices = i;
                c_mesh.vertices = v;
                c_mesh.vertices_length = mesh.vertices.Length;
                c_mesh.indices_length = mesh.indices.Length;
            }

            RunMeshDemo(c_mesh, camera, delta_time, frames_per_second);
            OutputRender();
        }

    }

    class GameplayState
    {
        public bool view_debug = false;

        //Game World
        public Transform camera = new Transform();
        public float field_of_view = 3 / 8f * Tau;
        public Transform[] transforms;
        public static readonly Player[] players = new Player[PLAYER_COUNT];
        public readonly Animator[] animators = new Animator[PLAYER_COUNT];
        public static readonly uint[] player_colors = new uint[] { red, 0xFF008000, blue, purple };
        public Transform[] blocks = new Transform[30];

        //Play variables
        public const int PLAYER_COUNT = 4; //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players
        public int winner = 0;
        public bool game_over = false;
        public float initial_time = 99;
        public float time_remaining;
        public float max_health = 10;

        //physics
        public readonly float gravity = 10;
    }

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
        A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        F4 = 115,
        NumPad0 = 96, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
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

    public struct Weight_Index
    {
        public int bone1, bone2, bone3, bone4;
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

        public override int GetHashCode() { return -1; /*TODO implement?*/ }

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
            return Concatenate(a, b);
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

    public static class Global
    {
        public const float Tau = 6.28318530717958f;
        public const float Pi = Tau / 2;

        #region Linear Algebra
        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Concatenate(Matrix4x4 a, Matrix4x4 b);
        [DllImport("SGL.dll")]
        public static extern Matrix4x4 Perspective(float near, float far, float field_of_view, float width, float height);
        [DllImport("SGL.dll")]
        public static extern Vector3 Transform_v3(Matrix4x4 m, Vector3 v);
        [DllImport("SGL.dll")]
        public static extern Transform InvertTransform(Transform t);
        [DllImport("SGL.dll")]
        public static extern Matrix4x4 WorldSpaceMatrix(int index, Transform[] hierarchy);
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

        public unsafe static Mesh LoadMesh(string path)
        {
            Stream stream = GetAssetStream(path);

            using (StreamReader reader = new StreamReader(stream))
            {
                List<Vector3> vertexList = new List<Vector3>();
                List<int> indexList = new List<int>();

                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    string[] subs = line.Split(' ');

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

        public unsafe static PointerCountArray<uint> LoadPolygonColors(string path)
        {
            Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(GetAssetPathPrefix() + path);
            using (BinaryReader reader = new BinaryReader(stream))
            {
                List<uint> polygon_colors = new List<uint>();
                while (reader.BaseStream.Position != reader.BaseStream.Length)
                {
                    polygon_colors.Add(reader.ReadUInt32());
                }
                fixed (uint* p = (polygon_colors.ToArray()))
                {
                    return new PointerCountArray<uint>() { pointer = p, count = polygon_colors.ToArray().Length };
                }
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

    class Input
    {
        [DllImport("SGL.dll")]
        public static extern bool KeyDownFresh(Keys key);
        [DllImport("SGL.dll")]
        public static extern bool KeyDown(Keys key);
        [DllImport("SGL.dll")]
        public static extern void PollKeyboard();
    }

    public unsafe struct PointerCountArray<T> where T : unmanaged
    {
        public T* pointer;
        public int count;
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
        public static extern void InitViewport(float field_of_view, int WIDTH, int HEIGHT, uint[] pixels); //TODO rename
        [DllImport("SGL.dll")]
        public static extern void PutPixel(uint color, int x, int y);

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
            InitViewport(Tau / 4, WIDTH, HEIGHT, pixels);
        }

        public static void OutputRender()
        {
            graphics.DrawImage(rendered_image, 0, 0); //TODO find something faster than this! Perhaps you can access the contents of the GDI drawing surface directly?
        }

        #region Text
        public static CharSprite[] font_set = new CharSprite[44]; //TODO don't rely on this magic number, at least until you've verified it will stay the same
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

    public class SplashScreen
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
                    splash_screen_started = false;
                }
            }

            if (!splash_screen_started)
            {
                System.Media.SoundPlayer player = new System.Media.SoundPlayer(GetAssetStream("preparations.wav"));
                //player.Play();
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
}