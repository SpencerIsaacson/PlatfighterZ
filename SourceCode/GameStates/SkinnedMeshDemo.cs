using Engine;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;

using static DrawingLibrary;
using static Engine.Global;
using static Game;

class SkinnedMeshDemo : IGameState
{
    Mesh mesh;
    uint[] body_poly_colors;

    Transform[] skeleton;
    Matrix4x4[] bind_matrices;
    Vector4[] weights;
    Weight_Index[] weight_indices;
    Dictionary<int, Vector3>[] morphs = new Dictionary<int, Vector3>[5];
    float[] morph_weights = new float[5];
    Vector3[] transformed_vertices;
    Transform camera = new Transform() { position = Vector3.Forward * -50, scale = Vector3.One };
    float light_rotation = 0;
    float field_of_view = Tau / 4;

    bool has_a_face = true;
    bool animate_face = false;
    int facial_index_offset = 266;

    public SkinnedMeshDemo()
    {
        BuildGuy();
    }

    void BuildGuy()
    {
        mesh = LoadMesh("skin_translated.obj");
        skeleton = LoadHierarchy("avatar");


        if (has_a_face)
        {
            //load face
            Mesh face = LoadMesh("face.obj");
            Mesh smile = LoadMesh("smile.obj");
            Mesh angry_eyes = LoadMesh("angry_eyes.obj");

            //adjust head vertices
            {
                mesh.vertices[08].z -= .3f;
                mesh.vertices[01].z -= .2f;
                mesh.vertices[21].z -= .2f;

                mesh.vertices[07].z -= .3f;
                mesh.vertices[22].z -= .3f;
                mesh.vertices[14].z -= .3f;
                mesh.vertices[19].z -= .3f;
                mesh.vertices[29].z -= .3f;
                mesh.vertices[32].z -= .3f;
            }

            //Attach face
            mesh = AppendMesh(mesh, face);

            //build facial morph targets
            {
                morphs[0] = new Dictionary<int, Vector3>();
                for (int i = 0; i < smile.vertices.Length; i++)
                {
                    if (smile.vertices[i] - face.vertices[i] != Vector3.Zero)
                    {
                        morphs[0].Add(i, smile.vertices[i]);
                    }
                }

                morphs[1] = new Dictionary<int, Vector3>();
                for (int i = 0; i < angry_eyes.vertices.Length; i++)
                {
                    if (angry_eyes.vertices[i] - face.vertices[i] != Vector3.Zero)
                    {
                        morphs[1].Add(i, angry_eyes.vertices[i]);
                    }
                }
            }
        }

        LoadPolygonColors();
        SetWeights();

        //build bind matrices
        {
            bind_matrices = new Matrix4x4[skeleton.Length];
            Transform[] bind_transforms = new Transform[skeleton.Length];

            for (int i = 0; i < bind_matrices.Length; i++)
            {
                bind_transforms[i] = InvertTransform(skeleton[i]);
                bind_matrices[i] = WorldSpaceMatrix(i, bind_transforms);
            }
        }

        transformed_vertices = new Vector3[mesh.vertices.Length];
        skeleton[0].position.y = -1;
    }

    void LoadPolygonColors()
    {
        Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream("PlatfighterZ.Assets.skin_poly_colors");
        using (BinaryReader reader = new BinaryReader(stream))
        {
            List<uint> polygon_colors = new List<uint>();
            while (reader.BaseStream.Position != reader.BaseStream.Length)
            {
                polygon_colors.Add(reader.ReadUInt32());
            }

            body_poly_colors = polygon_colors.ToArray();
        }

    }

    void SetWeights()
    {
        weights = new Vector4[mesh.vertices.Length];
        weight_indices = new Weight_Index[mesh.vertices.Length];

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

        for (int i = 255; i < 258; i++)
            weight_indices[i] = new Weight_Index(13, 0, 0, 0);

        for (int i = 258; i < facial_index_offset; i++)
            weight_indices[i] = new Weight_Index(13, 0, 0, 0);

        for (int i = facial_index_offset; i < mesh.vertices.Length; i++)
            weight_indices[i] = new Weight_Index(3, 0, 0, 0);


    }

    float frame;
    float animation_length = 32;
    float rotation_y = Tau / 2;
    bool animation_play = false;
    bool rotation_play = false;
    bool view_debug;
    bool view_fps;
    float facial_time = 0;

    public unsafe void Update()
    {
        //Input
        {
            float delta = 5 * delta_time;
            if (Input.KeyDownFresh(Keys.Y))
                view_fps = !view_fps;

            if (Input.KeyDownFresh(Keys.G))
                view_debug = !view_debug;
            if (Input.KeyDown(Keys.W))
                camera.position.y -= delta;
            if (Input.KeyDown(Keys.S))
                camera.position.y += delta;
            if (Input.KeyDown(Keys.A))
                camera.position.x += delta;
            if (Input.KeyDown(Keys.D))
                camera.position.x -= delta;

            if (Input.KeyDown(Keys.Up))
                camera.position.z += delta * 10;
            else if (Input.KeyDown(Keys.Down))
                camera.position.z -= delta * 10;

            if (Input.KeyDownFresh(Keys.T))
            {
                animation_play = !animation_play;
            }

            if (Input.KeyDownFresh(Keys.Q))
            {
                animate_face = !animate_face;
            }

            if (Input.KeyDownFresh(Keys.F))
            {
                has_a_face = !has_a_face;
                BuildGuy();
            }

            if (Input.KeyDownFresh(Keys.R))
            {
                rotation_play = !rotation_play;
            }

            if (Input.KeyDownFresh(Keys.F4))
                FullScreener.ToggleFullScreen();
        }

        //Animate
        {
            if (rotation_play)
            {
                rotation_y += delta_time;
                skeleton[0].rotation.y = rotation_y;
            }

            if (animation_play)
            {
                //Animate Skeleton
                {
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
                }
            }

            Matrix4x4[] skeleton_matrices = new Matrix4x4[skeleton.Length];

            //Get Skeleton Matrices
            {
                for (int i = 0; i < skeleton_matrices.Length; i++)
                {
                    skeleton_matrices[i] = WorldSpaceMatrix(i, skeleton);
                }
            }

            //Apply Mesh Skinning
            {
                for (int i = 0; i < mesh.vertices.Length; i++)
                {
                    Vector3 v_a = bind_matrices[weight_indices[i].bone1] * skeleton_matrices[weight_indices[i].bone1] * mesh.vertices[i];
                    Vector3 v_b = bind_matrices[weight_indices[i].bone2] * skeleton_matrices[weight_indices[i].bone2] * mesh.vertices[i];
                    Vector3 v_c = bind_matrices[weight_indices[i].bone3] * skeleton_matrices[weight_indices[i].bone3] * mesh.vertices[i];
                    Vector3 v_d = bind_matrices[weight_indices[i].bone4] * skeleton_matrices[weight_indices[i].bone4] * mesh.vertices[i];

                    transformed_vertices[i] = (v_a * weights[i].x) + (v_b * weights[i].y) + (v_c * weights[i].z) + (v_d * weights[i].w);
                }
            }

            //Apply Facial Morph Targets
            {
                if (has_a_face && animate_face)
                {
                    Vector3[] deltas = new Vector3[259];
                    for (int morph_index = 0; morph_index < morphs.Length; morph_index++)
                    {
                        if (morphs[morph_index] != null)
                        {
                            var current_morph = morphs[morph_index];

                            foreach (var entry in current_morph)
                            {
                                int key = entry.Key;
                                Vector3 point = entry.Value;
                                int vertex_index = key + facial_index_offset;
                                Weight_Index weight_index = weight_indices[vertex_index];
                                Vector4 weight = weights[key];

                                Vector3 v_a = bind_matrices[weight_index.bone1] * skeleton_matrices[weight_index.bone1] * point;
                                Vector3 v_b = bind_matrices[weight_index.bone2] * skeleton_matrices[weight_index.bone2] * point;
                                Vector3 v_c = bind_matrices[weight_index.bone3] * skeleton_matrices[weight_index.bone3] * point;
                                Vector3 v_d = bind_matrices[weight_index.bone4] * skeleton_matrices[weight_index.bone4] * point;

                                Vector3 skinned_morph = (v_a * weight.x) + (v_b * weight.y) + (v_c * weight.z) + (v_d * weight.w);

                                deltas[key] += (skinned_morph - transformed_vertices[vertex_index]) * morph_weights[morph_index];
                            }
                        }
                    }

                    for (int i = 0; i < deltas.Length; i++)
                    {
                        int vertex_index = i + facial_index_offset;
                        transformed_vertices[vertex_index] += deltas[i];
                    }
                }

                morph_weights[0] = ((float)Math.Cos(facial_time * 2) + 1) / 2;
                morph_weights[1] = ((float)Math.Sin(facial_time * 2) + 1) / 2;

                facial_time += delta_time;
            }

            //Advance Animation Time
            {
                frame += TARGET_FRAMERATE * delta_time;
                frame %= animation_length;
            }
        }

        //Render
        {
            Phil(black);

            if (mesh.indices?.Length > 0)
            {
                List<Triangle> triangles = new List<Triangle>();

                //populate triangle list
                {
                    for (int i = 0; i < mesh.indices.Length; i += 3)
                    {
                        triangles.Add(new Triangle()
                        {
                            a = transformed_vertices[mesh.indices[i + 0]],
                            b = transformed_vertices[mesh.indices[i + 1]],
                            c = transformed_vertices[mesh.indices[i + 2]],
                            color = body_poly_colors[i / 3]
                        });
                    }
                }

                //transform points
                {
                    //get object transform matrix
                    Matrix4x4 object_to_world = Matrix4x4.identity;

                    //get camera matrix
                    Matrix4x4 world_to_camera = GetMatrix(InvertTransform(camera));

                    Matrix4x4 object_to_camera = object_to_world * world_to_camera;

                    for (int i = 0; i < triangles.Count; i++)
                    {
                        Triangle t = triangles[i];

                        //To Camera Space
                        {
                            t.a = TransformVector(object_to_camera, t.a);
                            t.b = TransformVector(object_to_camera, t.b);
                            t.c = TransformVector(object_to_camera, t.c);
                        }

                        triangles[i] = t;
                    }

                    //cull backfaces and perform lighting
                    {
                        for (int i = 0; i < triangles.Count;)
                        {
                            Triangle t = triangles[i];
                            var v1 = t.b - t.a;
                            var v2 = t.c - t.a;
                            var normal = Vector3.CrossProduct(v1, v2).Normalized();

                            Vector3 from_camera_to_triangle = (t.a - camera.position).Normalized();

                            if (Vector3.DotProduct(normal, from_camera_to_triangle) > 0) //replace with a proper backface cull
                            {
                                triangles.RemoveAt(i);
                            }
                            else
                            {
                                var dot = Vector3.DotProduct(normal, TransformVector(Rotation(0, light_rotation, 0), -Vector3.Forward));

                                if (dot < 0)
                                    dot = 0;

                                if (!float.IsNaN(dot))//TODO - remove, just a temporary fix
                                {
                                    t.brightness = dot * 255;
                                    triangles[i] = t;
                                }

                                float light = t.brightness / 255f;

                                uint r = ((t.color & red) ^ black) >> 16;
                                uint g = ((t.color & green) ^ black) >> 8;
                                uint b = (t.color & blue) ^ black;

                                r = (uint)(r * light);
                                g = (uint)(g * light);
                                b = (uint)(b * light);

                                t.color = r << 16 | g << 8 | b | black;
                                triangles[i] = t;

                                i++;
                            }
                        }
                    }

                    Matrix4x4 camera_to_clip = Perspective(0.1f, 100, field_of_view);

                    for (int i = 0; i < triangles.Count; i++)
                    {
                        Triangle t = triangles[i];
                        CameraToClipToScreen(ref t.a);
                        CameraToClipToScreen(ref t.b);
                        CameraToClipToScreen(ref t.c);
                        triangles[i] = t;

                        void CameraToClipToScreen(ref Vector3 v)
                        {
                            var v4 = new Vector4(v.x, v.y, v.z, 1);
                            v4 = TransformVector(camera_to_clip, v4); //Projection

                            v = new Vector3(v4.x, v4.y, v4.z);

                            if (v4.w != 0)
                                v /= v4.w;

                            //place origin at center of screen
                            v.x++;
                            v.y++;

                            //scale space to fill screen
                            v.x *= WIDTH / 2;
                            v.y *= HEIGHT / 2;
                        }
                    }
                }

                //sort triangles by depth
                {
                    triangles.Sort((x, y) =>
                    {
                        return (GetCentroid(x).z - GetCentroid(y).z < 0) ? -1 : 1;
                    });
                }

                //rasterize
                {
                    for (int i = 0; i < triangles.Count; i++)
                    {
                        Triangle t = triangles[i];

                        Phil_Triangle(t.color, (int)t.a.x, (int)t.a.y, (int)t.b.x, (int)t.b.y, (int)t.c.x, (int)t.c.y);
                    }
                }
            }

            graphics.DrawImage(FullScreener.rendered_image, 0, 0);
        }

        if (view_fps)
            graphics.DrawString($"FPS: {frames_per_second:F3}", Control.DefaultFont, Brushes.White, 0, 0);
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
