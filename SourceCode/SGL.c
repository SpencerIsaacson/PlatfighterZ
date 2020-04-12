#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <float.h>

#define byte char
#define bool char
#define uint unsigned int
#define true 1
#define false 0
#define m4x4_identity {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}
#define v3_forward { 0, 0, 1 }
#define v3_zero { 0, 0, 0 }
#define v3_one { 1, 1, 1 }

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

#define brown 0xFFA52A2A
#define purple 0xFF800080

#define open_file fopen
#define seek_position fseek
#define read_bytes fread
#define close_file fclose

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
	int transform_index;
	char channel_offset;
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
	int vertices_length;
	v3* vertices;
	int indices_length;
	int* indices;
} Mesh;

typedef struct
{
	int length;
	Transform* joints;
} Skeleton;

typedef struct
{
	int entity_ID;
	int selected_character;
	bool defeated;
	int stock;
	float current_health;
	v2 velocity;
	bool grounded;
	int attackbox_count;
	Hitbox* attackboxes;
	int defendbox_count;
	Hitbox* defendboxes;
} Player;


typedef struct
{
	int width, height;
	uint* pixels;
} Bitmap;

//math and stuff
float GetMin(float a, float b, float c);
float GetMax(float a, float b, float c);

typedef enum
{
	SplashScreenState,
	TitleScreen,
	MeshDemo,
	SkinnedMesh,
	Gameplay,
	Particle
} GameStates;

#define state_count 6

typedef struct
{
	//Resolution
	int WIDTH;
	int HEIGHT;

	//Timing
	float TIME_RECALCULATION_INTERVAL; //1.0f
	float TARGET_FRAMERATE;// 60.0f
	float STANDARD_TIMESTEP;// 1 / TARGET_FRAMERATE
	//	public static Stopwatch stopwatch = new Stopwatch();
	clock_t previous_time;
	float delta_time;
	float time_since_last_frame;
	float time_scale; //1f
	float frames_per_second;
	float time_since_timing_recalculated;
	bool fixed_framerate; //false
	bool view_debug;
	int frames_since_last_second;
	GameStates current_game_state;
} Game;

Game game;

//Linear Algebra
Transform DefaultTransform();
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
v3 v3_Divide(v3 v, float s);
v4 v4_Divide(v4 v, float s);
float v3_DotProduct(v3 a, v3 b);
//Interpolation
v2 Lerp_v2(v2 a, v2 b, float t);
float Lerp_Float(float a, float b, float t);
void AnimateProperty(AnimationCurve curve, float frame, float* property);
float Sample(KeyFrame a, KeyFrame b, float frame);
uint LerpColor(uint a, uint b, float t);
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
//Printing
void PrintMesh(Mesh mesh);
void PrintMatrix(m4x4 m);
//File IO
Mesh LoadMesh(char* path);
void LoadFontSet();
Skeleton LoadTransformHierarchy(char* path);
uint* LoadPolygonColors(char* path);

uint Darker(uint color)
{
	uint r = (color & red ^ black) >> 17 << 16;
	uint g = (color & (green ^ black)) >> 9 << 8;
	uint b = (color & blue ^ black) >> 1;
	return black | r | g | b;
}

Transform InvertTransform(Transform t)
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

m4x4 Concatenate(m4x4 a, m4x4 b)
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

m4x4 WorldSpaceMatrix(int index, Transform hierarchy[])
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

v3 Transform_v3(m4x4 m, v3 v)
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

m4x4 Perspective(float near_plane, float far_plane, float field_of_view, float width, float height)
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
	return v3_Divide(v, v3_Magnitude(v));
}

float v3_Magnitude(v3 v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

v3 v3_Scale(v3 v, float s)
{
	v3 result = { v.x * s, v.y * s, v.z * s };
	return result;
}

v3 v3_Divide(v3 v, float s)
{
	v3 result = { v.x / s, v.y / s, v.z / s };
	return result;
}

v4 v4_Divide(v4 v, float s)
{
	v4 result = { v.x / s, v.y / s, v.z / s, v.w / s };
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

void AnimateProperty(AnimationCurve curve, float frame, float* property)
{
	for (size_t o = 0; o < curve.keyframes_length; o++)
	{
		KeyFrame keyframe = curve.keyframes[o];
	}

	int n = curve.keyframes_length;
	for (int i = 0; i < n - 1; i++)
	{
		KeyFrame a = curve.keyframes[i];
		KeyFrame b = curve.keyframes[i + 1];
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

float light_rotation = 0;
m4x4 camera_to_clip;
int WIDTH, HEIGHT;
uint* pixels;

Mesh mesh;
Transform cube_transform;
Transform mesh_demo_camera;


typedef struct
{
	bool started;
	bool ended;
	float time;
	float alpha;
	Bitmap logo;
} SplashScreen;

SplashScreen splash;

__declspec(dllexport) void InitViewport(int width, int height, uint _pixels[])  //TODO move more state here and out of the "run" arguments
{
	WIDTH = width;
	HEIGHT = height;
	pixels = &_pixels[0];
}

void Clear()
{
	memset(pixels, 0, WIDTH * HEIGHT * sizeof(uint));
}

void Fill(uint color)
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		pixels[i] = color;
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

void DrawHorizontalSegment(uint color, int y, int x1, int x2)
{
	int pixel_row = y * WIDTH;

	for (int i = pixel_row + x1; i <= pixel_row + x2; i++)
	{
		int x = i - pixel_row;
		PutPixel(color, x, y);
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

Mesh LoadMesh(char* path)
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

void FillRectangle_Blend(uint color, int x, int y, int width, int height)
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

void FillRectangle(uint color, float x, float y, float width, float height)
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

void Render(Mesh mesh, uint* body_poly_colors, Transform camera, bool fill_toggle)
{
	Clear();

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

bool KeyDownFresh(enum Keys key)
{
	return keys_down[key] && !keys_stale[key];
}

bool KeyDown(enum Keys key)
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

void PollKeyboard()
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
	Skeleton skeleton;
	int bind_matrices_length;
	m4x4* bind_matrices;
	int weights_length;
	v4* weights;
	int weight_indices_length;
	Weight_Index* weight_indices;
	//Dictionary<int, Vector3>[] morphs = new Dictionary<int, Vector3>[5];
	int morph_weights_length;
	float* morph_weights;
	int transformed_vertices_length;
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
	bool view_fps;
	float facial_time;
} SkinnedMeshDemo;

SkinnedMeshDemo skinned_demo;
//public static Mesh AppendMesh(Mesh a, Mesh b)
//{
//	List<Vector3> vertices = new List<Vector3>(a.vertices);
//	List<int> indices = new List<int>(a.indices);
//	for (int i = 0; i < b.indices.Length; i++)
//	{
//		b.indices[i] += a.vertices.Length;
//	}
//	vertices.AddRange(b.vertices);
//	indices.AddRange(b.indices);
//
//	return new Mesh{ vertices = vertices.ToArray(), indices = indices.ToArray() };
//}

void SetWeights()
{
	skinned_demo.weights = malloc(skinned_demo.mesh.vertices_length * sizeof(v4));
	skinned_demo.weights_length = mesh.vertices_length;

	for (int i = 0; i < skinned_demo.mesh.vertices_length; i++)
	{
		v4 weight = { 1, 0, 0, 0 };
		skinned_demo.weights[i] = weight;
	}

	FILE* file_pointer = open_file("Assets/weight_indices", "r");
	seek_position(file_pointer, 0L, SEEK_END);

	int file_size = ftell(file_pointer);
	skinned_demo.weight_indices_length = file_size / sizeof(Weight_Index);
	skinned_demo.weight_indices = malloc(file_size);

	rewind(file_pointer);
	read_bytes(skinned_demo.weight_indices, sizeof(Weight_Index), skinned_demo.weight_indices_length, file_pointer);
	close_file(file_pointer);
}

uint* LoadPolygonColors(char* path)//TODO fix endianness of file so you can read into memory in one go
{
	FILE* file_pointer = open_file(path, "r");

	int color_count = 0;
	while (true)
	{
		fgetc(file_pointer);
		fgetc(file_pointer);
		fgetc(file_pointer);
		fgetc(file_pointer);

		if (feof(file_pointer))
			break;

		color_count++;
	}

	rewind(file_pointer);
	uint* colors = malloc(4 * color_count);

	for (int i = 0; i < color_count; i++)
	{
		int r = fgetc(file_pointer);
		int g = fgetc(file_pointer);
		int b = fgetc(file_pointer);
		int a = fgetc(file_pointer);
		colors[i] = (a << 24) | (b << 16) | (g << 8) | r;
	}

	close_file(file_pointer);
	return colors;
}

typedef struct
{
	Animation walk_animation;
	Animation idle_animation;
} DefinedAnimations;

DefinedAnimations defined_animations; //TODO initialize

#define PLAYER_COUNT 4 //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players
#define block_count 30

typedef struct
{
	//Game World
	Transform camera;
	float field_of_view;
	int transform_count;
	Transform* transforms; //TODO init transforms
	Skeleton skeleton;
	Player players[PLAYER_COUNT];
	Animator animators[PLAYER_COUNT];
	uint player_colors[PLAYER_COUNT];// = new uint[]{ red, 0xFF008000, blue, purple };
	Transform blocks[block_count];

	//Play variables
	int winner;// = 0;
	bool game_over;// = false;
	float initial_time;// = 99;
	float time_remaining;
	float max_health;

	//physics
	float gravity;// = 10;
} GameplayState;

GameplayState gameplay_state = (GameplayState){.player_colors = { red, 0xFF008000, blue, purple }};

void ResetGame()
{
	gameplay_state.game_over = false;
	gameplay_state.time_remaining = gameplay_state.initial_time;

	int transform_count = gameplay_state.skeleton.length * PLAYER_COUNT;
	gameplay_state.transform_count = transform_count;
	gameplay_state.transforms = malloc(sizeof(Transform) * transform_count);

	float distance_apart = 3.5f;
	float leftmost_position = -(PLAYER_COUNT - 1) * distance_apart / 2;

	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		int player_root_index = i * gameplay_state.skeleton.length;


		for (int bone = 0; bone < gameplay_state.skeleton.length; bone++)
		{
			Transform joint = gameplay_state.skeleton.joints[bone];
			if (joint.parent > -1)
				joint.parent += player_root_index;
			gameplay_state.transforms[player_root_index + bone] = joint;
		}

		Transform entity = gameplay_state.transforms[player_root_index];

		entity.position.x = leftmost_position + i * distance_apart;
		entity.rotation.y = 1 / 4.0f * Tau;

		gameplay_state.players[i].current_health = gameplay_state.max_health;
		gameplay_state.players[i].defeated = false;
		gameplay_state.players[i].entity_ID = i * gameplay_state.skeleton.length;
		gameplay_state.players[i].stock = 5;
		gameplay_state.players[i].velocity.y = 0;

		gameplay_state.players[i].defendbox_count = 5;
		gameplay_state.players[i].defendboxes = malloc(sizeof(Hitbox) * gameplay_state.players[i].defendbox_count);
		gameplay_state.players[i].defendboxes[0] = (Hitbox) { .transform_index = 6, .radius = .2f, .active = true };
		gameplay_state.players[i].defendboxes[1] = (Hitbox) { .transform_index = 4, .radius = .2f, .active = true };
		gameplay_state.players[i].defendboxes[2] = (Hitbox) { .transform_index = 1, .radius = .3f, .active = true };
		gameplay_state.players[i].defendboxes[3] = (Hitbox) { .transform_index = 2, .radius = .4f, .active = true };
		gameplay_state.players[i].defendboxes[4] = (Hitbox) { .transform_index = 3, .radius = .2f, .active = true };

		gameplay_state.players[i].attackbox_count = 2;
		gameplay_state.players[i].attackboxes = malloc(sizeof(Hitbox) * gameplay_state.players[i].attackbox_count);
		gameplay_state.players[i].attackboxes[0] = (Hitbox) { .transform_index = 14, .radius = .2f };
		gameplay_state.players[i].attackboxes[1] = (Hitbox) { .transform_index = 15, .radius = .2f };

		for (int o = 0; o < gameplay_state.players[i].attackbox_count; o++)
		{
			gameplay_state.players[i].attackboxes[o].transform_index += gameplay_state.skeleton.length * i;
		}

		for (int o = 0; o < gameplay_state.players[i].defendbox_count; o++)
		{
			gameplay_state.players[i].defendboxes[o].transform_index += gameplay_state.skeleton.length * i;
		}

		gameplay_state.transforms[player_root_index] = entity;
	}


	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		gameplay_state.animators[i].current_animation = defined_animations.idle_animation;
		gameplay_state.animators[i].current_frame = 1;
	}

	gameplay_state.camera.position = (v3){ 0, 0, -20 };
}



void DrawHitbox(v3 center, uint color, float width)
{
	float half = width / 2.0f;
	uint transparent_color = (color ^ black) | 0x5E000000;
	Blend_Circle(transparent_color, center.x, center.y, half);
	Draw_Circle(Darker(color), center.x, center.y, half, 2);
	FillCircle(color, center.x, center.y, 4);
}

void PrintMesh(Mesh mesh)
{
	printf("indices:\n");
	for (int i = 0; i < mesh.indices_length; i += 3)
	{
		printf("{ %d, %d, %d }\n", mesh.indices[i], mesh.indices[i + 1], mesh.indices[i + 2]);
	}

	printf("vertices:\n");
	for (int i = 0; i < mesh.vertices_length; i++)
	{
		printf("{ %+f, %+f, %+f }\n", mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z);
	}
}

void FillSprites(CharSprite* sprites, int count)
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

Transform DefaultTransform()
{
	return (Transform)
	{
		-1,
		v3_zero,
		v3_zero,
		v3_one
	};
}


Skeleton LoadTransformHierarchy(char* path)
{
	int joint_count = 0;
	int file_size = 0;

	FILE* file_pointer = open_file(path, "r");
	Transform* hierarchy;

	seek_position(file_pointer, 0L, SEEK_END);

	file_size = ftell(file_pointer);
	joint_count = file_size / sizeof(Transform);

	hierarchy = malloc(file_size);

	rewind(file_pointer);
	read_bytes(hierarchy, sizeof(Transform), joint_count, file_pointer);
	close_file(file_pointer);

	Skeleton skel;
	skel.length = joint_count;
	skel.joints = hierarchy;
	return skel;
}


//static class DefinedAnimations
//{
//	public static List<AnimationCurve> idle_curves = new List<AnimationCurve>
//	{
//		new AnimationCurve()
//		{
//			transform_index = 1, //core 
//			property_tag = 1,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 2 },
//				new KeyFrame {frame = 30, value = 1.93f },
//				new KeyFrame {frame = 60, value = 2 },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 1, //core
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = .3f },
//				new KeyFrame {frame = 60, value = .3f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 2, //chest
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = .0f },
//				new KeyFrame {frame = 30, value = .3f },
//				new KeyFrame {frame = 60, value = .0f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 4,
//			property_tag = 5,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = Tau / 4f },
//				new KeyFrame {frame = 30, value = Tau / 5f },
//				new KeyFrame {frame = 60, value = Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 4,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = Tau / 6f },
//				new KeyFrame {frame = 30, value = Tau / 8f },
//				new KeyFrame {frame = 60, value = Tau / 6f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 5,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = Tau / 4f },
//				new KeyFrame {frame = 30, value = Tau / 3f },
//				new KeyFrame {frame = 60, value = Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 6,
//			property_tag = 5,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = -Tau / 4f },
//				new KeyFrame {frame = 30, value = -Tau / 5f },
//				new KeyFrame {frame = 60, value = -Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 6,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = -Tau / 6f },
//				new KeyFrame {frame = 30, value = -Tau / 8f },
//				new KeyFrame {frame = 60, value = -Tau / 6f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 7,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = -Tau / 4f },
//				new KeyFrame {frame = 30, value = -Tau / 3f },
//				new KeyFrame {frame = 60, value = -Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 8,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0f },
//				new KeyFrame {frame = 30, value = -0.3f },
//				new KeyFrame {frame = 60, value = 0f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 9,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0f },
//				new KeyFrame {frame = 30, value = 0.6f },
//				new KeyFrame {frame = 60, value = 0f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 11,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0.3f },
//				new KeyFrame {frame = 30, value = 0.0f },
//				new KeyFrame {frame = 60, value = 0.3f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 12,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0f },
//				new KeyFrame {frame = 30, value = 0.6f },
//				new KeyFrame {frame = 60, value = 0f },
//			},
//		},
//	};


//	public static List<AnimationCurve> punch_curves = new List<AnimationCurve>
//	{
//		new AnimationCurve()
//		{
//			transform_index = 1, //core 
//			property_tag = 1,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 2 },
//				new KeyFrame {frame = 30, value = 2 },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 1, //core
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = .3f },
//				new KeyFrame {frame = 30, value = .3f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 2, //chest
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = .0f },
//				new KeyFrame {frame = 15, value = -.9f },
//				new KeyFrame {frame = 30, value = .0f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 4,
//			property_tag = 5,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = Tau / 4f },
//				new KeyFrame {frame = 30, value = Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 4,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = Tau / 6f },
//				new KeyFrame {frame = 15, value = -Tau / 9f },
//				new KeyFrame {frame = 30, value = Tau / 6f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 5,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = Tau / 4f },
//				new KeyFrame {frame = 30, value = Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 6,
//			property_tag = 5,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = -Tau / 4f },
//				new KeyFrame {frame = 15, value = 0 },
//				new KeyFrame {frame = 30, value = -Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 6,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = -Tau / 6f },
//				new KeyFrame {frame = 15, value = -Tau / 4 },
//				new KeyFrame {frame = 30, value = -Tau / 6f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 7,
//			property_tag = 4,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = -Tau / 4f },
//				new KeyFrame {frame = 15, value = 0 },
//				new KeyFrame {frame = 30, value = -Tau / 4f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 8,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0f },
//				new KeyFrame {frame = 30, value = 0f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 9,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0f },
//				new KeyFrame {frame = 30, value = 0f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 11,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0.3f },
//				new KeyFrame {frame = 30, value = 0.3f },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 12,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0f },
//				new KeyFrame {frame = 30, value = 0f },
//			},
//		},
//	};
//	public static List<AnimationCurve> jump_curves = new List<AnimationCurve>
//	{
//		new AnimationCurve()
//		{
//			transform_index = 1, //core 
//			property_tag = 1,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0 },
//				new KeyFrame {frame = 27, value = -0.75f },
//				new KeyFrame {frame = 30, value = -0.5f },
//				new KeyFrame {frame = 45, value = 0f },
//				new KeyFrame {frame = 60, value = 0 },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 8,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0 },
//				new KeyFrame {frame = 30, value = -0.5f },
//				new KeyFrame {frame = 40, value = 0 },
//				new KeyFrame {frame = 60, value = 0 },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 9,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0 },
//				new KeyFrame {frame = 30, value = 1f },
//				new KeyFrame {frame = 40, value = 0 },
//				new KeyFrame {frame = 60, value = 0 },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 11,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0 },
//				new KeyFrame {frame = 30, value = -0.5f },
//				new KeyFrame {frame = 40, value = 0 },
//				new KeyFrame {frame = 60, value = 0 },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 12,
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0 },
//				new KeyFrame {frame = 30, value = 1f },
//				new KeyFrame {frame = 40, value = 0 },
//				new KeyFrame {frame = 60, value = 0 },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 4,
//			property_tag = 5,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 1 / 4f * Tau },
//				new KeyFrame {frame = 30, value = 1 / 8f * Tau },
//				new KeyFrame {frame = 40, value = 1 / 4f * Tau },
//				new KeyFrame {frame = 60, value = 1 / 4f * Tau },
//			},
//		},
//		new AnimationCurve()
//		{
//			transform_index = 6,
//			property_tag = 5,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = -1 / 4f * Tau },
//				new KeyFrame {frame = 30, value = -1 / 8f * Tau },
//				new KeyFrame {frame = 40, value = -1 / 4f * Tau },
//				new KeyFrame {frame = 60, value = -1 / 4f * Tau },
//			},
//		},
//	};
//
//	public static Animation idle_animation = new Animation(){ looped = true, curves = idle_curves };
//	public static Animation punch_animation = new Animation()
//	{
//		looped = true,
//		curves = punch_curves,
//		attackbox_keys = new int[][]
//		{
//		new int[] { 1 },
//		new int[] { 1, 5, 20 },
//		},
//		attackbox_values = new bool[][]
//		{
//		new bool[] { false },
//		new bool[] { false, true, false },
//		}
//	};
//	public static Animation jump_animation = new Animation(){ curves = jump_curves };
//	public static Animation die_animation = new Animation()
//	{
//		curves = new List<AnimationCurve>
//	{
//		new AnimationCurve()
//		{
//			transform_index = 1, //core 
//			property_tag = 1,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 2 },
//				new KeyFrame {frame = 60, value = 0 },
//			},
//		},
//
//		new AnimationCurve()
//		{
//			transform_index = 1, //core 
//			property_tag = 3,
//			keyframes = new KeyFrame[]
//			{
//				new KeyFrame {frame = 01, value = 0 },
//				new KeyFrame {frame = 60, value = 1.6f },
//			},
//		},
//	}
//	};
//}


//public static KeyFrame[] LoadKeyFrames(string path)
//{
//	Stream stream = GetAssetStream(path);
//	using (BinaryReader reader = new BinaryReader(stream))
//	{
//		List<KeyFrame> curve = new List<KeyFrame>();
//		while (reader.BaseStream.Position != reader.BaseStream.Length)
//		{
//			var keyframe = new KeyFrame();
//			keyframe.frame = reader.ReadSingle();
//			keyframe.value = reader.ReadSingle();
//			keyframe.left_handle_x = reader.ReadSingle();
//			keyframe.left_handle_y = reader.ReadSingle();
//			keyframe.right_handle_x = reader.ReadSingle();
//			keyframe.right_handle_y = reader.ReadSingle();
//			curve.Add(keyframe);
//		}
//		return curve.ToArray();
//	}
//}

void PrintMatrix(m4x4 m)
{
	printf("{ %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f }\n",
		m.m11, m.m12, m.m13, m.m14, m.m21, m.m22, m.m23, m.m24, m.m31, m.m32, m.m33, m.m34, m.m41, m.m42, m.m43, m.m44);
}

void PrintAnimation(Animation animation)
{
	for (size_t i = 0; i < animation.curves_length; i++)
	{
		printf("curve: %d transform: %d, property: %d, keyframe count: %d\n", i, animation.curves[0].transform_index, animation.curves[0].channel_offset, animation.curves[0].keyframes_length);
		for (size_t o = 0; o < animation.curves[0].keyframes_length; o++)
		{
			KeyFrame keyframe = animation.curves[0].keyframes[o];
			printf("keyframe: %d, frame: %.3f, value: %.3f, left handle: { %.3f, %.3f }, right handle: { %.3f, %.3f }\n", o, keyframe.frame, keyframe.value, keyframe.left_handle_x, keyframe.left_handle_y, keyframe.right_handle_x, keyframe.right_handle_y);
		}
	}
}

enum Channels
{
	POSX, POSY, POSZ, ROTX, ROTY, ROTZ, SCALEX, SCALEY, SCALEZ
};

__declspec(dllexport) void InitEverything()
{
	game.TIME_RECALCULATION_INTERVAL = 1.0f;

	game.TARGET_FRAMERATE = 60.0f;
	game.STANDARD_TIMESTEP = 1 / game.TARGET_FRAMERATE;
	game.time_scale = 1.0f;
	game.fixed_framerate = false;
	game.current_game_state = SplashScreenState;
	game.view_debug = false;
	float field_of_view = Tau / 4.0f;
	camera_to_clip = Perspective(0.1f, 100, field_of_view, WIDTH, HEIGHT);

	//Init Animations
	{
		defined_animations.walk_animation.looped = true;
		defined_animations.walk_animation.curves_length = 12;//12
		defined_animations.walk_animation.curves = malloc(sizeof(AnimationCurve) * defined_animations.walk_animation.curves_length);

		defined_animations.walk_animation.curves[0].transform_index = 1; //core
		defined_animations.walk_animation.curves[0].channel_offset = POSY;
		defined_animations.walk_animation.curves[0].keyframes_length = 5;
		defined_animations.walk_animation.curves[0].keyframes = malloc(5 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[0].keyframes[0] = ((KeyFrame) { 1, 2, 0, 0 });
		defined_animations.walk_animation.curves[0].keyframes[1] = ((KeyFrame) { 8, 1.75f, 0, 0 });
		defined_animations.walk_animation.curves[0].keyframes[2] = ((KeyFrame) { 16, 2, 0, 0 });
		defined_animations.walk_animation.curves[0].keyframes[3] = ((KeyFrame) { 24, 1.75f, 0, 0 });
		defined_animations.walk_animation.curves[0].keyframes[4] = ((KeyFrame) { 32, 2, 0, 0 });

		defined_animations.walk_animation.curves[1].transform_index = 2; //chest
		defined_animations.walk_animation.curves[1].channel_offset = ROTY;
		defined_animations.walk_animation.curves[1].keyframes_length = 5;
		defined_animations.walk_animation.curves[1].keyframes = malloc(5 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[1].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
		defined_animations.walk_animation.curves[1].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
		defined_animations.walk_animation.curves[1].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
		defined_animations.walk_animation.curves[1].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[1].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

		defined_animations.walk_animation.curves[2].transform_index = 4; //left shoulder
		defined_animations.walk_animation.curves[2].channel_offset = 5;
		defined_animations.walk_animation.curves[2].keyframes_length = 2;
		defined_animations.walk_animation.curves[2].keyframes = malloc(2 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[2].keyframes[0] = ((KeyFrame) { 1, Tau / 6.0f, 0, 0 });
		defined_animations.walk_animation.curves[2].keyframes[1] = ((KeyFrame) { 32, Tau / 6.0f, 0, 0 });

		defined_animations.walk_animation.curves[3].transform_index = 4; //left shoulder
		defined_animations.walk_animation.curves[3].channel_offset = 4;
		defined_animations.walk_animation.curves[3].keyframes_length = 5;
		defined_animations.walk_animation.curves[3].keyframes = malloc(5 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[3].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
		defined_animations.walk_animation.curves[3].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
		defined_animations.walk_animation.curves[3].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
		defined_animations.walk_animation.curves[3].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[3].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

		defined_animations.walk_animation.curves[4].transform_index = 5; //left elbow
		defined_animations.walk_animation.curves[4].channel_offset = 4;
		defined_animations.walk_animation.curves[4].keyframes_length = 2;
		defined_animations.walk_animation.curves[4].keyframes = malloc(2 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[4].keyframes[0] = ((KeyFrame) { 1, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[4].keyframes[1] = ((KeyFrame) { 32, 0.5f, 0, 0 });

		defined_animations.walk_animation.curves[5].transform_index = 6; //right shoulder
		defined_animations.walk_animation.curves[5].channel_offset = 5;
		defined_animations.walk_animation.curves[5].keyframes_length = 2;
		defined_animations.walk_animation.curves[5].keyframes = malloc(2 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[5].keyframes[0] = ((KeyFrame) { 1, -Tau / 6.0f, 0, 0 });
		defined_animations.walk_animation.curves[5].keyframes[1] = ((KeyFrame) { 32, -Tau / 6.0f, 0, 0 });

		defined_animations.walk_animation.curves[6].transform_index = 6; //right shoulder
		defined_animations.walk_animation.curves[6].channel_offset = 4;
		defined_animations.walk_animation.curves[6].keyframes_length = 5;
		defined_animations.walk_animation.curves[6].keyframes = malloc(5 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[6].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
		defined_animations.walk_animation.curves[6].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
		defined_animations.walk_animation.curves[6].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
		defined_animations.walk_animation.curves[6].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[6].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

		defined_animations.walk_animation.curves[7].transform_index = 7; //right elbow
		defined_animations.walk_animation.curves[7].channel_offset = 4;
		defined_animations.walk_animation.curves[7].keyframes_length = 2;
		defined_animations.walk_animation.curves[7].keyframes = malloc(2 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[7].keyframes[0] = ((KeyFrame) { 1, -0.5f, 0, 0 });
		defined_animations.walk_animation.curves[7].keyframes[1] = ((KeyFrame) { 32, -0.5f, 0, 0 });

		defined_animations.walk_animation.curves[8].transform_index = 8; //left hip
		defined_animations.walk_animation.curves[8].channel_offset = 3;
		defined_animations.walk_animation.curves[8].keyframes_length = 5;
		defined_animations.walk_animation.curves[8].keyframes = malloc(5 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[8].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
		defined_animations.walk_animation.curves[8].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
		defined_animations.walk_animation.curves[8].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
		defined_animations.walk_animation.curves[8].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[8].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

		defined_animations.walk_animation.curves[9].transform_index = 9; //left knee
		defined_animations.walk_animation.curves[9].channel_offset = 3;
		defined_animations.walk_animation.curves[9].keyframes_length = 3;
		defined_animations.walk_animation.curves[9].keyframes = malloc(3 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[9].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
		defined_animations.walk_animation.curves[9].keyframes[1] = ((KeyFrame) { 16, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[9].keyframes[2] = ((KeyFrame) { 32, 0, 0, 0 });

		defined_animations.walk_animation.curves[10].transform_index = 11; //right hip
		defined_animations.walk_animation.curves[10].channel_offset = 3;
		defined_animations.walk_animation.curves[10].keyframes_length = 5;
		defined_animations.walk_animation.curves[10].keyframes = malloc(5 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[10].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
		defined_animations.walk_animation.curves[10].keyframes[1] = ((KeyFrame) { 8, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[10].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
		defined_animations.walk_animation.curves[10].keyframes[3] = ((KeyFrame) { 24, -0.5f, 0, 0 });
		defined_animations.walk_animation.curves[10].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

		defined_animations.walk_animation.curves[11].transform_index = 12; //right knee
		defined_animations.walk_animation.curves[11].channel_offset = 3;
		defined_animations.walk_animation.curves[11].keyframes_length = 5;
		defined_animations.walk_animation.curves[11].keyframes = malloc(5 * sizeof(KeyFrame));
		defined_animations.walk_animation.curves[11].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
		defined_animations.walk_animation.curves[11].keyframes[1] = ((KeyFrame) { 8, 0, 0, 0 });
		defined_animations.walk_animation.curves[11].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
		defined_animations.walk_animation.curves[11].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
		defined_animations.walk_animation.curves[11].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });
	}

	// Init SkinnedMeshDemo
	{
		skinned_demo.camera = (Transform){ -1, { 0, 0, -50 }, { 0, 0, 0 }, { 1, 1, 1 } };
		skinned_demo.mesh = LoadMesh("Assets/guy.obj");

		skinned_demo.skeleton = LoadTransformHierarchy("Assets/avatar");
		skinned_demo.animation_length = 32;

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
		int triangle_count = skinned_demo.mesh.indices_length / 3;
		skinned_demo.body_poly_colors = LoadPolygonColors("Assets/skin_poly_colors");

		skinned_demo.body_poly_colors_length = triangle_count;

		SetWeights();

		//build bind matrices
		{
			skinned_demo.bind_matrices = malloc(sizeof(m4x4) * skinned_demo.skeleton.length);
			skinned_demo.bind_matrices_length = skinned_demo.skeleton.length;

			Transform bind_transforms[skinned_demo.skeleton.length];

			for (int i = 0; i < skinned_demo.bind_matrices_length; i++)
			{
				bind_transforms[i] = InvertTransform(skinned_demo.skeleton.joints[i]);
				skinned_demo.bind_matrices[i] = WorldSpaceMatrix(i, bind_transforms);

				m4x4 m = skinned_demo.bind_matrices[i];
			}
		}

		skinned_demo.transformed_vertices = malloc(sizeof(v3) * skinned_demo.mesh.vertices_length);
		skinned_demo.transformed_vertices_length = skinned_demo.mesh.vertices_length;
		skinned_demo.skeleton.joints[0].position.y = -1;
	}

	//Init MeshDemo
	{
		//Load FontSet
		{
			FILE* file_pointer = open_file("Assets/font_set", "r");
			read_bytes(font_set, 8, 44, file_pointer);
			close_file(file_pointer);
		}

		mesh = LoadMesh("Assets/teapot.obj");
		v3 forward_10 = { 0, 0, 10 };
		v3 backward_30 = { 0, 0, -30 };
		v3 zero = { 0, 0, 0 };
		v3 one = { 1, 1, 1 };
		cube_transform.position = forward_10;
		cube_transform.rotation = zero;
		cube_transform.scale = one;
		mesh_demo_camera.position = backward_30;
		mesh_demo_camera.rotation = zero;
		mesh_demo_camera.scale = one;
	}

	//Init GameplayState
	{	
		gameplay_state.initial_time = 99;
		gameplay_state.max_health = 10;
		gameplay_state.skeleton = LoadTransformHierarchy("Assets/avatar");
		gameplay_state.skeleton.joints[1].position.y = 2;
		gameplay_state.field_of_view = 3.0f / 8.0f * Tau;
		gameplay_state.camera = DefaultTransform();
		gameplay_state.camera.position.z = -20;

		ResetGame();
		for (int i = 0; i < block_count; i++)
		{
			gameplay_state.blocks[i] = DefaultTransform();
			gameplay_state.blocks[i].position.x = (i % 10) - 5;
		}

		for (int i = 0; i < 10; i++)
		{
			gameplay_state.blocks[i].position.y = 4.0f;
		}

		for (int i = 10; i < 20; i++)
		{
			gameplay_state.blocks[i].position.y = -2.0f;
		}

		for (int i = 20; i < 30; i++)
		{
			gameplay_state.blocks[i].position.y = -3.0f;
		}

		gameplay_state.blocks[17].position.y = -1;
		gameplay_state.blocks[15].position.y = -1;
		gameplay_state.blocks[15].position.x -= .25f;
		gameplay_state.blocks[18].scale.x = 50.0f;
		gameplay_state.blocks[29].scale.x = 10.0f;
		gameplay_state.blocks[29].position = (v3){ -10, 1, 0 };
	}

	//void Init SplashScreen
	{
		splash.started = false;
		splash.ended = false;
		splash.time = 0;
		splash.alpha = 0;

		//Load SplashScreen Image
		{
			FILE* file_pointer = open_file("Assets/viking_studios_logo", "r");
			int width = 1920, height = 1080;
			uint* pixels = malloc(sizeof(uint) * width * height);
			read_bytes(pixels, 4, width * height, file_pointer);
			splash.logo.width = width;
			splash.logo.height = height;
			splash.logo.pixels = pixels;

			close_file(file_pointer);
		}
	}
}


string WrapString(char* message)
{
	return (string){.characters = message, .length = strlen(message)};
}

__declspec(dllexport) void GameLoop()
{
	if (!game.fixed_framerate || (game.time_since_last_frame > game.STANDARD_TIMESTEP))
	{
		//Tick
		{
			//Update Input Devices
			{
				PollKeyboard();

				if (KeyDownFresh(Keys_G))
					game.view_debug = !game.view_debug;				
			}

			//Cycle Through GameStates
			{
				if (KeyDownFresh(Keys_Tab))
				{
					game.current_game_state = (game.current_game_state + 1) % state_count;
				}

				else if (KeyDownFresh(Keys_Z))
				{
					game.current_game_state--;

					if ((int)game.current_game_state < 0)
						game.current_game_state += state_count;
				}
			}

			game.frames_since_last_second++;

			switch (game.current_game_state)
			{
				case SplashScreenState:
				{
					if (splash.time > 10)
					{
						if (!splash.ended)
						{
							game.current_game_state = TitleScreen;
							splash.ended = true;
						}
						else
						{
							splash.time = 0;
							splash.ended = false;
							splash.started = false;
						}
					}

					if (!splash.started)
					{
						//System.Media.SoundPlayer player = new System.Media.SoundPlayer(GetAssetStream("preparations.wav"));
						//player.Play();
						splash.started = true;
					}

					//DrawSplashScreen
					{
						memcpy(pixels, splash.logo.pixels, WIDTH * HEIGHT * 4);

						int pixel_count = WIDTH * HEIGHT;

						for (int i = 0; i < pixel_count; i += 4)
						{
							if (pixels[i] != black)
							{
								uint red_channel = (uint)((pixels[i] & 0xFF0000) * splash.alpha) & 0xFF0000;
								pixels[i] = black | red_channel;
							}

							if (pixels[i + 1] != black)
							{
								uint red_channel = (uint)((pixels[i + 1] & 0xFF0000) * splash.alpha) & 0xFF0000;
								pixels[i + 1] = black | red_channel;
							}

							if (pixels[i + 2] != black)
							{
								uint red_channel = (uint)((pixels[i + 2] & 0xFF0000) * splash.alpha) & 0xFF0000;
								pixels[i + 2] = black | red_channel;
							}

							if (pixels[i + 3] != black)
							{
								uint red_channel = (uint)((pixels[i + 3] & 0xFF0000) * splash.alpha) & 0xFF0000;
								pixels[i + 3] = black | red_channel;
							}
						}
					}

					splash.time += game.delta_time;
					if (splash.time > 2 && splash.time < 7 && splash.alpha < 1)
					{
						splash.alpha += game.delta_time / 5;
						if (splash.alpha > 1)
							splash.alpha = 1;
					}

					if (splash.time > 8)
						splash.alpha -= game.delta_time;

					if (splash.alpha < 0)
						splash.alpha = 0;
				} break;
				case TitleScreen:
				{
					#define sprite_size 9
					if(KeyDownFresh(Keys_Space))
						game.current_game_state = Gameplay;
					FillVerticalGradient(cyan,blue);
					int x = WIDTH / 2;
					string title = WrapString("Title Here");
					string press_space = WrapString("Press Space");
					DrawString(title, x - (title.length * sprite_size / 2), HEIGHT / 2);
					DrawString(press_space, x - (press_space.length * sprite_size / 2), HEIGHT-sprite_size);
				} break;
				case SkinnedMesh:
				{
					//Input
					{
						float delta = 5 * game.delta_time;

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

					//Animate
					{
						if (skinned_demo.rotation_play)
						{
							skinned_demo.rotation_y += game.delta_time;
							skinned_demo.skeleton.joints[0].rotation.y = skinned_demo.rotation_y;
						}

						if (skinned_demo.animation_play)
						{
							//Animate Skeleton
							{
								for (int i = 0; i < defined_animations.walk_animation.curves_length; i++)
								{
									AnimationCurve curve = defined_animations.walk_animation.curves[i];
									int transform_index = curve.transform_index;

									Transform* p = &skinned_demo.skeleton.joints[transform_index];
									float* f = &(*p).position.x + curve.channel_offset;
									AnimateProperty(curve, skinned_demo.frame, f);
								}
							}
						}

						m4x4 skeleton_matrices[skinned_demo.skeleton.length];

						//Get Skeleton Matrices
						{
							for (int i = 0; i < skinned_demo.skeleton.length; i++)
							{
								skeleton_matrices[i] = WorldSpaceMatrix(i, skinned_demo.skeleton.joints);
							}
						}

						//Apply Mesh Skinning
						{
							for (int i = 0; i < skinned_demo.mesh.vertices_length; i++)
							{
								v3 v_a = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone1], skeleton_matrices[skinned_demo.weight_indices[i].bone1]), skinned_demo.mesh.vertices[i]);
								v3 v_b = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone2], skeleton_matrices[skinned_demo.weight_indices[i].bone2]), skinned_demo.mesh.vertices[i]);
								v3 v_c = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone3], skeleton_matrices[skinned_demo.weight_indices[i].bone3]), skinned_demo.mesh.vertices[i]);
								v3 v_d = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone4], skeleton_matrices[skinned_demo.weight_indices[i].bone4]), skinned_demo.mesh.vertices[i]);

								v_a = v3_Scale(v_a, skinned_demo.weights[i].x);
								v_b = v3_Scale(v_b, skinned_demo.weights[i].y);
								v_c = v3_Scale(v_c, skinned_demo.weights[i].z);
								v_d = v3_Scale(v_d, skinned_demo.weights[i].w);

								v3 i_a = v3_Add(v_a, v_b);
								v3 i_b = v3_Add(v_c, v_d);

								skinned_demo.transformed_vertices[i] = v3_Add(i_a, i_b);
							}
						}

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

						//Advance Animation Time
						{
							skinned_demo.frame += game.TARGET_FRAMERATE * game.delta_time;
							if (skinned_demo.frame >= skinned_demo.animation_length)
								skinned_demo.frame = 0;
						}
					}

					Mesh mesh = (Mesh) 
					{ 
						.vertices = skinned_demo.transformed_vertices, 
						.vertices_length = skinned_demo.transformed_vertices_length,
						.indices = skinned_demo.mesh.indices, 
						.indices_length = skinned_demo.mesh.indices_length, 
					};

					Render(mesh, skinned_demo.body_poly_colors, skinned_demo.camera, skinned_demo.fill_toggle);
				} break;
				case Gameplay:
				{
					//Update
					{
						//Get Debug Input
						{
							if (KeyDownFresh(Keys_R))
								ResetGame();

							if (KeyDownFresh(Keys_F))
								game.fixed_framerate = !game.fixed_framerate;
						}

						if (!gameplay_state.game_over)
						{
							for (int player_index = 0; player_index < PLAYER_COUNT; player_index++)
							{
								Transform* playerTransform = &(gameplay_state.transforms[gameplay_state.players[player_index].entity_ID]);

								//Animate Player
								{
									//KeyFrame[] first_curve_frames = gameplay_state.animators[player_index].current_animation.curves[0].keyframes;
									//float ending_frame = first_curve_frames[first_curve_frames.Length - 1].frame;

									//if (!gameplay_state.players[player_index].defeated)
									//{
									//	//Set Animation State
									//	{
									//		bool moving = false;

									//		if (gameplay_state.animators[player_index].current_animation.curves != DefinedAnimations.punch_curves) //TODO use animation, not just curves
									//		{
									//			if (ButtonDown(player_index, Buttons.LEFT))
									//			{
									//				(*playerTransform).rotation.y = -1 / 4f * Tau;
									//				moving = true;
									//			}

									//			if (ButtonDown(player_index, Buttons.RIGHT))
									//			{
									//				(*playerTransform).rotation.y = 1 / 4f * Tau;
									//				moving = true;
									//			}

									//			if (moving)
									//			{
									//				gameplay_state.animators[player_index].current_animation = DefinedAnimations.walk_animation;
									//				var rotation = (*playerTransform).rotation;
									//			}
									//			else
									//				gameplay_state.animators[player_index].current_animation = DefinedAnimations.idle_animation;

									//			if (ButtonDown(player_index, Buttons.PUNCH))
									//			{
									//				gameplay_state.animators[player_index].current_animation = DefinedAnimations.punch_animation;
									//				gameplay_state.animators[player_index].current_frame = 1;
									//			}
									//		}
									//		else if (gameplay_state.animators[player_index].current_frame >= ending_frame)
									//		{
									//			gameplay_state.animators[player_index].current_animation = DefinedAnimations.idle_animation;
									//			gameplay_state.animators[player_index].current_frame = 1;
									//		}
									//	}
									//}

									////Play Animation
									//{
									//	Animator animator = gameplay_state.animators[player_index];
									//	if (animator.current_animation.looped && animator.current_frame >= ending_frame)
									//		animator.current_frame = 1;


									//	float frame = gameplay_state.animators[player_index].current_frame;

									//	foreach(AnimationCurve curve in animator.current_animation.curves)
									//	{
									//		KeyFrame[] keyframes = curve.keyframes;
									//		int transform_index = curve.transform_index + player_index * gameplay_state.skeleton.Length;

									//		fixed(Transform * p = &gameplay_state.transforms[transform_index])
									//		{
									//			float* f = &(*p).position.x + curve.property_tag;

									//			AnimateProperty(keyframes, frame, f);
									//		}
									//	}

									//	for (int attackbox_index = 0; attackbox_index < gameplay_state.players[player_index].attackboxes.Length; attackbox_index++)
									//	{
									//		if (animator.current_animation.attackbox_keys != null)
									//			for (int i = 0; i < animator.current_animation.attackbox_keys[attackbox_index].Length; i++)
									//			{
									//				if (frame > animator.current_animation.attackbox_keys[attackbox_index][i])
									//				{
									//					gameplay_state.players[player_index].attackboxes[attackbox_index].active = animator.current_animation.attackbox_values[attackbox_index][i];
									//				}
									//			}
									//	}

									//	for (int defendbox_index = 0; defendbox_index < gameplay_state.players[player_index].defendboxes.Length; defendbox_index++)
									//	{
									//		if (animator.current_animation.defendbox_keys != null)
									//			for (int i = 0; i < animator.current_animation.defendbox_keys[defendbox_index].Length; i++)
									//			{
									//				if (frame > animator.current_animation.defendbox_keys[defendbox_index][i])
									//				{
									//					gameplay_state.players[player_index].defendboxes[defendbox_index].active = animator.current_animation.defendbox_values[defendbox_index][i];
									//				}
									//			}
									//	}

									//	animator.current_frame += TARGET_FRAMERATE * delta_time;

									//	gameplay_state.animators[player_index] = animator;
									//}
								}

								//Move Player
								{
									float acceleration = 100.0f;
									float jump_speed = 8;
									float max_speed = 5;
									float slide_coefficient = 0;
									bool no_horizontal_input = false;
									float ground_fall_velocity = -.01f;

									if (!gameplay_state.players[player_index].defeated)
									{
										if (ButtonDown(player_index, RIGHT))
											gameplay_state.players[player_index].velocity.x += acceleration * game.delta_time;
										else if (ButtonDown(player_index, LEFT))
											gameplay_state.players[player_index].velocity.x -= acceleration * game.delta_time;
										else
											no_horizontal_input = true;
									}

									if (gameplay_state.players[player_index].velocity.x > max_speed)
										gameplay_state.players[player_index].velocity.x = max_speed;
									else if (gameplay_state.players[player_index].velocity.x < -max_speed)
										gameplay_state.players[player_index].velocity.x = -max_speed;

									if (gameplay_state.players[player_index].grounded)
									{
										gameplay_state.players[player_index].velocity.y = ground_fall_velocity;

										if (no_horizontal_input)
											gameplay_state.players[player_index].velocity.x *= slide_coefficient;

										if (!gameplay_state.players[player_index].defeated && ButtonDown(player_index, JUMP))
											gameplay_state.players[player_index].velocity.y = jump_speed;
									}
									else
									{
										gameplay_state.players[player_index].velocity.y -= gameplay_state.gravity * game.delta_time;
									}

									float ax_half = gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].scale.x / 2;
									float ay_half = gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].scale.y / 2;


									float old_x = gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.x;
									gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.x += gameplay_state.players[player_index].velocity.x * game.delta_time;

									for (int i = 0; i < block_count; i++)
									{
										Transform b = gameplay_state.blocks[i];
										if (Intersect(gameplay_state.transforms[gameplay_state.players[player_index].entity_ID], b))
										{
											if (old_x < b.position.x)
												gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.x -= (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.x + (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].scale.x / 2)) - (b.position.x - (b.scale.x / 2));
											else if (old_x > b.position.x)
												gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.x += (b.position.x + (b.scale.x / 2)) - (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.x - (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].scale.x / 2));
										}
									}

									float old_y = gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.y;
									gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.y += gameplay_state.players[player_index].velocity.y * game.delta_time;

									gameplay_state.players[player_index].grounded = false;

									for (int i = 0; i < block_count; i++)
									{
										Transform b = gameplay_state.blocks[i];
										if (Intersect(gameplay_state.transforms[gameplay_state.players[player_index].entity_ID], b))
										{
											if (old_y < b.position.y)
											{
												gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.y -= (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.y + (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].scale.y / 2)) - (b.position.y - (b.scale.y / 2));
												gameplay_state.players[player_index].velocity.y = 0;
											}
											else if (old_y > b.position.y)
											{
												gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.y += (b.position.y + (b.scale.y / 2)) - (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position.y - (gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].scale.y / 2));
												gameplay_state.players[player_index].grounded = true;
											}
										}
									}

									if (v3_Magnitude(gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position) > 50)
									{
										gameplay_state.transforms[gameplay_state.players[player_index].entity_ID].position = (v3)v3_zero;
										gameplay_state.players[player_index].stock--;
									}
								}


								//Hurt Player --TODO fix. also make sure only applies the first time on the first frame of an intersection with first defendbox. Is currently be multiple damaging.
								{
									//for (int my_attack = 0; my_attack < gameplay_state.players[player_index].attackboxes.Length; my_attack++)
									//{
									//	if (gameplay_state.players[player_index].attackboxes[my_attack].active)
									//		for (int other_player = 0; other_player < gameplay_state.PLAYER_COUNT; other_player++)
									//		{
									//			if (other_player == player_index)
									//				continue;
									//			for (int your_defend = 0; your_defend < gameplay_state.players[other_player].defendboxes.Length; your_defend++)
									//			{
									//				var a = WorldSpaceMatrix(gameplay_state.players[player_index].attackboxes[my_attack].transform_index, gameplay_state.transforms);
									//				var b = WorldSpaceMatrix(gameplay_state.players[other_player].defendboxes[your_defend].transform_index, gameplay_state.transforms);

									//				Vector3 v = Transform_v3(a, Vector3.Zero);
									//				Vector3 w = Transform_v3(b, Vector3.Zero);

									//				var dist = Vector3.Distance(v, w);
									//				bool intersects = (dist <= (gameplay_state.players[other_player].defendboxes[your_defend].radius + gameplay_state.players[player_index].attackboxes[my_attack].radius));

									//				if (intersects)
									//				{
									//					gameplay_state.players[other_player].current_health -= 10 * delta_time;
									//					if (gameplay_state.players[other_player].current_health <= 0)
									//					{
									//						gameplay_state.players[other_player].stock--;
									//						if (gameplay_state.players[other_player].stock > 0)
									//							gameplay_state.players[other_player].current_health = gameplay_state.max_health;
									//						else if (!gameplay_state.players[other_player].defeated)
									//						{
									//							gameplay_state.players[other_player].defeated = true;
									//							gameplay_state.animators[other_player].current_animation = DefinedAnimations.die_animation;
									//							gameplay_state.animators[other_player].current_frame = 1;
									//						}
									//					}
									//				}
									//			}
									//		}
									//}
								}
							}

							//Update Camera
							{
								////TODO actual frustum check to keep players on screen
								float min_x = FLT_MAX;
								float min_y = FLT_MAX;

								float max_x = -FLT_MAX;
								float max_y = -FLT_MAX;

								for (int i = 0; i < PLAYER_COUNT; i++)
								{
									float x = gameplay_state.transforms[gameplay_state.players[i].entity_ID].position.x;
									float y = gameplay_state.transforms[gameplay_state.players[i].entity_ID].position.y;

									if (x < min_x)
										min_x = x;
									if (x > max_x)
										max_x = x;

									if (y < min_y)
										min_y = y;
									if (y > max_y)
										max_y = y;
								}

								gameplay_state.camera.position.x = (max_x + min_x) / 2;
								gameplay_state.camera.position.y = (max_y + min_y) / 2;
								gameplay_state.camera.position.z = -20 - (max_x - min_x);
							}

							//Check Match Complete
							{
								int remaining_players = 0;

								for (int i = 0; i < PLAYER_COUNT; i++)
								{
									if (!gameplay_state.players[i].defeated)
									{
										remaining_players++;
										gameplay_state.winner = i + 1;
									}
								}

								if (remaining_players != 1)
									gameplay_state.winner = 0;

								gameplay_state.time_remaining -= game.delta_time;

								if(gameplay_state.time_remaining < 0)
									gameplay_state.time_remaining = 0;

								gameplay_state.game_over = gameplay_state.winner != 0 || remaining_players == 0 || gameplay_state.time_remaining == 0;
							}
						}
					}

					//Render
					{
						FillVerticalGradient(cyan, 0xFF0044AA);

						//Draw Scene
						{
							//get camera matrix
							m4x4 world_to_camera = GetMatrix(InvertTransform(gameplay_state.camera));

							//Draw Blocks
							{
								for (int i = 0; i < block_count; i++)
								{
									m4x4 local_to_world = WorldSpaceMatrix(i, gameplay_state.blocks);
									m4x4 camera_to_clip = Perspective(0.1f, 100, gameplay_state.field_of_view, WIDTH, HEIGHT);
									m4x4 local_to_clip = Concatenate(Concatenate(local_to_world, world_to_camera), camera_to_clip);

									v4 position = { -.5f, .5f, 0, 1 };
									position = Transform_Vector4(local_to_clip, position);

									if (position.w != 0)
										position = v4_Divide(position, position.w);

									//place origin at center of screen
									position.x++;
									position.y++;

									//scale space to fill screen
									position.x *= WIDTH / 2;
									position.y *= HEIGHT / 2;

									v4 position2 = { .5f, -.5f, 0, 1 };
									position2 = Transform_Vector4(local_to_clip, position2);

									if (position2.w != 0)
										position2 = v4_Divide(position2, position2.w);

									//place origin at center of screen
									position2.x++;
									position2.y++;

									//scale space to fill screen
									position2.x *= WIDTH / 2;
									position2.y *= HEIGHT / 2;

									float width = position2.x - position.x;
									float height = position2.y - position.y;

									FillRectangle(brown, position.x, position.y, width, height);
								}
							}

							v3 transformed_positions[gameplay_state.transform_count];
							#define state gameplay_state
							#define Matrix4x4 m4x4
							#define Vector3 v3
							//Draw Transforms
							{
								for (int i = 0; i < state.transform_count; i++)
								{
									Matrix4x4 local_to_world = WorldSpaceMatrix(i, state.transforms);
									Matrix4x4 local_to_camera = Concatenate(local_to_world, world_to_camera);

									v3 position = Transform_v3(local_to_camera, (v3)v3_zero);

									Matrix4x4 camera_to_clip = Perspective(0.1f, 100, state.field_of_view, WIDTH, HEIGHT);

									v4 vec4 =  (v4){ position.x, position.y, position.z, 1 };
									vec4 = Transform_Vector4(camera_to_clip, vec4);

									position = (v3){ vec4.x, vec4.y, vec4.z };

									if (vec4.w != 0)
										v3_Divide(position, vec4.w);

									//place origin at center of screen
									position.x++;
									position.y++;

									//scale space to fill screen
									position.x *= WIDTH / 2;
									position.y *= HEIGHT / 2;

									transformed_positions[i] = position;
								}

								for (int i = 0; i < gameplay_state.transform_count; i++)
								{
									v3 position = transformed_positions[i];
									v3 parent_position = position;

									if (state.transforms[i].parent != -1)
										parent_position = transformed_positions[state.transforms[i].parent];

									float d = state.camera.position.z - position.z;
									float width = 450.0f / (d);
									float half_width = width / 2.0f;

									DrawLine(state.player_colors[i / state.skeleton.length], position.x, position.y, parent_position.x, parent_position.y);
									Draw_Circle(state.player_colors[i / state.skeleton.length], position.x, position.y, -half_width, 1);
								}
							}

							if (game.view_debug)
							{
								//Draw Hitboxes
								{
									#define PIXELS_PER_UNIT 32
									for (int player_index = 0; player_index < PLAYER_COUNT; player_index++)
									{
										for (int attackbox_index = 0; attackbox_index < state.players[player_index].attackbox_count; attackbox_index++)
										{
											if (state.players[player_index].attackboxes[attackbox_index].active)
											{
												v3 center = transformed_positions[state.players[player_index].attackboxes[attackbox_index].transform_index];
												float width = state.players[player_index].attackboxes[attackbox_index].radius * 2 * PIXELS_PER_UNIT;
												DrawHitbox(center, red, width);
											}
										}

										for (int i = 0; i < state.players[player_index].defendbox_count; i++)
										{
											if (state.players[player_index].defendboxes[i].active)
											{
												v3 center = transformed_positions[state.players[player_index].defendboxes[i].transform_index];
												float d = state.camera.position.z - center.z;
												float width = 30 * (state.players[player_index].defendboxes[i].radius * 2 * PIXELS_PER_UNIT) / (d);
												DrawHitbox(center, blue, -width);
											}
										}
									}
								}

								// //Draw Colliders
								// {
								// 	for (int i = 0; i < state.blocks.Length; i++)
								// 	{
								// 		Matrix4x4 local_to_world = WorldSpaceMatrix(i, state.blocks);
								// 		Matrix4x4 camera_to_clip = Perspective(0.1f, 100, state.field_of_view, WIDTH, HEIGHT);
								// 		Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

								// 		Vector4 position = new Vector4(-.5f, .5f, 0, 1);
								// 		position = Transform_Vector4(local_to_clip, position);

								// 		if (position.w != 0)
								// 			position /= position.w;

								// 		//place origin at center of screen
								// 		position.x++;
								// 		position.y++;

								// 		//scale space to fill screen
								// 		position.x *= WIDTH / 2;
								// 		position.y *= HEIGHT / 2;

								// 		Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
								// 		position2 = Transform_Vector4(local_to_clip, position2);

								// 		if (position2.w != 0)
								// 			position2 /= position2.w;

								// 		//place origin at center of screen
								// 		position2.x++;
								// 		position2.y++;

								// 		//scale space to fill screen
								// 		position2.x *= WIDTH / 2;
								// 		position2.y *= HEIGHT / 2;

								// 		DrawRectangle(blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
								// 	}

								// 	for (int i = 0; i < GameplayState.players.Length; i++)
								// 	{
								// 		Matrix4x4 local_to_world = WorldSpaceMatrix(GameplayState.players[i].entity_ID, state.transforms);
								// 		Matrix4x4 camera_to_clip = Perspective(0.1f, 100, state.field_of_view, WIDTH, HEIGHT);
								// 		Matrix4x4 local_to_clip = local_to_world * world_to_camera * camera_to_clip;

								// 		Vector4 position = new Vector4(-.5f, .5f, 0, 1);
								// 		position = Transform_Vector4(local_to_clip, position);

								// 		if (position.w != 0)
								// 			position /= position.w;

								// 		//place origin at center of screen
								// 		position.x++;
								// 		position.y++;

								// 		//scale space to fill screen
								// 		position.x *= WIDTH / 2;
								// 		position.y *= HEIGHT / 2;

								// 		Vector4 position2 = new Vector4(.5f, -.5f, 0, 1);
								// 		position2 = Transform_Vector4(local_to_clip, position2);

								// 		if (position2.w != 0)
								// 			position2 /= position2.w;

								// 		//place origin at center of screen
								// 		position2.x++;
								// 		position2.y++;

								// 		//scale space to fill screen
								// 		position2.x *= WIDTH / 2;
								// 		position2.y *= HEIGHT / 2;

								// 		DrawRectangle(blue, position.x, position.y, position2.x - position.x, position2.y - position.y);
								// 	}
								// }
							}
						}

						//Draw Heads-Up Display (HUD)
						{
							int available_space = WIDTH / PLAYER_COUNT;
							int indent_x = 30;
							int indent_y = 10;
							int max_width = available_space - indent_x * 2;
							int health_height = 15;
							int padding = 4;
							int half_padding = padding / 2;
							for (int player = 0; player < PLAYER_COUNT; player++)
							{
								//Draw HealthBar
								{
									float portion = state.players[player].current_health / state.max_health;
									int current_width = (int)(portion * max_width);
									int x_pos = indent_x + available_space * player;
									int padded_height = health_height - padding;
									int padded_x_pos = x_pos + half_padding;
									int padded_y_pos = indent_y + half_padding;

									FillRectangle(black, x_pos, indent_y, max_width, health_height);
									FillRectangle(red, padded_x_pos, padded_y_pos, max_width - padding, padded_height);
									FillRectangle(green, padded_x_pos, padded_y_pos, current_width - padding, padded_height);
								}

								//Draw Stocks
								{
									for (int stock = 0; stock < state.players[player].stock; stock++)
									{
										FillCircle(state.player_colors[player], available_space * player + indent_x + 10 + (stock * (20 + 5)), 40, 10);
										Draw_Circle(black, available_space * player + indent_x + 10 + (stock * (25)), 40, 10, 3.0f);
									}
								}
							}

							//Draw Timer
							{
								int char_sprite_size = 8;
								char result[40];

								sprintf(result, "%.0f", state.time_remaining);
								string message = WrapString(result);
								DrawString(message, WIDTH / 2 - char_sprite_size * (message.length - 1), char_sprite_size * 2);
							}

							if (state.game_over)
							{
								//Draw Game End Message
								{
									int offset_x = WIDTH / 2, offset_y = HEIGHT / 2;

									char result[40];
									if (state.winner == 0)
										sprintf(result, "TIE!");
									else
										sprintf(result, "PLAYER %d WINS!", state.winner);
									string message = WrapString(result);
									DrawString(message, offset_x, offset_y);
								}
							}
						}

						Flatten();
					}
				} break;
				case MeshDemo:
				{
					//Update
					{
						cube_transform.rotation.y += Tau / 16 * game.delta_time;
					}

					Clear();

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
						Transform inverted_camera = InvertTransform(mesh_demo_camera);
						m4x4 world_to_camera = GetMatrix(inverted_camera);
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

								v3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, mesh_demo_camera.position));

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
				} break;
				case Particle:
				{
					Fill(0xFFFF00FF);
					for (int i = 0; i < 250; i++)
					{
						float x = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						float y = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						FillRectangle(red, x, y, 10, 10);
						x = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						y = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						FillRectangle(red, x, y, 10, 10);
						x = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						y = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						FillRectangle(red, x, y, 10, 10);
						x = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						y = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						FillRectangle(red, x, y, 10, 10);																		
					}
				} break;
				default:
				{
					game.current_game_state = SplashScreenState;
				} break;
			}

			if (game.view_debug)
			{
				//Display Game Stats
				{
					char moop[100];
					char boop[100];
					sprintf(moop,"FPS: %.2f", game.frames_per_second);
					sprintf(boop,"delta_time: %.9f", game.delta_time);

					string fps_string = WrapString(moop);
					string delta_string = WrapString(boop);
					DrawString(fps_string, 16, 16);
					DrawString(delta_string, 16, 28);
				}
			}

			game.time_since_last_frame = 0;
		}
	}

	//Update Timing
	{
		float elapsed = (float)(clock() - game.previous_time) / CLOCKS_PER_SEC;
		game.time_since_last_frame += elapsed;
		game.time_since_timing_recalculated += elapsed;

		if(game.fixed_framerate)
			game.delta_time = game.STANDARD_TIMESTEP;
		else
			game.delta_time = game.time_since_last_frame * game.time_scale;

		if (game.time_since_timing_recalculated >= game.TIME_RECALCULATION_INTERVAL)
		{
			game.frames_per_second = game.frames_since_last_second / game.time_since_timing_recalculated;
			game.time_since_timing_recalculated = game.frames_since_last_second = 0;
		}

		game.previous_time = clock();
	}
}