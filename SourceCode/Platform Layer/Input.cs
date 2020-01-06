using System.Runtime.InteropServices;

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
        public static byte[] keys_down = new byte[256];
        public static byte[] keys_stale = new byte[256]; //whether a key has been pressed for more than one consecutive frame
        public static byte[] keyboard_state = new byte[256];

        public static Keys[,] control_mappings = //each row represents a player's control scheme
        {
            {Keys.A,       Keys.D ,       Keys.S,        Keys.W,       Keys.Q},
            {Keys.J,       Keys.L,        Keys.K,        Keys.I,       Keys.U},
            {Keys.Left,    Keys.Right,    Keys.Down,     Keys.Up,      Keys.Delete},
            {Keys.NumPad4, Keys.NumPad6,  Keys.NumPad5,  Keys.NumPad8, Keys.NumPad7}
        };

        [DllImport("SGL.dll")]
        public static extern bool ButtonDown(int player, Buttons action);
        [DllImport("SGL.dll")]
        public static extern bool ButtonDownFresh(int player, Buttons action);
        [DllImport("SGL.dll")]
        public static extern bool KeyDownFresh(Keys key);
        [DllImport("SGL.dll")]
        public static extern bool KeyDown(Keys key);
        [DllImport("SGL.dll")]
        public static extern void PollKeyboard();
        [DllImport("SGL.dll")]        
        public static extern void InitKeyboard(byte[] keys_down, byte[] keys_stale, byte[] keyboard_state);
    }

}