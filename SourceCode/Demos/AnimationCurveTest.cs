using Engine;
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using static Engine.Global;
using static Game;

class AnimationCurveTest : IDemo
{

    List<KeyFrame> key_frames = new List<KeyFrame>();

    public AnimationCurveTest()
    {
        for(int i = 1; i < 6; i ++)
        {
            key_frames.Add(new KeyFrame { frame = i, value = 0, left_handle_x = -.25f,  left_handle_y = 2f, right_handle_x = .25f,right_handle_y = 2f });
        }

        var foo = key_frames[key_frames.Count-1];
        foo.value = 1;
        foo.left_handle_x = -.5f;
        foo.left_handle_y = 0f;
        key_frames[key_frames.Count-1] = foo;

        foo = key_frames[0];
        foo.value = 1;
        key_frames[0] = foo;

        foo = key_frames[3];
        foo.left_handle_x = -.25f;
        foo.left_handle_y = 0;
        foo.right_handle_x = .25f;
        foo.right_handle_y = 0;
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
			AnimateProperty(key_frames.ToArray(), frame, out sample);
		}

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
            c2 = new PointF((a.frame + a.right_handle_x) * PIXELS_PER_UNIT, (a.value + a.right_handle_y) * PIXELS_PER_UNIT);
            c3 = new PointF((b.frame + b.left_handle_x) * PIXELS_PER_UNIT, (b.value + b.left_handle_y) * PIXELS_PER_UNIT);
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
}
