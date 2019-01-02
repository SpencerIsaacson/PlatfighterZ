using Engine;
using System;
using System.Drawing;
using System.Windows.Forms;
using static Game;

class HitBoxDemo: IDemo
{
	HitBox a = new HitBox(){ radius = 10 };
	HitBox b = new HitBox(){ radius = 32 };
	static Pen pen = new Pen(Color.White, 2f);
	
	public void Update()
	{
		var bar = 100 * time_step;
		var foo = 10 * time_step;

		if(KeyDown(Keys.D))
			a.position.x += bar;
		if(KeyDown(Keys.A))
			a.position.x -= bar;
		if(KeyDown(Keys.S))
			a.position.y += bar;
		if(KeyDown(Keys.W))
			a.position.y -= bar;
		if(KeyDown(Keys.Q))
			a.radius -= foo;
		if(KeyDown(Keys.E))
			a.radius += foo;
	
		//Render
		{
			var d = a.position - b.position;
			var distance = Math.Sqrt(d.x*d.x + d.y*d.y);
			pen.Color = (distance <= (a.radius + b.radius)) ? Color.Red : Color.Green;
			graphics.ResetTransform();
			graphics.Clear(Color.Black);

			graphics.TranslateTransform(WIDTH / 2,HEIGHT / 2);
			a.Draw();
			b.Draw();
			graphics_buffer.Render();
		}
	}

	struct HitBox
	{
		public Vector2 position;
		public float radius;
		
		public void Draw()
		{
			graphics.DrawEllipse(pen, position.x - radius, position.y - radius, radius * 2, radius * 2);
		}

	}
}
