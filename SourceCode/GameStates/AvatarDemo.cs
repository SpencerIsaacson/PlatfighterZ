using Engine;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using static Engine.Global;
using static Game;

class AvatarDemo : IGameState
{
    Transform camera = new Transform() { position = new Vector3(0, 1, -20), scale = Vector3.One, rotation = new Vector3(0, 0, 0) };
    float field_of_view = 3 / 8f * Tau;

    Transform[] skeleton;
    int avatar_count = 2;

    struct Avatar
    {
        public float frame;
        public List<AnimationCurve> current_animation;
    }

    public static List<AnimationCurve> walk_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 8, value = -0.25f },
                    new KeyFrame {frame = 16, value = 0 },
                    new KeyFrame {frame = 24, value = -0.25f },
                    new KeyFrame {frame = 32, value = 0 },
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
                new KeyFrame {frame = 01, value = 0 },
                new KeyFrame {frame = 30, value = 0 },
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
    public static List<AnimationCurve> idle_curves = new List<AnimationCurve>
        {
            new AnimationCurve()
            {
                transform_index = 1, //core 
                property_tag = 1,
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = -.07f },
                    new KeyFrame {frame = 60, value = 0 },
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
    public static List<AnimationCurve> jump_curves;

    public static Animation idle_animation = new Animation()
    {
        curves = idle_curves,
    };

    public static Animation walk_animation = new Animation() { curves = walk_curves };
    public static Animation punch_animation = new Animation()
    {
        curves = punch_curves,
        attackbox_keys = new int[] { 1, 5, 20 },
        attackbox_values = new bool[] { false, true, false },
    };

    public static Animation jump_animation = new Animation() { curves = jump_curves };
    List<Avatar> avatars;

    Transform[] transforms;

    public AvatarDemo()
    {
        skeleton = LoadHierarchy("Assets/avatar");
        List<Transform> list_transforms = new List<Transform>();

        for (int i = 0; i < avatar_count; i++)
        {
            list_transforms.AddRange(skeleton);
        }

        for (int i = 0; i < avatar_count; i++)
        {
            for (int index = 1; index < skeleton.Length; index++)
            {
                var foo = list_transforms[index + (i * skeleton.Length)];
                foo.parent += i * skeleton.Length;
                list_transforms[index + (i * skeleton.Length)] = foo;
            }
        }

        transforms = list_transforms.ToArray();







        jump_curves = new List<AnimationCurve>
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

        avatars = new List<Avatar>();

        for (int i = 0; i < avatar_count; i++)
        {
            Avatar new_avatar = new Avatar();
            new_avatar.current_animation = idle_curves;
            new_avatar.frame = 1;
            avatars.Add(new_avatar);
            transforms[i * skeleton.Length].rotation.y = 1 / 4f * Tau;
        }
    }

    public unsafe void Update()
    {
        fixed_framerate = true;

        //Zero Out Rotations
        for (int i = 1; i < transforms.Length; i++)
        {
            if (i % skeleton.Length == 0)
                continue;
            transforms[i].rotation = Vector3.Zero;
        }

        //Apply Character Controls
        {
            var first_curve_frames = avatars[0].current_animation[0].keyframes;
            var ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;
            var first_avatar = avatars[0];
            float move_speed = 6 * time_step;

            if (first_avatar.current_animation == idle_curves)
            {
                if (Input.KeyDown(Keys.A) || Input.KeyDown(Keys.D))
                {
                    first_avatar.current_animation = walk_curves;
                    first_avatar.frame = 1;
                }
            }
            else if (first_avatar.current_animation == walk_curves)
            {
                if (Input.KeyDown(Keys.A))
                {
                    transforms[0].rotation.y = -1 / 4f * Tau;
                    transforms[0].position.x -= move_speed;
                }
                else if (Input.KeyDown(Keys.D))
                {
                    transforms[0].rotation.y = 1 / 4f * Tau;
                    transforms[0].position.x += move_speed;
                }
                else
                {
                    first_avatar.current_animation = idle_curves;
                    first_avatar.frame = 1;
                }
            }
            else if (first_avatar.current_animation == punch_curves)
            {
                if (first_avatar.frame >= ending_frame)
                {
                    first_avatar.current_animation = idle_curves;
                    first_avatar.frame = 1;
                }
            }

            if (Input.KeyDown(Keys.Space) && avatars[0].current_animation != punch_curves)
            {
                first_avatar.current_animation = punch_curves;
                first_avatar.frame = 1;
            }
            avatars[0] = first_avatar;
        }

        for (int current_avatar_index = 0; current_avatar_index < avatar_count; current_avatar_index++)
        {
            var first_curve_frames = avatars[current_avatar_index].current_animation[0].keyframes;
            var ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;

            var current_avatar = avatars[current_avatar_index];
            if (current_avatar.frame >= ending_frame)
                current_avatar.frame = 1;


            float frame = avatars[current_avatar_index].frame;

            foreach (AnimationCurve curve in current_avatar.current_animation)
            {
                KeyFrame[] keyframes = curve.keyframes;
                int transform_index = curve.transform_index + current_avatar_index * skeleton.Length;

                fixed (void* p = &transforms[transform_index])
                {
                    float* f = (float*)p + 1 + curve.property_tag;
                    AnimateProperty(keyframes, frame, ref *f);
                }
            }

            current_avatar.frame++;

            avatars[current_avatar_index] = current_avatar;
        }


        //Render
        {
            graphics.Clear(Color.Black);

            //get camera matrix
            Transform inverted_camera = new Transform() { scale = Vector3.One };
            inverted_camera.position = -camera.position;
            inverted_camera.rotation = -camera.rotation;
            Matrix4x4 world_to_camera = GetMatrix(inverted_camera);
            Vector3[] positions = new Vector3[transforms.Length];

            //Draw Transforms
            {
                for (int i = 1; i < transforms.Length; i++)
                {
                    Matrix4x4 local_to_world = WorldSpaceMatrix(transforms[i], transforms);
                    Matrix4x4 local_to_camera = local_to_world * world_to_camera;

                    var position = TransformVector(local_to_camera, Vector3.Zero);

                    Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view);

                    var v4 = new Vector4(position.x, position.y, position.z, 1);
                    v4 = TransformVector(camera_to_clip, v4); //Projection

                    position = new Vector3(v4.x, v4.y, v4.z);

                    if (v4.w != 0)
                        position /= v4.w;

                    //place origin at center of screen
                    position.x++;
                    position.y++;

                    //scale space to fill screen
                    position.x *= WIDTH / 2;
                    position.y *= HEIGHT / 2;

                    positions[i] = position;
                }

                for (int i = 1; i < positions.Length; i++)
                {
                    var position = positions[i];
                    var parent_position = position;

                    if (transforms[i].parent != 0 && transforms[i].parent != -1)
                        parent_position = positions[transforms[i].parent];

                    float d = camera.position.z - position.z;
                    float width = 500 / (d);
                    float half_width = width / 2;

                    graphics.DrawLine(Pens.Purple, position.x, position.y, parent_position.x, parent_position.y);
                    graphics.DrawEllipse(Pens.Purple, position.x - half_width, position.y - half_width, width, width);
                }
            }

            //Draw Axes
            {
                Matrix4x4 camera_to_clip = Perspective(0.1f, 100, Tau / 4);

                var zero = TransformVector(world_to_camera, Vector3.Zero);
                var v4 = new Vector4(zero.x, zero.y, zero.z, 1);
                v4 = TransformVector(camera_to_clip, v4); //Projection
                zero = new Vector3(v4.x, v4.y, v4.z);

                if (v4.w != 0)
                    zero /= v4.w;

                //place origin at center of screen
                zero.x++;
                zero.y++;

                //scale space to fill screen
                zero.x *= WIDTH / 2;
                zero.y *= HEIGHT / 2;

                var right = TransformVector(world_to_camera, Vector3.Right);
                v4 = new Vector4(right.x, right.y, right.z, 1);
                v4 = TransformVector(camera_to_clip, v4); //Projection
                right = new Vector3(v4.x, v4.y, v4.z);

                if (v4.w != 0)
                    right /= v4.w;

                //place origin at center of screen
                right.x++;
                right.y++;

                //scale space to fill screen
                right.x *= WIDTH / 2;
                right.y *= HEIGHT / 2;

                var up = TransformVector(world_to_camera, Vector3.Up);
                v4 = new Vector4(up.x, up.y, up.z, 1);
                v4 = TransformVector(camera_to_clip, v4); //Projection
                up = new Vector3(v4.x, v4.y, v4.z);

                if (v4.w != 0)
                    up /= v4.w;

                //place origin at center of screen
                up.x++;
                up.y++;

                //scale space to fill screen
                up.x *= WIDTH / 2;
                up.y *= HEIGHT / 2;

                var forward = TransformVector(world_to_camera, Vector3.Forward);
                v4 = new Vector4(forward.x, forward.y, forward.z, 1);
                v4 = TransformVector(camera_to_clip, v4); //Projection
                forward = new Vector3(v4.x, v4.y, v4.z);

                if (v4.w != 0)
                    forward /= v4.w;

                //place origin at center of screen
                forward.x++;
                forward.y++;

                //scale space to fill screen
                forward.x *= WIDTH / 2;
                forward.y *= HEIGHT / 2;


                graphics.DrawLine(Pens.Green, zero.x, zero.y, up.x, up.y);
                graphics.DrawLine(Pens.Blue, zero.x, zero.y, forward.x, forward.y);
                graphics.DrawLine(Pens.Red, zero.x, zero.y, right.x, right.y);
            }
        }

        graphics.ResetTransform();
    }
}