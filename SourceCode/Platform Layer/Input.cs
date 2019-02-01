using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Engine
{
    public enum Buttons
    {
        LEFT,
        RIGHT,
        DOWN,
        JUMP,
        PUNCH
    }

    class Input
    {
        //Input
        public static bool[] keys_down = new bool[256];
        public static bool[] keys_stale = new bool[256]; //whether a key has been pressed for more than one consecutive frame
        public static byte[] keyboard_state = new byte[256];

        public static Keys[,] control_mappings = //each row represents a player's control scheme
        {
            {Keys.A,       Keys.D ,       Keys.S,        Keys.W,       Keys.Q},
            {Keys.J,       Keys.L,        Keys.K,        Keys.I,       Keys.U},
            {Keys.Left,    Keys.Right,    Keys.Down,     Keys.Up,      Keys.Back},
            {Keys.NumPad4, Keys.NumPad6,  Keys.NumPad5,  Keys.NumPad8, Keys.NumPad7}
        };

        public static bool ButtonDown(int player, Buttons action)
        {
            return KeyDown(control_mappings[player, (int)action]);
        }

        public static void PollKeyboard()
        {
            for (int i = 0; i < keys_stale.Length; i++)
            {
                keys_stale[i] = keys_down[i];
            }

#if Windows
            GetKeyboardState(keyboard_state);
#endif

            for (int i = 0; i < keys_down.Length; i++)
            {
                keys_down[i] = keyboard_state[i] > 127;

            }

            for (int i = 0; i < keys_stale.Length; i++)
            {
                if (!keys_down[i])
                    keys_stale[i] = false;
            }
        }


        public static bool KeyDownFresh(Keys key) { return keys_down[(int)key] && !keys_stale[(int)key]; }
        public static bool KeyDown(Keys key) { return keys_down[(int)key]; }

#if Windows
        [DllImport("User32.dll")]
        public static extern bool GetKeyboardState(byte[] state);
#endif
    }

}