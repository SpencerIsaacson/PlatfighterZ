using System.Drawing;
using static System.Math;
using static Engine.Global;

namespace Engine
{
    struct Player
    {
        public int entity_ID;
        public bool defeated;
        public int stock;
        public float health;
        public float y_velocity;
    }

    public struct Transform
    {
        public int parent;
        public Vector3 position;
        public Vector3 rotation;
        public Vector3 scale;
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

    public struct Vector3
    {
        public float x, y, z;

        public static readonly Vector3 Right = new Vector3 { x = 1, y = 0, z = 0 };
        public static readonly Vector3 Up = new Vector3 { x = 0, y = 1, z = 0 };
        public static readonly Vector3 Zero = new Vector3 { x = 0, y = 0, z = 0 };
        public static readonly Vector3 One = new Vector3 { x = 1, y = 1, z = 1 };

        public static Vector3 operator + (Vector3 a, Vector3 b) { return new Vector3 { x = a.x + b.x, y = a.y + b.y, z = a.z + b.z }; }
        public static Vector3 operator - (Vector3 a, Vector3 b) { return new Vector3 { x = a.x - b.x, y = a.y - b.y, z = a.z - b.z }; }
        public static Vector3 operator * (Vector3 v, float s) { return new Vector3 { x = v.x * s, y = v.y * s, z = v.z * s }; }
        public static Vector3 operator / (Vector3 v, float s) { return new Vector3 { x = v.x / s, y = v.y / s, z = v.z / s }; }
    }

    public struct Matrix4x4
    {
        public float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;

        public Matrix4x4(float[] buffer)
        {
            if(buffer.Length != 16)
                this = identity;
                
            this.m11 = buffer[0];
            this.m12 = buffer[1];
            this.m13 = buffer[2];
            this.m14 = buffer[3];
            this.m21 = buffer[4];
            this.m22 = buffer[5];
            this.m23 = buffer[6];
            this.m24 = buffer[7];
            this.m31 = buffer[8];
            this.m32 = buffer[9];
            this.m33 = buffer[10];
            this.m34 = buffer[11];
            this.m41 = buffer[12];
            this.m42 = buffer[13];
            this.m43 = buffer[14];
            this.m44 = buffer[15];
        }
        
        public static readonly Matrix4x4 identity = new Matrix4x4(new float [] { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 });

        public Matrix4x4 Concat(Matrix4x4 b) { return Engine.Global.Concat(this, b); }
    }

    interface IDemo
    {
        void Update();
    }
}
