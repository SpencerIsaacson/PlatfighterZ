﻿using Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using static Game;

class AvatarDemo : IDemo
{

	//Transform hierarchy and all animation curves are currently hardcoded, will soon be creating a more general solution
    Transform[] avatar;
    List<KeyFrame> root_position_x_curve = new List<KeyFrame>();
    List<KeyFrame> hip_position_y_curve = new List<KeyFrame>();
    List<KeyFrame> torso_rotation_y_curve = new List<KeyFrame>();
    List<KeyFrame> posiition_y_curve = new List<KeyFrame>();
    List<KeyFrame> left_arm_rotation_curve = new List<KeyFrame>();
    List<KeyFrame> right_arm_rotation_curve = new List<KeyFrame>();
    List<KeyFrame> left_leg_rotation_curve = new List<KeyFrame>();
    List<KeyFrame> right_leg_rotation_curve = new List<KeyFrame>();
    List<KeyFrame> left_knee_rotation_curve = new List<KeyFrame>();
    List<KeyFrame> right_knee_rotation_curve = new List<KeyFrame>();

    public AvatarDemo()
    {
        avatar = new Transform[16];
        transforms = avatar;

        for (int i = 0; i < avatar.Length; i++)
        {
            avatar[i].scale = new Vector3(1, 1, 1);
        }

        avatar[1].position = new Vector3(0, 1, 0); //waist
        avatar[2].position = new Vector3(0, .8f, 0); //neck
        avatar[3].position = new Vector3(0, .3f, 0); //head
        avatar[4].position = new Vector3(-.4f, 0, 0); //right shoulder
        avatar[5].position = new Vector3(-.3f, 0, 0); //right elbow
        avatar[6].position = new Vector3(.4f, 0, 0); //left shoulder
        avatar[7].position = new Vector3(.3f, 0, 0); //left elbow
        avatar[8].position = new Vector3(-.2f, 0, 0); //right leg
        avatar[9].position = new Vector3(0, -.5f, 0); //right knee
        avatar[10].position = new Vector3(0, -.5f, 0); //right foot
        avatar[11].position = new Vector3(.2f, 0, 0); //left leg
        avatar[12].position = new Vector3(0, -.5f, 0); //left knee
        avatar[13].position = new Vector3(0, -.5f, 0); //left foot
        avatar[14].position = new Vector3(-.4f, 0, 0); //right wrist
        avatar[15].position = new Vector3(.4f, 0, 0); //left wrist

		avatar[15].parent = 8;
		avatar[14].parent = 6;
        avatar[13].parent = 13;
        avatar[12].parent = 12;
        avatar[11].parent = 2;
        avatar[10].parent = 10;
        avatar[9].parent = 9;
        avatar[8].parent = 2;
        avatar[7].parent = 7;
        avatar[6].parent = 3;
        avatar[5].parent = 5;
        avatar[4].parent = 3;
        avatar[3].parent = 3;
        avatar[2].parent = 2;
        avatar[1].parent = 1;

        avatar[0].rotation.y = (float)-Math.PI / 2;
		avatar[4].rotation.z = -1.4f;
		avatar[5].rotation.y = -.4f;
		avatar[6].rotation.z = 1.4f;
		avatar[7].rotation.y = .4f;

		root_position_x_curve = new List<KeyFrame>()
		{
        	new KeyFrame { frame = 1, value = -5, inTangent = new PointF(-.25f,-.25f), outTangent = new PointF(.25f,.25f)},
        	new KeyFrame { frame = 61, value = 5, inTangent = new PointF(-.25f,-.25f), outTangent = new PointF(.25f,.25f)},
		};

		left_leg_rotation_curve = new List<KeyFrame>()
		{
			new KeyFrame { frame = 1, value = -.75f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 21, value = 1.2f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 41, value = -.75f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 61, value = 1.2f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
		};

		right_leg_rotation_curve = new List<KeyFrame>()
		{
			new KeyFrame { frame = 1, value = 1.2f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 21, value = -.75f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 41, value = 1.2f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 61, value = -.75f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
		};

		left_knee_rotation_curve = new List<KeyFrame>()
		{
			new KeyFrame { frame = 1, value = 0f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 21, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 41, value = 0f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 61, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
		};

		right_knee_rotation_curve = new List<KeyFrame>()
		{
			new KeyFrame { frame = 1, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 21, value = 0, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 41, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
			new KeyFrame { frame = 61, value = 0, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
		};

        hip_position_y_curve = new List<KeyFrame>()
        {
            new KeyFrame { frame = 1, value = .5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 11, value = 1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 21, value = .5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 31, value = 1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 41, value = .5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 51, value = 1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 61, value = .5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
        };

        torso_rotation_y_curve = new List<KeyFrame>()
        {
            new KeyFrame { frame = 1, value = .5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 21, value = -.5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 41, value = .5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 61, value = -.5f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
        };

        left_arm_rotation_curve = new List<KeyFrame>()
        {
            new KeyFrame { frame = 1, value = 1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 21, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 41, value = 1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 61, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
        };

        right_arm_rotation_curve = new List<KeyFrame>()
        {
            new KeyFrame { frame = 1, value = 1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 21, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 41, value = 1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
            new KeyFrame { frame = 61, value = -1f, inTangent = new PointF(-.25f,0), outTangent = new PointF(.25f,0)},
        };
    }

    float frame = 1;
    public void Update()
    {
		float delta = 0;
		if(keys_down[(int)Keys.A])
			delta = -time_step;
		else if(keys_down[(int)Keys.D])
			delta = time_step;
		
		delta *= 5;
        frame++;

        if(frame >= 61)
            frame = 1;

        animate_property(root_position_x_curve, out avatar[0].position.x);
        animate_property(posiition_y_curve, out avatar[0].position.y);
        animate_property(left_leg_rotation_curve, out avatar[11].rotation.x);
        animate_property(right_leg_rotation_curve, out avatar[8].rotation.x);
        animate_property(hip_position_y_curve, out avatar[1].position.y);
        animate_property(torso_rotation_y_curve, out avatar[2].rotation.y);
        animate_property(left_arm_rotation_curve, out avatar[6].rotation.y);
        animate_property(right_arm_rotation_curve, out avatar[4].rotation.y);
        animate_property(left_knee_rotation_curve, out avatar[12].rotation.x);
        animate_property(right_knee_rotation_curve, out avatar[9].rotation.x);

        graphics.FillRectangle(Brushes.Black, window.ClientRectangle);
        
        //Draw Entities
        {
            graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
            graphics.ScaleTransform(1, -1);

            //Draw Transforms
            for (int i = 1; i < avatar.Length; i++)
            {
                var position = Matrix4x4.TransformVector(Matrix4x4.WorldSpaceMatrix(avatar[i]), new Vector3());
                var d = .75f - position.z / 10f;
                graphics.DrawEllipse(Pens.Blue, position.x / d * PIXELS_PER_UNIT, position.y / d * PIXELS_PER_UNIT, PIXELS_PER_UNIT / (d * 8), PIXELS_PER_UNIT / (d * 8));
            }

        }


        graphics.ResetTransform();
        graphics.DrawString(frame.ToString(),Control.DefaultFont,Brushes.White,0,0);
    }

    void animate_property(List<KeyFrame> curve, out float property)
    {
        for(int i = 0; i < curve.Count-1; i++)
        {
            KeyFrame a = curve[i];
            KeyFrame b = curve[i + 1];
            if (frame >= a.frame && frame <= b.frame)
            {
                property = Sample(a, b, frame);
                return;
            }
        }

        property = 0;
    }

    public struct KeyFrame
    {
        public float frame;
        public float value;
        public PointF inTangent;
        public PointF outTangent;
    }

    float Sample(KeyFrame a, KeyFrame b, float frame)
    {
        float t = .5f;
        float step = .25f;
        PointF c1 = new PointF(a.frame, a.value);
        PointF c2 = new PointF(a.frame + a.outTangent.X, a.value + a.outTangent.Y);
        PointF c3 = new PointF(b.frame + b.inTangent.X, b.value + b.inTangent.Y);
        PointF c4 = new PointF(b.frame, b.value);

        while(true)
        {
            PointF d = Lerp(c1, c2, t);
            PointF e = Lerp(c2, c3, t);
            PointF f = Lerp(c3, c4, t);
            PointF g = Lerp(d, e, t);
            PointF h = Lerp(e, f, t);
            PointF i = Lerp(g, h, t);

            if(i.X > frame) 
                t -= step;
            else 
                t += step;
            
            step /= 2;

            if(Math.Abs(i.X - frame) < .001f)
                return i.Y;
        }
    }

    PointF Lerp(PointF a, PointF b, float t)
    {
        float x = a.X + t * (b.X - a.X);
        float y = a.Y + t * (b.Y - a.Y);
        return new PointF(x,y);
    }

    float Lerp(float a,float b, float t)
    {
        return a + t * (b - a);
    }
}
