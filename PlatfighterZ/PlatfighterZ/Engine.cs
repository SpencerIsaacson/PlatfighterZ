using System.Drawing;
using static System.Math;

namespace Engine
{
    struct Player
    {
        public Entity avatar;
        public bool defeated;
        public int stock;
        public float health;
        public float y_velocity;
    }


    public struct Entity
    {
        public Transform transform;
    }


    public struct Vector3
    {
        public static Vector3 Right = new Vector3(1, 0, 0);
        public static Vector3 Up = new Vector3(0, 1, 0);
        public static Vector3 Zero = new Vector3(0, 0, 0);
        public static Vector3 One = new Vector3(1, 1, 1);

        public float x, y, z;

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public static Vector3 operator +(Vector3 a, Vector3 b) { return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
        public static Vector3 operator -(Vector3 a, Vector3 b) { return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
        public static Vector3 operator *(Vector3 v, float s) { return new Vector3(v.x * s, v.y * s, v.z * s); }
        public static Vector3 operator /(Vector3 v, float s) { return new Vector3(v.x / s, v.y / s, v.z / s); }
        public override string ToString() { return $"[{x}, {y}, {z}]"; }
    }


    public struct Transform
    {
        public int parent;
        public Vector3 position;
        public Vector3 rotation;
        public Vector3 scale;

        public Matrix4x4 GetMatrix()
        {
            return Matrix4x4.identity
                .Concat(Matrix4x4.Scale(scale.x, scale.y, scale.z))
                .Concat(Matrix4x4.Rotation(rotation.x, rotation.y, rotation.z))
                .Concat(Matrix4x4.Translation(position.x, position.y, position.z));//TODO pre-concatenate at compile-time
        }
    }


    public struct Matrix4x4
    {
        public static readonly Matrix4x4 identity = new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

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

        public Matrix4x4 Concat(Matrix4x4 b)
        {
            return new Matrix4x4()
            {
                m11 = m11 * b.m11 + m12 * b.m21 + m13 * b.m31 + m14 * b.m41,
                m12 = m11 * b.m12 + m12 * b.m22 + m13 * b.m32 + m14 * b.m42,
                m13 = m11 * b.m13 + m12 * b.m23 + m13 * b.m33 + m14 * b.m43,
                m14 = m11 * b.m14 + m12 * b.m24 + m13 * b.m34 + m14 * b.m44,
                m21 = m21 * b.m11 + m22 * b.m21 + m23 * b.m31 + m24 * b.m41,
                m22 = m21 * b.m12 + m22 * b.m22 + m23 * b.m32 + m24 * b.m42,
                m23 = m21 * b.m13 + m22 * b.m23 + m23 * b.m33 + m24 * b.m43,
                m24 = m21 * b.m14 + m22 * b.m24 + m23 * b.m34 + m24 * b.m44,
                m31 = m31 * b.m11 + m32 * b.m21 + m33 * b.m31 + m34 * b.m41,
                m32 = m31 * b.m12 + m32 * b.m22 + m33 * b.m32 + m34 * b.m42,
                m33 = m31 * b.m13 + m32 * b.m23 + m33 * b.m33 + m34 * b.m43,
                m34 = m31 * b.m14 + m32 * b.m24 + m33 * b.m34 + m34 * b.m44,
                m41 = m41 * b.m11 + m42 * b.m21 + m43 * b.m31 + m44 * b.m41,
                m42 = m41 * b.m12 + m42 * b.m22 + m43 * b.m32 + m44 * b.m42,
                m43 = m41 * b.m13 + m42 * b.m23 + m43 * b.m33 + m44 * b.m43,
                m44 = m41 * b.m14 + m42 * b.m24 + m43 * b.m34 + m44 * b.m44,
            };
        }

        public static Matrix4x4 Concat(Matrix4x4 a, Matrix4x4 b)
        {
            return a.Concat(b);
        }

        public static Matrix4x4 Transpose(Matrix4x4 m)
        {
            return new Matrix4x4(m.m11, m.m21, m.m31, m.m41, m.m12, m.m22, m.m32, m.m42, m.m13, m.m23, m.m33, m.m43, m.m14, m.m24, m.m34, m.m44);
        }

        public static Matrix4x4 Translation(float x, float y, float z)
        {
            return new Matrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1);
        }

        public static Matrix4x4 Scale(float x, float y, float z)
        {
            return new Matrix4x4(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
        }

        public static Matrix4x4 Rotation(float x, float y, float z)
        {
            return new Matrix4x4()
            {
                m11 = (float)(Cos(y) * Cos(z) + Sin(y) * Sin(x) * Sin(z)),
                m12 = (float)(-Cos(y) * Sin(z) + Sin(y) * Sin(x) * Cos(z)),
                m13 = (float)(Sin(y) * Cos(x)),
                m21 = (float)(Sin(z) * Cos(x)),
                m22 = (float)(Cos(z) * Cos(x)),
                m23 = (float)(-Sin(x)),
                m31 = (float)(-Sin(y) * Cos(z) + Cos(y) * Sin(x) * Sin(z)),
                m32 = (float)(Sin(z) * Sin(y) + Cos(y) * Sin(x) * Cos(z)),
                m33 = (float)(Cos(y) * Cos(x)),
                m44 = 1
            };
        }

        public static Matrix4x4 Perspective(float d)
        {
            return new Matrix4x4() { m11 = 1, m22 = 1, m33 = 1, m34 = 1 / d };
        }

        public static Matrix4x4 WorldSpaceMatrix(Transform t)
        {
            Matrix4x4 m = t.GetMatrix();
            while (t.parent != 0)
            {
                m = Concat(m, Game.transforms[t.parent-1].GetMatrix());
                t = Game.transforms[t.parent-1];
            }
            return m;
        }

        public static Vector3 TransformVector(Matrix4x4 m, Vector3 v)
        {
            return new Vector3(m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41, m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42, m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43);
        }

        public override string ToString()
        {
            return $"[{m11}, {m12}, {m13}, {m14}, {m21}, {m22}, {m23}, {m24}, {m31}, {m32}, {m33}, {m34}, {m41}, {m42}, {m43}, {m44}]";
        }
    }

    interface IDemo
    {
        void Update();
    }
}