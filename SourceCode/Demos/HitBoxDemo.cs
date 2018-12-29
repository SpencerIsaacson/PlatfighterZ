using Engine;
using System.Drawing;
using System.Windows.Forms;
using static Game;

class HitBoxDemo: IDemo
{
	float x1 = 0 , y1 = 0, x2 = 0, y2 = 0;
	public void Update()
	{
		if(KeyDown(Keys.D))
			x1++;		
		

		//Render
		{
			graphics.ResetTransform();
			graphics.FillRectangle(Brushes.Black, window.ClientRectangle);
			graphics.TranslateTransform(WIDTH / 2,HEIGHT / 2);
			graphics.DrawEllipse(Pens.Green, x1 - 32, y1 - 32, 64, 64);
			graphics.DrawEllipse(Pens.Green, x2 - 32, y2 - 32, 64, 64);
			graphics_buffer.Render();
		}
	}
}
