#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define bool char
#define uint unsigned int
#define true 1
#define false 0
#define m4x4_identity {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}

#define Tau 6.28318530717958f
#define Pi 3.14159265358979f

#define red 0xFFFF0000
#define green 0xFF00FF00
#define blue 0xFF0000FF
#define cyan 0xFF00FFFF
#define magenta 0xFFFF00FF
#define yellow 0xFFFFFF00

#define black 0xFF000000
#define white 0xFFFFFFFF

#define brown 0xFFA52A2A;
#define purple 0xFF800080;

typedef struct
{
	float x, y;
} v2;

typedef struct
{
	float x, y, z;
} v3;

typedef struct
{
	float x, y, z, w;
} v4;

typedef struct
{
	int parent;
	v3
		position,
		rotation,
		scale;
} Transform;

typedef struct
{
	float
		frame, value,
		left_handle_x, left_handle_y,
		right_handle_x, right_handle_y;
} KeyFrame;

typedef struct
{
	float
		m11, m12, m13, m14,
		m21, m22, m23, m24,
		m31, m32, m33, m34,
		m41, m42, m43, m44;
} m4x4;

typedef struct
{
	int transform_index;
	float radius;
	bool active;
} Hitbox;

typedef struct
{
	v3 a, b, c;
	uint color;
	float brightness;
} Triangle;

typedef struct
{
	v3* vertices;
	int* indices;
	int vertices_length;
	int indices_length;
} Mesh;

typedef struct
{
    int entity_ID;
    int selected_character;
    bool defeated;
    int stock;
    float current_health;
    v2 velocity;
    bool grounded;
    Hitbox* attackboxes;
    Hitbox* defendboxes;
} Player;

//math and stuff
float GetMin(float a, float b, float c);
float GetMax(float a, float b, float c);

//Drawing
uint Darker(uint color);
void Fill(uint color);
void FillTriangle(uint color, int x1, int y1, int x2, int y2, int x3, int y3);
void FillTriangle_VertexColors(v2 a, v2 b, v2 c, uint a_color, uint b_color, uint c_color);
void FillFlatBottom(uint color, int bottom, int left, int right, int top, int middle);
void FillFlatTop(uint color, int top, int left, int right, int bottom, int middle);
void DrawHorizontalSegment(uint color, int y, int x1, int x2);
void PutPixel(uint color, int x, int y);
void PutPixel_ByIndex(uint color, int i);
void DrawHorizontal(uint color, int y);
//Linear Algebra
Transform InvertTransform(Transform t);
v3 NegateVector(v3 v);
m4x4 Concatenate(m4x4 a, m4x4 b);
m4x4 GetMatrix(Transform t);
m4x4 WorldSpaceMatrix(int index, Transform hierarchy[]);
v3 Transform_v3(m4x4 m, v3 v);
v4 TransformVector4(m4x4 m, v4 v);
m4x4 Transpose(m4x4 m);
m4x4 Translation(float x, float y, float z);
m4x4 Rotation(float x, float y, float z);
m4x4 Scale(float x, float y, float z);
v3 v3_Add(v3 a, v3 b);
v3 v3_Subtract(v3 a, v3 b);
v3 v3_CrossProduct(v3 a, v3 b);
v3 v3_Normalized(v3 v);
float v3_Magnitude(v3 v);
v3 v3_Scale(v3 v, float s);
float v3_DotProduct(v3 a, v3 b);
void DrawLine(uint color, float x1, float y1, float x2, float y2);
void DrawRectangle(uint color, float x, float y, float width, float height);
void Flatten();

//Interpolation
v2 Lerp_v2(v2 a, v2 b, float t);
float Lerp_Float(float a, float b, float t);
void AnimateProperty(KeyFrame curve[], float frame, float* property);
float Sample(KeyFrame a, KeyFrame b, float frame);

//Collision
bool Intersect(Transform a, Transform b);

//Mesh Operations
v3 GetCentroid(Triangle t);

//Sorting
bool Less(Triangle a, Triangle b);
void SwapTriangles(Triangle triangles[], int a, int b);
void SortByDepth(Triangle a[], int length);
void QuickSort(Triangle a[], int lo, int hi);
int Partition(Triangle a[], int lo, int hi);

//Render Pipeline Operations
v3 CameraToClipToScreen(v3 v);

//Game States
void InitMeshDemo(float field_of_view, int width, int height, uint _pixels[]);
Transform RunMeshDemo(Mesh mesh, Transform cube_transform, Transform camera, float delta_time);
void Render(Mesh mesh, uint body_poly_colors[], Transform camera, bool fill_toggle);

__declspec(dllexport) uint Darker(uint color)
{
	uint r = (color & red ^ black) >> 17 << 16;
	uint g = (color & (green ^ black)) >> 9 << 8;
	uint b = (color & blue ^ black) >> 1;
	return black | r | g | b;
}

__declspec(dllexport) Transform InvertTransform(Transform t)
{
	t.position = NegateVector(t.position);
	t.rotation = NegateVector(t.rotation);
	t.scale.x = 1 / t.scale.x;
	t.scale.y = 1 / t.scale.y;
	t.scale.z = 1 / t.scale.z;
	return t;
}

__declspec(dllexport) v3 NegateVector(v3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return v;
}

__declspec(dllexport) m4x4 Concatenate(m4x4 a, m4x4 b)
{
	m4x4 result;
	result.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
	result.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
	result.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
	result.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44;
	result.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
	result.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
	result.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
	result.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44;
	result.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
	result.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
	result.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
	result.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44;
	result.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
	result.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
	result.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
	result.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44;
	return result;
}

__declspec(dllexport) m4x4 GetMatrix(Transform t)
{
	m4x4 result = m4x4_identity;
	result = Concatenate(result, Scale(t.scale.x, t.scale.y, t.scale.z));
	result = Concatenate(result, Rotation(t.rotation.x, t.rotation.y, t.rotation.z));
	result = Concatenate(result, Translation(t.position.x, t.position.y, t.position.z));
	return result;
}

__declspec(dllexport) m4x4 WorldSpaceMatrix(int index, Transform hierarchy[])
{
	Transform t = hierarchy[index];
	m4x4 m = GetMatrix(t);
	while (t.parent != -1)
	{
		m = Concatenate(m, GetMatrix(hierarchy[t.parent]));
		t = hierarchy[t.parent];
	}

	return m;
}

__declspec(dllexport) v3 Transform_v3(m4x4 m, v3 v)
{
	v3 result =
	{
		m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41,
		m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42,
		m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43,
	};

	return result;
}

__declspec(dllexport) v4 Transform_Vector4(m4x4 m, v4 v)
{
	v4 result =
	{
		m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41 * v.w,
		m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42 * v.w,
		m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43 * v.w,
		m.m14 * v.x + m.m24 * v.y + m.m34 * v.z + m.m44 * v.w,
	};

	return result;
}

__declspec(dllexport) m4x4 Transpose(m4x4 m)
{
	m4x4 transposed = { m.m11, m.m21, m.m31, m.m41, m.m12, m.m22, m.m32, m.m42, m.m13, m.m23, m.m33, m.m43, m.m14, m.m24, m.m34, m.m44 };
	return transposed;
}

__declspec(dllexport) m4x4 Translation(float x, float y, float z)
{
	m4x4 translation = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1 };
	return translation;
}

__declspec(dllexport) m4x4 Scale(float x, float y, float z)
{
	m4x4 scale = { x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1 };
	return scale;
}

__declspec(dllexport) m4x4 Rotation(float x, float y, float z)
{
	m4x4 rotation;

	rotation.m11 = (float)(cos(y) * cos(z) - sin(y) * sin(x) * sin(z));
	rotation.m12 = (float)(cos(y) * sin(z) + sin(y) * sin(x) * cos(z));
	rotation.m13 = (float)(-sin(y) * cos(x));
	rotation.m14 = 0;
	rotation.m21 = (float)(-sin(z) * cos(x));
	rotation.m22 = (float)(cos(z) * cos(x));
	rotation.m23 = (float)(sin(x));
	rotation.m24 = 0;
	rotation.m31 = (float)(sin(y) * cos(z) + cos(y) * sin(x) * sin(z));
	rotation.m32 = (float)(sin(z) * sin(y) - cos(y) * sin(x) * cos(z));
	rotation.m33 = (float)(cos(y) * cos(x));
	rotation.m34 = 0;
	rotation.m41 = 0;
	rotation.m42 = 0;
	rotation.m43 = 0;
	rotation.m44 = 1;

	return rotation;
}

__declspec(dllexport) m4x4 Perspective(float near_plane, float far_plane, float field_of_view, float width, float height)
{
	float aspect_ratio = height / width;
	float zoom = (float)(1 / tan(field_of_view / 2));
	float q = far_plane / (far_plane - near_plane);

	m4x4 result =
	{
		aspect_ratio * zoom, 0, 0, 0,
		0, -zoom, 0, 0,
		0, 0, q, near_plane * q,
		0, 0, 1, 0
	};

	return result;
}

__declspec(dllexport) v3 v3_Add(v3 a, v3 b)
{
	v3 v;
	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return v;
}

__declspec(dllexport) v3 v3_Subtract(v3 a, v3 b)
{
	v3 v;
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return v;
}

__declspec(dllexport) v3 CrossProduct(v3 a, v3 b)
{
	v3 result = 
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};

	return result;
}

__declspec(dllimport) v3 v3_Normalized(v3 v)
{
	return v3_Scale(v, v3_Magnitude(v));
}

__declspec(dllimport) float v3_Magnitude(v3 v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

__declspec(dllimport) v3 v3_Scale(v3 v, float s)
{
	v3 result = {v.x / s, v.y / s, v.z / s };
	return result;
}

__declspec(dllimport) float v3_DotProduct(v3 a, v3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }


__declspec(dllexport) v2 Lerp_v2(v2 a, v2 b, float t)
{
	v2 v;
	v.x = a.x + (t * (b.x - a.x));
	v.y = a.y + (t * (b.y - a.y));
	return v;
}

__declspec(dllexport) float Lerp_Float(float a, float b, float t)
{
	return a + t * (b - a);
}

//Animate property doesn't work yet
__declspec(dllexport) void AnimateProperty(KeyFrame curve[], float frame, float* property)
{
	size_t n = sizeof(curve) / sizeof(curve[0]);
	for (int i = 0; i < n - 1; i++)
	{
		KeyFrame a = curve[i];
		KeyFrame b = curve[i + 1];
		if (frame >= a.frame && frame <= b.frame)
		{
			*property = Sample(a, b, frame);
			return;
		}
	}
}

__declspec(dllexport) float Sample(KeyFrame a, KeyFrame b, float frame)
{
	float t = (frame - a.frame) / (b.frame - a.frame);

	v2 c1 = { a.frame, a.value };
	v2 c2 = { a.frame + a.right_handle_x, a.value + a.right_handle_y };
	v2 c3 = { b.frame + b.left_handle_x, b.value + b.left_handle_y };
	v2 c4 = { b.frame, b.value };
	v2 d = Lerp_v2(c1, c2, t);
	v2 e = Lerp_v2(c2, c3, t);
	v2 f = Lerp_v2(c3, c4, t);
	v2 g = Lerp_v2(d, e, t);
	v2 h = Lerp_v2(e, f, t);
	v2 i = Lerp_v2(g, h, t);

	return i.y;
}


__declspec(dllexport) bool Intersect(Transform a, Transform b)
{
	float ax_half = a.scale.x / 2;
	float ay_half = a.scale.y / 2;
	float by_half = b.scale.y / 2;
	float bx_half = b.scale.x / 2;

	float a_right = a.position.x + ax_half;
	float a_left = a.position.x - ax_half;
	float a_top = a.position.y + ay_half;
	float a_bottom = a.position.y - ay_half;
	float b_right = b.position.x + bx_half;
	float b_left = b.position.x - bx_half;
	float b_top = b.position.y + by_half;
	float b_bottom = b.position.y - by_half;

	return a_right > b_left && a_left < b_right && a_top > b_bottom && a_bottom < b_top;
}


__declspec(dllexport) v3 GetCentroid(Triangle t)
{
	v3 v = v3_Add(v3_Add(t.a, t.b), t.c);
	v.x /= 3;
	v.y /= 3;
	v.z /= 3;
	return v;
}


bool Less(Triangle a, Triangle b)
{
	v3 a_centroid = GetCentroid(a);
	v3 b_centroid = GetCentroid(b);

	return a_centroid.z < b_centroid.z;
}

void SwapTriangles(Triangle triangles[], int a, int b)
{
	Triangle temp = triangles[a];
	triangles[a] = triangles[b];
	triangles[b] = temp;
}

void SortByDepth(Triangle a[], int length)
{
	QuickSort(a, 0, length - 1);
}

void QuickSort(Triangle a[], int lo, int hi)
{
	if (hi <= lo) return;
	int j = Partition(a, lo, hi);
	QuickSort(a, lo, j - 1);
	QuickSort(a, j + 1, hi);
}

int Partition(Triangle a[], int lo, int hi)
{
	int i = lo;
	int j = hi + 1;
	Triangle v = a[lo];
	while (true)
	{
		while (Less(a[++i], v))
		{
			if (i == hi) break;
		}

		while (Less(v, a[--j]))
		{
			if (j == lo) break;
		}

		if (i >= j) break;

		SwapTriangles(a, i, j);
	}

	SwapTriangles(a, lo, j);

	return j;
}



//todo initialize
float light_rotation = 0;
m4x4 camera_to_clip;
int WIDTH, HEIGHT;
uint* pixels;

__declspec(dllexport) void InitMeshDemo(float field_of_view, int width, int height, uint _pixels[])  //TODO move more state here and out of the "run" arguments
{
	WIDTH = width;
	HEIGHT = height;
	camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);
	pixels =  &_pixels[0];
}

__declspec(dllexport) Transform RunMeshDemo(Mesh mesh, Transform cube_transform, Transform camera, float delta_time)
{
    //Update
    {
        cube_transform.rotation.y += Tau / 16 * delta_time;
    }

	Fill(black);

	size_t triangle_count = mesh.indices_length / 3;
	Triangle* triangles = malloc(triangle_count * sizeof(Triangle));

	//fill triangle list
	{
		int i;
		for (i = 0; i < triangle_count; i++)
		{
			triangles[i].a = mesh.vertices[mesh.indices[i * 3 + 0]];
			triangles[i].b = mesh.vertices[mesh.indices[i * 3 + 1]];
			triangles[i].c = mesh.vertices[mesh.indices[i * 3 + 2]];
		}
	}

	//transform points
	{
		//get object transform matrix
		m4x4 object_to_world = GetMatrix(cube_transform);

		//get camera matrix
		Transform inverted_camera = InvertTransform(camera);
		m4x4 world_to_camera = GetMatrix(inverted_camera);
		m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

		int i;
		for (i = 0; i < triangle_count; i++)
		{
			Triangle t = triangles[i];

			//To Camera Space
			{
				t.a = Transform_v3(object_to_camera, t.a);
				t.b = Transform_v3(object_to_camera, t.b);
				t.c = Transform_v3(object_to_camera, t.c);
			}

			triangles[i] = t;
		}

		//cull backfaces and perform lighting
		{
			size_t remaining_count = triangle_count;
			for (int i = 0; i < triangle_count; i++)
			{
			label:
				if (i == remaining_count) //TODO verify no off by one error
					break;
				Triangle t = triangles[i];
				v3 a = v3_Subtract(t.b, t.a);
				v3 b = v3_Subtract(t.c, t.a);
				v3 normal = v3_Normalized(CrossProduct(a, b));

				v3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, camera.position));

				if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
				{
					SwapTriangles(triangles, i, remaining_count - 1);
					remaining_count--;
					goto label;//TODO replace with while
				}
				else
				{
					v3 backward = { 0,0,-1 };
					float dot = v3_DotProduct(normal, Transform_v3(Rotation(0, light_rotation, 0), backward));

					if (dot < 0)
						dot = 0;

					if (!isnan(dot))//TODO - remove, just a temporary fix
					{
						t.brightness = (unsigned char)(dot * 255);
						triangles[i] = t;
					}
				}
			}

			triangle_count = remaining_count;
			triangles = realloc(triangles, triangle_count * sizeof(Triangle));
		}

		for (int i = 0; i < triangle_count; i++)
		{
			Triangle t = triangles[i];
			t.a = CameraToClipToScreen(t.a);
			t.b = CameraToClipToScreen(t.b);
			t.c = CameraToClipToScreen(t.c);
			triangles[i] = t;
		}
	}
	
	//sort triangles by depth painter's algorithm YAY!
	{
		SortByDepth(triangles,triangle_count);
	}

	//rasterize
	{
		for (int i = 0; i < triangle_count; i++)
		{
			Triangle t = triangles[i];
			uint color = triangles[i].brightness;
			color = black | (color << 16) | (color << 8) | color;
			FillTriangle(color, (int)t.a.x, (int)t.a.y, (int)t.b.x, (int)t.b.y, (int)t.c.x, (int)t.c.y);
		}
	}

	free(triangles);
	return cube_transform;
}

__declspec(dllexport) void FillTriangle(uint color, int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (y1 == y2 && y2 == y3)
		return;

	//Sort Points top to bottom
	{
		int temp;
		if (y1 > y2)
		{
			temp = y1;
			y1 = y2;
			y2 = temp;
			temp = x1;
			x1 = x2;
			x2 = temp;
		}
		if (y1 > y3)
		{
			temp = y1;
			y1 = y3;
			y3 = temp;
			temp = x1;
			x1 = x3;
			x3 = temp;
		}
		if (y2 > y3)
		{
			temp = y2;
			y2 = y3;
			y3 = temp;
			temp = x2;
			x2 = x3;
			x3 = temp;
		}
	}

	int split = (int)(x1 + ((y2 - y1) / (float)(y3 - y1)) * (x3 - x1));

	if (x2 < split) // major right
	{
		FillFlatBottom(color, y2, x2, split, y1, x1);
		FillFlatTop(color, y2, x2, split, y3, x3);
	}
	else //major left
	{
		FillFlatBottom(color, y2, split, x2, y1, x1);
		FillFlatTop(color, y2, split, x2, y3, x3);
	}
}


void FillFlatBottom(uint color, int bottom, int left, int right, int top, int middle)
{
	float dy = bottom - top;

	float inverted_slope1 = (middle - left) / dy;
	float inverted_slope2 = (middle - right) / dy;

	float l = left;
	float r = right;

	for (int scanline = bottom; scanline >= top; scanline--)
	{
		DrawHorizontalSegment(color, scanline, (int)(l), (int)(r));
		l += inverted_slope1;
		r += inverted_slope2;
	}
}


void FillFlatTop(uint color, int top, int left, int right, int bottom, int middle)
{
	float dy = bottom - top;

	float inverted_slope1 = (middle - left) / dy;
	float inverted_slope2 = (middle - right) / dy;

	float l = left;
	float r = right;
	for (int scanline = top; scanline <= bottom; scanline++)
	{
		DrawHorizontalSegment(color, scanline, (int)(l), (int)(r));
		l += inverted_slope1;
		r += inverted_slope2;
	}
}

void DrawHorizontalSegment(uint color, int y, int x1, int x2)
{
	int pixel_row = y * WIDTH;

	for (int i = pixel_row + x1; i <= pixel_row + x2; i++)
	{
		int x = i - pixel_row;
		PutPixel(color, x, y);
	}
}

__declspec(dllexport) void PutPixel(uint color, int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[y * WIDTH + x] = color;
}

__declspec(dllexport) void PutPixel_ByIndex(uint color, int i)
{
    if (i >= 0 && i < WIDTH * HEIGHT)
        pixels[i] = color;
}

v3 CameraToClipToScreen(v3 v)
{
    v4 v_4 = {v.x, v.y, v.z, 1};
    v_4 = Transform_Vector4(camera_to_clip, v_4); //Projection

    v.x = v_4.x;
    v.y = v_4.y;
    v.z = v_4.z;
    if (v_4.w != 0)
    {
        v.x /= v_4.w;
        v.y /= v_4.w;
        v.z /= v_4.w;                
    }

    //place origin at center of screen
    v.x++;
    v.y++;

    //scale space to fill screen
    v.x *= WIDTH / 2;
    v.y *= HEIGHT / 2;

    return v;
}

uint LerpColor(uint a, uint b, float t);

__declspec(dllexport) void FillVerticalGradient(uint color1, uint color2)
{
    for(int y = 0; y < HEIGHT; y++)
    {
        uint color = LerpColor(color1, color2, y/(float)HEIGHT);
        for(int x = 0; x < WIDTH; x++)
        {
            pixels[y * WIDTH + x] = color;
        }
    }
}

__declspec(dllexport) uint LerpColor(uint a, uint b, float t)
{
    //separate out channels
    uint a_a = (0xFF000000 & a) >> 24;
    uint a_r = (0x00FF0000 & a) >> 16;
    uint a_g = (0x0000FF00 & a) >> 8;
    uint a_b = (0x000000FF & a);
    uint b_a = (0xFF000000 & b) >> 24;
    uint b_r = (0x00FF0000 & b) >> 16;
    uint b_g = (0x0000FF00 & b) >> 8;
    uint b_b = (0x000000FF & b);
    
    //lerp per channel
    uint l_a = (uint)(((float)a_a) + (t * ((float)b_a - (float)a_a)));
    uint l_r = (uint)(((float)a_r) + (t * ((float)b_r - (float)a_r)));
    uint l_g = (uint)(((float)a_g) + (t * ((float)b_g - (float)a_g)));
    uint l_b = (uint)(((float)a_b) + (t * ((float)b_b - (float)a_b)));


    //align lerped channels
    l_a <<= 24;
    l_r <<= 16;
    l_g <<= 8;


    //reassemble channels
    uint l = l_a | l_r | l_g | l_b;
    return l;
}

__declspec(dllexport) uint BlendColor(uint s, uint d)
{
    uint sA = (s & 0xFF000000) >> 24;
    uint sR = (s & 0x00FF0000) >> 16;
    uint sG = (s & 0x0000FF00) >> 8;
    uint sB = (s & 0x000000FF);

    uint dA = (d & 0xFF000000) >> 24;
    uint dR = (d & 0x00FF0000) >> 16;
    uint dG = (d & 0x0000FF00) >> 8;
    uint dB = (d & 0x000000FF);

    float _sA = (sA / 255.0f);
    float _sR = (sR / 255.0f);
    float _sG = (sG / 255.0f);
    float _sB = (sB / 255.0f);
    float _dA = (dA / 255.0f);
    float _dR = (dR / 255.0f);
    float _dG = (dG / 255.0f);
    float _dB = (dB / 255.0f);

    uint rA = (uint)(((_sA * _sA) + (_dA * (1.0f - _sA))) * 255.0f);
    uint rR = (uint)(((_sR * _sA) + (_dR * (1.0f - _sA))) * 255.0f);
    uint rG = (uint)(((_sG * _sA) + (_dG * (1.0f - _sA))) * 255.0f);
    uint rB = (uint)(((_sB * _sA) + (_dB * (1.0f - _sA))) * 255.0f);

    rA <<= 24;
    rR <<= 16;
    rG <<= 8;

    uint result = rA | rR | rG | rB;

    return result;
}

__declspec(dllexport) void Fill(uint color)
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		pixels[i] = color;
	}
}

int main()
{
	return 0;
}

__declspec(dllexport) void DrawHorizontal(uint color, int y)
{
    for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
        PutPixel_ByIndex(color, i);
}

__declspec(dllexport) void DrawLine(uint color, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    if(fabs(dx) >= fabs(dy))
    {
        if(x1 > x2)
        {
            float temp = y1;
            y1 = y2;
            y2 = temp;
            temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (float x = x1; x <= x2; x++)
        {
            float y = (y1 + dy * (x - x1) / dx);
            PutPixel(color, (int)x, (int)y);
        }
    }
    else
    {
        if(y1 > y2)
        {
            float temp = y1;
            y1 = y2;
            y2 = temp;
            temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (float y = y1; y <= y2; y++)
        {
            float x = (x1 + dx * (y - y1) / dy);
            PutPixel(color, (int)x, (int)y);
        }
    }
}


__declspec(dllexport) void DrawRectangle(uint color, float x, float y, float width, float height)
{
    DrawLine(color, x, y, x + width, y);
    DrawLine(color, x, y, x, y + height);
    DrawLine(color, x + width, y, x + width, y + height);
    DrawLine(color, x, y + height, x + width, y + height);
}

__declspec(dllexport) void Flatten()
{
    for(int i = 0; i < WIDTH * HEIGHT; i++)
    {
        pixels[i] |= black;
    }
}

__declspec(dllexport) FillRectangle_Blend(uint color, int x, int y, int width, int height)
{
    for (int _x = 0; _x < width; _x++)
    {
        for (int _y = 0; _y < height; _y++)
        {
            PutPixel(BlendColor(color, pixels[(y + _y) * WIDTH + (x + _x)]), _x + x, _y + y);
        }
    }
}

__declspec(dllexport) void  DrawHorizontal_Blend(uint color, int y)
{
    for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
        PutPixel_ByIndex(BlendColor(color, pixels[i]), i);
}

__declspec(dllexport) void DrawVertical_Blend(uint color, int x)
{
    for (int i = x; i < (WIDTH * HEIGHT) - WIDTH - x; i += WIDTH)
    {
        PutPixel_ByIndex(BlendColor(color, pixels[i]), i);
    }
}

__declspec(dllexport) void DrawVertical(uint color, int x)
{
    for (int i = x; i < (WIDTH * HEIGHT) - WIDTH - x; i += WIDTH)
    {
        pixels[i] = color;
    }
}

__declspec(dllexport) void DrawGrid_ScreenSpace(int unit_size)
{
    for (int x = 0; x < WIDTH; x += unit_size)
    {
        DrawVertical(green, x);
    }

    for (int y = 0; y < HEIGHT; y += unit_size)
    {
        DrawHorizontal(green, y);
    }
}

__declspec(dllexport) void DrawVerticalSegment(uint color, int x, int y1, int y2)
{
    for (int i = x + (y1 * WIDTH); i <= x + (y2 * WIDTH); i += WIDTH)
        PutPixel_ByIndex(color, i);
}

__declspec(dllexport) FillRectangle(uint color, float x, float y, float width, float height)
{
    for (float _x = 0; _x <= width; _x++)
    {
        for (float _y = 0; _y <= height; _y++)
        {
            PutPixel(color, (int)(_x + x), (int)(_y + y));
        }
    }
}

__declspec(dllexport) void Draw_Circle(uint color, float x, float y, float radius, float stroke)
{
    int x_min = (int)(x - radius - stroke/2);
    int x_max = (int)roundf(x + radius + stroke/2);
    int y_min = (int)(y - radius - stroke/2);
    int y_max = (int)roundf(y + radius + stroke/2);

    for (int _x = x_min; _x <= x_max; _x++)
    {
        for (int _y = y_min; _y <= y_max; _y++)
        {
            float dx = _x - x;
            float dy = _y - y;

            float distance_squared = (float)(dx * dx + dy * dy);
            float distance = (float)sqrt(distance_squared);
            bool distance_equals_radius_within_delta =  distance <= radius + stroke/2 && distance >= radius - stroke/2;

            if (distance_equals_radius_within_delta)
                PutPixel(color, _x, _y);
        }
    }
}

__declspec(dllexport) void FillCircle(uint color, float x, float y, float radius)
{
    int x_min = (int)roundf(x - radius);
    int x_max = (int)roundf(x + radius);
    int y_min = (int)roundf(y - radius);
    int y_max = (int)roundf(y + radius);

    for (int _x = x_min; _x <= x_max; _x++)
    {
        for (int _y = y_min; _y <= y_max; _y++)
        {
            float dx = _x - x;
            float dy = _y - y;

            bool distance_less_than_radius = dx * dx + dy * dy <= radius * radius;

            if (distance_less_than_radius)
                PutPixel(color, _x, _y);
        }
    }
}

__declspec(dllexport) void Blend_Circle(uint color, float x, float y, float radius)
{
    int x_min = (int)roundf(x - radius);
    int x_max = (int)roundf(x + radius);
    int y_min = (int)roundf(y - radius);
    int y_max = (int)roundf(y + radius);
    
    for (int _x = x_min; _x <= x_max; _x++)
    {
        for (int _y = y_min; _y <= y_max; _y++)
        {
            float dx = _x - x;
            float dy = _y - y;

            bool distance_less_than_radius = dx * dx + dy * dy <= radius * radius;

            if (distance_less_than_radius)
            {
                int index = _y * WIDTH + _x;

                if(index >= 0 && index < (WIDTH*HEIGHT))
                    PutPixel(BlendColor(color, pixels[_y * WIDTH + _x]), _x, _y);
            }
        }
    }
}


__declspec(dllexport) void Render(Mesh mesh, uint body_poly_colors[], Transform camera, bool fill_toggle)
{
    Fill(black);

    //if (mesh.indices?.Length > 0) //TODO?
    {
		size_t triangle_count = mesh.indices_length / 3;
		Triangle* triangles = malloc(triangle_count * sizeof(Triangle));

		//fill triangle list
		{
			int i;
			for (i = 0; i < triangle_count; i++)
			{
				triangles[i].a = mesh.vertices[mesh.indices[i * 3 + 0]];
				triangles[i].b = mesh.vertices[mesh.indices[i * 3 + 1]];
				triangles[i].c = mesh.vertices[mesh.indices[i * 3 + 2]];
				triangles[i].color = body_poly_colors[i];
			}
		}

        //transform points
        {
            //get object transform matrix
            m4x4 object_to_world = m4x4_identity;

            //get camera matrix
            m4x4 world_to_camera = GetMatrix(InvertTransform(camera));

            m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

            for (int i = 0; i < triangle_count; i++)
            {
                Triangle t = triangles[i];

                //To Camera Space
                {
                    t.a = Transform_v3(object_to_camera, t.a);
                    t.b = Transform_v3(object_to_camera, t.b);
                    t.c = Transform_v3(object_to_camera, t.c);
                }

                triangles[i] = t;
            }

			//cull backfaces and perform lighting
			{
				size_t remaining_count = triangle_count;
				for (int i = 0; i < triangle_count; i++)
				{
				label:
					if (i == remaining_count) //TODO verify no off by one error
						break;
					Triangle t = triangles[i];
					v3 a = v3_Subtract(t.b, t.a);
					v3 b = v3_Subtract(t.c, t.a);
					v3 normal = v3_Normalized(CrossProduct(a, b));

					v3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, camera.position));

					if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
					{
						SwapTriangles(triangles, i, remaining_count - 1);
						remaining_count--;
						goto label;//TODO replace with while
					}
					else
					{
						v3 backward = { 0,0,-1 };
						float dot = v3_DotProduct(normal, Transform_v3(Rotation(0, light_rotation, 0), backward));

						if (dot < 0)
							dot = 0;

						if (!isnan(dot))//TODO - remove, just a temporary fix
						{
							t.brightness = (unsigned char)(dot * 255);
							triangles[i] = t;
						}

	                    float light = t.brightness / 255.0f;

	                    uint r = ((t.color & red) ^ black) >> 16;
	                    uint g = ((t.color & green) ^ black) >> 8;
	                    uint b = (t.color & blue) ^ black;

	                    r = (uint)(r * light);
	                    g = (uint)(g * light);
	                    b = (uint)(b * light);

	                    t.color = r << 16 | g << 8 | b | black;
	                    triangles[i] = t;
					}
				}

				triangle_count = remaining_count;
				triangles = realloc(triangles, triangle_count * sizeof(Triangle));
			}

			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangles[i];
				t.a = CameraToClipToScreen(t.a);
				t.b = CameraToClipToScreen(t.b);
				t.c = CameraToClipToScreen(t.c);
				triangles[i] = t;
			}
        }

		//sort triangles by depth painter's algorithm YAY!
		{
			SortByDepth(triangles,triangle_count);
		}

        //rasterize
        {
            for (int i = 0; i < triangle_count; i++)
            {
                Triangle t = triangles[i];
                v2 a = { t.a.x, t.a.y };
                v2 b = { t.b.x, t.b.y };
                v2 c = { t.c.x, t.c.y };

                if(fill_toggle)
                    FillTriangle_VertexColors(a, b, c, red, green, blue);
                else
                    FillTriangle(t.color, (int)t.a.x, (int)t.a.y, (int)t.b.x, (int)t.b.y, (int)t.c.x, (int)t.c.y);
            }
        }

        free(triangles);
    }
}

float GetMin(float a, float b, float c)
{
	float r = (a < b) ? a : b;
	return (r < c) ? r : c;
}

float GetMax(float a, float b, float c)
{
	float r = (a > b) ? a : b;
	return (r > c) ? r : c;
}

v3 ToBarycentricSpace(float v_x, float v_y, v2 a, v2 b, v2 c)
{
    float b1,b2,b3;
    float denom = (a.y-c.y)*(b.x-c.x) + (b.y-c.y)*(c.x-a.x);

    b1 = ((v_y-c.y)*(b.x-c.x) + (b.y-c.y)*(c.x-v_x)) / denom;
    b2 = ((v_y-a.y)*(c.x-a.x) + (c.y-a.y)*(a.x-v_x)) / denom;
    b3 = ((v_y-b.y)*(a.x-b.x) + (a.y-b.y)*(b.x-v_x)) / denom;
    
    v3 result = { b1, b2, b3 };
    return result;
}

void FillTriangle_VertexColors(v2 a, v2 b, v2 c, uint a_color, uint b_color, uint c_color)
{
    int x_min = (int)GetMin(a.x, b.x, c.x);
    int y_min = (int)GetMin(a.y, b.y, c.y);
    int x_max = (int)roundf(GetMax(a.x, b.x, c.x));
    int y_max = (int)roundf(GetMax(a.y, b.y, c.y));
    
    
    for (int _x = x_min; _x <= x_max; _x++)
    {
        for (int _y = y_min; _y <= y_max; _y++)
        {
            v3 v = ToBarycentricSpace(_x, _y, a, b, c);
            bool in_triangle = !(v.x < 0 || v.y < 0 || v.z < 0);
            if(in_triangle)
            {
                uint d_color = LerpColor(c_color, a_color, v.x);
                uint e_color = LerpColor(a_color, b_color, v.y);
                uint f_color = LerpColor(e_color, d_color, v.z);
                PutPixel(f_color, _x, _y);
            }
        }
    }
}

    enum Keys
    {
        Tab = 9, 
        Space = 32,
        Left = 37, Up, Right, Down,
        Delete = 46, 
        A = 65,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, 
        F4 = 115, 
        NumPad0 = 96, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
    };


    enum Buttons
    {
        LEFT,
        RIGHT,
        DOWN,
        JUMP,
        PUNCH
    };

    //Input
    bool* keys_down_c;
    bool* keys_stale_c; //whether a key has been pressed for more than one consecutive frame
    char* keyboard_state_c;

    enum Keys control_mappings[4][5] = //each row represents a player's control scheme
    {
        {A,       D ,       S,		  W,	   Q},
        {J,       L,        K,        I,       U},
        {Left,    Right,    Down,     Up,      Delete},
        {NumPad4, NumPad6,  NumPad5,  NumPad8, NumPad7}
    };

    __declspec(dllexport) InitKeyboard(bool keys_down[256], bool keys_stale[256], char keyboard_state[256])
    {
    	keys_down_c = &keys_down[0];
    	keys_stale_c = &keys_stale[0];
    	keyboard_state_c = &keyboard_state[0];
    }

    __declspec(dllexport) bool KeyDownFresh(enum Keys key) { return keys_down_c[(int)key] && !keys_stale_c[(int)key]; }
    
    __declspec(dllexport) bool KeyDown(enum Keys key) { return keys_down_c[(int)key]; }
    
    __declspec(dllexport) bool ButtonDown(int player, enum Buttons action) { return KeyDown(control_mappings[player][(int)action]); }

    __declspec(dllexport) bool ButtonDownFresh(int player, enum Buttons action) { return KeyDownFresh(control_mappings[player][(int)action]); }


	__declspec(dllexport) void PollKeyboard()
	{            	
		for (int i = 0; i < 256; i++)
			keys_stale_c[i] = keys_down_c[i];

		GetKeyboardState(keyboard_state_c);

		for (int i = 0; i < 256; i++)
			keys_down_c[i] = keyboard_state_c[i] & 128;

		for (int i = 0; i < 256; i++)
		{
			if (!keys_down_c[i])
				keys_stale_c[i] = false;
		}
	}