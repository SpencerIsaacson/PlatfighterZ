using Engine;

using static Game;
using static DrawingLibrary;

class TriangleBenchmark : IGameState
{
    System.Collections.Generic.List<float> fps = new System.Collections.Generic.List<float>();
    float t;

    public void Update()
    {
        t += delta_time;
        if(t > 1)
        {
                    fps.Add(frames_per_second);
            t = 0;
        }

        Phil(black);
        for (int i = 0; i < 10_000; i++)
            Phil_Triangle(blue, 100, 300, 110, 290, 120, 305);
        graphics.DrawImage(FullScreener.rendered_image, 0, 0);
    }
}
