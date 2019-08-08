using Engine;
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

using static Game;
using static Engine.Global;

class TitleScreen : IGameState
{
    int half_width = WIDTH / 2;
    int half_height = HEIGHT / 2;
    float opacity;
    float t;

    Font title_font = new Font(SystemFonts.DefaultFont.FontFamily, 98, FontStyle.Regular);
    Font small_font = new Font(SystemFonts.DefaultFont.FontFamily, 28, FontStyle.Regular);
    
    LinearGradientBrush brush;
    
    ColorBlend color_blend = new ColorBlend()
    {
        Positions = new[] { 0, 1 / 6f, 2 / 6f, 3 / 6f, 4 / 6f, 5 / 6f, 1 },
        Colors = new[] { Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Blue, Color.Indigo, Color.Violet },
    };

    
    public void Update()
    {
        if (Input.KeyDownFresh(Keys.Space))
            game_state_index++;

        t += time_step * 5;
        opacity = (float)((Math.Sin(t-Tau/4) + 1) / 2);
        
        brush = new LinearGradientBrush(window.ClientRectangle, Color.Black, Color.Black, 0, false);
        brush.InterpolationColors = color_blend;
        brush.RotateTransform(45);

        graphics.Clear(Color.Black);
        graphics.SmoothingMode = SmoothingMode.AntiAlias;
        graphics.FillRectangle(new LinearGradientBrush(new Point(0, 0), new Point(WIDTH, HEIGHT), Color.Black, Color.FromArgb(20, 0, 30)), window.ClientRectangle);
        graphics.DrawString("PlatfighterZ", title_font, brush, half_width, half_height, centered_format);
        graphics.DrawString("press start", small_font, new SolidBrush(Color.FromArgb((int)(opacity * 255), 255, 255,255)), half_width, HEIGHT - 50, centered_format);
    }
}
