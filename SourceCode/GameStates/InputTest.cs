using Engine;
using System.Drawing;
using System.Windows.Forms;
using static Game;

class InputTest : IGameState
{
    public void Update()
    {

        Input.PollKeyboard();

        string state_string = "";
        string current_line = "";
        for (int i = 0; i < Input.keyboard_state.Length; i++)
        {
            current_line += $"{(Keys)i}:{Input.keyboard_state[i]:D3}    ";
            if (i % 8 == 7 || current_line.Length > 150)
            {
                current_line += "\n";
                state_string += current_line;
                current_line = "";
            }
        }
        graphics.Clear(Color.Black);
        graphics.DrawString(state_string, Control.DefaultFont, Brushes.White, 0, 0);
    }
}