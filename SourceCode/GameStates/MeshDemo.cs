using Engine;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

using static Engine.Global;
using static Game;

class MeshDemo : IGameState
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
			float camera_move_speed = 40 * time_step;
			float camera_rotation_speed = Tau/4 * time_step;
			float cube_rotation_speed = Tau / 16 * time_step;
			
			if(Input.KeyDown(Keys.E))
				camera.rotation.y += camera_rotation_speed;
			if(Input.KeyDown(Keys.Q))
				camera.rotation.y -= camera_rotation_speed;
			if(Input.KeyDown(Keys.W))
				camera.position.z += camera_move_speed;
			if(Input.KeyDown(Keys.A))
				camera.position.x -= camera_move_speed;
			if(Input.KeyDown(Keys.S))
				camera.position.z -= camera_move_speed;
			if(Input.KeyDown(Keys.D))
				camera.position.x += camera_move_speed;
			if(Input.KeyDown(Keys.X))
				camera.position.y += camera_move_speed;
			if(Input.KeyDown(Keys.C))
				camera.position.y -= camera_move_speed;

			cube_transform.rotation += new Vector3(cube_rotation_speed, cube_rotation_speed / 2, cube_rotation_speed / 3);
			light_rotation += time_step;
		}

		//Render
        {
            graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.None;
			graphics.ResetTransform();
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
					//get object transform matrix
					Matrix4x4 object_to_world = GetMatrix(cube_transform);
					
					//get camera matrix
					Transform inverted_camera = new Transform(){scale = Vector3.One};
					inverted_camera.position = -camera.position;
					inverted_camera.rotation = -camera.rotation;
					Matrix4x4 world_to_camera = GetMatrix(inverted_camera);
					
					Matrix4x4 object_to_camera = object_to_world.Concat(world_to_camera);
					
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
								var dot = Vector3.DotProduct(normal, TransformVector(Rotation(0,light_rotation,0), Vector3.Forward));

								if(dot < 0)
									dot = 0;

								t.brightness = dot * 255;
								triangles[i] = t;	

								i++;
							}
						}
					}

					Matrix4x4 camera_to_clip = Perspective(0.1f,100,field_of_view);

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
							
							v = new Vector3(v4.x,v4.y, v4.z);
							
							if(v4.w != 0)
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
					triangles.Sort((x,y) =>
					{
						var calc = GetCentroid(x).z - GetCentroid(y).z;
						if(calc < 0)
							return -1;
						else
							return 1;
					});
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
						
						var normal = Vector3.CrossProduct(t.b - t.a, t.c - t.a).Normalized();

						var b = (int)triangles[i].brightness;
						Color color = Color.FromArgb(b, b, b);
						graphics.FillPolygon(new SolidBrush(color), points);
						//graphics.DrawPolygon(Pens.DarkSlateGray, points);

						//Vector3 centroid = GetCentroid(t);
						//graphics.FillRectangle(Brushes.Red, centroid.x - 2, centroid.y - 2, 4, 4);
					}
				}

				graphics.DrawString(camera.position.ToString(), Control.DefaultFont, Brushes.White, 0, 0);
				graphics.DrawString(camera.rotation.ToString(), Control.DefaultFont, Brushes.White, 0, 32);
            }
        }
	}


	float light_rotation = 0;
	
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



	public struct Triangle
	{
		public Vector3 a, b, c;
		public float brightness;
	}
}
