using Engine;
using System.Drawing;
using System.Windows.Forms;

using static Game;

class PlatformerPhysicsTest : IGameState
{
    Transform player = Transform.Default();
    Transform[] blocks = new Transform[30];

    public PlatformerPhysicsTest()
    {
        player.scale.y = 2;
        for (int i = 0; i < blocks.Length; i++)
        {
            blocks[i] = Transform.Default();
            blocks[i].position.x = (i % 10) - 5;
        }

        for (int i = 0; i < 10; i++)
        {
            blocks[i].position.y = 3f;
        }

        for (int i = 10; i < 20; i++)
        {
            blocks[i].position.y = -2f;
        }

        for (int i = 20; i < 30; i++)
        {
            blocks[i].position.y = -3f;
        }

        blocks[17].position.y = -1;
    }

    float vel_x = 0;
    float vel_y = 0;
    bool grounded = false;

    public void Update()
    {
        if (Input.KeyDown(Keys.Escape))
            Application.Exit();
          


        float acceleration = 100f;
        float jump_speed = 9;
        float max_speed = 5;
        float slide_coefficient = 0;
        bool no_horizontal_input = false;
        float gravity = 10;
        float ground_fall_velocity = -.01f;

        if (Input.KeyDown(Keys.D))
            vel_x += acceleration * delta_time;
        else if (Input.KeyDown(Keys.A))
            vel_x -= acceleration * delta_time;
        else
            no_horizontal_input = true;

        if (vel_x > max_speed)
            vel_x = max_speed;
        else if (vel_x < -max_speed)
            vel_x = -max_speed;

        if (grounded)
        {
            vel_y = ground_fall_velocity;

            if (no_horizontal_input)
                vel_x *= slide_coefficient;

            if (Input.KeyDown(Keys.W))
                vel_y = jump_speed;
        }
        else
        {
            vel_y -= gravity * delta_time;
        }

        float ax_half = player.scale.x / 2;
        float ay_half = player.scale.y / 2;


        var old_x = player.position.x;
        player.position.x += vel_x * delta_time;

        for (int i = 0; i < blocks.Length; i++)
        {
            var b = blocks[i];
            if (Intersect(player, b))
            {
                graphics.DrawRectangle(Pens.Red, (player.position.x - ax_half) * PIXELS_PER_UNIT, (player.position.y - ay_half) * PIXELS_PER_UNIT, player.scale.x * PIXELS_PER_UNIT, player.scale.y * PIXELS_PER_UNIT);
                if (old_x < b.position.x)
                    player.position.x -= (player.position.x + (player.scale.x / 2)) - (b.position.x - (b.scale.x / 2));
                else if (old_x > b.position.x)
                    player.position.x += (b.position.x + (b.scale.x / 2)) - (player.position.x - (player.scale.x / 2));
            }
        }

        var old_y = player.position.y;
        player.position.y += vel_y * delta_time;

        grounded = false;

        for (int i = 0; i < blocks.Length; i++)
        {
            var b = blocks[i];
            if (Intersect(player, b))
            {
                graphics.DrawRectangle(Pens.Green, (player.position.x - ax_half) * PIXELS_PER_UNIT, (player.position.y - ay_half) * PIXELS_PER_UNIT, player.scale.x * PIXELS_PER_UNIT, player.scale.y * PIXELS_PER_UNIT);
                if (old_y < b.position.y)
                {
                    player.position.y -= (player.position.y + (player.scale.y / 2)) - (b.position.y - (b.scale.y / 2));
                    vel_y = 0;
                }
                else if (old_y > b.position.y)
                {
                    player.position.y += (b.position.y + (b.scale.y / 2)) - (player.position.y - (player.scale.y / 2));
                    grounded = true;
                }
            }
        }

        if (player.position.Magnitude() > 20)
        {
            player.position = Vector3.Zero;
        }


        graphics.Clear(Color.Black);
        graphics.ResetTransform();
        graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
        graphics.ScaleTransform(1, -1);
        graphics.DrawRectangle(new Pen(Color.FromArgb(255, Color.Blue)), (player.position.x - ax_half) * PIXELS_PER_UNIT, (player.position.y - ay_half) * PIXELS_PER_UNIT, player.scale.x * PIXELS_PER_UNIT, player.scale.y * PIXELS_PER_UNIT);
        graphics.DrawRectangle(Pens.Blue, player.position.x * PIXELS_PER_UNIT, player.position.y * PIXELS_PER_UNIT, 1, 1);

        for (int i = 0; i < blocks.Length; i++)
        {
            var b = blocks[i];
            float by_half = b.scale.y / 2;
            float bx_half = b.scale.x / 2;

            graphics.DrawRectangle(Pens.Blue, (blocks[i].position.x - bx_half) * PIXELS_PER_UNIT, (blocks[i].position.y - by_half) * PIXELS_PER_UNIT, PIXELS_PER_UNIT * b.scale.x, PIXELS_PER_UNIT * b.scale.y);
        }

        graphics.ResetTransform();
        graphics.DrawString(player.position.ToString(), Control.DefaultFont, Brushes.White, 0, 0);
        graphics.DrawString($"[{vel_x:F3}, {vel_y:F3}]", Control.DefaultFont, Brushes.White, 0, 16);
        graphics.DrawString(grounded.ToString(), Control.DefaultFont, Brushes.White, 0, 32);
        graphics.DrawString(string.Format("FPS: {0:F2}", frames_per_second), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 120);
        graphics.DrawString(string.Format("delta_time: {0:F9}", delta_time), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 65);
    }

    bool Intersect(Transform a, Transform b)
    {
        float ax_half = a.scale.x / 2;
        float ay_half = a.scale.y / 2;
        float by_half = b.scale.y / 2;
        float bx_half = b.scale.x / 2;

        float a_right = a.position.x + ax_half;
        float a_left = a.position.x - ax_half;
        float a_top = a.position.y + ay_half;
        float a_bottom = a.position.y - ay_half;
        float b_right = b.position.x + bx_half;
        float b_left = b.position.x - bx_half;
        float b_top = b.position.y + by_half;
        float b_bottom = b.position.y - by_half;

        return a_right > b_left && a_left < b_right && a_top > b_bottom && a_bottom < b_top;
    }
}