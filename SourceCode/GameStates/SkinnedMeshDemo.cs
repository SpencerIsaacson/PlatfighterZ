using Engine;
using System.Drawing;

using static Game;
using static Engine.Global;

class SkinnedMeshDemo : IGameState
{
    Mesh mesh;
    public float zoom_factor = 100;
    Transform[] world = new Transform[2];
    Matrix4x4[] bind_matrices = new Matrix4x4[2];
    Vector2[] weights;
    Vector2[] weight_indices;
    public SkinnedMeshDemo()
    {
        mesh = LoadMesh("skin_cylinder.obj");
        weights = new Vector2[mesh.vertices.Length];
        weight_indices = new Vector2[mesh.vertices.Length];

        for (int i = 0; i < world.Length; i++)
        {
            world[i] = Transform.Default();
        }

        world[1].parent = 0;
        world[0].position.y = -1;
        world[1].position.y = 2;

        Transform[] bind_transforms = new Transform[2];

        for (int i = 0; i < bind_matrices.Length; i++)
        {

            bind_transforms[i] = InvertTransform(world[i]);
            bind_matrices[i] = WorldSpaceMatrix(bind_transforms[i], bind_transforms);

        }
        for (int i = 0; i < weight_indices.Length; i++)
        {
            weight_indices[i] = new Vector2(0, 1);
            float t = mesh.vertices[i].y/2 +.5f;
            weights[i] = new Vector2(1 - t, t);
        }
    }

    float t;
    public void Update()
    {
        t += delta_time;
        graphics.Clear(Color.Black);

        world[0].position.x = (float)System.Math.Sin(t);
        world[0].rotation.y = t;
        world[1].rotation.z = (float)System.Math.Sin(t);
        world[1].position.y = 2 + (float)System.Math.Cos(t)/2;

        for (int i = 0; i < mesh.vertices.Length; i++)
        {
            Vector3 v_a = bind_matrices[(int)weight_indices[i].x] * WorldSpaceMatrix(world[(int)weight_indices[i].x], world) * mesh.vertices[i];
            Vector3 v_b = bind_matrices[(int)weight_indices[i].y] * WorldSpaceMatrix(world[(int)weight_indices[i].y], world) * mesh.vertices[i];

            Vector3 v_average = (v_a * weights[i].x) + (v_b * weights[i].y);

            Vector2 v = ToScreen(v_average);
            graphics.FillRectangle(Brushes.Red, v.x, v.y, 1, 1);
        }

        Vector2 screen_a = ToScreen(TransformVector(WorldSpaceMatrix(world[0], world), Vector3.Zero));
        Vector2 screen_b = ToScreen(TransformVector(WorldSpaceMatrix(world[1], world), Vector3.Zero));

        graphics.FillRectangle(Brushes.Red, screen_a.x - 5, screen_a.y - 5, 10, 10);
        graphics.FillRectangle(Brushes.Red, screen_b.x - 5, screen_b.y - 5, 10, 10);


    }

    Vector2 ToScreen(Vector3 source)
    {
        source.y = -source.y;
        source *= zoom_factor;
        source.x += WIDTH / 2;
        source.y += HEIGHT / 2;
        return new Vector2(source.x, source.y);
    }
}
