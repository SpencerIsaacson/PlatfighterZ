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
    public static int PIXELS_PER_UNIT = 64;
    public static int WIDTH = 1024;
    public static int HEIGHT = 576;

    //GUI
    public static Form window = new Form();
    public static BufferedGraphics graphics_buffer;
    public static Graphics graphics;

    //Timing
    public static Stopwatch stopwatch = new Stopwatch();
    public static bool fixed_framerate = false;
    public static float TARGET_FRAMERATE = 60;
    public static float STANDARD_TIMESTEP = 1 / TARGET_FRAMERATE;
    public static float time_step;
    public static float delta_time;
    public static float frames_per_second;
    public static float portion_of_current_second_complete;
    public static int frames_since_last_second;
    public static float previous_time;

    //Inputasdfasdfasdf
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
	IDemo[] demos = new IDemo[]{new GameplayDemo(), new AvatarDemo(), new AnimationCurveTest()};
	int demo_index;
    public static Transform[] transforms;

    Game()
    {
        //Setup Window
        {
            window.ClientSize = new Size(WIDTH, HEIGHT);
            window.FormBorderStyle = FormBorderStyle.FixedSingle;
            window.MaximizeBox = false;
			window.Text = "Platfighter Z";
        }

        //Initialize Graphics
        {
            graphics_buffer = BufferedGraphicsManager.Current.Allocate(window.CreateGraphics(), window.DisplayRectangle);
            graphics = graphics_buffer.Graphics;
        }

        //Bind Input
        {
            window.KeyDown += (s, e) => { keys_down[(int)e.KeyCode] = true; };
            window.KeyUp += (s, e) => { keys_down[(int)e.KeyCode] = keys_stale[(int)e.KeyCode] = false; };
        }

        //Start Game Loop
        {
            demo = demos[0];
            Application.Idle += GameLoop;
            Application.Run(window);
        }
    }


    void GameLoop(object sender, EventArgs e)
    {
        do
        {        
            //Set TimeStep
            {
                if (fixed_framerate)
                    time_step = STANDARD_TIMESTEP;
                else
                    time_step = delta_time;
            }

            //Update The Active Demo
            {
				//Cycle Through Demos
				{
		            if (KeyDownFresh(Keys.Tab))
		            {
						demo_index = (demo_index + 1) % demos.Length;
						demo = demos[demo_index];
		            }
					else if (KeyDownFresh(Keys.Z))
					{
						demo_index--;
						if(demo_index < 0)
							demo_index+= demos.Length;
						demo = demos[demo_index];
					}
				}

                if (!fixed_framerate || delta_time > STANDARD_TIMESTEP)
                {
                    frames_since_last_second++;
                    demo.Update();
                    delta_time = 0;
                }

                //Set Stale Keys
                {
                    for (int i = 0; i < keys_stale.Length; i++)
                        keys_stale[i] = keys_down[i];
                }
            }

            //Update Timing
            {
                delta_time = (float)(stopwatch.Elapsed.TotalSeconds - previous_time);
                portion_of_current_second_complete += delta_time;

                if (portion_of_current_second_complete >= 1)
                {
                    frames_per_second = frames_since_last_second / portion_of_current_second_complete;
                    portion_of_current_second_complete = frames_since_last_second = 0;
                }

                previous_time = (float)stopwatch.Elapsed.TotalSeconds;
            }
        } while (WindowIsIdle());
    }

    public static bool KeyDownFresh(Keys key) { return keys_down[(int)key] && !keys_stale[(int)key]; }

    bool WindowIsIdle()
    {
        #if Windows
		    NativeMessage result;
		    return PeekMessage(out result, IntPtr.Zero, 0, 0, 0) == 0;
        #else
        	return false;
        #endif
    }

    #if Windows
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
    #endif
}
