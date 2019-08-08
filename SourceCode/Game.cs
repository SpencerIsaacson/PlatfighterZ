using Engine;
using System;
using System.Diagnostics;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

class Game
{
    //Resolution
    public static int PIXELS_PER_UNIT = 64;
    public static int WIDTH = 1024;
    public static int HEIGHT = 576;

    //GUI
    public static Form window = new Form();
    public static BufferedGraphics graphics_buffer;
    public static Graphics graphics;
    public static StringFormat centered_format = new StringFormat() { LineAlignment = StringAlignment.Center, Alignment = StringAlignment.Center, };

    //Timing
    public const float TIME_RECALCULATION_INTERVAL = 1;
    public const float TARGET_FRAMERATE = 60;
    public const float STANDARD_TIMESTEP = 1 / TARGET_FRAMERATE;
    public static Stopwatch stopwatch = new Stopwatch();
    public static float previous_time;
    public static float delta_time;
    public static float time_step;
    public static float time_since_last_frame;
    public static float frames_per_second;
    public static float time_since_timing_recalculated;
    public static bool fixed_framerate = false;
    public static int frames_since_last_second;

    IGameState current_game_state;
    IGameState[] game_states = new IGameState[] 
    {
        new TitleScreen(),
        new CharacterSelect(),
        new GameplayDemo(),
        new AnimationCurveTest(),
        new AvatarDemo(),
        new HitBoxDemo(),
        new MeshDemo(),
        new PlatformerPhysicsTest(),
        new CapsuleIntersectionTest(),
    };

    public static int game_state_index = 0;

    static void Main()
    {
        try
        {
            new Game();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            Console.ReadLine();
        }
    }

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
			window.KeyDown += (s,e) => { Input.keys_down[(int)e.KeyCode] = true;};
			window.KeyUp += (s, e) => { Input.keys_down[(int)e.KeyCode] = false; Input.keys_stale[(int)e.KeyCode] = false; };
		}

        //Start Game Loop
        {
            current_game_state = game_states[0];
            Application.Idle += GameLoop;
            stopwatch.Start();
            Application.Run(window);
        }
    }


    void GameLoop(object sender, EventArgs e)
    {
        do
        {
            if (!fixed_framerate || time_since_last_frame > STANDARD_TIMESTEP)
            {
                //Tick
                {
                    //Set TimeStep
                    {
                        if (fixed_framerate)
                            time_step = STANDARD_TIMESTEP;
                        else
                            time_step = delta_time;
                    }

                    //Update Input Devices
                    {
                        //Input.PollKeyboard();
                    }

                    //Cycle Through GameStates
                    {
                        if (Input.KeyDownFresh(Keys.Tab))
                        {
                            fixed_framerate = false;
                            game_state_index = (game_state_index + 1) % game_states.Length;
                        }
                        else if (Input.KeyDownFresh(Keys.Z))
                        {
                            fixed_framerate = false;
                            game_state_index--;
                            if (game_state_index < 0)
                                game_state_index += game_states.Length;
                        }

                        current_game_state = game_states[game_state_index];
                    }

                    frames_since_last_second++;

                    current_game_state.Update();
                    graphics_buffer.Render();
                    
                    time_since_last_frame = 0;
                }
            }

            //Set Stale Keys
            {
                for (int i = 0; i < Input.keys_stale.Length; i++)
				{
                    Input.keys_stale[i] = Input.keys_down[i];
				}
			}

            //Update Timing
            {
                delta_time = (float)(stopwatch.Elapsed.TotalSeconds - previous_time);
                time_since_last_frame += delta_time;
                time_since_timing_recalculated += delta_time;

                if (time_since_timing_recalculated >= TIME_RECALCULATION_INTERVAL)
                {
                    frames_per_second = frames_since_last_second / time_since_timing_recalculated;
                    time_since_timing_recalculated = frames_since_last_second = 0;
                }
                previous_time = (float)stopwatch.Elapsed.TotalSeconds;
            }
        } while (WindowIsIdle());
    }

    bool WindowIsIdle()
    {
#if Windows
        return PeekMessage(out NativeMessage result, IntPtr.Zero, 0, 0, 0) == 0;
#else
        return false;
#endif
    }

#if Windows
    //Imports a native Win32 function for checking the windows message queue
    [DllImport("User32.dll")]
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
