using Engine;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

using static Engine.Global;
using static Game;

class MeshDemo : IDemo
{
	Mesh mesh;
	Transform camera = new Transform() { position = Vector3.Forward * -10, scale = Vector3.One };
	Transform cube_transform = new Transform() { position = Vector3.Forward * 10f, scale = Vector3.One };
	Stopwatch stopwatch = new Stopwatch();
    float field_of_view = Tau / 4;

	public MeshDemo()
    {
		mesh = LoadMesh("teapot.obj");
    }

	public void Update()
	{
		//Update
		{
			float camera_move_speed = 10 * time_step;
			float camera_rotation_speed = Tau/4 * time_step;
			float cube_rotation_speed = Tau / 16 * time_step;
			
			if(KeyDown(Keys.E))
				camera.rotation.y += camera_rotation_speed;
			if(KeyDown(Keys.Q))
				camera.rotation.y -= camera_rotation_speed;
			if(KeyDown(Keys.W))
				camera.position.z += camera_move_speed;
			if(KeyDown(Keys.A))
				camera.position.x -= camera_move_speed;
			if(KeyDown(Keys.S))
				camera.position.z -= camera_move_speed;
			if(KeyDown(Keys.D))
				camera.position.x += camera_move_speed;
			if(KeyDown(Keys.X))
				camera.position.y += camera_move_speed;
			if(KeyDown(Keys.C))
				camera.position.y -= camera_move_speed;

			cube_transform.rotation += new Vector3(cube_rotation_speed, cube_rotation_speed / 2, cube_rotation_speed / 3);
		}

		//Render
        {
            graphics.Clear(Color.Black);

            if (mesh.indices?.Length > 0)
            {
				List<Triangle> triangles = new List<Triangle>();

                //fill triangle buffer
                {
					for (int i = 0; i < mesh.indices.Length; i += 3)
					{
						triangles.Add(new Triangle()
						{
							a = mesh.vertices[mesh.indices[i + 0]], 
							b = mesh.vertices[mesh.indices[i + 1]], 
							c = mesh.vertices[mesh.indices[i + 2]],
						});
					}
                }

				//transform points
				{
					Matrix4x4 m = GetMatrix(cube_transform);
					
					for (int i = 0; i < triangles.Count; i++)
					{
						//To World Space
						Triangle t = triangles[i];
						t.a = TransformVector(m, t.a);
						t.b = TransformVector(m, t.b);
						t.c = TransformVector(m, t.c);
						triangles[i] = t;
					}

					//cull backfaces
					{							
						for(int i = 0; i < triangles.Count;)
						{
							Triangle t = triangles[i];
							var a = t.b - t.a;
							var b = t.c - t.a;
							var normal = Vector3.CrossProduct( a, b ).Normalized();

							Vector3 from_camera_to_triangle = (t.a - camera.position).Normalized();

							if(Vector3.DotProduct(normal, from_camera_to_triangle) > 0 )
							{				
								triangles.RemoveAt(i);
							}
							else
							{
								i++;
							}
						}
					}
					
					for (int i = 0; i < triangles.Count; i++)
					{
						Triangle t = triangles[i];
						
						Transform inverted_camera = new Transform(){scale = Vector3.One};
						inverted_camera.position = -camera.position;
						inverted_camera.rotation = -camera.rotation;
						var camera_matrix = GetMatrix(inverted_camera);
						t.a = TransformVector(camera_matrix, t.a);
						t.b = TransformVector(camera_matrix, t.b);
						t.c = TransformVector(camera_matrix, t.c);
						ThisFunctionNeedsANameSoHereItIs(ref t.a);
						ThisFunctionNeedsANameSoHereItIs(ref t.b);
						ThisFunctionNeedsANameSoHereItIs(ref t.c);
						triangles[i] = t;
					}
				}
				
				//sort triangles
				{
					stopwatch.Restart();
					for (int i = 0; i < triangles.Count; i++)
					{
						int min = i;
						for (int j = i + 1; j < triangles.Count; j++)
						{
							if (less(triangles[j], triangles[min])) min = j;
						}

						SwapTriangles(triangles, i, min);
					}
					stopwatch.Stop();
					Console.WriteLine("Depth sort time: " + stopwatch.Elapsed.TotalMilliseconds + " milliseconds");
				}

				//Rasterize
				{
					for (int i = 0; i < triangles.Count; i++)
					{
						Triangle t = triangles[i];
						PointF[] points = new PointF[] 
						{ 
							new PointF(t.a.x, t.a.y), 
							new PointF(t.b.x, t.b.y), 
							new PointF(t.c.x, t.c.y),
						};
						graphics.FillPolygon(Brushes.SlateGray, points);
						graphics.DrawPolygon(Pens.DarkSlateGray, points);

						//Vector3 centroid = GetCentroid(t);
						//graphics.FillRectangle(Brushes.Red, centroid.x - 2, centroid.y - 2, 4, 4);
					}
				}

				graphics.DrawString(camera.position.ToString(), Control.DefaultFont, Brushes.White, 0, 0);
				graphics.DrawString(camera.rotation.ToString(), Control.DefaultFont, Brushes.White, 0, 32);
            }

			graphics_buffer.Render();
			graphics.ResetTransform();
        }
	}

	bool less(Triangle a, Triangle b)
	{
		var a_centroid = GetCentroid(a);
		var b_centroid = GetCentroid(b);

		return a_centroid.z < b_centroid.z;
	}

	void SwapTriangles(List<Triangle> triangles, int a, int b)
	{
		var temp = triangles[a];
		triangles[a] = triangles[b];
		triangles[b] = temp;
	}

	Vector3 GetCentroid(Triangle t)
	{
		return (t.a + t.b + t.c) / 3;
	}

	void ThisFunctionNeedsANameSoHereItIs(ref Vector3 boo)
	{
		var v4 = new Vector4(boo.x, boo.y, boo.z, 1);
		v4 = TransformVector(Perspective(0.1f,100,field_of_view), v4); //Projection
		boo = new Vector3(v4.x,v4.y, v4.z);
		
		if(v4.w != 0)
			boo /= v4.w;

		boo.x++;
		boo.y++;

		boo.x *= WIDTH / 2;
		boo.y *= HEIGHT / 2;
	}

	public struct Triangle
	{
		public Vector3 a, b, c;
	}
}
