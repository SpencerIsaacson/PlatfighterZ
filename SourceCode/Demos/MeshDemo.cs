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

		cube_transform.rotation.x += cube_rotation_speed;
		cube_transform.rotation.y += cube_rotation_speed / 2;
		cube_transform.rotation.z += cube_rotation_speed / 3;
		
		//Render
        {
            graphics.Clear(Color.Black);

            if (mesh.vertices != null)
            {
				//declare triangle buffer
                Vector3[] vertices = new Vector3[mesh.vertices.Length];
                int[] indices = new int[mesh.indices.Length];
				List<Triangle> triangles = new List<Triangle>();

                //fill buffers
                {
                    for (int i = 0; i < mesh.vertices.Length; i++)
                        vertices[i] = mesh.vertices[i];

                    for (int i = 0; i < mesh.indices.Length; i++)
                        indices[i] = mesh.indices[i];

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


				//as triangle buffer
				{
					//transform points
					{

						for (int i = 0; i < triangles.Count; i++)
						{
							//To World Space
							Matrix4x4 m = GetMatrix(cube_transform);
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
								var a = triangles[i].b - triangles[i].a;
								var b = triangles[i].c - triangles[i].a;
								var normal = Vector3.CrossProduct( a, b ).Normalized();

								Vector3 from_camera_to_triangle = (triangles[i].a - camera.position).Normalized();

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
							Transform inverted_camera = new Transform(){scale = Vector3.One};
							inverted_camera.position = -camera.position;
							inverted_camera.rotation = -camera.rotation;
							Triangle t = triangles[i];
							t.a = TransformVector(GetMatrix(inverted_camera), t.a); //To Camera Space
							t.b = TransformVector(GetMatrix(inverted_camera), t.b); //To Camera Space
							t.c = TransformVector(GetMatrix(inverted_camera), t.c); //To Camera Space
							fuckit(ref t.a);
							fuckit(ref t.b);
							fuckit(ref t.c);
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
								if (less(triangles, j, min)) min = j;
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
							PointF[] points = new PointF[] { new PointF(t.a.x, t.a.y), new PointF(t.b.x, t.b.y), new PointF(t.c.x, t.c.y) };
							graphics.FillPolygon(Brushes.SlateGray, points);
							graphics.DrawPolygon(Pens.DarkSlateGray, points);

							//Vector3 centroid = GetCentroid(t);
							//graphics.FillRectangle(Brushes.Red, centroid.x - 2, centroid.y - 2, 4, 4);
						}
					}								
				}

				// //as vertex and index buffer
				// {
				// 	//transform points
				// 	{
				// 		for (int i = 0; i < vertices.Length; i++)
				// 		{
				// 			vertices[i] = TransformVector(GetMatrix(cube_transform), vertices[i]); //To World Space						
				// 		}

				// 		//cull backfaces
				// 		{
				// 			var index_list = new List<int> (indices);
							
				// 			for(int i = 0; i < index_list.Count;)
				// 			{
				// 				var a = vertices[index_list[i + 1]] - vertices[index_list[i]];
				// 				var b = vertices[index_list[i + 2]] - vertices[index_list[i]];
				// 				var normal = Vector3.CrossProduct( a, b ).Normalized();

				// 				Vector3 from_camera_to_triangle = (vertices[index_list[i]] - camera.position).Normalized();

				// 				if(Vector3.DotProduct(normal, from_camera_to_triangle) > 0 )
				// 				{				
				// 					index_list.RemoveAt(i);
				// 					index_list.RemoveAt(i);
				// 					index_list.RemoveAt(i);
				// 				}
				// 				else
				// 				{
				// 					i += 3;
				// 				}
				// 			}

				// 			indices = index_list.ToArray();
				// 		}
						
				// 		for (int i = 0; i < vertices.Length; i++)
				// 		{
				// 			Transform inverted_camera = new Transform(){scale = Vector3.One};
				// 			inverted_camera.position = -camera.position;
				// 			inverted_camera.rotation = -camera.rotation;
				// 			vertices[i] = TransformVector(GetMatrix(inverted_camera), vertices[i]); //To Camera Space
				// 			var v4 = new Vector4(vertices[i].x, vertices[i].y, vertices[i].z, 1);
				// 			v4 = TransformVector(Perspective(0.1f,100,field_of_view), v4); //Projection
				// 			vertices[i] = new Vector3(v4.x,v4.y, v4.z);
							
				// 			if(v4.w != 0)
				// 				vertices[i] /= v4.w;

				// 			vertices[i].x++;
				// 			vertices[i].y++;

				// 			vertices[i].x *= WIDTH / 2;
				// 			vertices[i].y *= HEIGHT / 2;
				// 		}
				// 	}

				// 	//sort triangles
				// 	{
				// 		stopwatch.Restart();
				// 		for (int i = 0; i < indices.Length; i += 3)
				// 		{
				// 			int min = i;
				// 			for (int j = i + 3; j < indices.Length; j += 3)
				// 			{
				// 				if (less(vertices,indices, j, min)) min = j;
				// 			}

				// 			SwapTriangles(indices, i, min);
				// 		}
				// 		stopwatch.Stop();
				// 		Console.WriteLine("Depth sort time: " + stopwatch.Elapsed.TotalMilliseconds + " milliseconds");
				// 	}

				// 	//Rasterize
				// 	{
				// 		for(int i = 0; i < vertices.Length; i++)
				// 		{
				// 			//graphics.DrawString($"{i+1}", Control.DefaultFont, Brushes.Blue, vertices[i].x,vertices[i].y);
				// 		}

				// 		for (int i = 0; i < indices.Length; i += 3)
				// 		{
				// 			Vector3 one = vertices[indices[i + 0]];
				// 			Vector3 two = vertices[indices[i + 1]];
				// 			Vector3 three = vertices[indices[i + 2]];
				// 			PointF[] points = new PointF[] { new PointF(one.x, one.y), new PointF(two.x, two.y), new PointF(three.x, three.y) };
				// 			graphics.FillPolygon(Brushes.SlateGray, points);
				// 			graphics.DrawPolygon(Pens.DarkSlateGray, points);

				// 			Vector3 centroid = GetCentroid(vertices, indices, i);
				// 			//graphics.FillRectangle(Brushes.Red, centroid.x - 2, centroid.y - 2, 4, 4);
				// 			//graphics.DrawString($"{i/3+1}", Control.DefaultFont, Brushes.Blue, centroid.x, centroid.y);
				// 		}
				// 	}
				// }

				graphics.DrawString(camera.position.ToString(), Control.DefaultFont, Brushes.White, 0, 0);
				graphics.DrawString(camera.rotation.ToString(), Control.DefaultFont, Brushes.White, 0, 32);
            }

			graphics_buffer.Render();
			graphics.ResetTransform();
        }
	}

	bool less(Vector3[] vertices, int[] indices, int a, int b)
	{
		var a_centroid = GetCentroid(vertices, indices, a);
		var b_centroid = GetCentroid(vertices, indices, b);

		return a_centroid.z < b_centroid.z;
	}

	Vector3 GetCentroid(Vector3[] vertices, int[] indices, int i)
	{
		return (vertices[indices[i]] + vertices[indices[i + 1]] + vertices[indices[i + 2]]) / 3;
	}

	void SwapTriangles(int[] indices, int a, int b)
	{
		var tempa = indices[a + 0];
		var tempb = indices[a + 1];
		var tempc = indices[a + 2];
		indices[a + 0] = indices[b + 0];
		indices[a + 1] = indices[b + 1];
		indices[a + 2] = indices[b + 2];
		indices[b + 0] = tempa;
		indices[b + 1] = tempb;
		indices[b + 2] = tempc;
	}

	bool less(List<Triangle> triangles, int a, int b)
	{
		var a_centroid = GetCentroid(triangles[a]);
		var b_centroid = GetCentroid(triangles[b]);

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

	void fuckit(ref Vector3 boo)
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

	//TODO reimplement graphics using triangle struct
	struct Triangle
	{
		public Vector3 a, b, c;
	}
}
