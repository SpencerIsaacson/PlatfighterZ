using Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using static Engine.Global;
using static Game;

class HitBoxDemo : IGameState
{
    static Pen pen = new Pen(Color.White, 2f);

    static Transform camera = new Transform { position = Vector3.Forward * -10 };

    static Transform[] transforms;
    Player[] players = new Player[4];

    HitBox[] hit_boxes;
    HitBox[] hurt_boxes;

    bool[,] hurt_hit_matrix;
    public HitBoxDemo()
    {
        players[0] = new Player { health = 100 };
        transforms = LoadHierarchy("Assets/avatar");
        transforms[0].rotation.y = 1 / 4f * Tau;

        var hurtbox_list = new List<HitBox>();
        var hitbox_list = new List<HitBox>();
        for (int i = 0; i < transforms.Length; i++)
        {
            hurtbox_list.Add(new HitBox { transform_id = i, radius = .35f, color = Color.Blue });
        }
        hurt_boxes = hurtbox_list.ToArray();
        hurt_boxes[3].radius = .25f;

        transforms[0].position.x = -4;
        List<Transform> list = new List<Transform>(transforms);
        list.Add(new Transform { scale = Vector3.One, position = Vector3.Zero, parent = -1 });
        transforms = list.ToArray();

        HitBox hit = new HitBox { radius = .5f, color = Color.Blue };
        hit.transform_id = transforms.Length - 1;
        hitbox_list.Add(hit);

        hit_boxes = hitbox_list.ToArray();
        hurt_hit_matrix = new bool[hurt_boxes.Length, hit_boxes.Length];
    }

    float frame = 1;
    public unsafe void Update()
    {
        fixed_framerate = true;

        //Animate
        {
            float interval = 10 * time_step;

            fixed (Transform* hitbox = &transforms[transforms.Length - 1])
            {
                if (Input.KeyDown(Keys.A))
                {
                    (*hitbox).position.x -= interval;
                }
                if (Input.KeyDown(Keys.D))
                {
                    (*hitbox).position.x += interval;
                }
                if (Input.KeyDown(Keys.S))
                {
                    (*hitbox).position.y -= interval;
                }
                if (Input.KeyDown(Keys.W))
                {
                    (*hitbox).position.y += interval;
                }
            }

            var first_curve_frames = AvatarDemo.idle_animation[0].keyframes;
            var ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;

            if (frame > ending_frame)
            {
                frame = 1;
            }
            foreach (AnimationCurve curve in AvatarDemo.idle_animation)
            {
                KeyFrame[] keyframes = curve.keyframes;
                int transform_index = curve.transform_id;

                fixed (void* p = &transforms[transform_index])
                {
                    float* f = (float*)p + 1 + curve.property_tag;
                    AnimateProperty(keyframes, frame, ref *f);
                }
            }
            frame += 60 * time_step;
        }

        //Clear HitBox matrix
        {
            for (int x = 0; x < hurt_hit_matrix.GetLength(0); x++)
            {
                for (int y = 0; y < hurt_hit_matrix.GetLength(1); y++)
                {
                    hurt_hit_matrix[x, y] = false;
                }
            }
        }

        players[0].health += time_step;
        //Render
        {
            graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
            graphics.ResetTransform();
            graphics.Clear(Color.Black);
            graphics.FillRectangle(Brushes.Green, 0, 0, 10 * players[0].health, 20);
            graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
            graphics.ScaleTransform(1, -1);

            for (int i = 0; i < hurt_boxes.Length; i++)
            {
                var hurt = hurt_boxes[i];
                Vector3 hurt_position = TransformVector(WorldSpaceMatrix(transforms[hurt.transform_id], transforms), Vector3.Zero);
                hurt_position.z = 0;

                for (int o = 0; o < hit_boxes.Length; o++)
                {
                    var hit = hit_boxes[o];
                    Vector3 hit_position = TransformVector(WorldSpaceMatrix(transforms[hit.transform_id], transforms), Vector3.Zero);
                    hit_position.z = 0;
                    float distance = (hurt_position - hit_position).Magnitude();
                    float combined_radius = hurt.radius + hit.radius;

                    if (distance < combined_radius)
                        hurt_hit_matrix[i, o] = true;
                }
            }


            //Set color
            {
                for (int i = 0; i < hurt_boxes.Length; i++)
                {
                    var hurt = hurt_boxes[i];
                    hurt.color = Color.Blue;
                    hurt_boxes[i] = hurt;
                }

                for (int i = 0; i < hit_boxes.Length; i++)
                {
                    var hit = hit_boxes[i];
                    hit.color = Color.Blue;
                    hit_boxes[i] = hit;
                }

                for (int x = 0; x < hurt_hit_matrix.GetLength(0); x++)
                {
                    for (int y = 0; y < hurt_hit_matrix.GetLength(1); y++)
                    {
                        if (hurt_hit_matrix[x, y])
                        {
                            players[0].health -= time_step;
                            var hit = hit_boxes[y];
                            var hurt = hurt_boxes[x];
                            hurt.color = Color.Red;
                            hit.color = Color.Red;
                            hit_boxes[y] = hit;
                            hurt_boxes[x] = hurt;
                        }
                    }

                }
            }


            foreach (HitBox hurt_box in hurt_boxes)
            {
                hurt_box.Draw();
            }

            foreach (HitBox hit_box in hit_boxes)
            {
                hit_box.Draw();
            }

        }
    }

    struct HitBox
    {
        public int transform_id;
        public float radius;
        public Color color;

        public void Draw()
        {
            Transform t = transforms[transform_id];
            Matrix4x4 m = WorldSpaceMatrix(t, transforms);

            var inverted_camera = new Transform()
            {
                position = -camera.position,
                scale = Vector3.One,
                rotation = -camera.rotation
            };
            m = Concat(m, GetMatrix(inverted_camera));

            Vector3 center = TransformVector(m, Vector3.Zero) * PIXELS_PER_UNIT;

            float width = radius * 2 * PIXELS_PER_UNIT;
            float half = width / 2f;
            graphics.FillEllipse(new SolidBrush(color), center.x - 4, center.y - 4, 8, 8);
            graphics.FillEllipse(new SolidBrush(Color.FromArgb(30, color)), center.x - half, center.y - half, width, width);
            graphics.DrawEllipse(new Pen(Color.FromArgb(color.R / 2, color.G / 2, color.B / 2), 2f), center.x - half, center.y - half, width, width);
        }
    }
}
