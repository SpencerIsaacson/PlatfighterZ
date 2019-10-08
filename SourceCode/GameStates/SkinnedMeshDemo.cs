using Engine;
using System.Windows.Forms;
using static Engine.Global;
using static Game;
using static DrawingLibrary;
class SkinnedMeshDemo : IGameState
{
    Mesh mesh;
    uint[] poly_colors;

    Transform[] skeleton;
    Matrix4x4[] bind_matrices;

    Vector4[] weights;
    Weight_Index[] weight_indices;

    public float zoom_factor = 70;

    public SkinnedMeshDemo()
    {
        mesh = LoadMesh("skin_translated.obj");
        skeleton = LoadHierarchy("avatar");
        poly_colors = new uint[mesh.indices.Length / 3];
        weights = new Vector4[mesh.vertices.Length];
        weight_indices = new Weight_Index[mesh.vertices.Length];

        bind_matrices = new Matrix4x4[skeleton.Length];
        Transform[] bind_transforms = new Transform[skeleton.Length];

        //Set polygon colors
        {
            for (int i = 1; i < 316; i++)
            {
                poly_colors[i] = 0xFF_00_00_00 | 13145700;
            }

            for (int i = 316; i < 376; i++)
            {
                poly_colors[i] = DrawingLibrary.red;
            }

            for (int i = 376; i < 444; i++)
            {
                poly_colors[i] = DrawingLibrary.blue;
            }

            for (int i = 444; i < 468; i++)
            {
                poly_colors[i] = 0xFF_00_00_00 | 10824234;
            }

            for (int i = 468; i < 504; i++)
            {
                poly_colors[i] = DrawingLibrary.blue;
            }

            for (int i = 504; i < poly_colors.Length; i++)
            {
                poly_colors[i] = 0xFF_00_00_00 | 10824234;
            }
        }

        //build bind matrices
        {
            for (int i = 0; i < bind_matrices.Length; i++)
            {
                bind_transforms[i] = InvertTransform(skeleton[i]);
                bind_matrices[i] = WorldSpaceMatrix(i, bind_transforms);
            }
        }

        SetWeights();
    }

    private void SetWeights()
    {
        //Set vertex weights

        for (int i = 0; i < mesh.vertices.Length; i++)
            weights[i] = new Vector4(1, 0, 0, 0);


        for (int i = 0; i <= 32; i++)
            weight_indices[i] = new Weight_Index(3, 0, 0, 0);

        for (int i = 33; i <= 48; i++)
            weight_indices[i] = new Weight_Index(2, 0, 0, 0);

        weight_indices[49] = new Weight_Index(2, 0, 0, 0);
        weight_indices[50] = new Weight_Index(5, 0, 0, 0);
        weight_indices[51] = new Weight_Index(5, 0, 0, 0);
        weight_indices[52] = new Weight_Index(2, 0, 0, 0);
        weight_indices[53] = new Weight_Index(5, 0, 0, 0);
        weight_indices[54] = new Weight_Index(5, 0, 0, 0);
        weight_indices[55] = new Weight_Index(2, 0, 0, 0);
        weight_indices[56] = new Weight_Index(2, 0, 0, 0);
        weight_indices[57] = new Weight_Index(5, 0, 0, 0);
        weight_indices[58] = new Weight_Index(5, 0, 0, 0);
        weight_indices[59] = new Weight_Index(5, 0, 0, 0);
        weight_indices[60] = new Weight_Index(5, 0, 0, 0);
        weight_indices[61] = new Weight_Index(5, 0, 0, 0);
        weight_indices[62] = new Weight_Index(5, 0, 0, 0);
        weight_indices[63] = new Weight_Index(5, 0, 0, 0);
        weight_indices[64] = new Weight_Index(5, 0, 0, 0);
        for (int i = 65; i <= 108; i++)
            weight_indices[i] = new Weight_Index(14, 0, 0, 0);

        weight_indices[109] = new Weight_Index(2, 0, 0, 0);
        weight_indices[110] = new Weight_Index(7, 0, 0, 0);
        weight_indices[111] = new Weight_Index(2, 0, 0, 0);
        weight_indices[112] = new Weight_Index(2, 0, 0, 0);
        weight_indices[113] = new Weight_Index(7, 0, 0, 0);
        weight_indices[114] = new Weight_Index(7, 0, 0, 0);
        weight_indices[115] = new Weight_Index(2, 0, 0, 0);
        weight_indices[116] = new Weight_Index(7, 0, 0, 0);
        weight_indices[117] = new Weight_Index(7, 0, 0, 0);
        weight_indices[118] = new Weight_Index(7, 0, 0, 0);
        weight_indices[119] = new Weight_Index(7, 0, 0, 0);
        weight_indices[120] = new Weight_Index(7, 0, 0, 0);
        weight_indices[121] = new Weight_Index(7, 0, 0, 0);
        weight_indices[122] = new Weight_Index(7, 0, 0, 0);
        weight_indices[123] = new Weight_Index(7, 0, 0, 0);
        weight_indices[124] = new Weight_Index(7, 0, 0, 0);

        for (int i = 125; i <= 168; i++)
            weight_indices[i] = new Weight_Index(7, 0, 0, 0);

        for (int i = 169; i <= 192; i++)
            weight_indices[i] = new Weight_Index(2, 0, 0, 0);

        for (int i = 193; i <= 209; i++)
            weight_indices[i] = new Weight_Index(2, 0, 0, 0);

        for (int i = 210; i <= 216; i++)
            weight_indices[i] = new Weight_Index(9, 0, 0, 0);

        weight_indices[217] = new Weight_Index(10, 0, 0, 0);
        weight_indices[218] = new Weight_Index(9, 0, 0, 0);
        weight_indices[219] = new Weight_Index(9, 0, 0, 0);
        weight_indices[220] = new Weight_Index(10, 0, 0, 0);
        weight_indices[221] = new Weight_Index(10, 0, 0, 0);
        weight_indices[222] = new Weight_Index(10, 0, 0, 0);
        weight_indices[223] = new Weight_Index(10, 0, 0, 0);
        weight_indices[224] = new Weight_Index(9, 0, 0, 0);
        weight_indices[225] = new Weight_Index(9, 0, 0, 0);
        weight_indices[226] = new Weight_Index(10, 0, 0, 0);
        weight_indices[227] = new Weight_Index(9, 0, 0, 0);

        for (int i = 228; i <= 237; i++)
            weight_indices[i] = new Weight_Index(10, 0, 0, 0);

        weight_indices[238] = new Weight_Index(12, 0, 0, 0);

        for (int i = 239; i <= 243; i++)
            weight_indices[i] = new Weight_Index(12, 0, 0, 0);

        weight_indices[244] = new Weight_Index(13, 0, 0, 0);
        weight_indices[245] = new Weight_Index(12, 0, 0, 0);
        weight_indices[246] = new Weight_Index(12, 0, 0, 0);
        weight_indices[247] = new Weight_Index(12, 0, 0, 0);
        weight_indices[248] = new Weight_Index(13, 0, 0, 0);
        weight_indices[249] = new Weight_Index(12, 0, 0, 0);
        weight_indices[250] = new Weight_Index(13, 0, 0, 0);
        weight_indices[251] = new Weight_Index(13, 0, 0, 0);

        weight_indices[252] = new Weight_Index(12, 0, 0, 0);
        weight_indices[253] = new Weight_Index(13, 0, 0, 0);
        weight_indices[254] = new Weight_Index(12, 0, 0, 0);

        for (int i = 255; i < mesh.vertices.Length; i++)
            weight_indices[i] = new Weight_Index(13, 0, 0, 0);
    }

    float frame;
    float rotation_y;
    bool toggle;
    bool view_debug;
    bool view_fps;

    public unsafe void Update()
    {
        //Input
        {
            if (Input.KeyDownFresh(Keys.Y))
                view_fps = !view_fps;

            if (Input.KeyDownFresh(Keys.G))
                view_debug = !view_debug;
            if (Input.KeyDown(Keys.W))
                offset_y -= 5;
            if (Input.KeyDown(Keys.S))
                offset_y += 5;
            if (Input.KeyDown(Keys.A))
                offset_x -= 5;
            if (Input.KeyDown(Keys.D))
                offset_x += 5;

            if (Input.KeyDown(Keys.Up))
                zoom_factor++;
            else if (Input.KeyDown(Keys.Down))
                zoom_factor--;
            if (Input.KeyDownFresh(Keys.T))
            {
                toggle = !toggle;
                if (!toggle)
                {
                    rotation_y = 0;
                    frame = 0;
                }
            }
        }

        frame++;
        rotation_y += delta_time / 10;


        skeleton[0].rotation.y = rotation_y;

        foreach (AnimationCurve curve in DefinedAnimations.walk_animation.curves)
        {
            KeyFrame[] keyframes = curve.keyframes;
            int transform_index = curve.transform_index;

            fixed (Transform* p = &skeleton[transform_index])
            {
                float* f = &(*p).position.x + curve.property_tag;

                AnimateProperty(keyframes, frame, ref *f);
            }
        }

        frame %= 32;
        skeleton[0].position.y = -1;

        Vector2[] transformed_vertices = new Vector2[mesh.vertices.Length];

        for (int i = 0; i < mesh.vertices.Length; i++)
        {
            Vector3 v_a = bind_matrices[weight_indices[i].bone1] * WorldSpaceMatrix(weight_indices[i].bone1, skeleton) * mesh.vertices[i];
            Vector3 v_b = bind_matrices[weight_indices[i].bone2] * WorldSpaceMatrix(weight_indices[i].bone2, skeleton) * mesh.vertices[i];
            Vector3 v_c = bind_matrices[weight_indices[i].bone3] * WorldSpaceMatrix(weight_indices[i].bone3, skeleton) * mesh.vertices[i];
            Vector3 v_d = bind_matrices[weight_indices[i].bone4] * WorldSpaceMatrix(weight_indices[i].bone4, skeleton) * mesh.vertices[i];

            Vector3 v_blended = (v_a * weights[i].x) + (v_b * weights[i].y) + (v_c * weights[i].z) + (v_d * weights[i].w);

            transformed_vertices[i] = ToScreenSpace(v_blended);
        }

        Phil(black);

        for (int i = 0; i < mesh.indices.Length; i += 3)
        {
            Phil_Triangle(poly_colors[i / 3],
            (int)transformed_vertices[mesh.indices[i + 0]].x,
            (int)transformed_vertices[mesh.indices[i + 0]].y,
            (int)transformed_vertices[mesh.indices[i + 1]].x,
            (int)transformed_vertices[mesh.indices[i + 1]].y,
            (int)transformed_vertices[mesh.indices[i + 2]].x,
            (int)transformed_vertices[mesh.indices[i + 2]].y);
        }

        graphics.DrawImage(FullScreener.rendered_image, 0, 0);

        //if (view_debug)
        //{
        //    for (int i = 0; i < skeleton.Length; i++)
        //    {
        //        Vector2 v = ToScreenSpace(TransformVector(WorldSpaceMatrix(i, skeleton), Vector3.Zero));
        //        graphics.FillRectangle(new SolidBrush(Color.FromArgb(90, 0, 90, 90)), v.x - 5, v.y - 5, 10, 10);
        //        graphics.DrawString(i.ToString(), Control.DefaultFont, Brushes.Yellow, v.x, v.y);
        //    }

        //    for (int i = 0; i < transformed_vertices.Length; i++)
        //    {
        //        Vector2 v = transformed_vertices[i];
        //        graphics.FillRectangle(Brushes.Black, v.x - 3, v.y - 3, 6, 6);
        //        graphics.FillRectangle(Brushes.Red, v.x - 2, v.y - 2, 4, 4);
        //    }

        //}
        //if (view_fps)
        //    graphics.DrawString(string.Format("FPS: {0:F2}", frames_per_second), Control.DefaultFont, Brushes.Yellow, PIXELS_PER_UNIT / 2, 50);
    }

    float offset_x, offset_y;
    Vector2 ToScreenSpace(Vector3 source)
    {
        source.y = -source.y;
        source *= zoom_factor;
        source.x += WIDTH / 2 - offset_x;
        source.y += HEIGHT / 2 - offset_y;
        return new Vector2(source.x, source.y);
    }

    struct Weight_Index
    {
        public int bone1, bone2, bone3, bone4;

        public Weight_Index(int bone1, int bone2, int bone3, int bone4)
        {
            this.bone1 = bone1;
            this.bone2 = bone2;
            this.bone3 = bone3;
            this.bone4 = bone4;
        }
    }
}
