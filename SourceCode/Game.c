#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <float.h>
#include "../Dependencies/SDL_Headers/SDL.h"
#include "Assets.h"

#define bool char
#define true 1
#define false 0
#define byte unsigned char
#define uint unsigned int
#define m4x4_identity {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}
#define v3_forward { 0, 0, 1 }
#define v3_zero { 0, 0, 0 }
#define v3_one { 1, 1, 1 }

#define Tau 6.28318530717958f
#define Pi 3.14159265358979f

#define open_file fopen
#define seek_position fseek
#define read_bytes fread
#define write_bytes fwrite
#define close_file fclose

#include "Types.h"

//math and stuff
float GetMin3(float a, float b, float c);
float GetMax3(float a, float b, float c);

typedef enum GameStates
{
	CleanRenderTest,
	SaveAnimation,
	AnimationEditor,
	SplashScreenState,
	TitleScreen,
	MainMenu,
	Level1,
	CharacterSelect,
	SkinnedMesh,
	Gameplay,
	ParticleState, 
	TextureMappedTriangle,
	TextureMappedCube,
	PeruseScreenCaptures
} GameStates;

#define state_count 14

typedef struct Timing
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
	int frames_since_last_second;
} Timing;

GameStates current_game_state;
Timing timing;

#include "LinearAlgebra.h"

void Clamp(int* value, int low, int high)
{
	if(*value < low)
		*value = low;
	if(*value > high)
		*value = high;
}

void Clamp_Float(float* value, float low, float high)
{
	if(*value < low)
		*value = low;
	if(*value > high)
		*value = high;
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

typedef struct BoxCollider
{
	Vec2* attachment;
	union
	{
		Vec2 size;
		struct 
		{
			float width, height;
		};
	};
} BoxCollider;

bool Intersect(BoxCollider a, BoxCollider b)
{
	Vec2 a_position = *a.attachment;
	Vec2 b_position = *b.attachment;

	float a_half_width = a.width / 2;
	float a_half_height = a.height / 2;
	float b_half_width = b.width / 2;
	float b_half_height = b.height / 2;

	float a_right = a_position.x + a_half_width;
	float a_left = a_position.x - a_half_width;
	float a_top = a_position.y + a_half_height;
	float a_bottom = a_position.y - a_half_height;
	float b_right = b_position.x + b_half_width;
	float b_left = b_position.x - b_half_width;
	float b_top = b_position.y + b_half_height;
	float b_bottom = b_position.y - b_half_height;

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


m4x4 camera_to_clip;
int WIDTH, HEIGHT, pixel_count;
Color* pixels;
float* z_buffer;
Mesh mesh;
Vec3* guy_normals;
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

Bitmap title_screen_background;


InitViewport(int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	pixel_count = WIDTH*HEIGHT;
}

int frames_captured;
#define frames_to_capture 60
uint screen_captures[frames_to_capture][1920*1080];
void CaptureScreen()
{
	static  bool written = false;
	if(frames_captured < frames_to_capture)
	{
		memcpy(&(screen_captures[frames_captured++]), pixels, WIDTH*HEIGHT*4);
	}
	else if(!written)
	{
		written = true;
		FILE* file_pointer = open_file("Assets/screen_captures_minified", "wb");
		byte* minified = malloc(WIDTH*HEIGHT*3*frames_to_capture);

		byte* old = (byte*)screen_captures;

		for (int i = 0, o=0; i < WIDTH*HEIGHT*3*frames_to_capture; i++,o++)
		{
			if(o!=0 && (o+1)%4==0)
				o++;			
			minified[i] = old[o];
		}
		write_bytes(minified, WIDTH*HEIGHT*3, frames_to_capture, file_pointer);
		close_file(file_pointer);
		free(minified);
	}
}

#include "Debug.h"
#include "Drawing.h"

float GetMin3(float a, float b, float c)
{
	float r = (a < b) ? a : b;
	return (r < c) ? r : c;
}

float GetMax3(float a, float b, float c)
{
	float r = (a > b) ? a : b;
	return (r > c) ? r : c;
}

#include "Input.h"

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

void InitEverything()
{
	InitShaders();
	timing.TIME_RECALCULATION_INTERVAL = 1.0f;

	timing.TARGET_FRAMERATE = 60.0f;
	timing.STANDARD_TIMESTEP = 1 / timing.TARGET_FRAMERATE;
	timing.time_scale = 1.0f;
	timing.fixed_framerate = false;
	current_game_state = CleanRenderTest;
	view_debug = false;
	float field_of_view = Tau / 6.0f;
	camera_to_clip = Perspective(.1f, 100, field_of_view, WIDTH, HEIGHT);

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
		FILE* file_pointer = open_file("Assets/title_screen", "r");
		int width = 1920, height = 1080;
		uint* pixels = malloc(sizeof(uint) * width * height);
		read_bytes(pixels, 4, width * height, file_pointer);
		title_screen_background.pixels = pixels;
		title_screen_background.width = width;
		title_screen_background.height = height;

		close_file(file_pointer);		
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
			read_bytes(font_set, 8, char_dict_length, file_pointer);
			close_file(file_pointer);
		}

		mesh = LoadMesh("Assets/guy.obj");
		FILE* file_pointer = open_file("Assets/guy_normals", "rb");
		guy_normals = malloc(mesh.vertices_length*sizeof(Vec3));
		read_bytes(guy_normals, sizeof(Vec3), mesh.vertices_length, file_pointer);
		mesh.normals = guy_normals;
		mesh.normals_length = mesh.vertices_length;
		Vec3 forward_10 = { 0, 0, 10 };
		Vec3 backward_50 = { 0, 0, -50 };
		cube_transform.position = forward_10;
		cube_transform.rotation = (Vec3)v3_zero;
		cube_transform.scale = (Vec3)v3_one;
		mesh_demo_camera.position = backward_50;
		mesh_demo_camera.rotation = (Vec3)v3_zero;
		mesh_demo_camera.scale = (Vec3)v3_one;
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
		splash.x_min = 550;
		splash.y_min = 125;
		splash.x_max = WIDTH - splash.x_min;
		splash.y_max = HEIGHT - splash.y_min;

		//Load SplashScreen Image
		{
			FILE* file_pointer = open_file("Assets/viking_studios_logo2", "r");
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

void GameLoop()
{
	if (!timing.fixed_framerate || (timing.time_since_last_frame >= timing.STANDARD_TIMESTEP))
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
					view_debug = !view_debug;
				if (KeyDownFresh(Keys_F))
					timing.fixed_framerate = !timing.fixed_framerate;
				if(KeyDownFresh(Keys_Add))
					timing.time_scale++;
				if(KeyDownFresh(Keys_Subtract))
					timing.time_scale--;
			}

			//Cycle Through GameStates
			{
				if (KeyDownFresh(Keys_Tab))
				{
					current_game_state = (current_game_state + 1) % state_count;
				}

				else if (KeyDownFresh(Keys_Z))
				{
					current_game_state--;

					if ((int)current_game_state < 0)
						current_game_state += state_count;
				}
			}

			timing.frames_since_last_second++;

			switch (current_game_state)
			{
				case CleanRenderTest:
				{
					static Transform camera = {-1,{0,0,0},{0,0,0},{1,1,1}};
					static Transform object_transform = {-1,{0,0,10},{0,0,0},{1,1,1}};
									
					//Camera Input
					{
						float camera_speed = 10.0f;
						float rotation_speed = 3.0f;
						Vec3 move_vector = v3_zero;
						if(KeyDown(Keys_W))
							move_vector.z += camera_speed;
						if(KeyDown(Keys_S))
							move_vector.z -= camera_speed;
						if(KeyDown(Keys_A))
							move_vector.x -= camera_speed;
						if(KeyDown(Keys_D))
							move_vector.x += camera_speed;

						if(KeyDown(Keys_Q))
							camera.rotation.y -= timing.delta_time * rotation_speed;
						if(KeyDown(Keys_E))
							camera.rotation.y += timing.delta_time * rotation_speed;							

						move_vector = Transform_v3(Rotation(camera.rotation.x,camera.rotation.y, camera.rotation.z),move_vector);
						move_vector = v3_Scale(move_vector, timing.delta_time);
						camera.position = v3_Add(camera.position, move_vector);						
					}

					if(KeyDown(Keys_Space))
						object_transform.rotation.y += timing.delta_time *4;

					//light_rotation += timing.delta_time / 3;
					
					Clear();
					ClearZBuffer();

					Color skin = 0xFFBB88;
					Color colors[3] = {red,green,blue};
					RenderMesh(mesh, object_transform, camera, ShadeSolidColor, &skin);
					for (int i = 0; i < 6000; ++i)
					{
						//RenderTriangle((Vec3){10,10,0},(Vec3){10,30,0},(Vec3){30,30,0}, 0, ShadeWhite, NULL);
					}

				} break;
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
								current_game_state = SaveAnimation;
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
								(*modifier).x -= timing.delta_time;
							if(KeyDown(Keys_D))
								(*modifier).x += timing.delta_time;
							if(KeyDown(Keys_W))
								(*modifier).y += timing.delta_time;
							if(KeyDown(Keys_S))
								(*modifier).y -= timing.delta_time;

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
						float_frame += timing.delta_time * 5;
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
						current_game_state = AnimationEditor;
					}
				} break;
				case SplashScreenState:
				{
					if (!splash.started)
					{
						Clear();
			            SDL_AudioSpec wav_spec;
			            SDL_AudioSpec obtained_spec;
			            Uint32 wav_length;
			            Uint8 *wav_buffer;

			            SDL_LoadWAV("Assets/preparations.wav", &wav_spec, &wav_buffer, &wav_length);

			            SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, &obtained_spec, 0);            
			            SDL_QueueAudio(device_id, wav_buffer, wav_length);
			            SDL_PauseAudioDevice(device_id, 0);
						splash.started = true;
					}

					//DrawSplashScreen
					{
						static float elapsed_time = 1;

						#define bytes_per_pixel 4
						int total_bytes = pixel_count * bytes_per_pixel;
						#undef bytes_per_pixel

						if(elapsed_time > timing.STANDARD_TIMESTEP)
						{
							elapsed_time = 0;
							
							if(splash.alpha > 0)
							{
								memcpy(pixels, splash.logo.pixels, total_bytes);

								for (int y = splash.y_min; y < splash.y_max; y++)
								for (int x = splash.x_min; x < splash.x_max; x++)
								{
									int i = y * WIDTH + x;
									if (pixels[i] != black)
									{
										uint r = (pixels[i] & 0xFF0000) >> 16;
										uint g = (pixels[i] & 0xFF00) >> 8;
										uint b = pixels[i] & 0xFF;

										r = (uint)(r*splash.alpha);
										r <<= 16;
										g = (uint)(g*splash.alpha);
										g <<= 8;
										b = (uint)(b*splash.alpha);
										pixels[i] = r | g | b;
									}
								}
							}
							else
								Clear();
						}

						elapsed_time += timing.delta_time;
					}

					splash.time += timing.delta_time;
					if (splash.time > 2 && splash.time < 7 && splash.alpha < 1)
					{
						splash.alpha += timing.delta_time / 5;
						if (splash.alpha > 1)
							splash.alpha = 1;
					}
					else if (splash.time > 8  && splash.alpha > 0)
					{
						splash.alpha -= timing.delta_time;
						if (splash.alpha < 0)
							splash.alpha = 0;
					}
					else if (splash.time > 10.5f)
					{
						if (!splash.ended)
						{
							current_game_state = TitleScreen;
							splash.ended = true;
						}
						else
						{
							splash.time = 0;
							splash.ended = false;
							splash.started = false;
						}
					}					
				} break;
				case TitleScreen:
				{
					if(KeyDownFresh(Keys_Space))
						current_game_state = MainMenu;

					memcpy(pixels,title_screen_background.pixels, pixel_count*sizeof(uint));

					#define sprite_size 9
					#define press_space_scale 4

					static float t = -Pi/2.0f;
					int x = WIDTH / 2;
					float alpha = (float)(sin(t) + 1)/2.0f;
					uint space_color = ((uint)(alpha *0xAF) << 24) | 0xFFFFFF;
					DrawStringScaled(press_space, x - (press_space.length * sprite_size*press_space_scale / 2), HEIGHT-sprite_size*press_space_scale*2,press_space_scale,space_color);

					t += timing.delta_time;
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
								current_game_state = CharacterSelect;
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
					static Transform player;
					static Transform camera;
					static bool init = false;
					static BoxCollider player_collider;
					static BoxCollider block_colliders[block_count];
					static Vec2 pos2;
					pos2.x =-2;
					pos2.y =-2;
					static float gravity = 10;
					static Vec2 velocity;
					static bool grounded;
					static Transform block_transforms[block_count];
					if(!init)
					{
						player = DefaultTransform();
						player.position.x = -2;
						camera = player;
						camera.position.z = -100;
						player.rotation.y = Tau / 4.0f;
						camera.rotation.x = 0.05f*Tau;
						player_collider.width = 1;
						player_collider.height = 1;
						player_collider.attachment = &player.position;

						for (int i = 0; i < block_count; ++i)
						{
							block_transforms[i] = DefaultTransform();
							block_colliders[i].attachment = &block_transforms[i].position;
							block_transforms[i].position.x = i;
							block_colliders[i].size.x = 1;
							block_colliders[i].size.y = 1;
						}

						block_transforms[0].position.x=-2;
						block_transforms[0].position.y=-2;
						init = true;
					}

					//Move Player
                    {
                        float acceleration = 20.0f;
                        float jump_speed = 8;
                        float max_speed = 5;
                        float slide_coefficient = 0.99f;
                        static bool no_horizontal_input_since_landed = true;
                        float ground_fall_velocity = -.01f;


						float dead_zone = .1f;
						if(fabs(game_pads[0].left_stick.x) > dead_zone)
						{
							velocity.x += timing.delta_time * game_pads[0].left_stick.x*acceleration;
							if(grounded)
								no_horizontal_input_since_landed = false;
						}
						else
						{
							if(grounded && !no_horizontal_input_since_landed)
								velocity.x = 0;
						}

                        if (velocity.x > max_speed)
                            velocity.x = max_speed;
                        else if (velocity.x < -max_speed)
                            velocity.x = -max_speed;

                        if (grounded)
                        {
                            velocity.y = ground_fall_velocity;

                            if (no_horizontal_input_since_landed)
                                velocity.x *= slide_coefficient; //TODO make framerate independent

                            if (game_pads[0].buttons[1])
                            {
                                velocity.y = jump_speed;
                            }
                        }
                        else
                        {
                            no_horizontal_input_since_landed = true;
                            velocity.y -= gravity * timing.delta_time;
                        }

                        float old_x = player.position.x;
                        player.position.x += velocity.x * timing.delta_time;

                        for (int i = 0; i < block_count; i++)
                        {
                            BoxCollider b = block_colliders[i];
                            if (Intersect(player_collider, b))
                            {
                                if (old_x < (*b.attachment).x)
                                    player.position.x -= (player.position.x + (player_collider.width / 2)) - ((*b.attachment).x - (b.width / 2));
                                else if (old_x > (*b.attachment).x)
                                    player.position.x += ((*b.attachment).x + (b.width / 2)) - (player.position.x - (player_collider.width / 2));
                            }
                        }

                        float old_y = player.position.y;
                        player.position.y += velocity.y * timing.delta_time;

                        grounded = false;

                        for (int i = 0; i < block_count; i++)
                        {
                            BoxCollider b = block_colliders[i];
                            if (Intersect(player_collider, b))
                            {
                                if (old_y < (*b.attachment).y)
                                {
                                    player.position.y -= (player.position.y + (player_collider.height / 2)) - ((*b.attachment).y - (b.height / 2));
                                    velocity.y = 0;
                                }
                                else if (old_y > (*b.attachment).y)
                                {
                                    player.position.y += ((*b.attachment).y + (b.height / 2)) - (player.position.y - (player_collider.height / 2));
                                    grounded = true;
                                }
                            }
                        }

                        static float target_rot_y = 0;
                        static float target_t = 0;

                        static float old_target;
                        if(velocity.x > 0)
                        {
                        	target_rot_y = Tau / 4.0f;
                        }
                        else if(velocity.x < 0)
                        {
                        	target_rot_y = -Tau / 4.0f;
                        }

                        if(target_rot_y != old_target)
                        	target_t = 0;
                        player.rotation.y = Lerp_Float(-target_rot_y, target_rot_y, target_t);
                        target_t += timing.delta_time*10;

                        if(target_t > 1)
                        	target_t = 1;

                        old_target = target_rot_y;
                    }
					
					camera.position.x = player.position.x;
					camera.position.y = player.position.y + 35;
					
					Color flat = red;
					Clear();
					ClearZBuffer();						
					for (int i = 0; i < block_count; ++i)
					{
						RenderMesh(cube_mesh, block_transforms[i], camera, ShadeSolidColor, &flat);
					}
					RenderMesh(skinned_demo.mesh, player, camera, ShadeSolidColor, &flat);
					static int unit = 32;
					for (int i = 0; i < block_count; ++i)
					{
						Vec2 position= *block_colliders[i].attachment;
						position.x *= unit;
						position.y *= -unit;
						position.x += WIDTH/2;
						position.y += HEIGHT/2;
						FillRectangle(blue,position.x-unit/2,position.y-unit/2,unit,unit);
					}

					{
						Vec2 position= {player.position.x,player.position.y};
						position.x *= unit;
						position.y *= -unit;
						position.x += WIDTH/2;
						position.y += HEIGHT/2;
						FillRectangle(green,position.x-unit/2,position.y-unit/2,unit,unit);
					}
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
						float delta = 5 * timing.delta_time;

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
							skinned_demo.rotation_y += timing.delta_time;
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
							skinned_demo.frame += timing.TARGET_FRAMERATE * timing.delta_time;
							if (skinned_demo.frame >= skinned_demo.animation_length)
								skinned_demo.frame = 0;
						}
					}

					//Render
					{
						Mesh mesh = (Mesh) 
						{ 
							.vertices = skinned_demo.transformed_vertices, 
							.vertices_length = skinned_demo.transformed_vertices_length,
							.indices = skinned_demo.mesh.indices, 
							.indices_length = skinned_demo.mesh.indices_length, 
						};


						Clear();
						ClearZBuffer();

						Color rgb[3] = {red,green,blue};

						if(skinned_demo.fill_toggle)
							RenderMesh(mesh, DefaultTransform(), skinned_demo.camera, ShadeVertexColors, &rgb);
						else
							RenderMesh(mesh, DefaultTransform(), skinned_demo.camera, ShadePolyColors, skinned_demo.body_poly_colors);
					}
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
								position->x -= timing.delta_time;
							if(ButtonDown(i, RIGHT))
								position->x += timing.delta_time;
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

								gameplay_state.time_remaining -= timing.delta_time;

								if(gameplay_state.time_remaining < 0)
									gameplay_state.time_remaining = 0;

								gameplay_state.game_over = gameplay_state.winner != 0 || remaining_players == 0 || gameplay_state.time_remaining == 0;

								if(gameplay_state.game_over)
									timing.time_scale = 0;
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
				case ParticleState:
				{
					typedef struct Particle
					{
						Vec2 position;
						Vec2 velocity;
						Vec2 acceleration;
						float lifetime;

					} Particle;
					Bitmap sprite;
					sprite.width = 10;
					sprite.height = 10;
					uint sprite_pixels[10*10];
					sprite.pixels = sprite_pixels;
					for(int i = 0; i < 100; i++)
					{
						if(i % 3 == 0)
							sprite.pixels[i] = red;
						else if(i % 7 == 0)
							sprite.pixels[i] = yellow;
						else if(i > 50)
							sprite.pixels[i] = red |yellow;

					}
					#define particle_capacity 10000
					static Particle particles[particle_capacity];

					static int count = 0;
					static bool warmed = false;

					static Vec2 emitter_position = {0,0};
					float emitter_radius = 30.0f;
					int emission_rate = 500; //todo change to emit per second, not per frame
					int emit_count = (emission_rate * timing.delta_time);
					if(true)
					{
						warmed = true;
						int foobar = count+emit_count;
						if(foobar>particle_capacity)
							foobar = particle_capacity;
						for(int i = count; i < foobar; i++) //TODO check for off by one error where particle at "count" would get replaced
						{
						 	particles[i].position.x = emitter_position.x + (float)rand() / ((float)RAND_MAX) * emitter_radius;
							particles[i].position.y = emitter_position.y + (float)rand() / ((float)RAND_MAX) * emitter_radius;

						 	particles[i].velocity.x = ((float)rand() / ((float)RAND_MAX)-.5f)*20;
							particles[i].velocity.y = ((float)rand() / ((float)RAND_MAX)-.5f)*20;
							particles[i].acceleration.x = 0;
							particles[i].acceleration.y = -100;
							particles[i].lifetime = 1.25f;
							count++;
						}
					}

					float move_speed = 100;
					if(KeyDown(Keys_Left))
						emitter_position.x-=timing.delta_time * move_speed;
					if(KeyDown(Keys_Right))
						emitter_position.x+=timing.delta_time * move_speed;
					if(KeyDown(Keys_Up))
						emitter_position.y+=timing.delta_time * move_speed;;
					if(KeyDown(Keys_Down))
						emitter_position.y-=timing.delta_time * move_speed;;

					for (int i = 0; i < count; ++i)
					{
						particles[i].position.x += particles[i].velocity.x * timing.delta_time;
						particles[i].position.y += particles[i].velocity.y * timing.delta_time;

						particles[i].velocity.x += particles[i].acceleration.x * timing.delta_time;
						particles[i].velocity.y += particles[i].acceleration.y * timing.delta_time;

						particles[i].lifetime -= timing.delta_time;
						if(particles[i].lifetime <= 0)
						{
							count--;
							Particle temp = particles[i];
							particles[i] = particles[count];
							particles[count] = temp;
						}
					}

					Clear();
					for (int i = 0; i < count; i++)
					{
						DrawSprite(particles[i].position.x, particles[i].position.y, sprite);																	
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

					Clamp(&offset_x, 0, splash.logo.width-texture.width);
					Clamp(&offset_y, 0, splash.logo.height-texture.height);

					for (int x = 0; x < texture.width; ++x)
					{				
						for (int y = 0; y < texture.height; ++y)
						{
							texture.pixels[texture.width*y+x] = splash.logo.pixels[splash.logo.width*(y+offset_y)+(x+offset_x)];
						}
					}

					Fill(white);
					DrawSprite(0,0,texture);

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

					my_x += timing.delta_time;
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

					Clamp(&offset_x, 0, splash.logo.width-texture.width);
					Clamp(&offset_y, 0, splash.logo.height-texture.height);

					for (int x = 0; x < texture.width; ++x)
					{				
						for (int y = 0; y < texture.height; ++y)
						{
							texture.pixels[texture.width*y+x] = splash.logo.pixels[splash.logo.width*(y+offset_y)+(x+offset_x)];
						}
					}

					FillHorizontalGradient(black,white);
					DrawSprite(0,0,texture);

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
					Vec3 backward_50 = { 0, (float)(sin(rot_y) * 3), -50 };
					camera.position = backward_50;
					camera.rotation = foo2;

					RenderTexturedMesh(cube_mesh, my_transform, camera, texture);
					//ClearZBuffer();
					//RenderMesh(cube_mesh,my_transform,camera,ShadeTexturedUnlit, &texture);
					rot_y += timing.delta_time;
				} break;
				case PeruseScreenCaptures:
				{
					static bool loaded = false;
					static float current_image = 0;
					static float last_image = -1;
					if(!loaded)
					{
						FILE* file_pointer = open_file("Assets/screen_captures", "rb");
						read_bytes(screen_captures, 1920*1080*4, frames_to_capture, file_pointer);
						loaded = true;
					}
					if(KeyDown(Keys_A))
						current_image -= timing.TARGET_FRAMERATE * timing.delta_time;
					if(KeyDown(Keys_D))
						current_image += timing.TARGET_FRAMERATE * timing.delta_time;
					if((int)current_image == frames_to_capture)
						current_image = 0;
					if(current_image < 0)
						current_image = frames_to_capture-1;

					if(current_image != last_image)
						memcpy(pixels,screen_captures[(int)current_image],1920*1080*4);

					int scroll_x_start = 50;
					int scroll_x = scroll_x_start + (int)(current_image/frames_to_capture*(WIDTH-100));
					FillRectangle(0xFF555555,scroll_x_start,HEIGHT - 25, WIDTH-100, 10);
					FillCircle(0xFF333333,scroll_x,HEIGHT-20,10);
					last_image = current_image;
				} break;
				default:
				{
					current_game_state = SplashScreenState;
				} break;
			}

			if (view_debug)
			{
				//Display Game Stats
				{
					char moop[100];
					char boop[100];
					char schoop[100];
					sprintf(moop,"FPS: %.2f", timing.frames_per_second);
					sprintf(boop,"delta_time: %.9f", timing.delta_time);
					sprintf(schoop,"time_scale: %.2f", timing.time_scale);

					string fps_string = WrapString(moop);
					string delta_string = WrapString(boop);
					string time_Scale_string = WrapString(schoop);
					DrawString(fps_string, 16, 16);
					DrawString(delta_string, 16, 28);
					DrawString(time_Scale_string, 16, 40);
				}
			}

			timing.time_since_last_frame = 0;
		}
	}

	//Update Timing
	{
		float elapsed = (float)(clock() - timing.previous_time) / CLOCKS_PER_SEC;
		timing.time_since_last_frame += elapsed;
		timing.time_since_timing_recalculated += elapsed;

		if(timing.fixed_framerate)
			timing.delta_time = timing.STANDARD_TIMESTEP;
		else
			timing.delta_time = timing.time_since_last_frame * timing.time_scale;

		if (timing.time_since_timing_recalculated >= timing.TIME_RECALCULATION_INTERVAL)
		{
			timing.frames_per_second = timing.frames_since_last_second / timing.time_since_timing_recalculated;
			timing.time_since_timing_recalculated = timing.frames_since_last_second = 0;
		}

		timing.previous_time = clock();
	}
}

#define main main

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
//Game Controller 1 handler
SDL_Joystick* gGameController = NULL;



int main()
{
    SDL_Window *window;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO) < 0)
        return;

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

    window = SDL_CreateWindow("Window Go Boom", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* surface;

	InitViewport(1920, 1080);//TODO make the game more resolution agnostic
	InitEverything();
	//SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
    surface = SDL_GetWindowSurface(window);
    pixels = surface->pixels;
    z_buffer = malloc(4*pixel_count);
    int is_active = true;

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

                    if( event.jaxis.axis == 0 )
                    {
                    	game_pads[event.jaxis.which].left_stick.x = (float)(event.jaxis.value / 32767.0f);
                    }
                    else if( event.jaxis.axis == 1 )
                    {
                        game_pads[event.jaxis.which].left_stick.y = (float)(event.jaxis.value / 32767.0f);
                    }
                }
                case SDL_JOYBUTTONDOWN:
                {
	                if(event.jbutton.type == SDL_JOYBUTTONDOWN)
	                	game_pads[event.jbutton.which].buttons[event.jbutton.button] = true;
                } break;
                case SDL_JOYBUTTONUP:
                {
	                if(event.jbutton.type == SDL_JOYBUTTONUP)
	                	game_pads[event.jbutton.which].buttons[event.jbutton.button] = false;
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