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


    public void Update()
    {
        if (Input.KeyDownFresh(Keys.Space))
            game_state_index++;

        t += delta_time * 5;
        opacity = (float)((Math.Sin(t - Tau / 4) + 1) / 2);

        graphics.Clear(Color.Black);
        graphics.SmoothingMode = SmoothingMode.AntiAlias;
        graphics.FillRectangle(Brushes.Black, window.ClientRectangle);
        graphics.DrawString("PlatfighterZ", title_font, Brushes.Indigo, half_width, half_height, centered_format);
        graphics.DrawString("press start", small_font, new SolidBrush(Color.FromArgb((int)(opacity * 255), 255, 255, 255)), half_width, HEIGHT - 50, centered_format);
    }
}
