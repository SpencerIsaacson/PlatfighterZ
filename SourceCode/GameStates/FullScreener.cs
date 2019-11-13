using Engine;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using static Game;

class FullScreener : IGameState
{
    static bool maximized = false;
    public static uint[] pixels = new uint[WIDTH * HEIGHT];
    public static Bitmap rendered_image;

    static GCHandle pixel_handle;

    public FullScreener()
    {
        pixel_handle = GCHandle.Alloc(pixels, GCHandleType.Pinned);
        rendered_image = new Bitmap(WIDTH, HEIGHT, WIDTH * 4, PixelFormat.Format32bppPArgb, pixel_handle.AddrOfPinnedObject());
    }

    public void Update()
    {
        ToFullScreenView();
        game_state_index++;
    }

    public static void ToggleFullScreen()
    {
        maximized = !maximized;
        if (maximized)
            ToFullScreenView();
        else
            ToWindowedView();
    }

    public static void ToFullScreenView()
    {
        WIDTH = Screen.PrimaryScreen.Bounds.Width;
        HEIGHT = Screen.PrimaryScreen.Bounds.Height;
        window.FormBorderStyle = FormBorderStyle.None;
        window.WindowState = FormWindowState.Maximized;
        ReinitializeGraphics();
    }


    public static void ToWindowedView()
    {
        WIDTH = 1024;
        HEIGHT = 576;
        window.FormBorderStyle = FormBorderStyle.FixedSingle;
        window.WindowState = FormWindowState.Normal;
        ReinitializeGraphics();
    }


    public static void ReinitializeGraphics()
    {
        window.ClientSize = new Size(WIDTH, HEIGHT);
        pixels = new uint[WIDTH * HEIGHT];
        pixel_handle.Free();
        pixel_handle = GCHandle.Alloc(pixels, GCHandleType.Pinned);
        rendered_image = new Bitmap(WIDTH, HEIGHT, WIDTH * 4, PixelFormat.Format32bppPArgb, pixel_handle.AddrOfPinnedObject());
        buffered_graphics = BufferedGraphicsManager.Current.Allocate(window.CreateGraphics(), window.DisplayRectangle);
        graphics = buffered_graphics.Graphics;
    }
}
