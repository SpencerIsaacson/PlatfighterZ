using Engine;
using System;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;

using static Game;

class CharacterSelect : IGameState
{
    static Character[] characters = new Character[4];
    const int icon_size = 100;

    public CharacterSelect()
    {
        Assembly assembly = Assembly.GetExecutingAssembly();
        characters[0] = new Character
        {
            name = "Bigfist McPunchydude",
            icon = (Bitmap)Image.FromStream(assembly.GetManifestResourceStream("PlatfighterZ.Assets.bigfist_mcpunchydude_icon.png"))
        };

        characters[1] = new Character
        {
            name = "Dr. Meroink",
            icon = (Bitmap)Image.FromStream(assembly.GetManifestResourceStream("PlatfighterZ.Assets.dr_meroink_icon.png"))
        };

        characters[2] = new Character
        {
            name = "Maestro",
            icon = (Bitmap)Image.FromStream(assembly.GetManifestResourceStream("PlatfighterZ.Assets.maestro_icon.png"))
        };

        characters[3] = new Character
        {
            name = "Jeffrey",
            icon = (Bitmap)Image.FromStream(assembly.GetManifestResourceStream("PlatfighterZ.Assets.jeffrey_icon.png"))
        };

        for (int i = 0; i < GameplayState.players.Length; i++)
            GameplayState.players[i].selected_character = i;
    }

    public unsafe void Update()
    {
        for (int player = 0; player < GameplayState.players.Length; player++)
        {
            if (Input.ButtonDownFresh(player, Buttons.RIGHT))
                GameplayState.players[player].selected_character++;
            else if (Input.ButtonDownFresh(player, Buttons.LEFT))
                GameplayState.players[player].selected_character--;

            if (GameplayState.players[player].selected_character == GameplayState.PLAYER_COUNT)
                GameplayState.players[player].selected_character = 0;
            if (GameplayState.players[player].selected_character < 0)
                GameplayState.players[player].selected_character = GameplayState.PLAYER_COUNT - 1;
        }

        graphics.Clear(Color.Teal);

        for (int i = 0; i < characters.Length; i++)
        {
            Rectangle rectangle = new Rectangle(i * icon_size, HEIGHT - icon_size, icon_size, icon_size);

            if (characters[i].icon != null)
                graphics.DrawImage(characters[i].icon, rectangle);
        }

        for (int i = 0; i < GameplayState.PLAYER_COUNT; i++)
        {
            var pen = new Pen(GameplayState.player_colors[i], 5f);
            pen.Alignment = System.Drawing.Drawing2D.PenAlignment.Inset;
            graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.None;
            graphics.DrawRectangle(pen, new Rectangle(GameplayState.players[i].selected_character * 100, HEIGHT - icon_size, icon_size, icon_size));
            graphics.DrawString(characters[GameplayState.players[i].selected_character].name, Control.DefaultFont, Brushes.White, 0, i*32);
        }

        for (int i = 0; i < GameplayState.PLAYER_COUNT; i++)
        {
            graphics.FillRectangle(new SolidBrush(GameplayState.player_colors[i]), new Rectangle(GameplayState.players[i].selected_character * 100 + (i % 2 * 75), HEIGHT - 100 + (i / 2 * 75), 25, 25));
            graphics.DrawString((i + 1) + "P", Control.DefaultFont, Brushes.White, GameplayState.players[i].selected_character * 100 + (i % 2 * 75), HEIGHT - 100 + (i / 2 * 75));
        }
    }
}

static class Extensions
{
    public static bool Between(this int a, int lower, int upper)
    {
        return a >= lower && a < upper;
    }
}