using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

using static Game;
using static System.Math;

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

        #endregion
    }
}
