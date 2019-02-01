using Engine;
using System.Drawing;
using static Game;

class PlatformerPhysicsTest : IGameState
{
    Transform a = Transform.Default();
    Transform b = Transform.Default();
    public void Update()
    {
        if (Input.KeyDown(System.Windows.Forms.Keys.Right))
            a.position.x += time_step;
        if (Input.KeyDown(System.Windows.Forms.Keys.Left))
            a.position.x -= time_step;
        if (Input.KeyDown(System.Windows.Forms.Keys.Up))
            a.position.y += time_step * 2;
        if (Input.KeyDown(System.Windows.Forms.Keys.Down))
            a.position.y -= time_step;

        a.position.y -= time_step;
        graphics.Clear(Color.Black);
        graphics.ResetTransform();
        graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
        graphics.ScaleTransform(1, -1);
        graphics.FillRectangle(Brushes.Red, a.position.x * PIXELS_PER_UNIT - PIXELS_PER_UNIT / 2, a.position.y * PIXELS_PER_UNIT - PIXELS_PER_UNIT / 2, PIXELS_PER_UNIT, PIXELS_PER_UNIT);

        graphics.FillRectangle(Brushes.Red, 200, 20, PIXELS_PER_UNIT, PIXELS_PER_UNIT);
    }
}
