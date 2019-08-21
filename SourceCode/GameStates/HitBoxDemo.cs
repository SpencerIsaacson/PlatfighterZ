using Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using static Engine.Global;
using static Game;

class HitBoxDemo : IGameState
{

    static Transform[] transforms;
    Player player = new Player { health = 100 };

    Hitbox[] defendboxes =
    {
        new Hitbox(){transform_index = 1, radius = .3f},
        new Hitbox(){transform_index = 2, radius = .5f},
        new Hitbox(){transform_index = 3, radius = .2f},
    };

    Hitbox[] attackboxes =
    {
        new Hitbox(){transform_index = 14, radius = .2f},
        new Hitbox(){transform_index = 15, radius = .2f},
    };

    int[][] defendbox_keys =
    {
        new int[]{ 1 },
        new int[]{ 1, 15},
        new int[]{ 1},
    };

    bool[][] defendbox_values =
{
        new bool[]{ true },
        new bool[]{ true, false },
        new bool[]{ true },
    };

    int[][] attackbox_keys =
{
        new int[]{ 1 },
        new int[]{ 1, 5, 20},
    };

    bool[][] attackbox_values =
{
        new bool[]{ false },
        new bool[]{ false, true, false },
    };

    bool[,] hurt_hit_matrix;
    public HitBoxDemo()
    {
        transforms = LoadHierarchy("Assets/avatar");
        transforms[0].rotation.y = 1 / 4f * Tau;

        transforms[0].position.x = -4;
    }

    float frame = 1;
    public unsafe void Update()
    {
        fixed_framerate = true;

        //Animate
        {
            var first_curve_frames = AvatarDemo.punch_curves[0].keyframes;
            var ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;

            if (frame > ending_frame)
            {
                frame = 1;
            }

            foreach (AnimationCurve curve in AvatarDemo.punch_curves)
            {
                KeyFrame[] keyframes = curve.keyframes;
                int transform_index = curve.transform_index;

                fixed (void* p = &transforms[transform_index])
                {
                    float* f = (float*)p + 1 + curve.property_tag;
                    AnimateProperty(keyframes, frame, ref *f);
                }
            }

            for (int defendbox_index = 0; defendbox_index < defendboxes.Length; defendbox_index++)
            {
                for (int i = 0; i < defendbox_keys[defendbox_index].Length; i++)
                {
                    if (frame == defendbox_keys[defendbox_index][i])
                    {
                        defendboxes[defendbox_index].active = defendbox_values[defendbox_index][i];
                    }
                }
            }

            for (int attackbox_index = 0; attackbox_index < attackboxes.Length; attackbox_index++)
            {
                for (int i = 0; i < attackbox_keys[attackbox_index].Length; i++)
                {
                    if (frame == attackbox_keys[attackbox_index][i])
                    {
                        attackboxes[attackbox_index].active = attackbox_values[attackbox_index][i];
                    }
                }
            }

            frame ++;
        }

        //Render
        {
            graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
            graphics.Clear(Color.Black);

            graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
            graphics.ScaleTransform(1, -1);

            Vector3[] transformed_vectors = new Vector3[transforms.Length];
            for (int i = 0; i < transforms.Length; i++)
            {
                Matrix4x4 m = WorldSpaceMatrix(transforms[i], transforms);

                transformed_vectors[i] = TransformVector(m, Vector3.Zero) * PIXELS_PER_UNIT;
            }

            for (int i = 0; i < transforms.Length; i++)
            {
                if (transforms[i].parent != -1)
                {
                    var parent_vector = transformed_vectors[transforms[i].parent];
                    graphics.DrawLine(Pens.Gray, transformed_vectors[i].x, transformed_vectors[i].y, parent_vector.x, parent_vector.y);
                }
            }

            for (int i = 0; i < defendboxes.Length; i++)
            {
                if (defendboxes[i].active)
                {
                    Transform t = transforms[defendboxes[i].transform_index];
                    Matrix4x4 m = WorldSpaceMatrix(t, transforms);

                    Vector3 center = TransformVector(m, Vector3.Zero) * PIXELS_PER_UNIT;

                    float width = defendboxes[i].radius * 2 * PIXELS_PER_UNIT;
                    float half = width / 2f;
                    Color color = Color.Blue;
                    graphics.FillEllipse(new SolidBrush(color), center.x - 4, center.y - 4, 8, 8);
                    graphics.FillEllipse(new SolidBrush(Color.FromArgb(30, color)), center.x - half, center.y - half, width, width);
                    graphics.DrawEllipse(new Pen(Color.FromArgb(color.R / 2, color.G / 2, color.B / 2), 2f), center.x - half, center.y - half, width, width);
                }
            }

            for (int i = 0; i < attackboxes.Length; i++)
            {
                if (attackboxes[i].active)
                {
                    Transform t = transforms[attackboxes[i].transform_index];
                    Matrix4x4 m = WorldSpaceMatrix(t, transforms);

                    Vector3 center = TransformVector(m, Vector3.Zero) * PIXELS_PER_UNIT;

                    float width = attackboxes[i].radius * 2 * PIXELS_PER_UNIT;
                    float half = width / 2f;
                    Color color = Color.Red;
                    graphics.FillEllipse(new SolidBrush(color), center.x - 4, center.y - 4, 8, 8);
                    graphics.FillEllipse(new SolidBrush(Color.FromArgb(30, color)), center.x - half, center.y - half, width, width);
                    graphics.DrawEllipse(new Pen(Color.FromArgb(color.R / 2, color.G / 2, color.B / 2), 2f), center.x - half, center.y - half, width, width);
                }
            }

            graphics.ResetTransform();
            graphics.FillRectangle(Brushes.Green, 0, 0, 10 * player.health, 20);
        }
    }
}
