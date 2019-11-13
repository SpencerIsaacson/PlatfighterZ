using Engine;
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using System.Media;
using System.Reflection;
using System.IO;

using static Game;
using static Engine.Global;

class TitleScreen : IGameState
{
    float opacity;
    float t;

    Font title_font = new Font(SystemFonts.DefaultFont.FontFamily, 98, FontStyle.Regular);
    Font small_font = new Font(SystemFonts.DefaultFont.FontFamily, 28, FontStyle.Regular);
    SoundPlayer player;
    bool started;
    public void Update()
    {
        if (!started)
        {
            started = true;
            Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("PlatfighterZ.Assets.chiptronical_short.wav");
            player = new SoundPlayer(stream);
            player.Play();
        }
        else
        {
            if (Input.KeyDownFresh(Keys.Space))
            {
                player.Stop();
                game_state_index++;
            }
            t += delta_time * 5;
            opacity = (float)((Math.Sin(t - Tau / 4) + 1) / 2);

            int half_width = WIDTH / 2;
            int half_height = HEIGHT / 2;
            graphics.Clear(Color.Black);
            graphics.SmoothingMode = SmoothingMode.HighQuality;
            graphics.DrawString("PlatfighterZ", title_font, Brushes.Indigo, half_width, half_height, centered_format);
            graphics.DrawString("press start", small_font, new SolidBrush(Color.FromArgb((int)(opacity * 255), 255, 255, 255)), half_width, HEIGHT - 50, centered_format);
        }
    }
}
