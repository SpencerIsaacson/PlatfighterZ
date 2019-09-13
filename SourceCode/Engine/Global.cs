using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using static System.Math;
using static Game;

namespace Engine
{
    public static class Global
    {
        public const float Tau = 6.28318530717958f;

        #region Linear Algebra

        public static Transform InvertTransform(Transform t)
        {
            t.position = -t.position;
            t.rotation = -t.rotation;
            t.scale.x = 1 / t.scale.x;
            t.scale.y = 1 / t.scale.y;
            t.scale.z = 1 / t.scale.z;
            return t;
        }

        public static Matrix4x4 GetMatrix(Transform t)
        {
            return Matrix4x4.identity
                * Scale(t.scale.x, t.scale.y, t.scale.z)
                * Rotation(t.rotation.x, t.rotation.y, t.rotation.z)
                * Translation(t.position.x, t.position.y, t.position.z);
        }


        public static Matrix4x4 WorldSpaceMatrix(Transform t, Transform[] world)
        {
            Matrix4x4 m = GetMatrix(t);
            while (t.parent != -1)
            {
                m = Concatenate(m, GetMatrix(world[t.parent]));
                t = world[t.parent];
            }

            return m;
        }


        public static Matrix4x4 Concatenate(Matrix4x4 a, Matrix4x4 b)
        {
            return new Matrix4x4()
            {
                m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41,
                m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42,
                m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43,
                m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44,
                m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41,
                m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42,
                m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43,
                m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44,
                m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41,
                m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42,
                m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43,
                m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44,
                m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41,
                m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42,
                m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43,
                m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44,
            };
        }


        public static Matrix4x4 Transpose(Matrix4x4 m)
        {
            return new Matrix4x4(new float[] { m.m11, m.m21, m.m31, m.m41, m.m12, m.m22, m.m32, m.m42, m.m13, m.m23, m.m33, m.m43, m.m14, m.m24, m.m34, m.m44 });
        }


        public static Matrix4x4 Translation(float x, float y, float z)
        {
            return new Matrix4x4(new float[] { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1 });
        }


        public static Matrix4x4 Scale(float x, float y, float z)
        {
            return new Matrix4x4(new float[] { x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1 });
        }


        public static Matrix4x4 Rotation(float x, float y, float z)
        {
            return new Matrix4x4()
            {
                m11 = (float)(Cos(y) * Cos(z) - Sin(y) * Sin(x) * Sin(z)),
                m12 = (float)(Cos(y) * Sin(z) + Sin(y) * Sin(x) * Cos(z)),
                m13 = (float)(-Sin(y) * Cos(x)),
                m21 = (float)(-Sin(z) * Cos(x)),
                m22 = (float)(Cos(z) * Cos(x)),
                m23 = (float)(Sin(x)),
                m31 = (float)(Sin(y) * Cos(z) + Cos(y) * Sin(x) * Sin(z)),
                m32 = (float)(Sin(z) * Sin(y) - Cos(y) * Sin(x) * Cos(z)),
                m33 = (float)(Cos(y) * Cos(x)),
                m44 = 1
            };
        }

        public static Matrix4x4 Perspective(float near, float far, float field_of_view)
        {
            float aspect_ratio = HEIGHT / (float)WIDTH;
            float zoom = (float)(1 / Tan(field_of_view / 2));
            float q = far / (far - near);

            return new Matrix4x4(new float[]
            {
                aspect_ratio * zoom, 0, 0, 0,
                0,-zoom,0,0,
                0,0,q,near * q,
                0,0,1,0
            });
        }


        public static Vector3 TransformVector(Matrix4x4 m, Vector3 v)
        {
            return new Vector3
            {
                x = m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41,
                y = m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42,
                z = m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43,
            };
        }

        public static Vector4 TransformVector(Matrix4x4 m, Vector4 v)
        {
            return new Vector4
            {
                x = m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41 * v.w,
                y = m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42 * v.w,
                z = m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43 * v.w,
                w = m.m14 * v.x + m.m24 * v.y + m.m34 * v.z + m.m44 * v.w,
            };
        }

        #endregion

        #region Animation


        public static void AnimateProperty(KeyFrame[] curve, float frame, ref float property)
        {
            for (int i = 0; i < curve.Length - 1; i++)
            {
                KeyFrame a = curve[i];
                KeyFrame b = curve[i + 1];
                if (frame >= a.frame && frame <= b.frame)
                {
                    property = Sample(a, b, frame);
                    return;
                }
            }
        }


        public static float Sample(KeyFrame a, KeyFrame b, float frame)
        {
            float t = .5f;
            float step = .25f;
            PointF c1 = new PointF(a.frame, a.value);
            PointF c2 = new PointF(a.frame + a.right_handle_x, a.value + a.right_handle_y);
            PointF c3 = new PointF(b.frame + b.left_handle_x, b.value + b.left_handle_y);
            PointF c4 = new PointF(b.frame, b.value);

            while (true)
            {
                PointF d = Lerp(c1, c2, t);
                PointF e = Lerp(c2, c3, t);
                PointF f = Lerp(c3, c4, t);
                PointF g = Lerp(d, e, t);
                PointF h = Lerp(e, f, t);
                PointF i = Lerp(g, h, t);

                if (i.X > frame)
                    t -= step;
                else
                    t += step;

                step /= 2;

                if (Math.Abs(i.X - frame) < .001f)
                    return i.Y;
            }
        }


        static PointF Lerp(PointF a, PointF b, float t)
        {
            float x = a.X + t * (b.X - a.X);
            float y = a.Y + t * (b.Y - a.Y);
            return new PointF(x, y);
        }


        static float Lerp(float a, float b, float t)
        {
            return a + t * (b - a);
        }


        #endregion

        #region FileIO

        public static Mesh LoadMesh(string file_name)
        {
            using (StreamReader reader = new StreamReader("Assets/" + file_name))
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
            using (BinaryReader reader = new BinaryReader(File.Open(path, FileMode.Open)))
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
            using (BinaryReader reader = new BinaryReader(File.Open(path, FileMode.Open)))
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
