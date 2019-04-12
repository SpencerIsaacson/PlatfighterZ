﻿using System;
using System.Collections.Generic;
using static System.Math;

namespace PesdiEngine
{
    struct Player
    {
        public int entity_ID;
        public bool defeated;
        public int stock;
        public float health;
        public float y_velocity;
    }

    struct HitBox
    {
        public int transform_id;
        public float radius;
    }

    struct Animator
    {
        public float current_frame;
        public List<AnimationCurve> current_animation;
    }


    struct AnimationCurve
    {
        public int transform_id;
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

        public static readonly Vector2 Right = new Vector2 { x = 1, y = 0 };
        public static readonly Vector2 Left = new Vector2 { x = -1, y = 0 };
        public static readonly Vector2 Up = new Vector2 { x = 0, y = 1 };
        public static readonly Vector2 Down = new Vector2 { x = 0, y = -1 };
        public static readonly Vector2 Zero = new Vector2 { x = 0, y = 0 };
        public static readonly Vector2 One = new Vector2 { x = 1, y = 1 };

        public static Vector2 operator + (Vector2 a, Vector2 b) { return new Vector2 { x = a.x + b.x, y = a.y + b.y }; }
        public static Vector2 operator - (Vector2 a, Vector2 b) { return new Vector2 { x = a.x - b.x, y = a.y - b.y }; }
        public static Vector2 operator * (Vector2 v, float s) { return new Vector2 { x = v.x * s, y = v.y * s }; }
        public static Vector2 operator / (Vector2 v, float s) { return new Vector2 { x = v.x / s, y = v.y / s }; }

        public Vector2 Normalized() { return this / Magnitude(); }

        public float Magnitude() { return (float)Sqrt(x * x + y * y); }


        public static float Distance(Vector2 a, Vector2 b) { return (a - b).Magnitude(); }
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

        public static Vector3 operator - (Vector3 v) { return new Vector3 { x = -v.x, y = -v.y, z = -v.z }; }
        public static Vector3 operator + (Vector3 a, Vector3 b) { return new Vector3 { x = a.x + b.x, y = a.y + b.y, z = a.z + b.z }; }
        public static Vector3 operator - (Vector3 a, Vector3 b) { return new Vector3 { x = a.x - b.x, y = a.y - b.y, z = a.z - b.z }; }
        public static Vector3 operator * (Vector3 v, float s) { return new Vector3 { x = v.x * s, y = v.y * s, z = v.z * s }; }
        public static Vector3 operator / (Vector3 v, float s) { return new Vector3 { x = v.x / s, y = v.y / s, z = v.z / s }; }
		
        
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
            return $"[{x}, {y}, {z}]";
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

        //public Matrix4x4 Concat(Matrix4x4 b) { return Engine.Global.Concat(this, b); }
    }


	public struct Mesh
	{
		public Vector3[] vertices;
		public int[] indices;
	}


    interface IGameState
    {
        void Update();
    }
}
