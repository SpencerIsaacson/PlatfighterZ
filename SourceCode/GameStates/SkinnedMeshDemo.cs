using Engine;
using System.Drawing;

using static Game;
using static Engine.Global;

class SkinnedMeshDemo : IGameState
{
    Mesh mesh;
    public float zoom_factor = 100;
    Transform[] world = new Transform[2];
    Transform[] bind = new Transform[2];
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

        //world[1].parent = 0;
        world[0].position.y = -1;
        world[1].position.y = 1;

        for (int i = 0; i < bind.Length; i++)
        {
            bind[i] = world[i];
            bind[i].position = -bind[i].position;
            bind[i].rotation = -bind[i].rotation;
            bind[i].scale.x = 1 / bind[i].scale.x;
            bind[i].scale.y = 1 / bind[i].scale.y;
            bind[i].scale.z = 1 / bind[i].scale.z;
        }

        for (int i = 0; i < weight_indices.Length; i++)
        {
            if (mesh.vertices[i].y <= 0)
            {
                weight_indices[i] = new Vector2(0, 1);
                weights[i] = new Vector2(1, 0);
            }
            else
            {
                weight_indices[i] = new Vector2(0, 1);
                weights[i] = new Vector2(0, 1);
            }
        }
    }

    float t;
    public void Update()
    {
        t += delta_time;
        graphics.Clear(Color.Black);
        //world[0].position.x -= delta_time * 0.100f;
        //world[1].position.x += delta_time * 0.191f;
        world[1].position.y -= delta_time / 10f;
        world[1].rotation.z += delta_time / 3f;

        for (int i = 0; i < mesh.vertices.Length; i++)
        {
            Vector3 v_a_prime = TransformVector(WorldSpaceMatrix(bind[(int)weight_indices[i].x], bind), mesh.vertices[i]);
            Vector3 v_a = TransformVector(WorldSpaceMatrix(world[(int)weight_indices[i].x], world), v_a_prime);

            Vector3 v_b_prime = TransformVector(WorldSpaceMatrix(bind[(int)weight_indices[i].y], bind), mesh.vertices[i]);
            Vector3 v_b = TransformVector(GetMatrix(world[(int)weight_indices[i].y]), v_b_prime);

            Vector3 v_average = (v_a * weights[i].x) + (v_b * weights[i].y);

            Vector2 v = ToScreen(v_average);
            graphics.FillRectangle(Brushes.Red, v.x, v.y, 1, 1);
        }

        Vector2 screen_a = ToScreen(TransformVector(WorldSpaceMatrix(world[0],world),Vector3.Zero));
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
