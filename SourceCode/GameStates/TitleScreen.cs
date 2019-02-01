using Engine;
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using static Game;
using static Engine.Global;

class TitleScreen : IGameState
{
    float opacity;
    float t;
    public void Update()
    {
        if (Input.KeyDownFresh(Keys.Space))
            game_state_index++;

        t += time_step * 5;
        int half_width = WIDTH / 2;
        int half_height = HEIGHT / 2;
        graphics.Clear(Color.Black);
        graphics.SmoothingMode = SmoothingMode.AntiAlias;
        Font font = new Font(SystemFonts.DefaultFont.FontFamily, 98, FontStyle.Regular);
        Font font2 = new Font(SystemFonts.DefaultFont.FontFamily, 28, FontStyle.Regular);
        opacity = (float)((Math.Sin(t-Tau/4) + 1) / 2);

        StringFormat format = new StringFormat()
        {
            LineAlignment = StringAlignment.Center,
            Alignment = StringAlignment.Center,
        };

        LinearGradientBrush br = new LinearGradientBrush(window.ClientRectangle, Color.Black, Color.Black, 0, false);
        ColorBlend cb = new ColorBlend()
        {
            Positions = new[] { 0, 1 / 6f, 2 / 6f, 3 / 6f, 4 / 6f, 5 / 6f, 1 },
            Colors = new[] { Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Blue, Color.Indigo, Color.Violet },
        };
        br.InterpolationColors = cb;

        // rotate
        br.RotateTransform(45);


        graphics.FillRectangle(new LinearGradientBrush(new Point(0, 0), new Point(WIDTH, HEIGHT), Color.Black, Color.FromArgb(20, 0, 30)), window.ClientRectangle);
        graphics.DrawString("PlatfighterZ", font, br, half_width, half_height, format);
        graphics.DrawString("press start", font2, new SolidBrush(Color.FromArgb((int)(opacity * 255), 255, 255,255)), half_width, HEIGHT - 50, format);
    }
}
