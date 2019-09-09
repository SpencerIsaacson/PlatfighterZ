using Engine;
using System.Drawing;
using System.Windows.Forms;

using static Game;

class CharacterSelect : IGameState
{
    int characters = 12;
    int number_of_columns = 4;
    int slot_width = 100;

    int selected;
    float right_key_time;
    float left_key_time;
    float right_key_delay;
    float left_key_delay;
    float key_delay = .125f;
    float initial_delay = .5f;

    int selected_column;
    int selected_row;
    float[] key_delays = new float[4];

    float t = 0;

    Image face = GetFaceImage();

    public void Update()
    {
        t += delta_time;
        int number_of_rows = characters/number_of_columns;
        if(Input.KeyDownFresh(Keys.S))
        {
            selected_row = (selected_row + 1) % number_of_rows;
        }

        if (Input.KeyDownFresh(Keys.W))
        {
            selected_row = (selected_row -1 + number_of_rows) % number_of_rows;
        }
        if (Input.KeyDownFresh(Keys.D) || right_key_delay > key_delay)
        {
            selected_column = (selected_column + 1) % number_of_columns;
            right_key_delay = 0;
        }
        if (Input.KeyDownFresh(Keys.A) || left_key_delay > key_delay)
        {
            selected_column = (selected_column - 1 + number_of_columns) % number_of_columns;
            left_key_delay = 0;
        }

        if (Input.KeyDown(System.Windows.Forms.Keys.D))
        {
            right_key_time += delta_time;
        }
        else
            right_key_time = 0;

        if (Input.KeyDown(System.Windows.Forms.Keys.A))
        {
            left_key_time += delta_time;
        }
        else
            left_key_time = 0;

        if (right_key_time > initial_delay)
        {
            right_key_delay += delta_time;
        }
        if (left_key_time > initial_delay)
        {
            left_key_delay += delta_time;
        }

        selected = selected_column + number_of_columns * selected_row;
        graphics.Clear(Color.Blue);
        int total_height = slot_width * characters / number_of_columns;
        int row_width = number_of_columns * slot_width;
        int center_X = (WIDTH - row_width) / 2;
        
        for (int i = 0; i < characters; i++)
        {
            int row = i / number_of_columns;
            Rectangle rectangle = new Rectangle(center_X + slot_width * (i % number_of_columns), (HEIGHT - total_height) + row * slot_width, slot_width, slot_width);

            graphics.DrawImage(face, rectangle);
            graphics.DrawRectangle(Pens.Black, rectangle);
        }

        for (int i = 0; i < characters; i++)
        {
            int row = i / number_of_columns;
            Rectangle rectangle = new Rectangle(center_X + slot_width * (i % number_of_columns), (HEIGHT - total_height) + row * slot_width, slot_width, slot_width);

            if (i == selected)
                graphics.DrawRectangle(new Pen(Color.Red, 5f), rectangle);
        }
    }

    static Bitmap GetFaceImage()
    {
        Bitmap image1 = (Bitmap)Image.FromFile("Assets/face-03.jpg", true);
        return image1;
    }
}

static class Extensions
{
    public static bool Between(this int a, int lower, int upper)
    {
        return a >= lower && a < upper;
    }
}