using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Windows.Forms;


class Client
{
    int WIDTH = 1024;
    int HEIGHT = 576;
    bool maximized = false;
    uint[] pixels;

    Form window = new Form();
    BufferedGraphics buffered_graphics;
    Graphics graphics;

    GCHandle pixel_handle;
    Bitmap rendered_image;

    static void Main()
    {
        try
        {
            new Client();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            Console.ReadLine();
        }
    }

    Client()
    {
        //Setup Window
        {
            window.ClientSize = new Size(WIDTH, HEIGHT);
            window.FormBorderStyle = FormBorderStyle.FixedSingle;
            window.MaximizeBox = false;
            window.Text = "Platfighter Z";
        }

        window.KeyDown += (s, e) => { if (e.KeyCode == Keys.F4) ToggleFullScreen(); };
        InitGraphics();
        InitEverything();
        ToggleFullScreen();

        //Start Game Loop
        {
            Application.Idle += GameLoop;
            Application.Run(window);
        }
    }

    void GameLoop(object sender, EventArgs e)
    {
        while (WindowIsIdle())
        {
            GameLoop();
            OutputRender();
        }
    }

    bool WindowIsIdle() { return PeekMessage(out NativeMessage result, IntPtr.Zero, 0, 0, 0) == 0; }

    void ToggleFullScreen()
    {
        maximized = !maximized;
        if (maximized)
            ToFullScreenView();
        else
            ToWindowedView();
    }

    void ToFullScreenView() { SetClientState(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height, FormBorderStyle.None, FormWindowState.Maximized, Cursor.Hide); }

    void ToWindowedView() { SetClientState(1024, 576, FormBorderStyle.FixedSingle, FormWindowState.Normal, Cursor.Show); }

    void SetClientState(int width, int height, FormBorderStyle style, FormWindowState state, Action cursor_op)
    {
        WIDTH = width;
        HEIGHT = height;
        window.FormBorderStyle = style;
        window.WindowState = state;
        cursor_op();
        window.ClientSize = new Size(WIDTH, HEIGHT);
        buffered_graphics = BufferedGraphicsManager.Current.Allocate(window.CreateGraphics(), window.DisplayRectangle);
        graphics = buffered_graphics.Graphics;
        graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
        graphics.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceCopy;
    }

    void InitGraphics()
    {
        int width = 1920, height = 1080;
        pixels = new uint[width * height];
        pixel_handle = GCHandle.Alloc(pixels, GCHandleType.Pinned);
        rendered_image = new Bitmap(width, height, width * 4, PixelFormat.Format32bppPArgb, pixel_handle.AddrOfPinnedObject());

        InitViewport(width, height, pixels);
    }

    void OutputRender()
    {
        graphics.DrawImage(rendered_image, 0, 0, WIDTH, HEIGHT); //TODO find something faster than this to blit your renders to the window! Perhaps you can access the contents of the GDI drawing surface directly?
        buffered_graphics.Render();
    }

    [DllImport("SGL.dll")]
    static extern void InitViewport(int WIDTH, int HEIGHT, uint[] pixels);
    [DllImport("SGL.dll")]
    static extern void InitEverything();
    [DllImport("SGL.dll")]
    static extern unsafe void GameLoop();
    //Imports a native Win32 function for checking the windows message queue
    [DllImport("User32.dll")]
    static extern int PeekMessage(out NativeMessage message, IntPtr handle, uint filterMin, uint filterMax, uint remove);

    struct NativeMessage
    {
        public IntPtr Handle;
        public uint Message;
        public IntPtr WParameter;
        public IntPtr LParameter;
        public uint Time;
        public Point Location;
    }
}