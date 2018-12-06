using Engine;
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using static Game;

class AnimationCurveTest : IDemo
{

    List<KeyFrame> key_frames = new List<KeyFrame>();

    public AnimationCurveTest()
    {
        for(int i = 1; i < 6; i ++)
        {
            key_frames.Add(new KeyFrame(){frame = i, value = 0, inTangent = new PointF(-.25f,2f), outTangent = new PointF(.25f,2f)});
        }

        var foo = key_frames[key_frames.Count-1];
        foo.value = 1;
        foo.inTangent.X = -.5f;
        foo.inTangent.Y = 0f;
        key_frames[key_frames.Count-1] = foo;

        foo = key_frames[0];
        foo.value = 1;
        key_frames[0] = foo;

        foo = key_frames[3];
        foo.inTangent = new PointF(-.25f, 0);
        foo.outTangent = new PointF(.25f, 0);
        foo.value = 2.5f;
        key_frames[3] = foo;
    }

    Pen pen = new Pen(Color.White, 2f);
    float width = 10f;
    float sample;
    float frame = 2f;
    float elapsed_time = 0f;

    public void Update()
    {
		if(!keys_down[(int)Keys.Space]) // if not paused
		{
		    elapsed_time += time_step;
			frame = 1 + elapsed_time % (6);

            for(int i = 0; i < key_frames.Count-1; i++)
            {
                KeyFrame a = key_frames[i];
                KeyFrame b = key_frames[i + 1];
                if (frame > a.frame && frame < b.frame)
                {
                    sample = Sample(a, b, frame);
                    break;
                }
            }
		}

        graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
        graphics.FillRectangle(Brushes.Black, window.ClientRectangle);
        graphics.DrawString(frame.ToString("F2") + ": " + sample.ToString(), Control.DefaultFont, Brushes.White, 0, 0);
        graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);

		//Draw Grid
		{
		    for (float x = -10; x <= 10; x+=.5f)
		    {
		        graphics.DrawLine(Pens.DarkGray, x * PIXELS_PER_UNIT, -10 * PIXELS_PER_UNIT, x * PIXELS_PER_UNIT, 10 * PIXELS_PER_UNIT);
		        graphics.DrawString(x.ToString(), Control.DefaultFont, Brushes.White, x * PIXELS_PER_UNIT + 1, 1);
		    }
		    for (float y = -10; y <= 10; y+=.5f)
		    {
		        graphics.DrawLine(Pens.DarkGray, -10 * PIXELS_PER_UNIT, y * PIXELS_PER_UNIT, 10 * PIXELS_PER_UNIT, y * PIXELS_PER_UNIT);
		        graphics.DrawString((-y).ToString(), Control.DefaultFont, Brushes.White, 1, y * PIXELS_PER_UNIT + 1);
		    }

		    graphics.DrawLine(new Pen(Color.LightGray, 3f), 0, -10 * PIXELS_PER_UNIT, 0, 10 * PIXELS_PER_UNIT);
		    graphics.DrawLine(new Pen(Color.LightGray, 3f), -10 * PIXELS_PER_UNIT, 0, 10 * PIXELS_PER_UNIT, 0);
		}

        graphics.ScaleTransform(1, -1);

        for(int i = 0; i < key_frames.Count-1; i++)
        {
            KeyFrame a = key_frames[i];
            KeyFrame b = key_frames[i + 1];
            PointF c1, c2, c3, c4;
            c1 = new PointF(a.frame * PIXELS_PER_UNIT, a.value * PIXELS_PER_UNIT);
            c2 = new PointF((a.frame + a.outTangent.X) * PIXELS_PER_UNIT, (a.value + a.outTangent.Y) * PIXELS_PER_UNIT);
            c3 = new PointF((b.frame + b.inTangent.X) * PIXELS_PER_UNIT, (b.value + b.inTangent.Y) * PIXELS_PER_UNIT);
            c4 = new PointF(b.frame * PIXELS_PER_UNIT, b.value * PIXELS_PER_UNIT);

            //DrawSpline
            {
                    pen.Color = Color.White;
                    graphics.DrawBezier(pen, c1, c2, c3, c4);
                    pen.Color = Color.Green;
                    graphics.DrawLine(pen, c1, c2);
                    pen.Color = Color.Blue;
                    graphics.DrawLine(pen, c3, c4);
                    graphics.FillEllipse(Brushes.White, c1.X - width / 2, c1.Y - width / 2, width, width);
                    graphics.FillEllipse(Brushes.Green, c2.X - width / 2, c2.Y - width / 2, width, width);
                    graphics.FillEllipse(Brushes.Blue, c3.X - width / 2, c3.Y - width / 2, width, width);
                    graphics.FillEllipse(Brushes.White, c4.X - width / 2, c4.Y - width / 2, width, width);
            }
        }

        //DrawFrameCursor        
        graphics.DrawLine(new Pen(Color.Red, 2f), frame * PIXELS_PER_UNIT, -HEIGHT/2, frame * PIXELS_PER_UNIT, HEIGHT/2);
        PointF sample_point = new PointF(frame * PIXELS_PER_UNIT, sample * PIXELS_PER_UNIT);
        graphics.FillEllipse(Brushes.Red, sample_point.X - width / 2, sample_point.Y - width / 2, width, width);
        
        graphics_buffer.Render();
        graphics.ResetTransform();
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
