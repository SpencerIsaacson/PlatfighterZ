#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define byte char
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
	int length;
	char* characters;
} string;

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
void DrawString(string s, int x, int y);
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
void InitViewport(float field_of_view, int width, int height, uint _pixels[]);
void RunMeshDemo(Mesh mesh, Transform camera, float delta_time, float frames_per_second);
void Render(Mesh mesh, uint body_poly_colors[], Transform camera, bool fill_toggle);
void PrintMesh(Mesh mesh);
Mesh LoadMesh(char* path);

uint Darker(uint color)
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

v3 NegateVector(v3 v)
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

m4x4 GetMatrix(Transform t)
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

v4 Transform_Vector4(m4x4 m, v4 v)
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

m4x4 Transpose(m4x4 m)
{
	m4x4 transposed = { m.m11, m.m21, m.m31, m.m41, m.m12, m.m22, m.m32, m.m42, m.m13, m.m23, m.m33, m.m43, m.m14, m.m24, m.m34, m.m44 };
	return transposed;
}

m4x4 Translation(float x, float y, float z)
{
	m4x4 translation = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1 };
	return translation;
}

m4x4 Scale(float x, float y, float z)
{
	m4x4 scale = { x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1 };
	return scale;
}

m4x4 Rotation(float x, float y, float z)
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

v3 v3_Add(v3 a, v3 b)
{
	v3 v;
	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return v;
}

v3 v3_Subtract(v3 a, v3 b)
{
	v3 v;
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return v;
}

v3 CrossProduct(v3 a, v3 b)
{
	v3 result =
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};

	return result;
}

v3 v3_Normalized(v3 v)
{
	return v3_Scale(v, v3_Magnitude(v));
}

float v3_Magnitude(v3 v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

v3 v3_Scale(v3 v, float s)
{
	v3 result = { v.x / s, v.y / s, v.z / s };
	return result;
}

float v3_DotProduct(v3 a, v3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }


v2 Lerp_v2(v2 a, v2 b, float t)
{
	v2 v;
	v.x = a.x + (t * (b.x - a.x));
	v.y = a.y + (t * (b.y - a.y));
	return v;
}

float Lerp_Float(float a, float b, float t)
{
	return a + t * (b - a);
}

//Animate property doesn't work yet
void AnimateProperty(KeyFrame curve[], float frame, float* property)
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

float Sample(KeyFrame a, KeyFrame b, float frame)
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


bool Intersect(Transform a, Transform b)
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


v3 GetCentroid(Triangle t)
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

Mesh mesh;
Transform cube_transform;

__declspec(dllexport) void InitViewport(float field_of_view, int width, int height, uint _pixels[])  //TODO move more state here and out of the "run" arguments
{
	WIDTH = width;
	HEIGHT = height;
	camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);
	pixels = &_pixels[0];
}


__declspec(dllexport) void InitMeshDemo()
{
	mesh = LoadMesh("P:/Assets/teapot.obj");
	cube_transform.parent = -1;
	v3 forward_10 = { 0, 0, 10 };
	v3 zero = { 0, 0, 0 };
	v3 one = { 1, 1, 1 };
	cube_transform.position = forward_10;
	cube_transform.rotation = zero;
	cube_transform.scale = one;
}

__declspec(dllexport) void RunMeshDemo(Mesh mezsh, Transform camera, float delta_time, float frames_per_second)
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
		SortByDepth(triangles, triangle_count);
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

	char result[50];
	sprintf(result, "%.3f", frames_per_second);
	char foo[50];
	strcpy(foo, "FPS: ");

	strcat(foo, result);
	string moopa = { strlen(foo), foo };
	DrawString(moopa, 16, 16);
}

void FillTriangle(uint color, int x1, int y1, int x2, int y2, int x3, int y3)
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

void PutPixel(uint color, int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[y * WIDTH + x] = color;
}

void PutPixel_ByIndex(uint color, int i)
{
	if (i >= 0 && i < WIDTH * HEIGHT)
		pixels[i] = color;
}

v3 CameraToClipToScreen(v3 v)
{
	v4 v_4 = { v.x, v.y, v.z, 1 };
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

void FillVerticalGradient(uint color1, uint color2)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		uint color = LerpColor(color1, color2, y / (float)HEIGHT);
		for (int x = 0; x < WIDTH; x++)
		{
			pixels[y * WIDTH + x] = color;
		}
	}
}

uint LerpColor(uint a, uint b, float t)
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

uint BlendColor(uint s, uint d)
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

void Fill(uint color)
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		pixels[i] = color;
	}
}

__declspec(dllexport) Mesh LoadMesh(char* path)
{
	FILE* fp = fopen(path, "r");
	int line_number = 0;

	int vertex_count = 0;
	int index_count = 0;

	while (true)
	{
		char str[500];
		char* line = fgets(str, 500, fp);
		if (feof(fp))
			break;
		char* token = strtok(line, " ");
		char* ptr;
		switch (*token)
		{
		case 'v':
			vertex_count++;
			break;
		case 'f':
			index_count += 3;
			break;
		default:
			break;
		}
	}

	rewind(fp);

	Mesh return_mesh;
	v3* vertices = malloc(sizeof(v3) * vertex_count);
	int* indices = malloc(sizeof(int) * index_count);

	return_mesh.vertices = vertices;
	return_mesh.vertices_length = vertex_count;
	return_mesh.indices = indices;
	return_mesh.indices_length = index_count;

	int vertex = 0;
	int index = 0;

	while (true)
	{
		char str[500];
		char* line = fgets(str, 500, fp);
		if (feof(fp))
			break;
		line_number++;
		char* token = strtok(line, " ");
		char* ptr;
		switch (*token)
		{
		case 'v':
			token = strtok(NULL, " ");
			float x = (float)strtod(token, &ptr);
			token = strtok(NULL, " ");
			float y = (float)strtod(token, &ptr);
			token = strtok(NULL, " ");
			float z = (float)strtod(token, &ptr);
			v3 v = { x, y, z };
			return_mesh.vertices[vertex++] = v;
			break;
		case 'f':
			token = strtok(NULL, " ");
			int a = (int)strtol(token, &ptr, 10);
			token = strtok(NULL, " ");
			int b = (int)strtol(token, &ptr, 10);
			token = strtok(NULL, " ");
			int c = (int)strtol(token, &ptr, 10);
			return_mesh.indices[index++] = a - 1;
			return_mesh.indices[index++] = b - 1;
			return_mesh.indices[index++] = c - 1;
			break;
		case '\n':
			//empty line
			break;
		default:
			//unsupported line ignored
			break;
		}
	}

	fclose(fp);
	return return_mesh;
}

void DrawHorizontal(uint color, int y)
{
	for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
		PutPixel_ByIndex(color, i);
}

void DrawLine(uint color, float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	if (fabs(dx) >= fabs(dy))
	{
		if (x1 > x2)
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
		if (y1 > y2)
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


void DrawRectangle(uint color, float x, float y, float width, float height)
{
	DrawLine(color, x, y, x + width, y);
	DrawLine(color, x, y, x, y + height);
	DrawLine(color, x + width, y, x + width, y + height);
	DrawLine(color, x, y + height, x + width, y + height);
}

void Flatten()
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		pixels[i] |= black;
	}
}

FillRectangle_Blend(uint color, int x, int y, int width, int height)
{
	for (int _x = 0; _x < width; _x++)
	{
		for (int _y = 0; _y < height; _y++)
		{
			PutPixel(BlendColor(color, pixels[(y + _y) * WIDTH + (x + _x)]), _x + x, _y + y);
		}
	}
}

void  DrawHorizontal_Blend(uint color, int y)
{
	for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
		PutPixel_ByIndex(BlendColor(color, pixels[i]), i);
}

void DrawVertical_Blend(uint color, int x)
{
	for (int i = x; i < (WIDTH * HEIGHT) - WIDTH - x; i += WIDTH)
	{
		PutPixel_ByIndex(BlendColor(color, pixels[i]), i);
	}
}

void DrawVertical(uint color, int x)
{
	for (int i = x; i < (WIDTH * HEIGHT) - WIDTH - x; i += WIDTH)
	{
		pixels[i] = color;
	}
}

void DrawGrid_ScreenSpace(int unit_size)
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

void DrawVerticalSegment(uint color, int x, int y1, int y2)
{
	for (int i = x + (y1 * WIDTH); i <= x + (y2 * WIDTH); i += WIDTH)
		PutPixel_ByIndex(color, i);
}

FillRectangle(uint color, float x, float y, float width, float height)
{
	for (float _x = 0; _x <= width; _x++)
	{
		for (float _y = 0; _y <= height; _y++)
		{
			PutPixel(color, (int)(_x + x), (int)(_y + y));
		}
	}
}

void Draw_Circle(uint color, float x, float y, float radius, float stroke)
{
	int x_min = (int)(x - radius - stroke / 2);
	int x_max = (int)roundf(x + radius + stroke / 2);
	int y_min = (int)(y - radius - stroke / 2);
	int y_max = (int)roundf(y + radius + stroke / 2);

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			float dx = _x - x;
			float dy = _y - y;

			float distance_squared = (float)(dx * dx + dy * dy);
			float distance = (float)sqrt(distance_squared);
			bool distance_equals_radius_within_delta = distance <= radius + stroke / 2 && distance >= radius - stroke / 2;

			if (distance_equals_radius_within_delta)
				PutPixel(color, _x, _y);
		}
	}
}

void FillCircle(uint color, float x, float y, float radius)
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

void Blend_Circle(uint color, float x, float y, float radius)
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

				if (index >= 0 && index < (WIDTH * HEIGHT))
					PutPixel(BlendColor(color, pixels[_y * WIDTH + _x]), _x, _y);
			}
		}
	}
}


__declspec(dllexport) void Render(Mesh mesh, uint* body_poly_colors, Transform camera, bool fill_toggle)
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
			SortByDepth(triangles, triangle_count);
		}

		//rasterize
		{
			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangles[i];
				v2 a = { t.a.x, t.a.y };
				v2 b = { t.b.x, t.b.y };
				v2 c = { t.c.x, t.c.y };

				if (fill_toggle)
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
	float b1, b2, b3;
	float denom = (a.y - c.y) * (b.x - c.x) + (b.y - c.y) * (c.x - a.x);

	b1 = ((v_y - c.y) * (b.x - c.x) + (b.y - c.y) * (c.x - v_x)) / denom;
	b2 = ((v_y - a.y) * (c.x - a.x) + (c.y - a.y) * (a.x - v_x)) / denom;
	b3 = ((v_y - b.y) * (a.x - b.x) + (a.y - b.y) * (b.x - v_x)) / denom;

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
			if (in_triangle)
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
	Keys_Tab = 9,
	Keys_Space = 32,
	Keys_Left = 37, Keys_Up, Keys_Right, Keys_Down,
	Keys_Delete = 46,
	Keys_A = 65, Keys_B, Keys_C, Keys_D, Keys_E, Keys_F, Keys_G, Keys_H, Keys_I, Keys_J, Keys_K, Keys_L, Keys_M, Keys_N, Keys_O, Keys_P, Keys_Q, Keys_R, Keys_S, Keys_T, Keys_U, Keys_V, Keys_W, Keys_X, Keys_Y, Keys_Z,
	Keys_F4 = 115,
	Keys_NumPad0 = 96, Keys_NumPad1, Keys_NumPad2, Keys_NumPad3, Keys_NumPad4, Keys_NumPad5, Keys_NumPad6, Keys_NumPad7, Keys_NumPad8, Keys_NumPad9,
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
bool keys_down[256];
bool keys_stale[256]; //whether a key has been pressed for more than one consecutive frame
bool keyboard_state[256];

enum Keys control_mappings[4][5] = //each row represents a player's control scheme
{
	{Keys_A,       Keys_D ,       Keys_S,		 Keys_W,	   Keys_Q },
	{Keys_J,       Keys_L,        Keys_K,        Keys_I,       Keys_U },
	{Keys_Left,    Keys_Right,    Keys_Down,     Keys_Up,      Keys_Delete },
	{Keys_NumPad4, Keys_NumPad6,  Keys_NumPad5,  Keys_NumPad8, Keys_NumPad7 }
};

__declspec(dllexport) bool KeyDownFresh(enum Keys key)
{
	return keys_down[key] && !keys_stale[key];
}

__declspec(dllexport) bool KeyDown(enum Keys key)
{
	return keys_down[key];
}

bool ButtonDown(int player, enum Buttons action)
{
	return KeyDown(control_mappings[player][action]);
}

bool ButtonDownFresh(int player, enum Buttons action)
{
	return KeyDownFresh(control_mappings[player][action]);
}

__declspec(dllexport) void PollKeyboard()
{
	for (int i = 0; i < 256; i++)
		keys_stale[i] = keys_down[i];

	GetKeyboardState(keyboard_state);

	for (int i = 0; i < 256; i++)
		keys_down[i] = keyboard_state[i] & 128;

	for (int i = 0; i < 256; i++)
	{
		if (!keys_down[i])
			keys_stale[i] = false;
	}
}

typedef struct
{
	int bone1, bone2, bone3, bone4;
} Weight_Index;

typedef struct
{
	Mesh mesh;
	int body_poly_colors_length;
	uint* body_poly_colors;
	int skeleton_length;
	Transform* skeleton;
	int bind_matrices_length;
	m4x4* bind_matrices;
	int weights_length;
	v4* weights;
	int weight_indices_length;
	Weight_Index* weight_indices;
	//Dictionary<int, Vector3>[] morphs = new Dictionary<int, Vector3>[5];
	int morph_weights_length;
	float* morph_weights;
	v3 transformed_vertices_length;
	v3* transformed_vertices;
	Transform camera;

	bool has_a_face;
	bool animate_face;
	int facial_index_offset;
	bool fill_toggle;

	float frame;
	float animation_length;
	float rotation_y;
	bool animation_play;
	bool rotation_play;
	bool view_debug;
	bool view_fps;
	float facial_time;
} SkinnedMeshDemo;

SkinnedMeshDemo skinned_demo;

void SetWeights()
{
//    fixed (Vector4* p = new Vector4[mesh.vertices_length])
//    {
//        weights = p;
//        weights_length = mesh.vertices_length;
//    }

//    fixed (Weight_Index* p = new Weight_Index[mesh.vertices_length])
//    {
//        weight_indices = p;
//    }

//    for (int i = 0; i < mesh.vertices_length; i++)
//        weights[i] = new Vector4(1, 0, 0, 0);

//    Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(GetAssetPathPrefix() + "weight_indices");
//    using (BinaryReader reader = new BinaryReader(stream))
//    {
//        List<Weight_Index> weight_index_list = new List<Weight_Index>();
//        while (reader.BaseStream.Position != reader.BaseStream.Length)
//        {
//            Weight_Index w = new Weight_Index();
//            w.bone1 = reader.ReadInt32();
//            w.bone2 = reader.ReadInt32();
//            w.bone3 = reader.ReadInt32();
//            w.bone4 = reader.ReadInt32();
//            weight_index_list.Add(w);
//        }

//        fixed (Weight_Index* p = weight_index_list.ToArray())
//        {
//            weight_indices = p;
//        }
//    }
}

__declspec(dllexport) void SkinnedMeshDemo_Init()
{
	Transform camera = { 0, { 0, 0, -50 }, { 0, 0, 0 }, { 1, 1, 1 } };
	skinned_demo.camera = camera;
	skinned_demo.mesh = LoadMesh("P:/Assets/skin_translated.obj");

	//skeleton = LoadHierarchy("avatar");
	//skeleton_length = skeleton.Length;

	//if (has_a_face)
	//{
	//	//load face
	//	Mesh face = LoadMesh("face.obj");
	//	Mesh smile = LoadMesh("smile.obj");
	//	Mesh angry_eyes = LoadMesh("angry_eyes.obj");

	//	//adjust head vertices
	//	{
	//		mesh.vertices[08].z -= .3f;
	//		mesh.vertices[01].z -= .2f;
	//		mesh.vertices[21].z -= .2f;

	//		mesh.vertices[07].z -= .3f;
	//		mesh.vertices[22].z -= .3f;
	//		mesh.vertices[14].z -= .3f;
	//		mesh.vertices[19].z -= .3f;
	//		mesh.vertices[29].z -= .3f;
	//		mesh.vertices[32].z -= .3f;
	//	}

	//	//Attach face
	//	//mesh = AppendMesh(mesh, face);

	//	//build facial morph targets
	//	{
	//		//morphs[0] = new Dictionary<int, Vector3>();
	//		//for (int i = 0; i < smile.vertices.Length; i++)
	//		//{
	//		//    if (smile.vertices[i] - face.vertices[i] != Vector3.Zero)
	//		//    {
	//		//        morphs[0].Add(i, smile.vertices[i]);
	//		//    }
	//		//}

	//		//morphs[1] = new Dictionary<int, Vector3>();
	//		//for (int i = 0; i < angry_eyes.vertices.Length; i++)
	//		//{
	//		//    if (angry_eyes.vertices[i] - face.vertices[i] != Vector3.Zero)
	//		//    {
	//		//        morphs[1].Add(i, angry_eyes.vertices[i]);
	//		//    }
	//		//}
	//	}
	//}

	////TODO replace with files to load
	//PointerCountArray<uint> poly_colors = LoadPolygonColors("skin_poly_colors");
	int triangle_count = skinned_demo.mesh.indices_length / 3;

	skinned_demo.body_poly_colors = malloc(triangle_count * sizeof(uint)); //TODO malloc the correct size (the number of triangles, which is 1/3 the number of indices)
	
	//todo load triangle colors from file
	for (int i = 0; i < triangle_count; i++)
	{
		skinned_demo.body_poly_colors[i] = red;
	}

	skinned_demo.body_poly_colors_length = triangle_count;

	SetWeights();

	////build bind matrices
	//{
	//	fixed(Matrix4x4 * p = new Matrix4x4[skeleton_length])
	//	{
	//		bind_matrices = p;
	//		bind_matrices_length = skeleton.Length;
	//	}

	//	Transform[] bind_transforms = new Transform[skeleton_length];

	//	for (int i = 0; i < bind_matrices_length; i++)
	//	{
	//		bind_transforms[i] = InvertTransform(skeleton[i]);
	//		bind_matrices[i] = WorldSpaceMatrix(i, bind_transforms);
	//	}
	//}

	//fixed(Vector3 * p = new Vector3[c_mesh.vertices_length])
	//{
	//	transformed_vertices = p;
	//	transformed_vertices_length = c_mesh.vertices_length;
	//}
	//skeleton[0].position.y = -1;
}


void SkinnedMeshDemo_Input(float delta_time)
{
	float delta = 5 * delta_time;
	if (KeyDownFresh(Keys_Y))
		skinned_demo.view_fps = !skinned_demo.view_fps;

	if (KeyDownFresh(Keys_G))
		skinned_demo.view_debug = !skinned_demo.view_debug;
	if (KeyDown(Keys_W))
		skinned_demo.camera.position.y -= delta;
	if (KeyDown(Keys_S))
		skinned_demo.camera.position.y += delta;
	if (KeyDown(Keys_A))
		skinned_demo.camera.position.x += delta;
	if (KeyDown(Keys_D))
		skinned_demo.camera.position.x -= delta;

	if (KeyDown(Keys_Up))
		skinned_demo.camera.position.z += delta * 10;
	else if (KeyDown(Keys_Down))
		skinned_demo.camera.position.z -= delta * 10;

	if (KeyDownFresh(Keys_T))
	{
		skinned_demo.animation_play = !skinned_demo.animation_play;
	}

	if (KeyDownFresh(Keys_Q))
	{
		skinned_demo.animate_face = !skinned_demo.animate_face;
	}

	if (KeyDownFresh(Keys_F))
	{
		skinned_demo.has_a_face = !skinned_demo.has_a_face;
		//skinned_demo.BuildGuy();
	}

	if (KeyDownFresh(Keys_R))
	{
		skinned_demo.rotation_play = !skinned_demo.rotation_play;
	}

	if (KeyDownFresh(Keys_Space))
		skinned_demo.fill_toggle = !skinned_demo.fill_toggle;
}

__declspec(dllexport) void SkinnedMeshDemo_Update(float delta_time)
{
	SkinnedMeshDemo_Input(delta_time);

	//Animate
	{
		if (skinned_demo.rotation_play)
		{
			skinned_demo.rotation_y += delta_time;
			//skinned_demo.skeleton[0].rotation.y = skinned_demo.rotation_y;
		}

		if (skinned_demo.animation_play)
		{
			//Animate Skeleton
			{
				//foreach(AnimationCurve curve in DefinedAnimations.walk_animation.curves)
				//{
				//	KeyFrame[] keyframes = curve.keyframes;
				//	int transform_index = curve.transform_index;

				//	fixed(Transform * p = &skinned_demo.skeleton[transform_index])
				//	{
				//		float* f = &(*p).position.x + curve.property_tag;
				//		AnimateProperty(keyframes, skinned_demo.frame, f);
				//	}

				//}
			}
		}

	m4x4 skeleton_matrices[skinned_demo.skeleton_length];

	//Get Skeleton Matrices
	{
		for (int i = 0; i < skinned_demo.skeleton_length; i++)
		{
			skeleton_matrices[i] = WorldSpaceMatrix(i, skinned_demo.skeleton);
		}
	}

	//	//Apply Mesh Skinning
	//	{
	//		for (int i = 0; i < skinned_demo.c_mesh.vertices_length; i++)
	//		{
	//			Vector3 v_a = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone1] * skeleton_matrices[skinned_demo.weight_indices[i].bone1] * skinned_demo.mesh.vertices[i];
	//			Vector3 v_b = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone2] * skeleton_matrices[skinned_demo.weight_indices[i].bone2] * skinned_demo.mesh.vertices[i];
	//			Vector3 v_c = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone3] * skeleton_matrices[skinned_demo.weight_indices[i].bone3] * skinned_demo.mesh.vertices[i];
	//			Vector3 v_d = skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone4] * skeleton_matrices[skinned_demo.weight_indices[i].bone4] * skinned_demo.mesh.vertices[i];

	//			skinned_demo.transformed_vertices[i] = (v_a * skinned_demo.weights[i].x) + (v_b * skinned_demo.weights[i].y) + (v_c * skinned_demo.weights[i].z) + (v_d * skinned_demo.weights[i].w);
	//		}
	//	}

	//	//Apply Facial Morph Targets
	//	{
	//		//if (skinned_demo.has_a_face && skinned_demo.animate_face)
	//		//{
	//		//    Vector3[] deltas = new Vector3[259];
	//		//    for (int morph_index = 0; morph_index < skinned_demo.morphs_length; morph_index++)
	//		//    {
	//		//        if (skinned_demo.morphs[morph_index] != null)
	//		//        {
	//		//            var current_morph = skinned_demo.morphs[morph_index];

	//		//            foreach (var entry in current_morph)
	//		//            {
	//		//                int key = entry.Key;
	//		//                Vector3 point = entry.Value;
	//		//                int vertex_index = key + skinned_demo.facial_index_offset;
	//		//                Weight_Index weight_index = skinned_demo.weight_indices[vertex_index];
	//		//                Vector4 weight = skinned_demo.weights[key];

	//		//                Vector3 v_a = skinned_demo.bind_matrices[weight_index.bone1] * skeleton_matrices[weight_index.bone1] * point;
	//		//                Vector3 v_b = skinned_demo.bind_matrices[weight_index.bone2] * skeleton_matrices[weight_index.bone2] * point;
	//		//                Vector3 v_c = skinned_demo.bind_matrices[weight_index.bone3] * skeleton_matrices[weight_index.bone3] * point;
	//		//                Vector3 v_d = skinned_demo.bind_matrices[weight_index.bone4] * skeleton_matrices[weight_index.bone4] * point;

	//		//                Vector3 skinned_morph = (v_a * weight.x) + (v_b * weight.y) + (v_c * weight.z) + (v_d * weight.w);

	//		//                deltas[key] += (skinned_morph - skinned_demo.transformed_vertices[vertex_index]) * skinned_demo.morph_weights[morph_index];
	//		//            }
	//		//        }
	//		//    }

	//		//    for (int i = 0; i < deltas.Length; i++)
	//		//    {
	//		//        int vertex_index = i + skinned_demo.facial_index_offset;
	//		//        skinned_demo.transformed_vertices[vertex_index] += deltas[i];
	//		//    }
	//		//}

	//		//skinned_demo.morph_weights[0] = ((float)Math.Cos(skinned_demo.facial_time * 2) + 1) / 2;
	//		//skinned_demo.morph_weights[1] = ((float)Math.Sin(skinned_demo.facial_time * 2) + 1) / 2;

	//		//skinned_demo.facial_time += delta_time;
	//	}

	//	//Advance Animation Time
	//	{
	//		skinned_demo.frame += TARGET_FRAMERATE * delta_time;
	//		skinned_demo.frame %= skinned_demo.animation_length;
	//	}
	}



	//C_Mesh c_mesh = new C_Mesh();

	//c_mesh.vertices = skinned_demo.transformed_vertices;
	//c_mesh.indices = skinned_demo.c_mesh.indices;
	//c_mesh.indices_length = skinned_demo.c_mesh.indices_length;
	//c_mesh.vertices_length = skinned_demo.transformed_vertices_length;

	Render(skinned_demo.mesh, skinned_demo.body_poly_colors, skinned_demo.camera, skinned_demo.fill_toggle);
}

typedef struct
{
	int transform_index;
	char property_tag;
	int keyframes_length;
	KeyFrame* keyframes;
} AnimationCurve;

typedef struct
{
	bool looped;
	int curves_length;
	AnimationCurve* curves;
	int** defendbox_keys;
	bool** defendbox_values;
	int** attackbox_keys;
	bool** attackbox_values;
} Animation;

typedef struct
{
	float current_frame;
	Animation current_animation;
} Animator;

#define PLAYER_COUNT 4 //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players

typedef struct
{
	bool view_debug;//false;

	//Game World
	Transform camera;
	float field_of_view;// 3 / 8f * Tau;
	Transform* transforms;
	Player players[PLAYER_COUNT];
	Animator animators[PLAYER_COUNT];
	uint player_colors[PLAYER_COUNT];// = new uint[]{ red, 0xFF008000, blue, purple };
	Transform blocks[30];

	//Play variables
	int winner;// = 0;
	bool game_over;// = false;
	float initial_time;// = 99;
	float time_remaining;
	float max_health;// = 10;

	//physics
	float gravity;// = 10;


} GameplayState;


__declspec(dllexport) void UpdateGameplay(GameplayState state)
{
	//	//Update
	//	{
	//		//Get Debug Input
	//		{
	//			if (Input.KeyDownFresh(Keys.G))
	//				state.view_debug = !state.view_debug;

	//			if (Input.KeyDownFresh(Keys.R))
	//				Game.ResetGame(state);

	//			if (Input.KeyDownFresh(Keys.F))
	//				fixed_framerate = !fixed_framerate;
	//		}

	//		if (!state.game_over)
	//		{
	//			for (int player_index = 0; player_index < GameplayState.PLAYER_COUNT; player_index++)
	//			{
	//				fixed(Transform * playerTransform = &(state.transforms[GameplayState.players[player_index].entity_ID]))
	//				{
	//					//Animate Player
	//					{
	//						KeyFrame[] first_curve_frames = state.animators[player_index].current_animation.curves[0].keyframes;
	//						float ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;

	//						if (!GameplayState.players[player_index].defeated)
	//						{
	//							//Set Animation State
	//							{
	//								bool moving = false;

	//								if (state.animators[player_index].current_animation.curves != DefinedAnimations.punch_curves) //TODO use animation, not just curves
	//								{
	//									if (Input.ButtonDown(player_index, Buttons.LEFT))
	//									{
	//										(*playerTransform).rotation.y = -1 / 4f * Tau;
	//										moving = true;
	//									}

	//									if (Input.ButtonDown(player_index, Buttons.RIGHT))
	//									{
	//										(*playerTransform).rotation.y = 1 / 4f * Tau;
	//										moving = true;
	//									}

	//									if (moving)
	//									{
	//										state.animators[player_index].current_animation = DefinedAnimations.walk_animation;
	//										var rotation = (*playerTransform).rotation;
	//									}
	//									else
	//										state.animators[player_index].current_animation = DefinedAnimations.idle_animation;

	//									if (Input.ButtonDown(player_index, Buttons.PUNCH))
	//									{
	//										state.animators[player_index].current_animation = DefinedAnimations.punch_animation;
	//										state.animators[player_index].current_frame = 1;
	//									}
	//								}
	//								else if (state.animators[player_index].current_frame >= ending_frame)
	//								{
	//									state.animators[player_index].current_animation = DefinedAnimations.idle_animation;
	//									state.animators[player_index].current_frame = 1;
	//								}
	//							}
	//						}

	//						//Play Animation
	//						{
	//							Animator animator = state.animators[player_index];
	//							if (animator.current_animation.looped && animator.current_frame >= ending_frame)
	//								animator.current_frame = 1;


	//							float frame = state.animators[player_index].current_frame;

	//							foreach(AnimationCurve curve in animator.current_animation.curves)
	//							{
	//								KeyFrame[] keyframes = curve.keyframes;
	//								int transform_index = curve.transform_index + player_index * state.skeleton.Length;

	//								fixed(Transform * p = &state.transforms[transform_index])
	//								{
	//									float* f = &(*p).position.x + curve.property_tag;

	//									AnimateProperty(keyframes, frame, f);
	//								}
	//							}

	//							for (int attackbox_index = 0; attackbox_index < GameplayState.players[player_index].attackboxes.Length; attackbox_index++)
	//							{
	//								if (animator.current_animation.attackbox_keys != null)
	//									for (int i = 0; i < animator.current_animation.attackbox_keys[attackbox_index].Length; i++)
	//									{
	//										if (frame > animator.current_animation.attackbox_keys[attackbox_index][i])
	//										{
	//											GameplayState.players[player_index].attackboxes[attackbox_index].active = animator.current_animation.attackbox_values[attackbox_index][i];
	//										}
	//									}
	//							}

	//							for (int defendbox_index = 0; defendbox_index < GameplayState.players[player_index].defendboxes.Length; defendbox_index++)
	//							{
	//								if (animator.current_animation.defendbox_keys != null)
	//									for (int i = 0; i < animator.current_animation.defendbox_keys[defendbox_index].Length; i++)
	//									{
	//										if (frame > animator.current_animation.defendbox_keys[defendbox_index][i])
	//										{
	//											GameplayState.players[player_index].defendboxes[defendbox_index].active = animator.current_animation.defendbox_values[defendbox_index][i];
	//										}
	//									}
	//							}

	//							animator.current_frame += TARGET_FRAMERATE * delta_time;

	//							state.animators[player_index] = animator;
	//						}
	//					}

	//					//Move Player
	//					{
	//						float acceleration = 100f;
	//						float jump_speed = 8;
	//						float max_speed = 5;
	//						float slide_coefficient = 0;
	//						bool no_horizontal_input = false;
	//						float ground_fall_velocity = -.01f;

	//						if (!GameplayState.players[player_index].defeated)
	//						{
	//							if (Input.ButtonDown(player_index, Buttons.RIGHT))
	//								GameplayState.players[player_index].velocity.x += acceleration * delta_time;
	//							else if (Input.ButtonDown(player_index, Buttons.LEFT))
	//								GameplayState.players[player_index].velocity.x -= acceleration * delta_time;
	//							else
	//								no_horizontal_input = true;
	//						}

	//						if (GameplayState.players[player_index].velocity.x > max_speed)
	//							GameplayState.players[player_index].velocity.x = max_speed;
	//						else if (GameplayState.players[player_index].velocity.x < -max_speed)
	//							GameplayState.players[player_index].velocity.x = -max_speed;

	//						if (GameplayState.players[player_index].grounded)
	//						{
	//							GameplayState.players[player_index].velocity.y = ground_fall_velocity;

	//							if (no_horizontal_input)
	//								GameplayState.players[player_index].velocity.x *= slide_coefficient;

	//							if (!GameplayState.players[player_index].defeated && Input.ButtonDown(player_index, Buttons.JUMP))
	//								GameplayState.players[player_index].velocity.y = jump_speed;
	//						}
	//						else
	//						{
	//							GameplayState.players[player_index].velocity.y -= state.gravity * delta_time;
	//						}

	//						float ax_half = state.transforms[GameplayState.players[player_index].entity_ID].scale.x / 2;
	//						float ay_half = state.transforms[GameplayState.players[player_index].entity_ID].scale.y / 2;


	//						var old_x = state.transforms[GameplayState.players[player_index].entity_ID].position.x;
	//						state.transforms[GameplayState.players[player_index].entity_ID].position.x += GameplayState.players[player_index].velocity.x * delta_time;

	//						for (int i = 0; i < state.blocks.Length; i++)
	//						{
	//							var b = state.blocks[i];
	//							if (Intersect(state.transforms[GameplayState.players[player_index].entity_ID], b))
	//							{
	//								if (old_x < b.position.x)
	//									state.transforms[GameplayState.players[player_index].entity_ID].position.x -= (state.transforms[GameplayState.players[player_index].entity_ID].position.x + (state.transforms[GameplayState.players[player_index].entity_ID].scale.x / 2)) - (b.position.x - (b.scale.x / 2));
	//								else if (old_x > b.position.x)
	//									state.transforms[GameplayState.players[player_index].entity_ID].position.x += (b.position.x + (b.scale.x / 2)) - (state.transforms[GameplayState.players[player_index].entity_ID].position.x - (state.transforms[GameplayState.players[player_index].entity_ID].scale.x / 2));
	//							}
	//						}

	//						var old_y = state.transforms[GameplayState.players[player_index].entity_ID].position.y;
	//						state.transforms[GameplayState.players[player_index].entity_ID].position.y += GameplayState.players[player_index].velocity.y * delta_time;

	//						GameplayState.players[player_index].grounded = false;

	//						for (int i = 0; i < state.blocks.Length; i++)
	//						{
	//							var b = state.blocks[i];
	//							if (Intersect(state.transforms[GameplayState.players[player_index].entity_ID], b))
	//							{
	//								if (old_y < b.position.y)
	//								{
	//									state.transforms[GameplayState.players[player_index].entity_ID].position.y -= (state.transforms[GameplayState.players[player_index].entity_ID].position.y + (state.transforms[GameplayState.players[player_index].entity_ID].scale.y / 2)) - (b.position.y - (b.scale.y / 2));
	//									GameplayState.players[player_index].velocity.y = 0;
	//								}
	//								else if (old_y > b.position.y)
	//								{
	//									state.transforms[GameplayState.players[player_index].entity_ID].position.y += (b.position.y + (b.scale.y / 2)) - (state.transforms[GameplayState.players[player_index].entity_ID].position.y - (state.transforms[GameplayState.players[player_index].entity_ID].scale.y / 2));
	//									GameplayState.players[player_index].grounded = true;
	//								}
	//							}
	//						}

	//						if (state.transforms[GameplayState.players[player_index].entity_ID].position.Magnitude() > 50)
	//						{
	//							state.transforms[GameplayState.players[player_index].entity_ID].position = Vector3.Zero;
	//							GameplayState.players[player_index].stock--;
	//						}
	//					}

	//				}

	//				//Hurt Player --TODO fix. also make sure only applies the first time on the first frame of an intersection with first defendbox. Is currently be multiple damaging.
	//				{
	//					for (int my_attack = 0; my_attack < GameplayState.players[player_index].attackboxes.Length; my_attack++)
	//					{
	//						if (GameplayState.players[player_index].attackboxes[my_attack].active)
	//							for (int other_player = 0; other_player < GameplayState.PLAYER_COUNT; other_player++)
	//							{
	//								if (other_player == player_index)
	//									continue;
	//								for (int your_defend = 0; your_defend < GameplayState.players[other_player].defendboxes.Length; your_defend++)
	//								{
	//									var a = WorldSpaceMatrix(GameplayState.players[player_index].attackboxes[my_attack].transform_index, state.transforms);
	//									var b = WorldSpaceMatrix(GameplayState.players[other_player].defendboxes[your_defend].transform_index, state.transforms);

	//									Vector3 v = Transform_v3(a, Vector3.Zero);
	//									Vector3 w = Transform_v3(b, Vector3.Zero);

	//									var dist = Vector3.Distance(v, w);
	//									bool intersects = (dist <= (GameplayState.players[other_player].defendboxes[your_defend].radius + GameplayState.players[player_index].attackboxes[my_attack].radius));

	//									if (intersects)
	//									{
	//										GameplayState.players[other_player].current_health -= 10 * delta_time;
	//										if (GameplayState.players[other_player].current_health <= 0)
	//										{
	//											GameplayState.players[other_player].stock--;
	//											if (GameplayState.players[other_player].stock > 0)
	//												GameplayState.players[other_player].current_health = state.max_health;
	//											else if (!GameplayState.players[other_player].defeated)
	//											{
	//												GameplayState.players[other_player].defeated = true;
	//												state.animators[other_player].current_animation = DefinedAnimations.die_animation;
	//												state.animators[other_player].current_frame = 1;
	//											}
	//										}
	//									}
	//								}
	//							}
	//					}
	//				}
	//			}

	//			//Update Camera
	//			{
	//				//TODO actual frustum check to keep players on screen
	//				float min_x = float.MaxValue;
	//				float min_y = float.MaxValue;

	//				float max_x = -float.MaxValue;
	//				float max_y = -float.MaxValue;

	//				foreach(var player in GameplayState.players)
	//				{
	//					var x = state.transforms[player.entity_ID].position.x;
	//					var y = state.transforms[player.entity_ID].position.y;

	//					if (x < min_x)
	//						min_x = x;
	//					if (x > max_x)
	//						max_x = x;

	//					if (y < min_y)
	//						min_y = y;
	//					if (y > max_y)
	//						max_y = y;
	//				}

	//				state.camera.position.x = (max_x + min_x) / 2;
	//				state.camera.position.y = (max_y + min_y) / 2;
	//				state.camera.position.z = -20 - (max_x - min_x);
	//			}

	//			//Check Match Complete
	//			{
	//				int remaining_players = 0;

	//				for (int i = 0; i < GameplayState.PLAYER_COUNT; i++)
	//				{
	//					if (!GameplayState.players[i].defeated)
	//					{
	//						remaining_players++;
	//						state.winner = i + 1;
	//					}
	//				}

	//				if (remaining_players != 1)
	//					state.winner = 0;

	//				state.time_remaining -= delta_time;
	//				state.game_over = state.winner != 0 || remaining_players == 0 || state.time_remaining <= 0;
	//			}
	//		}
	//	}

	//	//Render
	//	{
	//		FillVerticalGradient(cyan, 0xFF_00_44_AA);

	//		//Draw Scene
	//		{
	//			//get camera matrix
	//			Matrix4x4 world_to_camera = GetMatrix(InvertTransform(state.camera));


	//			//Draw Blocks
	//			{
	//				for (int i = 0; i < state.blocks.Length; i++)
	//				{
	//					Matrix4x4 local_to_world = WorldSpaceMatrix(i, state.blocks);
	//					Matrix4x4 camera_to_clip = Perspective(0.1f, 100, state.field_of_view, WIDTH, HEIGHT);
	//					Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

	//					Vector4 position = new Vector4(-.5f, .5f, 0, 1);
	//					position = Transform_Vector4(local_to_clip, position);

	//					if (position.w != 0)
	//						position /= position.w;

	//					//place origin at center of screen
	//					position.x++;
	//					position.y++;

	//					//scale space to fill screen
	//					position.x *= WIDTH / 2;
	//					position.y *= HEIGHT / 2;

	//					Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
	//					position2 = Transform_Vector4(local_to_clip, position2);

	//					if (position2.w != 0)
	//						position2 /= position2.w;

	//					//place origin at center of screen
	//					position2.x++;
	//					position2.y++;

	//					//scale space to fill screen
	//					position2.x *= WIDTH / 2;
	//					position2.y *= HEIGHT / 2;

	//					float width = position2.x - position.x;
	//					float height = position2.y - position.y;
	//					FillRectangle(brown, position.x, position.y, width, height);
	//				}
	//			}

	//			Vector3[] transformed_positions = new Vector3[state.transforms.Length];

	//			//Draw Transforms
	//			{
	//				for (int i = 0; i < state.transforms.Length; i++)
	//				{
	//					Matrix4x4 local_to_world = WorldSpaceMatrix(i, state.transforms);
	//					Matrix4x4 local_to_camera = local_to_world * world_to_camera;

	//					Vector3 position = Transform_v3(local_to_camera, Vector3.Zero);

	//					Matrix4x4 camera_to_clip = Perspective(0.1f, 100, state.field_of_view, WIDTH, HEIGHT);

	//					var v4 = new Vector4(position.x, position.y, position.z, 1);
	//					v4 = Transform_Vector4(camera_to_clip, v4);

	//					position = new Vector3(v4.x, v4.y, v4.z);

	//					if (v4.w != 0)
	//						position /= v4.w;

	//					//place origin at center of screen
	//					position.x++;
	//					position.y++;

	//					//scale space to fill screen
	//					position.x *= WIDTH / 2;
	//					position.y *= HEIGHT / 2;

	//					transformed_positions[i] = position;
	//				}

	//				for (int i = 0; i < transformed_positions.Length; i++)
	//				{
	//					var position = transformed_positions[i];
	//					var parent_position = position;

	//					if (state.transforms[i].parent != -1)
	//						parent_position = transformed_positions[state.transforms[i].parent];

	//					float d = state.camera.position.z - position.z;
	//					float width = 450 / (d);
	//					float half_width = width / 2;

	//					DrawLine(GameplayState.player_colors[i / state.GetSkeleton().Length], position.x, position.y, parent_position.x, parent_position.y);
	//					Draw_Circle(GameplayState.player_colors[i / state.GetSkeleton().Length], position.x, position.y, -half_width, 1);
	//				}
	//			}

	//			if (state.view_debug)
	//			{
	//				//Draw Hitboxes
	//				{
	//					for (int player_index = 0; player_index < GameplayState.PLAYER_COUNT; player_index++)
	//					{
	//						for (int attackbox_index = 0; attackbox_index < GameplayState.players[player_index].attackboxes.Length; attackbox_index++)
	//						{
	//							if (GameplayState.players[player_index].attackboxes[attackbox_index].active)
	//							{
	//								Vector3 center = transformed_positions[GameplayState.players[player_index].attackboxes[attackbox_index].transform_index];
	//								float width = GameplayState.players[player_index].attackboxes[attackbox_index].radius * 2 * PIXELS_PER_UNIT;
	//								GameplayState.DrawHitbox(center, red, width);
	//							}
	//						}

	//						for (int i = 0; i < GameplayState.players[player_index].defendboxes.Length; i++)
	//						{

	//							if (GameplayState.players[player_index].defendboxes[i].active)
	//							{
	//								Vector3 center = transformed_positions[GameplayState.players[player_index].defendboxes[i].transform_index];
	//								float d = state.camera.position.z - center.z;
	//								float width = 30 * (GameplayState.players[player_index].defendboxes[i].radius * 2 * PIXELS_PER_UNIT) / (d);
	//								GameplayState.DrawHitbox(center, blue, -width);
	//							}
	//						}
	//					}
	//				}

	//				//Draw Colliders
	//				{
	//					for (int i = 0; i < state.blocks.Length; i++)
	//					{
	//						Matrix4x4 local_to_world = WorldSpaceMatrix(i, state.blocks);
	//						Matrix4x4 camera_to_clip = Perspective(0.1f, 100, state.field_of_view, WIDTH, HEIGHT);
	//						Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

	//						Vector4 position = new Vector4(-.5f, .5f, 0, 1);
	//						position = Transform_Vector4(local_to_clip, position);

	//						if (position.w != 0)
	//							position /= position.w;

	//						//place origin at center of screen
	//						position.x++;
	//						position.y++;

	//						//scale space to fill screen
	//						position.x *= WIDTH / 2;
	//						position.y *= HEIGHT / 2;

	//						Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
	//						position2 = Transform_Vector4(local_to_clip, position2);

	//						if (position2.w != 0)
	//							position2 /= position2.w;

	//						//place origin at center of screen
	//						position2.x++;
	//						position2.y++;

	//						//scale space to fill screen
	//						position2.x *= WIDTH / 2;
	//						position2.y *= HEIGHT / 2;

	//						DrawRectangle(blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
	//					}

	//					for (int i = 0; i < GameplayState.players.Length; i++)
	//					{
	//						Matrix4x4 local_to_world = WorldSpaceMatrix(GameplayState.players[i].entity_ID, state.transforms);
	//						Matrix4x4 camera_to_clip = Perspective(0.1f, 100, state.field_of_view, WIDTH, HEIGHT);
	//						Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

	//						Vector4 position = new Vector4(-.5f, .5f, 0, 1);
	//						position = Transform_Vector4(local_to_clip, position);

	//						if (position.w != 0)
	//							position /= position.w;

	//						//place origin at center of screen
	//						position.x++;
	//						position.y++;

	//						//scale space to fill screen
	//						position.x *= WIDTH / 2;
	//						position.y *= HEIGHT / 2;

	//						Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
	//						position2 = Transform_Vector4(local_to_clip, position2);

	//						if (position2.w != 0)
	//							position2 /= position2.w;

	//						//place origin at center of screen
	//						position2.x++;
	//						position2.y++;

	//						//scale space to fill screen
	//						position2.x *= WIDTH / 2;
	//						position2.y *= HEIGHT / 2;

	//						DrawRectangle(blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
	//					}
	//				}
	//			}
	//		}

	//		//Draw Heads-Up Display (HUD)
	//		{
	//			var available_space = WIDTH / GameplayState.PLAYER_COUNT;
	//			int indent_x = 30;
	//			int indent_y = 10;
	//			int max_width = available_space - indent_x * 2;
	//			int health_height = 15;
	//			int padding = 4;
	//			int half_padding = padding / 2;
	//			for (int player = 0; player < GameplayState.PLAYER_COUNT; player++)
	//			{
	//				//Draw HealthBar
	//				{
	//					float portion = GameplayState.players[player].current_health / state.max_health;
	//					int current_width = (int)(portion * max_width);
	//					int x_pos = indent_x + available_space * player;
	//					int padded_height = health_height - padding;
	//					int padded_x_pos = x_pos + half_padding;
	//					int padded_y_pos = indent_y + half_padding;

	//					FillRectangle(black, x_pos, indent_y, max_width, health_height);
	//					FillRectangle(red, padded_x_pos, padded_y_pos, max_width - padding, padded_height);
	//					FillRectangle(green, padded_x_pos, padded_y_pos, current_width - padding, padded_height);
	//				}

	//				//Draw Stocks
	//				{
	//					for (int stock = 0; stock < GameplayState.players[player].stock; stock++)
	//					{
	//						FillCircle(GameplayState.player_colors[player], available_space * player + indent_x + 10 + (stock * (20 + 5)), 40, 10);
	//						Draw_Circle(black, available_space * player + indent_x + 10 + (stock * (25)), 40, 10, 3f);
	//					}
	//				}
	//			}

	//			//Draw Timer
	//			{
	//				int char_sprite_size = 8;
	//				DrawString($"{state.time_remaining:F0}", WIDTH / 2 - char_sprite_size * (((int)state.time_remaining).ToString().Length - 1), char_sprite_size * 2);
	//			}

	//			if (state.game_over)
	//			{
	//				//Draw Game End Message
	//				{
	//					int offset_x = WIDTH / 2, offset_y = HEIGHT / 2;

	//					string message = (state.winner == 0) ? "TIE!" : ("PLAYER " + state.winner + " WINS!");
	//					DrawString(message, offset_x - 5, offset_y - 5);
	//					DrawString(message, offset_x, offset_y);
	//				}
	//			}
	//		}

	//		if (state.view_debug)
	//		{
	//			//Display Game Stats
	//			{
	//				DrawString($"FPS: {frames_per_second:F2}", PIXELS_PER_UNIT / 2, 50);
	//				DrawString($"delta_time: {delta_time:F9}", PIXELS_PER_UNIT / 2, 65);
	//			}
	//		}

	//		Flatten();
	//		OutputRender();
	//	}
}


void GameplayState_Init(GameplayState state)
{
	//ResetGame(state);
	//for (int i = 0; i < state.blocks.Length; i++)
	//{
	//	state.blocks[i] = Transform.Default();
	//	state.blocks[i].position.x = (i % 10) - 5;
	//}

	//for (int i = 0; i < 10; i++)
	//{
	//	state.blocks[i].position.y = 4f;
	//}

	//for (int i = 10; i < 20; i++)
	//{
	//	state.blocks[i].position.y = -2f;
	//}

	//for (int i = 20; i < 30; i++)
	//{
	//	state.blocks[i].position.y = -3f;
	//}

	//state.blocks[17].position.y = -1;
	//state.blocks[15].position.y = -1;
	//state.blocks[15].position.x -= .25f;
	//state.blocks[18].scale.x = 50f;
	//state.blocks[29].scale.x = 10f;
	//state.blocks[29].position = new Vector3(-10, 1, 0);
}

void ResetGame(GameplayState state)
{
	//state.game_over = false;
	//state.time_remaining = state.initial_time;
	//state.skeleton = state.GetSkeleton();
	//state.skeleton[1].position.y = 2;

	//state.transforms = new Transform[state.skeleton.Length * GameplayState.PLAYER_COUNT];

	//float distance_apart = 3.5f;
	//float leftmost_position = -(GameplayState.PLAYER_COUNT - 1) * distance_apart / 2;

	//for (int i = 0; i < GameplayState.PLAYER_COUNT; i++)
	//{
	//	int player_root_index = i * state.skeleton.Length;


	//	for (int bone = 0; bone < state.skeleton.Length; bone++)
	//	{
	//		Transform joint = state.skeleton[bone];
	//		if (joint.parent > -1)
	//			joint.parent += player_root_index;
	//		state.transforms[player_root_index + bone] = joint;
	//	}

	//	Transform entity = state.transforms[player_root_index];

	//	entity.position.x = leftmost_position + i * distance_apart;
	//	entity.rotation.y = 1 / 4f * Tau;

	//	GameplayState.players[i].current_health = state.max_health;
	//	GameplayState.players[i].defeated = false;
	//	GameplayState.players[i].entity_ID = i * state.skeleton.Length;
	//	GameplayState.players[i].stock = 5;
	//	GameplayState.players[i].velocity.y = 0;
	//	GameplayState.players[i].defendboxes = new Hitbox[]
	//	{
	//		new Hitbox() { transform_index = 6, radius = .2f, active = true },
	//		new Hitbox() { transform_index = 4, radius = .2f, active = true },
	//		new Hitbox() { transform_index = 1, radius = .3f, active = true },
	//		new Hitbox() { transform_index = 2, radius = .4f, active = true },
	//		new Hitbox() { transform_index = 3, radius = .2f, active = true },
	//	};

	//	GameplayState.players[i].attackboxes = new Hitbox[]
	//	{
	//		new Hitbox() { transform_index = 14, radius = .2f },
	//		new Hitbox() { transform_index = 15, radius = .2f },
	//	};

	//	for (int o = 0; o < GameplayState.players[i].attackboxes.Length; o++)
	//	{
	//		GameplayState.players[i].attackboxes[o].transform_index += state.skeleton.Length * i;
	//	}

	//	for (int o = 0; o < GameplayState.players[i].defendboxes.Length; o++)
	//	{
	//		GameplayState.players[i].defendboxes[o].transform_index += state.skeleton.Length * i;
	//	}

	//	state.transforms[player_root_index] = entity;
	//}


	//for (int i = 0; i < GameplayState.PLAYER_COUNT; i++)
	//{
	//	Animator new_animator = new Animator();
	//	new_animator.current_animation = DefinedAnimations.idle_animation;
	//	new_animator.current_frame = 1;
	//	state.animators[i] = new_animator;
	//}

	//state.camera.position = new Vector3(0, 0, -20);
	//state.camera.scale = Vector3.One;
}




//public static void DrawHitbox(Vector3 center, uint color, float width)
//{
//	float half = width / 2f;
//	uint transparent_color = (color ^ black) | 0x5E000000;
//	Blend_Circle(transparent_color, center.x, center.y, half);
//	Draw_Circle(Darker(color), center.x, center.y, half, 2);
//	FillCircle(color, center.x, center.y, 4);
//}
//
//public Transform[] skeleton;
//public Transform[] GetSkeleton()
//{
//	if (skeleton == null)
//		skeleton = LoadHierarchy("avatar");
//	return skeleton;
//}









void PrintMesh(Mesh mesh)
{
	printf("indices:\n");
	for (int i = 0; i < mesh.indices_length; i += 3)
	{
		printf("{ %d, %d, %d }\n", mesh.indices[i], mesh.indices[i+1], mesh.indices[i+2]);
	}

	printf("vertices:\n");
	for (int i = 0; i < mesh.vertices_length; i++)
	{
		printf("{ %+f, %+f, %+f }\n", mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z);
	}
}



typedef struct
{
	byte
		row1,
		row2,
		row3,
		row4,
		row5,
		row6,
		row7,
		row8;
} CharSprite;



char char_dict[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ', '.', ':', ',', '_', '[', ']', '-', };
#define char_dict_length 44 //TODO don't rely on this magic number long term, at least until you've verified it will stay the same
CharSprite font_set[char_dict_length];

__declspec(dllexport) void FillSprites(CharSprite* sprites, int count)
{
	for (int i = 0; i < count; i++)
	{
		font_set[i] = sprites[i];
	}
}

void DrawCharacter(CharSprite sprite, int x, int y)
{
	char* p = &sprite.row1;
	for (int row = 0; row < 8; row++, p++)
	{
		for (int col = 0; col < 8; col++)
		{
			bool pixel_active = ((*p << col) & 0b10000000) == 0b10000000;
			if (pixel_active)
				PutPixel(white, col + x, row + y);
		}
	}
}

void DrawString(string s, int x, int y)
{
	for (int i = 0; i < s.length; i++)
	{
		char a = tolower(s.characters[i]);
		for (int o = 0; o < char_dict_length; o++)
		{
			if (a == char_dict[o])
			{
				DrawCharacter(font_set[o], x + i * 9, y);
				//todo break and see how much time is saved
			}

		}
	}
}



void main()
{
	Mesh mesh = LoadMesh("P:/Assets/cube.obj");
	PrintMesh(mesh);
}