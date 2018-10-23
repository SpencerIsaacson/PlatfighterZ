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
        Form = new Form();
        Form.ClientSize = new Size(640, 480);

        graphics_buffer = BufferedGraphicsManager.Current.Allocate(Form.CreateGraphics(), Form.DisplayRectangle);
        graphics_context = graphics_buffer.Graphics;

        //Initialize Input
        {
            Form.KeyDown += (s, e) => { keys_down[(int)e.KeyCode] = true; };
            Form.KeyUp += (s, e) => { keys_down[(int)e.KeyCode] = false; keys_stale[(int)e.KeyCode] = false; };
        }

        Application.Idle += GameLoop;
        Application.Run(Form);
    }

    void GameLoop(object sender, System.EventArgs e)
    {
        while (WindowIsIdling())
        {
            //Update
            {
                //TODO gameplay logic

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

    bool WindowIsIdling()
    {
        NativeMessage currentMessage;
        return PeekMessage(out currentMessage, IntPtr.Zero, 0, 0, 0) == 0;
    }

    [System.Runtime.InteropServices.DllImport("User32.dll")]
    static extern int PeekMessage(out NativeMessage message, System.IntPtr handle, uint filterMin, uint filterMax, uint remove);

    struct NativeMessage
    {
        IntPtr Handle;
        uint Message;
        IntPtr WParameter;
        IntPtr LParameter;
        uint Time;
        Point Location;
    }

    unsafe struct Transform
    {
        Transform* parent;
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
    }

    struct Vector3
    {
        float x, y, z;

        Vector3(float x, float y, float z)
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