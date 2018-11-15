using Engine;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

class Game
{
    static void Main() { new Game(); }
    
    //Resolution
    public const int PIXELS_PER_UNIT = 64;
    public const int WIDTH = 1024;
    public const int HEIGHT = 576;

    //GUI
    public static Form window = new Form();
    public static BufferedGraphics graphics_buffer;
    public static Graphics graphics;
    
    //Timing
    public static Stopwatch stopwatch = new Stopwatch();
    public const float TARGET_FRAMERATE = 60;
    public const float STANDARD_TIMESTEP = 1 / TARGET_FRAMERATE;
    public static float time_step;
    public static float time_since_last_frame;
    public static float delta_time;
    public static float frames_per_second;
    public static float portion_of_current_second_complete;
    public static int frames_since_last_second;
    public static bool fixed_framerate = false;
    public static float previous_time;

    //Input
    public static bool[] keys_down = new bool[256];
    public static bool[] keys_stale = new bool[256]; //whether a key has been pressed for more than one consecutive frame
    public static int[,] control_mappings = //each row represents a player's control scheme
    {
            {(int)Keys.A,       (int)Keys.D ,       (int)Keys.S,        (int)Keys.W,       (int)Keys.Q},
            {(int)Keys.J,       (int)Keys.L,        (int)Keys.K,        (int)Keys.I,       (int)Keys.U},
            {(int)Keys.Left,    (int)Keys.Right,    (int)Keys.Down,     (int)Keys.Up,      (int)Keys.Back},
            {(int)Keys.NumPad4, (int)Keys.NumPad6,  (int)Keys.NumPad5,  (int)Keys.NumPad8, (int)Keys.NumPad7}
    };

    IDemo demo;
    public static Transform[] transforms;

    Game()
    {
        //Setup Form
        {
            window.ClientSize = new Size(WIDTH, HEIGHT);
            window.FormBorderStyle = FormBorderStyle.FixedSingle;
            window.MaximizeBox = false;
        }

        //Initialize Graphics
        {
            graphics_buffer = BufferedGraphicsManager.Current.Allocate(window.CreateGraphics(), window.DisplayRectangle);
            graphics = graphics_buffer.Graphics;
        }

        //Bind Input
        {
            window.KeyDown += (s, e) => { keys_down[(int)e.KeyCode] = true; };
            window.KeyUp += (s, e) => { keys_down[(int)e.KeyCode] = false; keys_stale[(int)e.KeyCode] = false; };
        }
        
        //Start Game Loop
        {
            demo = new GameplayDemo();
            Application.Idle += GameLoop;
            Application.Run(window);
        }
    }


    void GameLoop(object sender, EventArgs e)
    {
        NativeMessage result;

        //while window is idling (i.e., while windows message queue is empty)
        while (PeekMessage(out result, IntPtr.Zero, 0, 0, 0) == 0)
        {
            demo.Update();
        }
    }

    //Imports a native Win32 function for checking the windows message queue
    [System.Runtime.InteropServices.DllImport("User32.dll")]
    static extern int PeekMessage(out NativeMessage message, IntPtr handle, uint filterMin, uint filterMax, uint remove);

    struct NativeMessage
    {
        IntPtr Handle;
        uint Message;
        IntPtr WParameter;
        IntPtr LParameter;
        uint Time;
        Point Location;
    }
}