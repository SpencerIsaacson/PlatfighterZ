#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <float.h>
#include "SDL_Headers/SDL.h"

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
#define write_bytes fwrite
#define close_file fclose

typedef struct
{
	int length;
	char* characters;
} string;

typedef struct
{
	float x, y;
} Vec2;

typedef struct
{
	float x, y, z;
} Vec3;

typedef struct
{
	float x, y, z, w;
} Vec4;

typedef struct
{
	int parent;
	Vec3
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
	Vec2 position;
	Vec2 size;
} Hitbox;

#define MAX_HITBOX_COUNT 20
typedef struct 
{
	int hit_count;
	int hurt_count;
	Hitbox boxes[MAX_HITBOX_COUNT];
} HitFrame;

#define MAX_HITBOX_FRAMES 120
typedef struct {
	int frame_count;
	HitFrame frames[MAX_HITBOX_FRAMES];

} HitboxAnimation;

typedef struct
{
	Vec3 a, b, c;
	uint color;
	float brightness;
	Vec2 a_uv, b_uv, c_uv;
} Triangle;

typedef struct Mesh
{
	int vertices_length;
	Vec3* vertices;
	int indices_length;
	int* indices;
	int uvs_length;
	Vec2* uvs;
	int uv_indices_length;
	int* uv_indices;
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
	Vec2 velocity;
	bool grounded;
} Player;


typedef struct
{
	int width, height;
	uint* pixels;
} Bitmap;

//math and stuff
float GetMin(float a, float b, float c);
float GetMax(float a, float b, float c);

typedef enum GameStates
{
	SaveAnimation,
	AnimationEditor,
	SplashScreenState,
	TitleScreen,
	MainMenu,
	Level1,
	CharacterSelect,
	MeshDemo,
	SkinnedMesh,
	Gameplay,
	Particle, 
	TextureMappedTriangle,
	TextureMappedCube
} GameStates;

#define state_count 13

typedef struct
{
	//Timing
	float TIME_RECALCULATION_INTERVAL; //1.0f
	float TARGET_FRAMERATE;// 60.0f
	float STANDARD_TIMESTEP;// 1 / TARGET_FRAMERATE
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

uint Darker(uint color)
{
	uint r = (color & red ^ black) >> 17 << 16;
	uint g = (color & (green ^ black)) >> 9 << 8;
	uint b = (color & blue ^ black) >> 1;
	return black | r | g | b;
}

Vec3 NegateVector(Vec3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return v;
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

Vec3 v3_Add(Vec3 a, Vec3 b)
{
	Vec3 v;
	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return v;
}

Vec3 v3_Subtract(Vec3 a, Vec3 b)
{
	Vec3 v;
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return v;
}

Vec3 CrossProduct(Vec3 a, Vec3 b)
{
	Vec3 result =
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};

	return result;
}

float v3_Magnitude(Vec3 v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 v3_Scale(Vec3 v, float s)
{
	Vec3 result = { v.x * s, v.y * s, v.z * s };
	return result;
}

Vec3 v3_Divide(Vec3 v, float s)
{
	Vec3 result = { v.x / s, v.y / s, v.z / s };
	return result;
}

Vec4 v4_Divide(Vec4 v, float s)
{
	Vec4 result = { v.x / s, v.y / s, v.z / s, v.w / s };
	return result;
}

float v3_DotProduct(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

Vec3 v3_Normalized(Vec3 v)
{
	return v3_Divide(v, v3_Magnitude(v));
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

Vec3 Transform_v3(m4x4 m, Vec3 v)
{
	Vec3 result =
	{
		m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41,
		m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42,
		m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43,
	};

	return result;
}

Vec4 Transform_Vector4(m4x4 m, Vec4 v)
{
	Vec4 result =
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

Vec2 Lerp_v2(Vec2 a, Vec2 b, float t)
{
	Vec2 v;
	v.x = a.x + (t * (b.x - a.x));
	v.y = a.y + (t * (b.y - a.y));
	return v;
}

float Lerp_Float(float a, float b, float t)
{
	return a + t * (b - a);
}

float Sample(KeyFrame a, KeyFrame b, float frame)
{
	float t = (frame - a.frame) / (b.frame - a.frame);

	Vec2 c1 = { a.frame, a.value };
	Vec2 c2 = { a.frame + a.right_handle_x, a.value + a.right_handle_y };
	Vec2 c3 = { b.frame + b.left_handle_x, b.value + b.left_handle_y };
	Vec2 c4 = { b.frame, b.value };
	Vec2 d = Lerp_v2(c1, c2, t);
	Vec2 e = Lerp_v2(c2, c3, t);
	Vec2 f = Lerp_v2(c3, c4, t);
	Vec2 g = Lerp_v2(d, e, t);
	Vec2 h = Lerp_v2(e, f, t);
	Vec2 i = Lerp_v2(g, h, t);

	return i.y;
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

Vec3 GetCentroid(Triangle t)
{
	Vec3 v = v3_Add(v3_Add(t.a, t.b), t.c);
	v.x /= 3;
	v.y /= 3;
	v.z /= 3;
	return v;
}

bool Less(Triangle a, Triangle b)
{
	Vec3 a_centroid = GetCentroid(a);
	Vec3 b_centroid = GetCentroid(b);

	return a_centroid.z < b_centroid.z;
}

void SwapTriangles(Triangle triangles[], int a, int b)
{
	Triangle temp = triangles[a];
	triangles[a] = triangles[b];
	triangles[b] = temp;
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

void QuickSort(Triangle a[], int lo, int hi)
{
	if (hi <= lo) return;
	int j = Partition(a, lo, hi);
	QuickSort(a, lo, j - 1);
	QuickSort(a, j + 1, hi);
}

void SortByDepth(Triangle a[], int length)
{
	QuickSort(a, 0, length - 1);
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
int WIDTH, HEIGHT, pixel_count;
uint* pixels;

Mesh mesh;
Mesh cube_mesh;
Transform cube_transform;
Transform mesh_demo_camera;


typedef struct
{
	bool started;
	bool ended;
	float time;
	float alpha;
	Bitmap logo;
	int x_min, x_max, y_min, y_max;
} SplashScreen;

SplashScreen splash;

__declspec(dllexport) void InitViewport(int width, int height, uint _pixels[])  //TODO move more state here and out of the "run" arguments
{
	WIDTH = width;
	HEIGHT = height;
	pixel_count = WIDTH*HEIGHT;
	pixels = &_pixels[0];
}

InitViewport2(int width, int height)  //TODO move more state here and out of the "run" arguments
{
	WIDTH = width;
	HEIGHT = height;
	pixel_count = WIDTH*HEIGHT;
}

void Clear()
{
	memset(pixels, 0, pixel_count * sizeof(uint));
}

void Fill(uint color)
{
	for (int i = 0; i < pixel_count; i+=8)
	{
		pixels[i+0] = color;
		pixels[i+1] = color;
		pixels[i+2] = color;
		pixels[i+3] = color;
		pixels[i+4] = color;
		pixels[i+5] = color;
		pixels[i+6] = color;
		pixels[i+7] = color;								
	}
}

void PutPixel_ByPosition(uint color, int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[y * WIDTH + x] = color;
}

void PutPixel_ByIndex(uint color, int i)
{
	if (i >= 0 && i < pixel_count)
		pixels[i] = color;
}

void DrawHorizontalSegment(uint color, int y, int x1, int x2)
{
	int pixel_row = y * WIDTH;

	for (int i = pixel_row + x1; i <= pixel_row + x2; i++)
	{
		int x = i - pixel_row;
		PutPixel_ByPosition(color, x, y);
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

Vec3 ToBarycentricSpace(float v_x, float v_y, Vec2 a, Vec2 b, Vec2 c)
{
	float b1, b2, b3;
	float denom = (a.y - c.y) * (b.x - c.x) + (b.y - c.y) * (c.x - a.x);

	b1 = ((v_y - c.y) * (b.x - c.x) + (b.y - c.y) * (c.x - v_x)) / denom;
	b2 = ((v_y - a.y) * (c.x - a.x) + (c.y - a.y) * (a.x - v_x)) / denom;
	b3 = ((v_y - b.y) * (a.x - b.x) + (a.y - b.y) * (b.x - v_x)) / denom;

	Vec3 result = { b1, b2, b3 };
	return result;
}

Vec2 FromBaryCentricSpace(float b1, float b2, float b3, Vec2 a, Vec2 b, Vec2 c)
{
	float v_x, v_y;

	v_x = b1*a.x + b2*b.x + b3*c.x;
	v_y = b1*a.y + b2*b.y + b3*c.y;
	Vec2 result = {v_x, v_y};
	return result;
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

void FillTriangle_VertexColors(Vec2 a, Vec2 b, Vec2 c, uint a_color, uint b_color, uint c_color)
{
	int x_min = (int)GetMin(a.x, b.x, c.x);
	int y_min = (int)GetMin(a.y, b.y, c.y);
	int x_max = (int)roundf(GetMax(a.x, b.x, c.x));
	int y_max = (int)roundf(GetMax(a.y, b.y, c.y));


	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			Vec3 v = ToBarycentricSpace(_x, _y, a, b, c);
			bool in_triangle = !(v.x < 0 || v.y < 0 || v.z < 0);
			if (in_triangle)
			{
				uint d_color = LerpColor(c_color, a_color, v.x);
				uint e_color = LerpColor(a_color, b_color, v.y);
				uint f_color = LerpColor(e_color, d_color, v.z);
				PutPixel_ByPosition(f_color, _x, _y);
			}
		}
	}
}

void FillTriangle_Texture(Vec2 a, Vec2 b, Vec2 c, Vec2 a_uv, Vec2 b_uv, Vec2 c_uv, Bitmap texture)
{
	int x_min = (int)GetMin(a.x, b.x, c.x);
	int y_min = (int)GetMin(a.y, b.y, c.y);
	int x_max = (int)roundf(GetMax(a.x, b.x, c.x));
	int y_max = (int)roundf(GetMax(a.y, b.y, c.y));


	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			Vec3 v = ToBarycentricSpace(_x, _y, a, b, c);
			bool in_triangle = !(v.x < 0 || v.y < 0 || v.z < 0);
			if (in_triangle)
			{
				Vec2 v_uv = FromBaryCentricSpace(v.x, v.y, v.z, a_uv, b_uv, c_uv);
				
				while(v_uv.y > 1)
					v_uv.y--;

				while(v_uv.x > 1)
					v_uv.x--;

				v_uv.x*=texture.width-1;
				v_uv.y*=texture.height-1;

				int texture_index = (int)v_uv.y*texture.width+(int)v_uv.x;
				
				if(texture_index >= texture.width*texture.height)
					texture_index = texture.width*texture.height - 1;
				else if(texture_index < 0)
					texture_index = 0;
				
				uint color_from_texture = texture.pixels[texture_index];
				PutPixel_ByPosition(color_from_texture, _x, _y);
			}
		}
	}
}


Vec3 CameraToClipToScreen(Vec3 v)
{
	Vec4 v_4 = { v.x, v.y, v.z, 1 };
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

void FillHorizontalGradient(uint color1, uint color2)
{
	for (int x = 0; x < WIDTH; x++)
	{
		uint color = LerpColor(color1, color2, x / (float)WIDTH);
		for (int y = 0; y < HEIGHT; y++)
		{
			pixels[y * WIDTH + x] = color;
		}
	}
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

Mesh LoadMeshWithUVindices(char* path)
{
	FILE* fp = fopen(path, "r");
	int line_number = 0;

	int vertex_count = 0;
	int index_count = 0;
	int uv_count = 0;
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
		case 'u': //TODO replace with vt
			uv_count++;
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
	Vec3* vertices = malloc(sizeof(Vec3) * vertex_count);
	Vec2* uvs = malloc(sizeof(Vec2) * uv_count);
	int* indices = malloc(sizeof(int) * index_count);
	int* uv_indices = malloc(sizeof(int) * index_count);

	return_mesh.vertices = vertices;
	return_mesh.vertices_length = vertex_count;
	return_mesh.indices = indices;
	return_mesh.indices_length = index_count;
	return_mesh.uvs = uvs;
	return_mesh.uvs_length = uv_count;
	return_mesh.uv_indices = uv_indices;
	return_mesh.uv_indices_length = index_count;

	int vertex = 0;
	int vertex_index = 0;
	int uv = 0;
	int uv_index = 0;

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
			{

				token = strtok(NULL, " ");
				float x = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float y = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float z = (float)strtod(token, &ptr);
				Vec3 v = { x, y, z };
				return_mesh.vertices[vertex++] = v;
			} break;
			case 'u': //TODO replace with vt
			{
				token = strtok(NULL, " ");
				float u = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float v = (float)strtod(token, &ptr);
				Vec2 v2 = { u, v };
				return_mesh.uvs[uv++] = v2;
			} break;			
			case 'f':
				token = strtok(NULL, " /");
				int a = (int)strtol(token, &ptr, 10);

				token = strtok(NULL, "/ ");
				int uv_a = (int)strtol(token, &ptr, 10);

				token = strtok(NULL, " /");
				int b = (int)strtol(token, &ptr, 10);

				token = strtok(NULL, "/ ");
				int uv_b = (int)strtol(token, &ptr, 10);

				token = strtok(NULL, " /");
				int c = (int)strtol(token, &ptr, 10);

				token = strtok(NULL, "/ ");
				int uv_c = (int)strtol(token, &ptr, 10);

				return_mesh.indices[vertex_index++] = a - 1;
				return_mesh.indices[vertex_index++] = b - 1;
				return_mesh.indices[vertex_index++] = c - 1;

				return_mesh.uv_indices[uv_index++] = uv_a - 1;
				return_mesh.uv_indices[uv_index++] = uv_b - 1;
				return_mesh.uv_indices[uv_index++] = uv_c - 1;
				break;
			case '\n':
				//empty line
				break;
			default:
				//unsupported line ignored
				break;
		}
	}

	close_file(fp);
	return return_mesh;
}

Mesh LoadMesh(char* path)
{
	FILE* fp = fopen(path, "r");
	int line_number = 0;

	int vertex_count = 0;
	int index_count = 0;
	int uv_count = 0;
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
		case 'u': //TODO replace with vt
			uv_count++;
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
	Vec3* vertices = malloc(sizeof(Vec3) * vertex_count);
	Vec2* uvs = malloc(sizeof(Vec2) * uv_count);
	int* indices = malloc(sizeof(int) * index_count);
	int* uv_indices = malloc(sizeof(int) * index_count);

	return_mesh.vertices = vertices;
	return_mesh.vertices_length = vertex_count;
	return_mesh.indices = indices;
	return_mesh.indices_length = index_count;
	return_mesh.uvs = uvs;
	return_mesh.uvs_length = uv_count;
	return_mesh.uv_indices = uv_indices;
	return_mesh.uv_indices_length = index_count;

	int vertex = 0;
	int vertex_index = 0;
	int uv = 0;
	int uv_index = 0;

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
			{

				token = strtok(NULL, " ");
				float x = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float y = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float z = (float)strtod(token, &ptr);
				Vec3 v = { x, y, z };
				return_mesh.vertices[vertex++] = v;
			} break;
			case 'u': //TODO replace with vt
			{
				token = strtok(NULL, " ");
				float u = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float v = (float)strtod(token, &ptr);
				Vec2 v2 = { u, v };
				return_mesh.uvs[uv++] = v2;
			} break;			
			case 'f':
				token = strtok(NULL, " ");
				int a = (int)strtol(token, &ptr, 10);
				token = strtok(NULL, " ");
				int b = (int)strtol(token, &ptr, 10);
				token = strtok(NULL, " ");
				int c = (int)strtol(token, &ptr, 10);
				return_mesh.indices[vertex_index++] = a - 1;
				return_mesh.indices[vertex_index++] = b - 1;
				return_mesh.indices[vertex_index++] = c - 1;
				break;
			case '\n':
				//empty line
				break;
			default:
				//unsupported line ignored
				break;
		}
	}

	close_file(fp);
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
			PutPixel_ByPosition(color, (int)x, (int)y);
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
			PutPixel_ByPosition(color, (int)x, (int)y);
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
	for (int i = 0; i < pixel_count; i++)
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
			PutPixel_ByPosition(BlendColor(color, pixels[(y + _y) * WIDTH + (x + _x)]), _x + x, _y + y);
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
	for (int i = x; i < pixel_count - WIDTH - x; i += WIDTH)
	{
		PutPixel_ByIndex(BlendColor(color, pixels[i]), i);
	}
}

void DrawVertical(uint color, int x)
{
	for (int i = x; i < pixel_count - WIDTH - x; i += WIDTH)
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
			PutPixel_ByPosition(color, (int)(_x + x), (int)(_y + y));
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
				PutPixel_ByPosition(color, _x, _y);
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
				PutPixel_ByPosition(color, _x, _y);
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

				if (index >= 0 && index < pixel_count)
					PutPixel_ByPosition(BlendColor(color, pixels[_y * WIDTH + _x]), _x, _y);
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
			m4x4 object_to_world = m4x4_identity; //replace with object transform parameter

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
					Vec3 a = v3_Subtract(t.b, t.a);
					Vec3 b = v3_Subtract(t.c, t.a);
					Vec3 normal = v3_Normalized(CrossProduct(a, b));

					Vec3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, camera.position));

					if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
					{
						SwapTriangles(triangles, i, remaining_count - 1);
						remaining_count--;
						goto label;//TODO replace with while
					}
					else
					{
						Vec3 backward = { 0,0,-1 };
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
				Vec2 a = { t.a.x, t.a.y };
				Vec2 b = { t.b.x, t.b.y };
				Vec2 c = { t.c.x, t.c.y };

				if (fill_toggle)
					FillTriangle_VertexColors(a, b, c, red, green, blue);
				else
					FillTriangle(t.color, (int)t.a.x, (int)t.a.y, (int)t.b.x, (int)t.b.y, (int)t.c.x, (int)t.c.y);
			}
		}

		free(triangles);
	}
}


void RenderTexturedMesh(Mesh mesh, Transform object_transform, Transform camera, Bitmap texture)
{
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
				triangles[i].a_uv = mesh.uvs[mesh.uv_indices[i * 3 + 0]];
				triangles[i].b_uv = mesh.uvs[mesh.uv_indices[i * 3 + 1]];
				triangles[i].c_uv = mesh.uvs[mesh.uv_indices[i * 3 + 2]];
			}
		}

		//transform points
		{
			//get object transform matrix
			m4x4 object_to_world =  GetMatrix(object_transform);

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
					Vec3 a = v3_Subtract(t.b, t.a);
					Vec3 b = v3_Subtract(t.c, t.a);
					Vec3 normal = v3_Normalized(CrossProduct(a, b));

					Vec3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, camera.position));

					if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
					{
						SwapTriangles(triangles, i, remaining_count - 1);
						remaining_count--;
						goto label;//TODO replace with while
					}
					else
					{
						Vec3 backward = { 0,0,-1 };
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
				Vec2 a = { t.a.x, t.a.y };
				Vec2 b = { t.b.x, t.b.y };
				Vec2 c = { t.c.x, t.c.y };

				FillTriangle_Texture(a, b, c, t.a_uv, t.b_uv, t.c_uv, texture);
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
	Keys_Backspace = 8,
	Keys_Tab = 9,
	Keys_Enter = 13,
	Keys_Space = 32,
	Keys_Left = 37, Keys_Up, Keys_Right, Keys_Down,
	Keys_Delete = 46,
	Keys_A = 65, Keys_B, Keys_C, Keys_D, Keys_E, Keys_F, Keys_G, Keys_H, Keys_I, Keys_J, Keys_K, Keys_L, Keys_M, Keys_N, Keys_O, Keys_P, Keys_Q, Keys_R, Keys_S, Keys_T, Keys_U, Keys_V, Keys_W, Keys_X, Keys_Y, Keys_Z,
	Keys_Add = 107,
	Keys_Subtract = 109,
	Keys_NumPad0 = 96, Keys_NumPad1, Keys_NumPad2, Keys_NumPad3, Keys_NumPad4, Keys_NumPad5, Keys_NumPad6, Keys_NumPad7, Keys_NumPad8, Keys_NumPad9,
	Keys_F4 = 115,
	Keys_LCtrl = 162,
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
	Vec4* weights;
	int weight_indices_length;
	Weight_Index* weight_indices;
	int transformed_vertices_length;
	Vec3* transformed_vertices;
	Transform camera;

	bool fill_toggle;

	float frame;
	float animation_length;
	float rotation_y;
	bool animation_play;
	bool rotation_play;
	bool view_fps;
} SkinnedMeshDemo;

SkinnedMeshDemo skinned_demo;

void SetWeights()
{
	skinned_demo.weights = malloc(skinned_demo.mesh.vertices_length * sizeof(Vec4));
	skinned_demo.weights_length = mesh.vertices_length;

	for (int i = 0; i < skinned_demo.mesh.vertices_length; i++)
	{
		Vec4 weight = { 1, 0, 0, 0 };
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

	printf("uvs:\n");
	for (int i = 0; i < mesh.uvs_length; i++)
	{
		printf("{ %+f, %+f }\n", mesh.uvs[i].x, mesh.uvs[i].y);
	}

	printf("uv indices:\n");
	for (int i = 0; i < mesh.uv_indices_length; i += 3)
	{
		printf("{ %d, %d, %d }\n", mesh.uv_indices[i], mesh.uv_indices[i + 1], mesh.uv_indices[i + 2]);
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
				PutPixel_ByPosition(white, col + x, row + y);
		}
	}
}

void DrawCharacterScaled(CharSprite sprite, int x, int y, int scale, uint color)
{
	char* p = &sprite.row1;
	for (int row = 0; row < 8; row++, p++)
	{
		for (int col = 0; col < 8; col++)
		{
			bool pixel_active = ((*p << col) & 0b10000000) == 0b10000000;
			if (pixel_active)
				FillRectangle_Blend(color, col*scale + x, row*scale + y, scale, scale);
		}
	}
}

void DrawStringScaled(string s, int x, int y, int scale, uint color)
{
	for (int i = 0; i < s.length; i++)
	{
		char a = tolower(s.characters[i]);
		for (int o = 0; o < char_dict_length; o++)
		{
			if (a == char_dict[o])
			{
				DrawCharacterScaled(font_set[o], x + i * 9*scale, y, scale, color);
				//todo break and see how much time is saved
			}

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
		.parent = -1,
		.position = v3_zero,
		.rotation = v3_zero,
		.scale = v3_one
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

string WrapString(char* message)
{
	return (string){.characters = message, .length = strlen(message)};
}

string title;
string press_space;



#define PLAYER_COUNT 4 //currently capped at 4, as control mappings aren't yet flexible enough to handle arbitrary numbers of players
#define block_count 30

typedef struct
{
	//Game World
	int transform_count;
	Transform transforms[1000]; //TODO init transforms


	Player players[PLAYER_COUNT];
	uint player_colors[PLAYER_COUNT];// = new uint[]{ red, 0xFF008000, blue, purple };

	//Play variables
	int winner;// = 0;
	bool game_over;// = false;
	float initial_time;// = 99;
	float time_remaining;
	float max_health;

	//physics
	float gravity;// = 10;
} GameplayState;

GameplayState gameplay_state;

#define PIXELS_PER_UNIT 128

void ResetGame()
{
	gameplay_state.game_over = false;
	gameplay_state.time_remaining = gameplay_state.initial_time;

	gameplay_state.transform_count = PLAYER_COUNT;

	float distance_apart = 3.5f;
	float leftmost_position = -(PLAYER_COUNT - 1) * distance_apart / 2;

	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		gameplay_state.players[i].entity_ID = i;
		gameplay_state.transforms[gameplay_state.players[i].entity_ID] = DefaultTransform();
		gameplay_state.transforms[gameplay_state.players[i].entity_ID].position.x = leftmost_position + distance_apart * i;
		gameplay_state.players[i].current_health = gameplay_state.max_health;
		gameplay_state.players[i].defeated = false;
		gameplay_state.players[i].stock = 5;
		gameplay_state.players[i].velocity.y = 0;
	}
}

HitboxAnimation punch;

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

	//Init HItboxAnimations
	{
		FILE* file_pointer = open_file("Assets/idle", "r");
		read_bytes(&punch,sizeof(HitboxAnimation),1,file_pointer);
		close_file(file_pointer);
	}

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

	//Init TitleScreen
	{
		title = WrapString("Platfighter Z");
		press_space = WrapString("Press Space");
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

		skinned_demo.transformed_vertices = malloc(sizeof(Vec3) * skinned_demo.mesh.vertices_length);
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
		Vec3 forward_10 = { 0, 0, 10 };
		Vec3 backward_30 = { 0, 0, -30 };
		Vec3 zero = { 0, 0, 0 };
		Vec3 one = { 1, 1, 1 };
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

		gameplay_state.player_colors[0] = red;
		gameplay_state.player_colors[1] = 0xFF008000;
		gameplay_state.player_colors[2] = blue;
		gameplay_state.player_colors[3] =  purple;
		
		ResetGame();
	}

	//void Init SplashScreen
	{
		splash.started = false;
		splash.ended = false;
		splash.time = 0;
		splash.alpha = 0;
		splash.x_min = 650;
		splash.y_min = 125;
		splash.x_max = WIDTH - splash.x_min;
		splash.y_max = HEIGHT - splash.y_min;

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

	//Init Textured Cube demo
	{
		cube_mesh = LoadMeshWithUVindices("Assets/cube2.obj");
	}
}

__declspec(dllexport) void GameLoop()
{
	if (!game.fixed_framerate || (game.time_since_last_frame >= game.STANDARD_TIMESTEP))
	{
		//Tick
		{
			//Update Input Devices
			{
				PollKeyboard();								
			}

			//Handle Input
			{
				if (KeyDownFresh(Keys_G))
					game.view_debug = !game.view_debug;
				if (KeyDownFresh(Keys_F))
					game.fixed_framerate = !game.fixed_framerate;
				if(KeyDownFresh(Keys_Add))
					game.time_scale++;
				if(KeyDownFresh(Keys_Subtract))
					game.time_scale--;
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
				case AnimationEditor:
				{
					static float float_frame = 0;
					static int frame = 0;
					static bool play = true;
					static int selected_box;
					static HitFrame clipboard;
					#define Translate 0
					#define Scale 1
					static int mode = Translate;
					Vec2* modifier;

					if(mode == Translate)
						modifier = &(punch.frames[frame].boxes[selected_box].position);
					else if(mode == Scale)
						modifier = &punch.frames[frame].boxes[selected_box].size;

					if(KeyDownFresh(Keys_Space))
						play = !play;

					if(!play)
					{
						if(KeyDown(Keys_LCtrl))
						{
							if(KeyDownFresh(Keys_B))
							{
								punch.frame_count++;
							}

							if(KeyDownFresh(Keys_M))
							{
								if(mode == Translate)
									mode = Scale;
								else
									mode = Translate;
							}

							if(KeyDownFresh(Keys_R))
							{
								punch.frames[frame].hurt_count = 1;
								punch.frames[frame].hit_count = 0;

								for (int i = 0; i < MAX_HITBOX_COUNT; i++)
								{								
									punch.frames[frame].boxes[i] = (Hitbox){ .position = { 0, 0 }, .size = { 1, 1 } };
								}

							}
							if(KeyDown(Keys_S)) //save
							{
								game.current_game_state = SaveAnimation;
							}

							if(KeyDown(Keys_C)) //copy frame
								clipboard = punch.frames[frame];

							if(KeyDown(Keys_V)) //paste frame
								punch.frames[frame] = clipboard;						

							if(KeyDownFresh(Keys_Up))
							{
								if(selected_box < punch.frames[frame].hurt_count)
									punch.frames[frame].hurt_count++;
								else
									punch.frames[frame].hit_count++;
							}
							if(KeyDownFresh(Keys_Down))
							{
								if(selected_box < punch.frames[frame].hurt_count)
									punch.frames[frame].hurt_count--;
								else
									punch.frames[frame].hit_count--;
							}
						}
						else
						{								
							if(KeyDown(Keys_A))
								(*modifier).x -= game.delta_time;
							if(KeyDown(Keys_D))
								(*modifier).x += game.delta_time;
							if(KeyDown(Keys_W))
								(*modifier).y += game.delta_time;
							if(KeyDown(Keys_S))
								(*modifier).y -= game.delta_time;

							if(KeyDownFresh(Keys_Up) && selected_box < MAX_HITBOX_COUNT - 1)
								selected_box++;
							if(KeyDownFresh(Keys_Down) && selected_box > 0)
								selected_box--;

							if(selected_box > punch.frames[frame].hit_count + punch.frames[frame].hurt_count)
								selected_box = punch.frames[frame].hit_count + punch.frames[frame].hurt_count;

							if(KeyDownFresh(Keys_Left))
							{
								frame--;
								if(frame < 0)
									frame = punch.frame_count-1;
							}

							if(KeyDownFresh(Keys_Right))
							{
								frame++;
								if(frame == punch.frame_count)
									frame = 0;
							}
						}
					}


					Clear();
					PutPixel_ByPosition(white, WIDTH/2, HEIGHT/2);
					for (int i = 0; i < punch.frames[frame].hurt_count; i++)
					{
						Vec2 position = punch.frames[frame].boxes[i].position;
						position.x -= punch.frames[frame].boxes[i].size.x / 2.0f;
						position.y += punch.frames[frame].boxes[i].size.y / 2.0f;
						position.x *= +PIXELS_PER_UNIT;
						position.y *= -PIXELS_PER_UNIT;
						position.x += WIDTH / 2;
						position.y += HEIGHT / 2;
						DrawRectangle(blue, position.x, position.y , punch.frames[frame].boxes[i].size.x * PIXELS_PER_UNIT, punch.frames[frame].boxes[i].size.y * PIXELS_PER_UNIT);
					}

					for (int i = punch.frames[frame].hurt_count; i < punch.frames[frame].hurt_count + punch.frames[frame].hit_count; i++)
					{
						Vec2 position = punch.frames[frame].boxes[i].position;
						position.x -= punch.frames[frame].boxes[i].size.x / 2.0f;
						position.y += punch.frames[frame].boxes[i].size.y / 2.0f;
						position.x *= +PIXELS_PER_UNIT;
						position.y *= -PIXELS_PER_UNIT;
						position.x += WIDTH / 2;
						position.y += HEIGHT / 2;
						DrawRectangle(red, position.x, position.y , punch.frames[frame].boxes[i].size.x * PIXELS_PER_UNIT, punch.frames[frame].boxes[i].size.y * PIXELS_PER_UNIT);
					}

					FillRectangle(0xFFAAAAAA, 0, HEIGHT - 60, WIDTH, 60);
					
					int moop = WIDTH/punch.frame_count;
					FillRectangle(red, frame*moop+1, HEIGHT - 60, 5, 60);
					for(int i = 0; i < punch.frame_count; i++)
					{
						DrawVerticalSegment(black, i * moop, HEIGHT - 60, HEIGHT);

						char foo[3];
						sprintf(foo, "%d", i);
						DrawStringScaled(WrapString(foo), i*moop+6, HEIGHT - 60, 2,white);
					}
					

					if(play)
					{
						float_frame += game.delta_time * 5;
						if(float_frame >= punch.frame_count)
							float_frame = 0;

						frame = (int)float_frame;
					}
					else if(selected_box < punch.frames[frame].hurt_count + punch.frames[frame].hit_count)
					{
						Vec2 position = punch.frames[frame].boxes[selected_box].position;
						position.x -= punch.frames[frame].boxes[selected_box].size.x / 2.0f;
						position.y += punch.frames[frame].boxes[selected_box].size.y / 2.0f;
						position.x *= +PIXELS_PER_UNIT;
						position.y *= -PIXELS_PER_UNIT;
						position.x += WIDTH / 2;
						position.y += HEIGHT / 2;
						DrawRectangle(green, position.x-2, position.y-2, punch.frames[frame].boxes[selected_box].size.x * PIXELS_PER_UNIT + 4, punch.frames[frame].boxes[selected_box].size.y * PIXELS_PER_UNIT + 4);
					}
					
				} break;
				case SaveAnimation:
				{
					#define max_name_length 20
					#define char_sprite_width 9

					static char file_name[max_name_length];
					static int cursor = 0;
					for (int i = Keys_A; i < Keys_Z; i++)
					{
						if(KeyDownFresh(i) && cursor < max_name_length)
						{
							file_name[cursor] = i + 32; //add 32 to make lowercase
							cursor++;
						}
					}

					if(KeyDownFresh(Keys_Backspace))
					{
						if(cursor > 0)
						{
							cursor--;
							file_name[cursor] = 0;
						}
					}

					FillRectangle(0xFF888888, WIDTH/2-2, HEIGHT/2-2, max_name_length * char_sprite_width + 4, 14);
					FillRectangle(0xFFAAAAAA, WIDTH/2, HEIGHT/2, max_name_length * char_sprite_width, 10);
					FillRectangle(0xFF555555, WIDTH/2+cursor*char_sprite_width,HEIGHT/2,2,8);
					DrawString(WrapString(file_name), WIDTH/2, HEIGHT/2);
					
					if(KeyDownFresh(Keys_Enter))
					{
						char path[50] = "Assets/";
						strcat(path,file_name);
						FILE* file_pointer = open_file(path, "w");
						write_bytes(&punch, sizeof(HitboxAnimation), 1, file_pointer);
						close_file(file_pointer);						
						game.current_game_state = AnimationEditor;
					}
				} break;
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
						#define bytes_per_pixel 4
						int total_bytes = pixel_count * bytes_per_pixel;
						#undef bytes_per_pixel
						memcpy(pixels, splash.logo.pixels, total_bytes);

						for (int y = splash.y_min; y < splash.y_max; y++)
						for (int x = splash.x_min; x < splash.x_max; x++)
						{
							int i = y * WIDTH + x;
							if (pixels[i] != black)
								pixels[i] = (uint)((pixels[i] & 0xFF0000) * splash.alpha) & 0xFF0000;
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
					#define title_scale 15
					#define press_space_scale 4

					if(KeyDownFresh(Keys_Space))
						game.current_game_state = MainMenu;
					FillVerticalGradient(cyan,blue);
					int x = WIDTH / 2;

					DrawStringScaled(title, x - (title.length * (sprite_size*title_scale) / 2), HEIGHT / 2 - sprite_size*title_scale/2, title_scale,white);

					static float t = -Pi/2.0f;
					static bool switched;
					float alpha = (float)(sin(t) + 1)/2.0f;

					uint space_color = ((uint)(alpha *0xAF) << 24) | 0xFFFFFF;
					DrawStringScaled(press_space, x - (press_space.length * sprite_size*press_space_scale / 2), HEIGHT-sprite_size*press_space_scale*2,press_space_scale,space_color);

					t+= game.delta_time;
				} break;
				case MainMenu:
				{
					static int cursor = 0;

					if(KeyDownFresh(Keys_Down) | KeyDownFresh(Keys_S))
					{
						cursor++;
						if(cursor == 3)
							cursor = 0;
					}

					if(KeyDownFresh(Keys_Up) | KeyDownFresh(Keys_W))
					{
						cursor--;
						if(cursor == -1)
							cursor = 2;
					}

					if(KeyDownFresh(Keys_Enter))
					{
						switch(cursor)
						{
							case 0:
								break;
							case 1:
								game.current_game_state = CharacterSelect;
								break;							
							case 2:
								break;							
						}
					}

					Fill(blue);
					FillRectangle(red, 0, 0, 400, 50);
					DrawStringScaled(WrapString("1P Mode"), 9, 9, 4, white);

					FillRectangle(red, 0, 100, 400, 50);
					DrawStringScaled(WrapString("VS Mode"), 9, 109, 4,white);
					
					FillRectangle(red, 0, 200, 400, 50);
					DrawStringScaled(WrapString("Settings"), 9, 209, 4,white);

					DrawRectangle(yellow, 0, cursor * 100, 400, 50);										
				} break;
				case Level1:
				{
					static int position_x = 0;
					static int position_y = 0;
					int player_width = 60;

					static float delay =0;
					if(KeyDown(Keys_Right) || KeyDown(Keys_Left))
					{
						delay+=game.delta_time;
						if(delay > .35f)
						{
							if(KeyDown(Keys_Left))
								position_x--;
							if(KeyDown(Keys_Right))
								position_x++;														
							delay = 0;
						}
					}
					else if(KeyDown(Keys_Up) || KeyDown(Keys_Down))
					{
						delay+=game.delta_time;
						if(delay > .35f)
						{
							if(KeyDown(Keys_Down))
								position_y++;
							if(KeyDown(Keys_Up))
								position_y--;															
							delay = 0;
						}
					}

					Fill(black);
					FillRectangle(green, position_x*player_width, position_y*player_width, player_width, player_width);
				} break;
				case CharacterSelect:
				{
					Fill(blue);
					DrawStringScaled(WrapString("Character Select"), 0, 0, 4,white);
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
								Vec3 v_a = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone1], skeleton_matrices[skinned_demo.weight_indices[i].bone1]), skinned_demo.mesh.vertices[i]);
								Vec3 v_b = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone2], skeleton_matrices[skinned_demo.weight_indices[i].bone2]), skinned_demo.mesh.vertices[i]);
								Vec3 v_c = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone3], skeleton_matrices[skinned_demo.weight_indices[i].bone3]), skinned_demo.mesh.vertices[i]);
								Vec3 v_d = Transform_v3(Concatenate(skinned_demo.bind_matrices[skinned_demo.weight_indices[i].bone4], skeleton_matrices[skinned_demo.weight_indices[i].bone4]), skinned_demo.mesh.vertices[i]);

								v_a = v3_Scale(v_a, skinned_demo.weights[i].x);
								v_b = v3_Scale(v_b, skinned_demo.weights[i].y);
								v_c = v3_Scale(v_c, skinned_demo.weights[i].z);
								v_d = v3_Scale(v_d, skinned_demo.weights[i].w);

								Vec3 i_a = v3_Add(v_a, v_b);
								Vec3 i_b = v3_Add(v_c, v_d);

								skinned_demo.transformed_vertices[i] = v3_Add(i_a, i_b);
							}
						}

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
						if (KeyDownFresh(Keys_R))
							ResetGame();

						for (int i = 0; i < PLAYER_COUNT; ++i)
						{
							Vec3* position = &gameplay_state.transforms[gameplay_state.players[i].entity_ID].position;
							if(ButtonDown(i, LEFT))
								position->x -= game.delta_time;
							if(ButtonDown(i, RIGHT))
								position->x += game.delta_time;
						}

						if (!gameplay_state.game_over)
						{
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

								if(gameplay_state.game_over)
									game.time_scale = 0;
							}
						}
					}

					//Render
					{
						Fill(black);


						for(int i = 0; i < PLAYER_COUNT;i++)
						{
							Vec3 position = gameplay_state.transforms[gameplay_state.players[i].entity_ID].position;
							position.x -= .5f;
							position.y -= .5f;
							position.x *= PIXELS_PER_UNIT;
							position.y *= -PIXELS_PER_UNIT;
							position.x += WIDTH / 2;
							position.y += HEIGHT / 2;
							FillRectangle(gameplay_state.player_colors[i], position.x, position.y, PIXELS_PER_UNIT, PIXELS_PER_UNIT);
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
									float portion = gameplay_state.players[player].current_health / gameplay_state.max_health;
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
									for (int stock = 0; stock < gameplay_state.players[player].stock; stock++)
									{
										FillCircle(gameplay_state.player_colors[player], available_space * player + indent_x + 10 + (stock * (20 + 5)), 40, 10);
										Draw_Circle(black, available_space * player + indent_x + 10 + (stock * (25)), 40, 10, 3.0f);
									}
								}
							}

							//Draw Timer
							{
								int char_sprite_size = 8;
								char result[40];

								sprintf(result, "%.0f", gameplay_state.time_remaining);
								string message = WrapString(result);
								DrawStringScaled(message, WIDTH / 2 - char_sprite_size * (message.length - 1) * 2, char_sprite_size, 2,white);
							}

							if (gameplay_state.game_over)
							{
								//Draw Game End Message
								{
									int offset_x = WIDTH / 2, offset_y = HEIGHT / 2;

									char result[40];
									if (gameplay_state.winner == 0)
										sprintf(result, "TIE!");
									else
										sprintf(result, "PLAYER %d WINS!", gameplay_state.winner);
									string message = WrapString(result);
									DrawString(message, offset_x, offset_y);
								}
							}
						}
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
								Vec3 a = v3_Subtract(t.b, t.a);
								Vec3 b = v3_Subtract(t.c, t.a);
								Vec3 normal = v3_Normalized(CrossProduct(a, b));

								Vec3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, mesh_demo_camera.position));

								if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
								{
									SwapTriangles(triangles, i, remaining_count - 1);
									remaining_count--;
									goto label;//TODO replace with while
								}
								else
								{
									Vec3 backward = { 0,0,-1 };
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
					Fill(0xFF000000);
					for (int i = 0; i < 1000; i++)
					{
						float x = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						float y = (float)rand() / ((float)RAND_MAX) * 1000.0f;
						FillRectangle(red, x, y, 10, 10);																	
					}
				} break;
				case TextureMappedTriangle:
				{
					Bitmap texture;
					texture.width = 200;
					texture.height = 200;
					uint checker_pixels[200*200];
					texture.pixels = checker_pixels; 
					uint checker_color = red;
					static int offset_x = 600;
					static int offset_y = 300;
					if(KeyDown(Keys_Left))
						offset_x--;
					if(KeyDown(Keys_Right))
						offset_x++;
					if(KeyDown(Keys_Down))
						offset_y++;	
					if(KeyDown(Keys_Up))
						offset_y--;						
					for (int x = 0; x < texture.width; ++x)
					{				
						for (int y = 0; y < texture.height; ++y)
						{
							texture.pixels[texture.width*y+x] = splash.logo.pixels[splash.logo.width*(y+offset_y)+(x+offset_x)];
						}
					}

					Fill(black);

					for (int x = 0; x < texture.width; ++x)
					{
						for (int y = 0; y < texture.height; ++y)
						{
							pixels[y*WIDTH+x] = texture.pixels[y*texture.width+x];
						}
					}

					static float my_x = 0;
					Vec2 center = {WIDTH/2, HEIGHT/2};
					float radius = 100;
					Vec3 av = {-1,-1,0};

					av = Transform_v3(Rotation(0,0,my_x), av);
					Vec2 a = {center.x + (av.x*50), center.y + (av.y*50)};

					Vec3 bv = {1,-1,0};
					bv = Transform_v3(Rotation(0,0,my_x), bv);
					Vec2 b = {center.x + (bv.x*50), center.y + (bv.y*50)};


					Vec3 cv = {-1,1,0};
					cv = Transform_v3(Rotation(0,0,my_x), cv);
					Vec2 c = {center.x + (cv.x*50), center.y + (cv.y*50)};

					Vec3 dv = {1,1,0};
					dv = Transform_v3(Rotation(0,0,my_x), dv);
					Vec2 d = {center.x + (dv.x*50), center.y + (dv.y*50)};

					Vec2 a_uv = {0,0};
					Vec2 b_uv = {1,0};
					Vec2 c_uv = {0,1};
					Vec2 d_uv = {1,1};
						
					FillTriangle_Texture(a, b, c, a_uv, b_uv, c_uv, texture);
					FillTriangle_Texture(c, b, d, c_uv, b_uv, d_uv, texture);

					my_x += game.delta_time;
				} break;
				case TextureMappedCube:
				{
					Bitmap texture;
					texture.width = 200;
					texture.height = 200;
					uint checker_pixels[200*200];
					texture.pixels = checker_pixels; 
					uint checker_color = red;
					static int offset_x = 600;
					static int offset_y = 300;
					if(KeyDown(Keys_Left))
						offset_x--;
					if(KeyDown(Keys_Right))
						offset_x++;
					if(KeyDown(Keys_Down))
						offset_y++;	
					if(KeyDown(Keys_Up))
						offset_y--;						
					for (int x = 0; x < texture.width; ++x)
					{				
						for (int y = 0; y < texture.height; ++y)
						{
							texture.pixels[texture.width*y+x] = splash.logo.pixels[splash.logo.width*(y+offset_y)+(x+offset_x)];
						}
					}

					FillVerticalGradient(black,white);

					for (int x = 0; x < texture.width; ++x)
					{
						for (int y = 0; y < texture.height; ++y)
						{
							pixels[y*WIDTH+x] = texture.pixels[y*texture.width+x];
						}
					}

					static float rot_y = 0;
					static Transform my_transform;
					Vec3 foo = v3_one;
					my_transform.scale = foo;
					Vec3 foo2 = v3_zero;
					my_transform.position = foo2;
					my_transform.rotation.x = rot_y;
					my_transform.rotation.y = rot_y;
					my_transform.rotation.z = rot_y;
					Transform camera;
					Vec3 foo3 = v3_one;
					camera.scale = foo3;
					Vec3 backward_30 = { 0, (float)(sin(rot_y) * 3), -30 };
					camera.position = backward_30;
					camera.rotation = foo2;

					RenderTexturedMesh(cube_mesh, my_transform, camera, texture);
					rot_y += game.delta_time;
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
					char schoop[100];
					sprintf(moop,"FPS: %.2f", game.frames_per_second);
					sprintf(boop,"delta_time: %.9f", game.delta_time);
					sprintf(schoop,"time_scale: %.2f", game.time_scale);

					string fps_string = WrapString(moop);
					string delta_string = WrapString(boop);
					string time_Scale_string = WrapString(schoop);
					DrawString(fps_string, 16, 16);
					DrawString(delta_string, 16, 28);
					DrawString(time_Scale_string, 16, 40);
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

#define main main
//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
//Game Controller 1 handler
SDL_Joystick* gGameController = NULL;


int main(int argc, char* argv[]) {
    SDL_Window *window;                    // Declare a pointer

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0)
        return;

    //Check for joysticks
    if( SDL_NumJoysticks() < 1 )
    {
        printf( "Warning: No joysticks connected!\n" );
    }
    else
    {
        //Load joystick
        gGameController = SDL_JoystickOpen( 0 );
        if( gGameController == NULL )
        {
            printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
        }
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Window Boom",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1920,                               // width, in pixels
        1080,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* surface;

	InitViewport2(1920, 1080);
	InitEverything();
	//SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
    surface = SDL_GetWindowSurface(window);
    pixels = surface->pixels;
    int is_active = true;
    int x, y;

    while (is_active) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            switch(event.type)
        	{
                case SDL_QUIT:
                {
                    is_active = false;
                } break;
                case SDL_JOYAXISMOTION:
                {
                    if( event.jaxis.which == 0 )
                    {
                        if( event.jaxis.axis == 0 )
                        {
                            x = event.jaxis.value;
                        }
                        else if( event.jaxis.axis == 1 )
                        {
                            y = event.jaxis.value;
                        }
                        printf("{ %d, %d }\n",x,y);
                    }
                }
                case SDL_JOYBUTTONDOWN:
                {
                    if(event.jbutton.which==0)
                    {
                        if(event.jbutton.button == 1 && event.jbutton.type == SDL_JOYBUTTONDOWN)
                            printf("yay");
                    }
                } break;
        		default:
        			break;
        	}
        }

        GameLoop();
        SDL_UpdateWindowSurface(window);
    }



    return 0;
}