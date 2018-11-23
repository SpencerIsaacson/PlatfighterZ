using Engine;
using System.Drawing;

using static Game;
using System.Windows.Forms;
using System;

class AnimationCurveDemo : IDemo
{
    KeyFrame a;
    KeyFrame b;

    public AnimationCurveDemo()
    {
        a = new KeyFrame() { frame = 1, value = 0, outTangent = new PointF(.1f, 1) };
        b = new KeyFrame() { frame = 3, value = 0, inTangent = new PointF(.1f, 1) };
    }

    Pen pen = new Pen(Color.White, 2f);
    float width = 10f;
    float sample;
    float frame = 2f;
    float timer = 0f;
	float radius = 0.8f;
    public void Update()
    {
		a.outTangent = new PointF((float)Math.Cos(timer)*radius,(float)Math.Sin(timer)*radius);
		b.inTangent = new PointF((float)Math.Cos(timer+.1f)*radius,(float)Math.Sin(timer+.1f)*radius);
        timer += 0.1f;
		radius+=.01f;

        sample = Sample(a, b, frame);
        graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
        graphics.FillRectangle(Brushes.Black, window.ClientRectangle);
        graphics.DrawString(frame.ToString("F2") + ": " + sample.ToString(), Control.DefaultFont, Brushes.White, 0, 0);
        graphics.TranslateTransform(window.ClientSize.Width / 2, window.ClientSize.Height / 2);

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


        graphics.ScaleTransform(1, -1);

        PointF c1, c2, c3, c4;
        c1 = new PointF(a.frame * PIXELS_PER_UNIT, a.value * PIXELS_PER_UNIT);
        c2 = new PointF((a.frame + a.outTangent.X) * PIXELS_PER_UNIT, (a.value + a.outTangent.Y) * PIXELS_PER_UNIT);
        c3 = new PointF((b.frame + b.inTangent.X) * PIXELS_PER_UNIT, (b.value + b.inTangent.Y) * PIXELS_PER_UNIT);
        c4 = new PointF(b.frame * PIXELS_PER_UNIT, b.value * PIXELS_PER_UNIT);

        float range = (b.frame - a.frame);
        float frames_in = (frame - a.frame);
        float t = frames_in / range;

        PointF d = Lerp(c1, c2, t);
        PointF e = Lerp(c2, c3, t);
        PointF f = Lerp(c3, c4, t);

        PointF h = Lerp(d, e, t);
        PointF i = Lerp(e, f, t);

        PointF j = Lerp(h, i, t);

        if (Game.keys_down[(int)Keys.A])
        {
            //DrawDebugLattice
            {
                graphics.DrawLine(Pens.Yellow, c1, c2);
                graphics.DrawLine(Pens.Yellow, c2, c3);
                graphics.DrawLine(Pens.Yellow, c3, c4);
                graphics.DrawLine(Pens.Yellow, d, e);
                graphics.DrawLine(Pens.Yellow, e, f);
                graphics.DrawLine(Pens.Yellow, h, i);
                graphics.FillEllipse(Brushes.Yellow, d.X - width / 2, d.Y - width / 2, width, width);
                graphics.FillEllipse(Brushes.Yellow, e.X - width / 2, e.Y - width / 2, width, width);
                graphics.FillEllipse(Brushes.Yellow, f.X - width / 2, f.Y - width / 2, width, width);
                graphics.FillEllipse(Brushes.Yellow, h.X - width / 2, h.Y - width / 2, width, width);
                graphics.FillEllipse(Brushes.Yellow, i.X - width / 2, i.Y - width / 2, width, width);
                graphics.FillEllipse(Brushes.Yellow, j.X - width / 2, j.Y - width / 2, width, width);
            }
        }

        pen.Color = Color.White;
        graphics.DrawBezier(pen, c1, c2, c3, c4);
        pen.Color = Color.Red;
        graphics.DrawLine(pen, c1, c2);
        pen.Color = Color.Blue;
        graphics.DrawLine(pen, c3, c4);


        graphics.FillEllipse(Brushes.White, c1.X - width / 2, c1.Y - width / 2, width, width);
        graphics.FillEllipse(Brushes.White, c4.X - width / 2, c4.Y - width / 2, width, width);
        graphics.FillEllipse(Brushes.Red, c2.X - width / 2, c2.Y - width / 2, width, width);
        graphics.FillEllipse(Brushes.Blue, c3.X - width / 2, c3.Y - width / 2, width, width);
        graphics.DrawLine(Pens.Red, frame * PIXELS_PER_UNIT, 0, frame * PIXELS_PER_UNIT, 10 * PIXELS_PER_UNIT);

        graphics_buffer.Render();
        graphics.ResetTransform();
		System.Threading.Thread.Sleep(2000);
    }

    public struct KeyFrame
    {
        public int frame;
        public float value;
        public PointF inTangent;
        public PointF outTangent;
    }

    float Sample(KeyFrame a, KeyFrame b, float frame)
    {
        float range = (b.frame - a.frame);
        float t = .5f;
		float step = .25f;
		PointF j;

		int iterations_run = 0;
		while(true)
		{
			PointF c1 = new PointF(a.frame, a.value);
			PointF c2 = new PointF(a.frame + a.outTangent.X * range, a.value + a.outTangent.Y);
			PointF c3 = new PointF(b.frame + b.inTangent.X * range, b.value + b.inTangent.Y);
			PointF c4 = new PointF(b.frame, b.value);

			PointF d = Lerp(c1, c2, t);
			PointF e = Lerp(c2, c3, t);
			PointF f = Lerp(c3, c4, t);

			PointF h = Lerp(d, e, t);
			PointF i = Lerp(e, f, t);

			j = Lerp(h, i, t);
			
			var difference = Math.Abs(j.X-frame);
			//Console.WriteLine(difference);
			if(difference < .00001f)
			{
				Console.WriteLine("Converged in " + iterations_run + " iterations. T: " + t);
				break;
			}
			else if(j.X > frame)
				t -= step;
			else
				t += step;
			
			step /= 2;

			if(++iterations_run > 100)
			{
				Console.WriteLine("Taking too long to compute sample");
				break;
			}
		}

        return j.Y;
    }

    PointF Lerp(PointF a, PointF b, float t)
    {
        return new PointF(Lerp(a.X, b.X, t), Lerp(a.Y, b.Y, t));
    }

    float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }
}
