using Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using static Engine.Global;
using static Game;

class AvatarDemo : IDemo
{	
    Transform[] avatar;
    
    List<AnimationCurve> current_animation;

    List<AnimationCurve> walk_animation;
    List<AnimationCurve> punch_animation;

    public AvatarDemo()
    {
        avatar = LoadHierarchy("Assets/avatar");
        transforms = avatar;

        walk_animation = new List<AnimationCurve>();
        using (BinaryReader reader = new BinaryReader(File.Open("Assets/walk", FileMode.Open)))
        {
            while(reader.BaseStream.Position < reader.BaseStream.Length)
            {
                AnimationCurve curve = new AnimationCurve();
                curve.transform_id = reader.ReadInt32();
                curve.property_tag = new string(reader.ReadChars(4));
                
                List<KeyFrame> keyframes = new List<KeyFrame>();
                int number_of_keyframes = reader.ReadInt32();

                for(int i = 0; i < number_of_keyframes; i++)
                {
                    KeyFrame keyframe = new KeyFrame()
                    {
                        frame = reader.ReadSingle(),
                        value = reader.ReadSingle(),
                        left_handle_x = reader.ReadSingle(),
                        left_handle_y = reader.ReadSingle(),
                        right_handle_x = reader.ReadSingle(),
                        right_handle_y = reader.ReadSingle(),
                    };

                    keyframes.Add(keyframe);
                }

                curve.keyframes = keyframes.ToArray();
                walk_animation.Add(curve);
            }
        }

        punch_animation = new List<AnimationCurve>()
        {
            new AnimationCurve()
            {
                transform_id = 1,
                property_tag = "POSY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 1, value = 0 },
                    new KeyFrame {frame = 40, value = -0.1f },
                    new KeyFrame {frame = 60, value = -0.1f },
                    new KeyFrame {frame = 75, value = 0.3f },
                    new KeyFrame {frame = 80, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_id = 1,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 1, value = 0 },
                    new KeyFrame {frame = 55, value = 0.4f },
                    new KeyFrame {frame = 75, value = 0f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 2,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 1, value = 0 },
                    new KeyFrame {frame = 50, value = 0.7f },
                    new KeyFrame {frame = 70, value = -0.8f },
                    new KeyFrame {frame = 80, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_id = 4,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 1, value = 0 },
                    new KeyFrame {frame = 50, value = 1.7f },
                    new KeyFrame {frame = 70, value = -1.8f },
                    new KeyFrame {frame = 80, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_id = 8,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 1, value = 0 },
                    new KeyFrame {frame = 30, value = -0.4f },
                    new KeyFrame {frame = 80, value = -0.4f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 11,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 1, value = 0 },
                    new KeyFrame {frame = 20, value = 0.4f },
                    new KeyFrame {frame = 80, value = 0.4f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 12,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 1, value = 0 },
                    new KeyFrame {frame = 20, value = -0.3f },
                    new KeyFrame {frame = 80, value = -0.3f },
                },
            },            
        };

        current_animation = walk_animation;
    }

    struct AnimationCurve
    {
        public int transform_id;
        public string property_tag;
        public KeyFrame[] keyframes;
    }

    float frame = 1;
	float rotation = 0;
	
    public void Update()
    {
        frame++;

        if(frame >= 43)//current_animation[0].keyframes[current_animation[0].keyframes.Length-1].frame)
            frame = 1;

        foreach(AnimationCurve curve in current_animation)
        {
            var keyframes = curve.keyframes;

            switch(curve.property_tag)
            {
                case "POSX":
                    AnimateProperty(keyframes, frame, out avatar[curve.transform_id].position.x);
                    break;
                case "POSY":
                    AnimateProperty(keyframes, frame, out avatar[curve.transform_id].position.y);
                    break;
                case "POSZ":
                    AnimateProperty(keyframes, frame, out avatar[curve.transform_id].position.z);
                    break;                    
                case "ROTX":
                    AnimateProperty(keyframes, frame, out avatar[curve.transform_id].rotation.x);
                    break;
                case "ROTY":
                    AnimateProperty(keyframes, frame, out avatar[curve.transform_id].rotation.y);
                    break;
                case "ROTZ":
                    AnimateProperty(keyframes, frame, out avatar[curve.transform_id].rotation.z);
                    break;                    
            }
        }

		rotation += time_step;
		avatar[0].position.x = 0;
		avatar[1].rotation.y = rotation;

        graphics.FillRectangle(Brushes.Black, window.ClientRectangle);
        
        //Draw Entities
        {
			graphics.DrawString(avatar[1].rotation.y.ToString(), Control.DefaultFont, Brushes.White, 128, 0);
            graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
            graphics.ScaleTransform(1, -1);

            //Draw Transforms
            for (int i = 1; i < avatar.Length; i++)
            {
                var position = TransformVector(WorldSpaceMatrix(avatar[i]), new Vector3());
                var d = .75f - position.z / 10f;
                graphics.DrawEllipse(Pens.Blue, position.x / d * PIXELS_PER_UNIT, position.y / d * PIXELS_PER_UNIT, PIXELS_PER_UNIT / (d * 8), PIXELS_PER_UNIT / (d * 8));
            }
        }

        graphics.ResetTransform();
        graphics.DrawString(frame.ToString(),Control.DefaultFont,Brushes.White,0,0);
		graphics_buffer.Render();
    }
}
