using Engine;
using System.Drawing;
using System.Drawing.Imaging;
using System.Reflection;

using static Game;
using static Engine.Global;

class SplashScreen : IGameState
{
    bool splash_screen_started = false;
    bool splash_screen_ended = false;
    float splash_screen_time;
    float splash_screen_alpha;
    Bitmap logo = (Bitmap)Image.FromStream(GetAssetStream("VikingStudios.png"));

    public void Update()
    {
        if (splash_screen_time > 10)
        {
            if (!splash_screen_ended)
            {
                game_state_index++;
                splash_screen_ended = true;
            }
            else
            {
                splash_screen_time = 0;
                splash_screen_ended = false;
            }
        }

        if (!splash_screen_started)
        {
            System.Media.SoundPlayer player = new System.Media.SoundPlayer(GetAssetStream("preparations.wav"));
            player.Play();
            splash_screen_started = true;
        }

        ImageAttributes imageAttributes = new ImageAttributes();
        int width = logo.Width;
        int height = logo.Height;

        float[][] colorMatrixElements = {
                    new float[] {1,  0,  0,  0, 0},        // red scaling factor of 1
                    new float[] {0,  1,  0,  0, 0},        // green scaling factor of 1
                    new float[] {0,  0,  1,  0, 0},        // blue scaling factor of 1
                    new float[] {0,  0,  0,  splash_screen_alpha, 0},        // alpha scaling factor of 1
                    new float[] {0,  0,  0,  0, 1}};    // translations

        ColorMatrix colorMatrix = new ColorMatrix(colorMatrixElements);

        imageAttributes.SetColorMatrix(colorMatrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);

        graphics.Clear(Color.Black);
        graphics.DrawImage(logo, new Rectangle(0, 0, WIDTH, HEIGHT), 0, 0, 1920, 1080, GraphicsUnit.Pixel, imageAttributes);

        splash_screen_time += delta_time;
        if (splash_screen_time > 2 && splash_screen_time < 7 && splash_screen_alpha < .9)
            splash_screen_alpha += delta_time / 5;

        if (splash_screen_time > 8)
            splash_screen_alpha -= delta_time;

        if (splash_screen_alpha < 0)
            splash_screen_alpha = 0;
    }
}