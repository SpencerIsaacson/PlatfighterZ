using Engine;
using System.Drawing;
using static Game;

class CapsuleIntersectionTest : IGameState
{

    Capsule a = new Capsule { radius = 20, a = new Vector2 { x = 0, y = 0 }, b = new Vector2 { x = 30, y = 80 } };
    Capsule b;

    public void Update()
    {
        graphics.Clear(Color.Black);
        graphics.TranslateTransform(WIDTH / 2, HEIGHT / 2);
        graphics.ScaleTransform(1, -1);
        a.Draw();
        Vector2 p = new Vector2 { x = 30, y = 30 };
        graphics.FillEllipse(Brushes.Blue, p.x - 5, p.y - 5, 10, 10);
        graphics.ResetTransform();
    }

    struct Capsule
    {
        public Vector2 a, b;
        public float radius;

        public void Draw()
        {
            float diameter = radius * 2;
            graphics.DrawEllipse(Pens.White, a.x-radius, a.y-radius, diameter, diameter);
            graphics.DrawEllipse(Pens.White, b.x-radius, b.y-radius, diameter, diameter);
            graphics.DrawLine(Pens.White, a.x, a.y, b.x, b.y);

            Vector2 p = Vector2.Right;
        }
    }
}
