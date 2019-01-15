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
    Transform camera = new Transform() { position = new Vector3(0, 1, -20), scale = Vector3.One, rotation = new Vector3(0, 0, 0) };
    float field_of_view = 3/8f * Tau;
    
    Transform[] avatar;
    
    List<AnimationCurve> current_animation;

    List<AnimationCurve> walk_animation;
    List<AnimationCurve> punch_animation;
	List<AnimationCurve> idle_animation;
    List<AnimationCurve> jump_animation;

    List<Transform> my_transforms = new List<Transform>();

    public AvatarDemo()
    {        
        avatar = LoadHierarchy("Assets/avatar");
        
        for(int i = 0; i < 4; i ++)
        {
            my_transforms.AddRange(avatar);
        }
		transforms = avatar;

        walk_animation = new List<AnimationCurve>
		{
            new AnimationCurve()
            {
                transform_id = 1, //core 
                property_tag = "POSY",
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
                transform_id = 2, //chest 
                property_tag = "ROTY",
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
                transform_id = 4, //left shoulder 
                property_tag = "ROTZ",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/6 },
                    new KeyFrame {frame = 32, value = Tau/6 },
                },
            },  
            new AnimationCurve()
            {
                transform_id = 4, //left shoulder 
                property_tag = "ROTY",
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
                transform_id = 5, //left elbow 
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .5f },
                    new KeyFrame {frame = 60, value = .5f },
                },
            },                     
            new AnimationCurve()
            {
                transform_id = 6, //right shoulder 
                property_tag = "ROTZ",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/6 },
                    new KeyFrame {frame = 32, value = -Tau/6 },
                },
            }, 
            new AnimationCurve()
            {
                transform_id = 6, //right shoulder 
                property_tag = "ROTY",
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
                transform_id = 7, //right elbow 
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -.5f },
                    new KeyFrame {frame = 32, value = -.5f },
                },
            },                             
            new AnimationCurve()
            {
                transform_id = 8, //left hip 
                property_tag = "ROTX",
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
                transform_id = 9, //left knee 
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 16, value = .5f },
                    new KeyFrame {frame = 32, value = 0 },
                },
            },            
            new AnimationCurve()
            {
                transform_id = 11, //right hip 
                property_tag = "ROTX",
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
                transform_id = 12, //right knee 
                property_tag = "ROTX",
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

        punch_animation = new List<AnimationCurve>
		{
            new AnimationCurve()
            {
                transform_id = 1, //core 
                property_tag = "POSY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_id = 1, //core
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .3f },
                    new KeyFrame {frame = 30, value = .3f },
                },
            },            
            new AnimationCurve()
            {
                transform_id = 2, //chest
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .0f },
                    new KeyFrame {frame = 15, value = -.9f },
                    new KeyFrame {frame = 30, value = .0f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 4,
                property_tag = "ROTZ",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 4,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/6f },
                    new KeyFrame {frame = 15, value = -Tau/9f },
                    new KeyFrame {frame = 30, value = Tau/6f },
                },
            },            
            new AnimationCurve()
            {
                transform_id = 5,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/4f },
                },
            },  
            new AnimationCurve()
            {
                transform_id = 6,
                property_tag = "ROTZ",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 15, value = 0 },
                    new KeyFrame {frame = 30, value = -Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 6,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/6f },
                    new KeyFrame {frame = 15, value = -Tau/4 },
                    new KeyFrame {frame = 30, value = -Tau/6f },
                },
            },            
            new AnimationCurve()
            {
                transform_id = 7,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 15, value = 0 },
                    new KeyFrame {frame = 30, value = -Tau/4f },
                },
            },                                                 
            new AnimationCurve()
            {
                transform_id = 8,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 9,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0f },
                },
            },  
            new AnimationCurve()
            {
                transform_id = 11,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0.3f },
                    new KeyFrame {frame = 30, value = 0.3f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 12,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0f },
                },
            },                                         
		};

		idle_animation = new List<AnimationCurve>
		{
            new AnimationCurve()
            {
                transform_id = 1, //core 
                property_tag = "POSY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0 },
                    new KeyFrame {frame = 30, value = -.07f },
                    new KeyFrame {frame = 60, value = 0 },
                },
            },
            new AnimationCurve()
            {
                transform_id = 1, //core
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .3f },
                    new KeyFrame {frame = 60, value = .3f },
                },
            },            
            new AnimationCurve()
            {
                transform_id = 2, //chest
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = .0f },
                    new KeyFrame {frame = 30, value = .3f },
                    new KeyFrame {frame = 60, value = .0f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 4,
                property_tag = "ROTZ",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/5f },
                    new KeyFrame {frame = 60, value = Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 4,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/6f },
                    new KeyFrame {frame = 30, value = Tau/8f },
                    new KeyFrame {frame = 60, value = Tau/6f },
                },
            },            
            new AnimationCurve()
            {
                transform_id = 5,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = Tau/4f },
                    new KeyFrame {frame = 30, value = Tau/3f },
                    new KeyFrame {frame = 60, value = Tau/4f },
                },
            },  
            new AnimationCurve()
            {
                transform_id = 6,
                property_tag = "ROTZ",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 30, value = -Tau/5f },
                    new KeyFrame {frame = 60, value = -Tau/4f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 6,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/6f },
                    new KeyFrame {frame = 30, value = -Tau/8f },
                    new KeyFrame {frame = 60, value = -Tau/6f },
                },
            },            
            new AnimationCurve()
            {
                transform_id = 7,
                property_tag = "ROTY",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -Tau/4f },
                    new KeyFrame {frame = 30, value = -Tau/3f },
                    new KeyFrame {frame = 60, value = -Tau/4f },
                },
            },                                                 
            new AnimationCurve()
            {
                transform_id = 8,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = -0.3f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 9,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0.6f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },  
            new AnimationCurve()
            {
                transform_id = 11,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0.3f },
                    new KeyFrame {frame = 30, value = 0.0f },
                    new KeyFrame {frame = 60, value = 0.3f },
                },
            },
            new AnimationCurve()
            {
                transform_id = 12,
                property_tag = "ROTX",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = 0f },
                    new KeyFrame {frame = 30, value = 0.6f },
                    new KeyFrame {frame = 60, value = 0f },
                },
            },                                         
		};

		jump_animation = new List<AnimationCurve>
		{
            new AnimationCurve()
            {
                transform_id = 1, //core 
                property_tag = "POSY",
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
                transform_id = 8,
                property_tag = "ROTX",
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
                transform_id = 9,
                property_tag = "ROTX",
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
                transform_id = 11,
                property_tag = "ROTX",
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
                transform_id = 12,
                property_tag = "ROTX",
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
                transform_id = 4,
                property_tag = "ROTZ",
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
                transform_id = 6,
                property_tag = "ROTZ",
                keyframes = new KeyFrame[]
                {
                    new KeyFrame {frame = 01, value = -1/4f*Tau },
                    new KeyFrame {frame = 30, value = -1/8f*Tau },
                    new KeyFrame {frame = 40, value = -1/4f*Tau },                    
                    new KeyFrame {frame = 60, value = -1/4f*Tau },
                },
            },                                                        
        };

        current_animation = idle_animation;

        avatar[0].rotation.y = 1/4f * Tau;
    }

    float frame = 1;

    public void Update()
    {
        var first_curve_frames = current_animation[0].keyframes;
		var ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;
        
        fixed_framerate = true;

        //Zero Out Rotations
        for(int i = 1; i < avatar.Length; i++)
        {
            avatar[i].rotation = Vector3.Zero;
        }

        //Apply Character Controls
        {
            float move_speed = 6 * time_step;
            
            if(current_animation == idle_animation)
            {
                if(KeyDown(Keys.A) || KeyDown(Keys.D))
                {
                    current_animation = walk_animation;
                    frame = 1;
                }               
            }
            else if(current_animation == walk_animation)
            {
                if(KeyDown(Keys.A))
                {
                    avatar[0].rotation.y = -1/4f * Tau;
                    avatar[0].position.x -= move_speed;
                }
                else if(KeyDown(Keys.D))
                {
                    avatar[0].rotation.y = 1/4f * Tau;
                    avatar[0].position.x += move_speed;
                }
                else
                {
                    current_animation = idle_animation;
                    frame = 1;
                }              
            }          
            else if(current_animation == punch_animation)
            {
                if(frame >= ending_frame)
                {
                    current_animation = idle_animation;
                    frame = 1;
                }
            }

            if(KeyDown(Keys.Space) && current_animation != punch_animation)
            {
                current_animation = punch_animation;
                frame = 1;
            } 
        }

        
		if(frame >= ending_frame)
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


        frame++;

        //Render
        {
            graphics.Clear(Color.Black);
            
            //get camera matrix
            Transform inverted_camera = new Transform(){scale = Vector3.One};
            inverted_camera.position = -camera.position;
            inverted_camera.rotation = -camera.rotation;
            Matrix4x4 world_to_camera = GetMatrix(inverted_camera);
            Vector3[] positions = new Vector3[avatar.Length];
            
            //Draw Transforms
            { 
                for (int i = 1; i < avatar.Length; i++)
                {
                    Matrix4x4 local_to_world = WorldSpaceMatrix(avatar[i]);
                    Matrix4x4 local_to_camera = local_to_world.Concat(world_to_camera);

                    var position = TransformVector(local_to_camera, Vector3.Zero);

                    Matrix4x4 camera_to_clip = Perspective(0.1f,100,field_of_view);

                    var v4 = new Vector4(position.x, position.y, position.z, 1);
                    v4 = TransformVector(camera_to_clip, v4); //Projection
                    
                    position = new Vector3(v4.x,v4.y, v4.z);
                    
                    if(v4.w != 0)
                        position /= v4.w;

                    //place origin at center of screen
                    position.x++;
                    position.y++;

                    //scale space to fill screen
                    position.x *= WIDTH / 2;
                    position.y *= HEIGHT / 2;

                    positions[i] = position;
                }

                for(int i = 1; i < positions.Length; i++)
                {
                    var position = positions[i];
                    var parent_position = position;

                    if(avatar[i].parent != 0 && avatar[i].parent != -1)
                        parent_position = positions[avatar[i].parent];
                    
                    float d = camera.position.z - position.z;
                    float width =  500/(d);
                    float half_width = width / 2;
                    
                    graphics.DrawLine(Pens.Purple, position.x,position.y,parent_position.x,parent_position.y);
                    graphics.DrawEllipse(Pens.Purple, position.x - half_width, position.y-half_width, width, width);
                }
            }

            //Draw Axes
            {
                Matrix4x4 camera_to_clip = Perspective(0.1f,100,Tau/4);
                    
                var zero = TransformVector(world_to_camera, Vector3.Zero);
                var v4 = new Vector4(zero.x, zero.y, zero.z, 1);
                v4 = TransformVector(camera_to_clip, v4); //Projection
                zero = new Vector3(v4.x,v4.y, v4.z);
                
                if(v4.w != 0)
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
                right = new Vector3(v4.x,v4.y, v4.z);
                
                if(v4.w != 0)
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
                up = new Vector3(v4.x,v4.y, v4.z);
                
                if(v4.w != 0)
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
                forward = new Vector3(v4.x,v4.y, v4.z);
                
                if(v4.w != 0)
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
		graphics_buffer.Render();
    }



    struct AnimationCurve
    {
        public int transform_id;
        public string property_tag;
        public KeyFrame[] keyframes;
    }
}