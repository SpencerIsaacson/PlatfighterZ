using System;
using System.Drawing;
using System.Windows.Forms;

class Game
{
    static void Main() { new Game(); }

    Form Form;
    BufferedGraphics graphics_buffer;
    Graphics graphics_context;
    bool[] keys_down = new bool[256];
    bool[] keys_stale = new bool[256];

    Game()
    {
        //Instantiate Form
        {
            Form = new Form();
			Form.FormBorderStyle = FormBorderStyle.FixedSingle;
			Form.MaximizeBox = false;
            Form.ClientSize = new Size(1024, 576);
        }

        //Initialize Graphics
        {
            graphics_buffer = BufferedGraphicsManager.Current.Allocate(Form.CreateGraphics(), Form.DisplayRectangle);
            graphics_context = graphics_buffer.Graphics;
        }

        //Initialize Input
        {
            Form.KeyDown += (s, e) => { keys_down[(int)e.KeyCode] = true; };
            Form.KeyUp += (s, e) => { keys_down[(int)e.KeyCode] = false; keys_stale[(int)e.KeyCode] = false; };
        }

        //Startup GameLoop
        {
            Application.Idle += GameLoop;
            Application.Run(Form);
        }
    }

    unsafe void GameLoop(object sender, EventArgs e)
    {
        NativeMessage result;

        //while window is idling
        while (PeekMessage(out result, IntPtr.Zero, 0, 0, 0) == 0)
        {
            //Update
            {
				//TODO Gameplay Logic
				
                //Set Stale Keys
                {
                    for (int i = 0; i < keys_stale.Length; i++)
                    {
                        if (keys_down[i])
                            keys_stale[i] = true;
                    }
                }
            }

            //Render
            {
                graphics_context.FillRectangle(Brushes.Black, Form.DisplayRectangle);
				graphics_buffer.Render();
            }
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
	
	public struct Vector3
	{
		public float x, y, z;

		public Vector3(float x, float y, float z)
		{
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public static Vector3 operator +(Vector3 a, Vector3 b) { return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
		public static Vector3 operator -(Vector3 a, Vector3 b) { return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
		public static Vector3 operator *(Vector3 v, float s) { return new Vector3(v.x * s, v.y * s, v.z * s); }
		public static Vector3 operator /(Vector3 v, float s) { return new Vector3(v.x / s, v.y / s, v.z / s); }
	}	
}