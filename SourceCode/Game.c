#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <float.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Assets.h"
#include "IO.h"

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
	CurveEditor,
	SplashScreenState,
	TitleScreen,
	MainMenu,
	Level1,
	CharacterSelect,
	SkinnedMesh,
	Gameplay,
	ParticleState, 
	PeruseScreenCaptures,
	MorphTargetsDemo,
	Credits
} GameStates;

#define state_count 15

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



float Sample(KeyFrame a, KeyFrame b, float frame)
{
    float t = .5f;
    float step = .25f;
	v2 c1 = { a.frame, a.value };
	v2 c2 = { a.frame + a.right_handle_x, a.value + a.right_handle_y };
	v2 c3 = { b.frame + b.left_handle_x, b.value + b.left_handle_y };
	v2 c4 = { b.frame, b.value };

    while (true)
    {
        v2 d = Lerp_v2(c1, c2, t);
        v2 e = Lerp_v2(c2, c3, t);
        v2 f = Lerp_v2(c3, c4, t);
        v2 g = Lerp_v2(d, e, t);
        v2 h = Lerp_v2(e, f, t);
        v2 i = Lerp_v2(g, h, t);

        if (i.x > frame)
            t -= step;
        else
            t += step;

        step /= 2;

        if (fabs(i.x - frame) < .001f)
            return i.y;
    }
}

v2 Sample2_v2(v2 c1, v2 c2, v2 c3, v2 c4, float x)
{
	float t = (x - c1.x) / (c4.x - c1.x);

	v2 d = Lerp_v2(c1, c2, t);
	v2 e = Lerp_v2(c2, c3, t);
	v2 f = Lerp_v2(c3, c4, t);

	v2 g = Lerp_v2(d, e, t);
	v2 h = Lerp_v2(e, f, t);
	
	v2 i = Lerp_v2(g, h, t);

	return i;
}

void AnimateProperty(AnimationCurve curve, float frame, float* property)
{
	for (size_t o = 0; o < curve.keyframes_count; o++)
	{
		KeyFrame keyframe = curve.keyframes[o];
	}

	int n = curve.keyframes_count;
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
	v2* attachment;
	v2 offset;
	float width, height;
} BoxCollider;

bool Intersect(BoxCollider a, BoxCollider b)
{
	v2 a_position = *a.attachment;
	v2 b_position = *b.attachment;

	a_position.x += a.offset.x;
	a_position.y += a.offset.y;
	b_position.x += b.offset.x;
	b_position.y += b.offset.y;

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

v3 GetCentroid(Triangle t)
{
	v3 v = v3_Add(v3_Add(t.a.position, t.b.position), t.c.position);
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
	byte rows[8];
} CharSprite;

char char_dict[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ', '.', ':', ',', '_', '[', ']', '-', };
#define char_dict_count 44 //TODO don't rely on this magic number long term, at least until you've verified it will stay the same
CharSprite font_set[char_dict_count];

string WrapString(char* message)
{
	return (string){.characters = message, .length = strlen(message)};
}

m4x4 camera_to_clip;
int WIDTH, HEIGHT, pixel_count;
Color* pixels;
float* z_buffer;
Mesh conan_mesh;
Mesh guy_mesh;
Mesh cube_mesh;
Mesh cube2_mesh;
Mesh teapot_mesh;
Mesh face_mesh;
Mesh bigfist_mcpunchydude_mesh;
Mesh ship_mesh;



#define bytes_per_mega_byte (1024*1024)
byte mesh_arena[1*bytes_per_mega_byte];

//TODO calculate as result of mesh baking, automatically create include file
#define cube_arena_index (0)
#define teapot_arena_index (456)
#define guy_arena_index (163792)
#define face_arena_index (187752)
#define conan_arena_index (209416)


int window_is_active = true;
#include "Debug.h"
#include "Drawing.h"
#include "Input.h"
#include "GUI.h"
int arena_write_index = 0;
int FillMeshArena(Mesh old_mesh) //TODO put all mesh data in mesh arena, write to file, read from file, create converter that handles all new Meshes coming in
{
	IndexedMesh mesh;
	mesh.vertices_count = old_mesh.vertices_count;
	mesh.vertices_offset = 0;
	mesh.indices_count = old_mesh.indices_count;
	mesh.indices_offset = mesh.vertices_count * sizeof(v3);

	mesh.normals_count = old_mesh.normals_count;
	mesh.normals_offset = mesh.indices_offset + mesh.indices_count * sizeof(int);

	mesh.uvs_count = old_mesh.uvs_count;
	mesh.uvs_offset = mesh.normals_offset + mesh.normals_count * sizeof(v3);


	mesh.uv_indices_count = old_mesh.uv_indices_count;
	mesh.uv_indices_offset = mesh.uvs_offset + mesh.uvs_count * sizeof(v2);

	IndexedMesh* mesh_data = (IndexedMesh*) &(mesh_arena[arena_write_index]);
	mesh_data[0] = mesh;

	v3* verts = (v3*)mesh_data[0].data;

	for (int i = 0; i < mesh.vertices_count; ++i)
		verts[i] = old_mesh.vertices[i];

	int* indices = (int*)(&(mesh_data[0].data[mesh.indices_offset]));

	for (int i = 0; i < mesh.indices_count; ++i)
		indices[i] = old_mesh.indices[i];


	v3* normals = (v3*)(&(mesh_data[0].data[mesh.normals_offset]));

	for (int i = 0; i < mesh.normals_count; ++i)
		normals[i] = old_mesh.normals[i];


	v2* uvs = (v2*)(&(mesh_data[0].data[mesh.uvs_offset]));

	for (int i = 0; i < mesh.uvs_count; ++i)
		uvs[i] = old_mesh.uvs[i];

	int* uv_indices = (int*)(&(mesh_data[0].data[mesh.uv_indices_offset]));

	for (int i = 0; i < mesh.uv_indices_count; ++i)
		uv_indices[i] = old_mesh.uv_indices[i];

	int address = arena_write_index;
	#define mesh_header_size 40
	arena_write_index += mesh_header_size + mesh.uv_indices_offset + mesh.uv_indices_count * sizeof(int);
	printf("Arena index : %d\n", arena_write_index);
	return address;
	
}

Mesh GetMeshFromArena(int mesh_address)
{
	IndexedMesh* mesh = (IndexedMesh*)(&mesh_arena[mesh_address]);

	Mesh result = (Mesh)
	{
		.vertices_count = (*mesh).vertices_count,
		.vertices = (v3*) &((*mesh).data[(*mesh).vertices_offset]),
		.indices_count = (*mesh).indices_count,
		.indices = (int*) &((*mesh).data[(*mesh).indices_offset]),
		.uvs_count = (*mesh).uvs_count,
		.uvs = (v2*) &((*mesh).data[(*mesh).uvs_offset]),
		.uv_indices_count = (*mesh).uv_indices_count,
		.uv_indices = (int*) &((*mesh).data[(*mesh).uv_indices_offset]),
		.normals_count = (*mesh).normals_count,
		.normals = (v3*) &((*mesh).data[(*mesh).normals_offset]),
	};

	return result;
}


enum FighterList
{
	BigfistMcPunchydude,
	Jeffrey,
	DrMeroink,
	Maestro
};

Bitmap guy_texture;
Bitmap conan_texture;
Bitmap conan_normals;
Bitmap face_texture;
Bitmap block_texture;
Bitmap cube2normals_texture;
Bitmap bigfist_mcpunchydude_texture;
Bitmap bigfist_mcpunchydude_icon;
Bitmap jeffrey_icon;
Bitmap dr_meroink_icon;
Bitmap maestro_icon;
Bitmap character_icons[4];

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

int frames_captured = 0;
#define frames_to_capture 300
#define region_x 640
#define region_y 240
#define region_width 640
#define region_height 480

uint screen_captures[frames_to_capture][region_width*region_height];
void CaptureScreen()
{
	static  bool written = false;
	if(frames_captured < frames_to_capture)
	{
		for (int x = 0; x < region_width; ++x)
		{
			for (int y = 0; y < region_height; ++y){	
				screen_captures[frames_captured][y*region_width+x] = pixels[(y+region_y)*WIDTH+(x+region_x)];
			}
		}
		frames_captured++;
	}
	else if(!written)
	{
		written = true;
		FILE* file_pointer = open_file("Assets/screen_captures", "wb");
		write_bytes(screen_captures, region_width*region_height*4, frames_to_capture, file_pointer);
		close_file(file_pointer);
		file_pointer = open_file("Assets/screen_captures_minified", "wb");
		byte* minified = malloc(region_width*region_height*3*frames_to_capture);

		byte* old = (byte*)screen_captures;

		for (int i = 0, o=0; i < region_width*region_height*3*frames_to_capture; i++,o++)
		{
			if(o!=0 && (o+1)%4==0)
				o++;			
			minified[i] = old[o];
		}
		write_bytes(minified, region_width*region_height*3, frames_to_capture, file_pointer);
		close_file(file_pointer);
		free(minified);
		frames_captured = 0;
		printf("wrote screen capture files");
	}
}





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



typedef struct
{
	int bone1, bone2, bone3, bone4;
} Weight_Index;

typedef struct
{
	Mesh mesh;
	int body_poly_colors_count;
	uint* body_poly_colors;
	Skeleton skeleton;
	int bind_matrices_count;
	m4x4* bind_matrices;
	int weights_count;
	Vec4* weights;
	int weight_indices_count;
	Weight_Index* weight_indices;
	int transformed_vertices_count;
	v3* transformed_vertices;
	Transform camera;

	bool fill_toggle;

	float frame;
	float animation_length;
	float rotation_y;
	bool animation_play;
	bool rotation_play;
	bool view_fps;
	bool has_a_face;
	bool animate_face;
	#define morph_count 2
	v3* morphs[morph_count];
	float morph_weights[morph_count];
	float facial_time;

} SkinnedMeshDemo;

SkinnedMeshDemo skinned_demo;

void SetWeights()
{
	skinned_demo.weights = malloc(skinned_demo.mesh.vertices_count * sizeof(Vec4));
	skinned_demo.weights_count = skinned_demo.mesh.vertices_count;

	for (int i = 0; i < skinned_demo.mesh.vertices_count; i++)
	{
		Vec4 weight = { 1, 0, 0, 0 };
		skinned_demo.weights[i] = weight;
	}

	FILE* file_pointer = open_file("Assets/weight_indices", "r");
	seek_position(file_pointer, 0L, SEEK_END);

	int file_size = ftell(file_pointer);
	skinned_demo.weight_indices_count = file_size / sizeof(Weight_Index);
	skinned_demo.weight_indices = malloc(file_size);

	rewind(file_pointer);
	read_bytes(skinned_demo.weight_indices, sizeof(Weight_Index), skinned_demo.weight_indices_count, file_pointer);
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
	Animation idle_animation;
	Animation walk_animation;
	Animation jump_animation;
	Animation punch_animation;
	Animation kick_animation;
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
	skel.joint_count = joint_count;
	skel.joints = hierarchy;
	return skel;
}



enum Channels
{
	POSX, POSY, POSZ, ROTX, ROTY, ROTZ, SCALEX, SCALEY, SCALEZ
};



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

HitboxAnimation selected_hitbox_animation;

void HeaderSerializeCubeMesh()
{
	byte* p = &mesh_arena[guy_arena_index];
	printf("byte guy_mesh[] = { ");
	int x = 0;
	int wide = 30;
	for (int i = guy_arena_index; i < face_arena_index; ++i)
	{
		printf("0x%02x",p[i]);
		if(i == face_arena_index-1)
			printf(" };");
		else
			printf(", ");
		x++;
		if(x == wide)
		{
			x = 0;
			printf("\n");
		}
	}

	printf("\n");
}


void InitEverything()
{
	timing.TIME_RECALCULATION_INTERVAL = .5f;

	timing.TARGET_FRAMERATE = 30.0f;
	timing.STANDARD_TIMESTEP = 1 / timing.TARGET_FRAMERATE;
	timing.time_scale = 1.0f;
	timing.fixed_framerate = false;
	current_game_state = CharacterSelect;
	view_debug = false;
	float field_of_view = Tau / 6.0f;
	camera_to_clip = Perspective(.1f, 100, field_of_view, WIDTH, HEIGHT);

	//Init HitboxAnimations
	{
		FILE* file_pointer = open_file("Assets/kick.hit", "r");
		read_bytes(&selected_hitbox_animation,sizeof(HitboxAnimation),1,file_pointer);
		close_file(file_pointer);
	}

	//Init Animations
	{
		//TODO set up animation memory arena, inline animations, save all animations to binary format, delete all this
		
		//Walk Animation
		{
			defined_animations.walk_animation.looped = true;
			defined_animations.walk_animation.animation_length = 32;
			defined_animations.walk_animation.curves_count = 12;//12
			defined_animations.walk_animation.curves = malloc(sizeof(AnimationCurve) * defined_animations.walk_animation.curves_count);

			defined_animations.walk_animation.curves[0].transform_index = 1; //core
			defined_animations.walk_animation.curves[0].channel_offset = POSY;
			defined_animations.walk_animation.curves[0].keyframes_count = 5;
			defined_animations.walk_animation.curves[0].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[0].keyframes[0] = ((KeyFrame) { 1, 2, 0, 0 });
			defined_animations.walk_animation.curves[0].keyframes[1] = ((KeyFrame) { 8, 1.75f, 0, 0 });
			defined_animations.walk_animation.curves[0].keyframes[2] = ((KeyFrame) { 16, 2, 0, 0 });
			defined_animations.walk_animation.curves[0].keyframes[3] = ((KeyFrame) { 24, 1.75f, 0, 0 });
			defined_animations.walk_animation.curves[0].keyframes[4] = ((KeyFrame) { 32, 2, 0, 0 });

			defined_animations.walk_animation.curves[1].transform_index = 2; //chest
			defined_animations.walk_animation.curves[1].channel_offset = ROTY;
			defined_animations.walk_animation.curves[1].keyframes_count = 5;
			defined_animations.walk_animation.curves[1].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[1].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.walk_animation.curves[1].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
			defined_animations.walk_animation.curves[1].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
			defined_animations.walk_animation.curves[1].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[1].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

			defined_animations.walk_animation.curves[2].transform_index = 4; //left shoulder
			defined_animations.walk_animation.curves[2].channel_offset = 5;
			defined_animations.walk_animation.curves[2].keyframes_count = 2;
			defined_animations.walk_animation.curves[2].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[2].keyframes[0] = ((KeyFrame) { 1, Tau / 6.0f, 0, 0 });
			defined_animations.walk_animation.curves[2].keyframes[1] = ((KeyFrame) { 32, Tau / 6.0f, 0, 0 });

			defined_animations.walk_animation.curves[3].transform_index = 4; //left shoulder
			defined_animations.walk_animation.curves[3].channel_offset = 4;
			defined_animations.walk_animation.curves[3].keyframes_count = 5;
			defined_animations.walk_animation.curves[3].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[3].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.walk_animation.curves[3].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
			defined_animations.walk_animation.curves[3].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
			defined_animations.walk_animation.curves[3].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[3].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

			defined_animations.walk_animation.curves[4].transform_index = 5; //left elbow
			defined_animations.walk_animation.curves[4].channel_offset = 4;
			defined_animations.walk_animation.curves[4].keyframes_count = 2;
			defined_animations.walk_animation.curves[4].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[4].keyframes[0] = ((KeyFrame) { 1, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[4].keyframes[1] = ((KeyFrame) { 32, 0.5f, 0, 0 });

			defined_animations.walk_animation.curves[5].transform_index = 6; //right shoulder
			defined_animations.walk_animation.curves[5].channel_offset = 5;
			defined_animations.walk_animation.curves[5].keyframes_count = 2;
			defined_animations.walk_animation.curves[5].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[5].keyframes[0] = ((KeyFrame) { 1, -Tau / 6.0f, 0, 0 });
			defined_animations.walk_animation.curves[5].keyframes[1] = ((KeyFrame) { 32, -Tau / 6.0f, 0, 0 });

			defined_animations.walk_animation.curves[6].transform_index = 6; //right shoulder
			defined_animations.walk_animation.curves[6].channel_offset = 4;
			defined_animations.walk_animation.curves[6].keyframes_count = 5;
			defined_animations.walk_animation.curves[6].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[6].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.walk_animation.curves[6].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
			defined_animations.walk_animation.curves[6].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
			defined_animations.walk_animation.curves[6].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[6].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

			defined_animations.walk_animation.curves[7].transform_index = 7; //right elbow
			defined_animations.walk_animation.curves[7].channel_offset = 4;
			defined_animations.walk_animation.curves[7].keyframes_count = 2;
			defined_animations.walk_animation.curves[7].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[7].keyframes[0] = ((KeyFrame) { 1, -0.5f, 0, 0 });
			defined_animations.walk_animation.curves[7].keyframes[1] = ((KeyFrame) { 32, -0.5f, 0, 0 });

			defined_animations.walk_animation.curves[8].transform_index = 8; //left hip
			defined_animations.walk_animation.curves[8].channel_offset = 3;
			defined_animations.walk_animation.curves[8].keyframes_count = 5;
			defined_animations.walk_animation.curves[8].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[8].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.walk_animation.curves[8].keyframes[1] = ((KeyFrame) { 8, -0.5f, 0, 0 });
			defined_animations.walk_animation.curves[8].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
			defined_animations.walk_animation.curves[8].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[8].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

			defined_animations.walk_animation.curves[9].transform_index = 9; //left knee
			defined_animations.walk_animation.curves[9].channel_offset = 3;
			defined_animations.walk_animation.curves[9].keyframes_count = 3;
			defined_animations.walk_animation.curves[9].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[9].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.walk_animation.curves[9].keyframes[1] = ((KeyFrame) { 16, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[9].keyframes[2] = ((KeyFrame) { 32, 0, 0, 0 });

			defined_animations.walk_animation.curves[10].transform_index = 11; //right hip
			defined_animations.walk_animation.curves[10].channel_offset = 3;
			defined_animations.walk_animation.curves[10].keyframes_count = 5;
			defined_animations.walk_animation.curves[10].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[10].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.walk_animation.curves[10].keyframes[1] = ((KeyFrame) { 8, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[10].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
			defined_animations.walk_animation.curves[10].keyframes[3] = ((KeyFrame) { 24, -0.5f, 0, 0 });
			defined_animations.walk_animation.curves[10].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });

			defined_animations.walk_animation.curves[11].transform_index = 12; //right knee
			defined_animations.walk_animation.curves[11].channel_offset = 3;
			defined_animations.walk_animation.curves[11].keyframes_count = 5;
			defined_animations.walk_animation.curves[11].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.walk_animation.curves[11].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.walk_animation.curves[11].keyframes[1] = ((KeyFrame) { 8, 0, 0, 0 });
			defined_animations.walk_animation.curves[11].keyframes[2] = ((KeyFrame) { 16, 0, 0, 0 });
			defined_animations.walk_animation.curves[11].keyframes[3] = ((KeyFrame) { 24, 0.5f, 0, 0 });
			defined_animations.walk_animation.curves[11].keyframes[4] = ((KeyFrame) { 32, 0, 0, 0 });
		}

		//Idle Animation
		{
			defined_animations.idle_animation.looped = true;
			defined_animations.idle_animation.animation_length = 60;
			defined_animations.idle_animation.curves_count = 13;
			defined_animations.idle_animation.curves = malloc(sizeof(AnimationCurve) * defined_animations.idle_animation.curves_count);

			defined_animations.idle_animation.curves[0].transform_index = 1;
			defined_animations.idle_animation.curves[0].channel_offset = 1;
			defined_animations.idle_animation.curves[0].keyframes_count = 3;
			defined_animations.idle_animation.curves[0].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[0].keyframes[0] = ((KeyFrame) { 1, 2, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[0].keyframes[1] = ((KeyFrame) { 30, 1.93f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[0].keyframes[2] = ((KeyFrame) { 60, 2.00f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[1].transform_index = 1;
			defined_animations.idle_animation.curves[1].channel_offset = 4;
			defined_animations.idle_animation.curves[1].keyframes_count = 2;
			defined_animations.idle_animation.curves[1].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[1].keyframes[0] = ((KeyFrame) { 1, .3f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[1].keyframes[1] = ((KeyFrame) { 60, .3f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[2].transform_index = 2;
			defined_animations.idle_animation.curves[2].channel_offset = 4;
			defined_animations.idle_animation.curves[2].keyframes_count = 3;
			defined_animations.idle_animation.curves[2].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[2].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[2].keyframes[1] = ((KeyFrame) { 30, .3f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[2].keyframes[2] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[3].transform_index = 4;
			defined_animations.idle_animation.curves[3].channel_offset = 5;
			defined_animations.idle_animation.curves[3].keyframes_count = 3;
			defined_animations.idle_animation.curves[3].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[3].keyframes[0] = ((KeyFrame) { 1, Tau/4.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[3].keyframes[1] = ((KeyFrame) { 30, Tau/5.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[3].keyframes[2] = ((KeyFrame) { 60, Tau/4.0f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[4].transform_index = 4;
			defined_animations.idle_animation.curves[4].channel_offset = 4;
			defined_animations.idle_animation.curves[4].keyframes_count = 3;
			defined_animations.idle_animation.curves[4].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[4].keyframes[0] = ((KeyFrame) { 1, Tau/6.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[4].keyframes[1] = ((KeyFrame) { 30, Tau/8.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[4].keyframes[2] = ((KeyFrame) { 60, Tau/6.0f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[5].transform_index = 5;
			defined_animations.idle_animation.curves[5].channel_offset = 4;
			defined_animations.idle_animation.curves[5].keyframes_count = 3;
			defined_animations.idle_animation.curves[5].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[5].keyframes[0] = ((KeyFrame) { 1, Tau/4.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[5].keyframes[1] = ((KeyFrame) { 30, Tau/3.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[5].keyframes[2] = ((KeyFrame) { 60, Tau/4.0f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[6].transform_index = 6;
			defined_animations.idle_animation.curves[6].channel_offset = 5;
			defined_animations.idle_animation.curves[6].keyframes_count = 3;
			defined_animations.idle_animation.curves[6].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[6].keyframes[0] = ((KeyFrame) { 1, -Tau/4.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[6].keyframes[1] = ((KeyFrame) { 30, -Tau/5.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[6].keyframes[2] = ((KeyFrame) { 60, -Tau/4.0f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[7].transform_index = 6;
			defined_animations.idle_animation.curves[7].channel_offset = 4;
			defined_animations.idle_animation.curves[7].keyframes_count = 3;
			defined_animations.idle_animation.curves[7].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[7].keyframes[0] = ((KeyFrame) { 1, -Tau/6.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[7].keyframes[1] = ((KeyFrame) { 30, -Tau/8.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[7].keyframes[2] = ((KeyFrame) { 60, -Tau/6.0f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[8].transform_index = 7;
			defined_animations.idle_animation.curves[8].channel_offset = 4;
			defined_animations.idle_animation.curves[8].keyframes_count = 3;
			defined_animations.idle_animation.curves[8].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[8].keyframes[0] = ((KeyFrame) { 1, -Tau/4.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[8].keyframes[1] = ((KeyFrame) { 30, -Tau/3.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[8].keyframes[2] = ((KeyFrame) { 60, -Tau/4.0f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[9].transform_index = 8;
			defined_animations.idle_animation.curves[9].channel_offset = 3;
			defined_animations.idle_animation.curves[9].keyframes_count = 3;
			defined_animations.idle_animation.curves[9].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[9].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[9].keyframes[1] = ((KeyFrame) { 30, -0.3f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[9].keyframes[2] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[10].transform_index = 9;
			defined_animations.idle_animation.curves[10].channel_offset = 3;
			defined_animations.idle_animation.curves[10].keyframes_count = 3;
			defined_animations.idle_animation.curves[10].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[10].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[10].keyframes[1] = ((KeyFrame) { 30, 0.6f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[10].keyframes[2] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[11].transform_index = 11;
			defined_animations.idle_animation.curves[11].channel_offset = 3;
			defined_animations.idle_animation.curves[11].keyframes_count = 3;
			defined_animations.idle_animation.curves[11].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[11].keyframes[0] = ((KeyFrame) { 1, 0.3f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[11].keyframes[1] = ((KeyFrame) { 30, 0.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[11].keyframes[2] = ((KeyFrame) { 60, 0.3f, 0, 0, 0, 0 });

			defined_animations.idle_animation.curves[12].transform_index = 12;
			defined_animations.idle_animation.curves[12].channel_offset = 3;
			defined_animations.idle_animation.curves[12].keyframes_count = 3;
			defined_animations.idle_animation.curves[12].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.idle_animation.curves[12].keyframes[0] = ((KeyFrame) { 1, 0.0f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[12].keyframes[1] = ((KeyFrame) { 30, 0.6f, 0, 0, 0, 0 });
			defined_animations.idle_animation.curves[12].keyframes[2] = ((KeyFrame) { 60, 0.0f, 0, 0, 0, 0 });
		}

		//Jump Animation
		{
			defined_animations.jump_animation.looped = true;
			defined_animations.jump_animation.animation_length = 60;
			defined_animations.jump_animation.curves_count = 9;
			defined_animations.jump_animation.curves = malloc(sizeof(AnimationCurve) * defined_animations.jump_animation.curves_count);

			defined_animations.jump_animation.curves[0].transform_index = 1;
			defined_animations.jump_animation.curves[0].channel_offset = 1;
			defined_animations.jump_animation.curves[0].keyframes_count = 5;
			defined_animations.jump_animation.curves[0].keyframes = malloc(5 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[0].keyframes[0] = ((KeyFrame) { 1, 2, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[0].keyframes[1] = ((KeyFrame) { 27, 2, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[0].keyframes[2] = ((KeyFrame) { 30, 2, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[0].keyframes[3] = ((KeyFrame) { 45, 2, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[0].keyframes[4] = ((KeyFrame) { 60, 2, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[1].transform_index = 8;
			defined_animations.jump_animation.curves[1].channel_offset = 3;
			defined_animations.jump_animation.curves[1].keyframes_count = 4;
			defined_animations.jump_animation.curves[1].keyframes = malloc(4 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[1].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[1].keyframes[1] = ((KeyFrame) { 30, -0.5f, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[1].keyframes[2] = ((KeyFrame) { 40, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[1].keyframes[3] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[2].transform_index = 9;
			defined_animations.jump_animation.curves[2].channel_offset = 3;
			defined_animations.jump_animation.curves[2].keyframes_count = 4;
			defined_animations.jump_animation.curves[2].keyframes = malloc(4 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[2].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[2].keyframes[1] = ((KeyFrame) { 30, 1, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[2].keyframes[2] = ((KeyFrame) { 40, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[2].keyframes[3] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[3].transform_index = 11;
			defined_animations.jump_animation.curves[3].channel_offset = 3;
			defined_animations.jump_animation.curves[3].keyframes_count = 4;
			defined_animations.jump_animation.curves[3].keyframes = malloc(4 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[3].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[3].keyframes[1] = ((KeyFrame) { 30, -0.5f, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[3].keyframes[2] = ((KeyFrame) { 40, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[3].keyframes[3] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[4].transform_index = 12;
			defined_animations.jump_animation.curves[4].channel_offset = 3;
			defined_animations.jump_animation.curves[4].keyframes_count = 4;
			defined_animations.jump_animation.curves[4].keyframes = malloc(4 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[4].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[4].keyframes[1] = ((KeyFrame) { 30, 1, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[4].keyframes[2] = ((KeyFrame) { 40, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[4].keyframes[3] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[5].transform_index = 4;
			defined_animations.jump_animation.curves[5].channel_offset = 5;
			defined_animations.jump_animation.curves[5].keyframes_count = 4;
			defined_animations.jump_animation.curves[5].keyframes = malloc(4 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[5].keyframes[0] = ((KeyFrame) { 1, 1/4.0f*Tau, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[5].keyframes[1] = ((KeyFrame) { 30, 1/8.0f*Tau, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[5].keyframes[2] = ((KeyFrame) { 40, 1/4.0f*Tau, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[5].keyframes[3] = ((KeyFrame) { 60, 1/4.0f*Tau, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[6].transform_index = 6;
			defined_animations.jump_animation.curves[6].channel_offset = 5;
			defined_animations.jump_animation.curves[6].keyframes_count = 4;
			defined_animations.jump_animation.curves[6].keyframes = malloc(4 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[6].keyframes[0] = ((KeyFrame) { 1, -1/4.0f*Tau, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[6].keyframes[1] = ((KeyFrame) { 30, -1/8.0f*Tau, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[6].keyframes[2] = ((KeyFrame) { 40, -1/4.0f*Tau, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[6].keyframes[3] = ((KeyFrame) { 60, -1/4.0f*Tau, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[7].transform_index = 1;
			defined_animations.jump_animation.curves[7].channel_offset = ROTY;
			defined_animations.jump_animation.curves[7].keyframes_count = 2;
			defined_animations.jump_animation.curves[7].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[7].keyframes[0] = ((KeyFrame) { 1, .3f, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[7].keyframes[1] = ((KeyFrame) { 60, .3f, 0, 0, 0, 0 });

			defined_animations.jump_animation.curves[8].transform_index = 2;
			defined_animations.jump_animation.curves[8].channel_offset = ROTY;
			defined_animations.jump_animation.curves[8].keyframes_count = 3;
			defined_animations.jump_animation.curves[8].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.jump_animation.curves[8].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[8].keyframes[1] = ((KeyFrame) { 30, .6f, 0, 0, 0, 0 });
			defined_animations.jump_animation.curves[8].keyframes[2] = ((KeyFrame) { 60, 0, 0, 0, 0, 0 });		
		}

		//Punch Animation
		{
			defined_animations.punch_animation.looped = true;
			defined_animations.punch_animation.animation_length = 60;
			defined_animations.punch_animation.curves_count = 13;
			defined_animations.punch_animation.curves = malloc(sizeof(AnimationCurve) * defined_animations.punch_animation.curves_count);

			defined_animations.punch_animation.curves[0].transform_index = 1;
			defined_animations.punch_animation.curves[0].channel_offset = POSY;
			defined_animations.punch_animation.curves[0].keyframes_count = 2;
			defined_animations.punch_animation.curves[0].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[0].keyframes[0] = ((KeyFrame) { 1, 2, 0, 0 });
			defined_animations.punch_animation.curves[0].keyframes[1] = ((KeyFrame) { 30, 2, 0, 0 });

			defined_animations.punch_animation.curves[1].transform_index = 1;
			defined_animations.punch_animation.curves[1].channel_offset = 4;
			defined_animations.punch_animation.curves[1].keyframes_count = 2;
			defined_animations.punch_animation.curves[1].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[1].keyframes[0] = ((KeyFrame) { 1, .3f, 0, 0 });
			defined_animations.punch_animation.curves[1].keyframes[1] = ((KeyFrame) { 30, .3f, 0, 0 });

			defined_animations.punch_animation.curves[2].transform_index = 2;
			defined_animations.punch_animation.curves[2].channel_offset = 4;
			defined_animations.punch_animation.curves[2].keyframes_count = 3;
			defined_animations.punch_animation.curves[2].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[2].keyframes[0] = ((KeyFrame) { 1, .0f, 0, 0 });
			defined_animations.punch_animation.curves[2].keyframes[1] = ((KeyFrame) { 15, -.9f, 0, 0 });
			defined_animations.punch_animation.curves[2].keyframes[2] = ((KeyFrame) { 30, .0f, 0, 0 });			

			defined_animations.punch_animation.curves[3].transform_index = 4;
			defined_animations.punch_animation.curves[3].channel_offset = 5;
			defined_animations.punch_animation.curves[3].keyframes_count = 2;
			defined_animations.punch_animation.curves[3].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[3].keyframes[0] = ((KeyFrame) { 1, Tau/4.0f, 0, 0 });
			defined_animations.punch_animation.curves[3].keyframes[1] = ((KeyFrame) { 30, Tau/4.0f, 0, 0 });

			defined_animations.punch_animation.curves[4].transform_index = 4;
			defined_animations.punch_animation.curves[4].channel_offset = 4;
			defined_animations.punch_animation.curves[4].keyframes_count = 3;
			defined_animations.punch_animation.curves[4].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[4].keyframes[0] = ((KeyFrame) { 1, Tau/6.0f, 0, 0 });
			defined_animations.punch_animation.curves[4].keyframes[1] = ((KeyFrame) { 15, -Tau/9.0f, 0, 0 });
			defined_animations.punch_animation.curves[4].keyframes[2] = ((KeyFrame) { 30, Tau/6.0f, 0, 0 });

			defined_animations.punch_animation.curves[5].transform_index = 5;
			defined_animations.punch_animation.curves[5].channel_offset = 4;
			defined_animations.punch_animation.curves[5].keyframes_count = 2;
			defined_animations.punch_animation.curves[5].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[5].keyframes[0] = ((KeyFrame) { 1, Tau/4.0f, 0, 0 });
			defined_animations.punch_animation.curves[5].keyframes[1] = ((KeyFrame) { 30, Tau/4.0f, 0, 0 });


			defined_animations.punch_animation.curves[6].transform_index = 6;
			defined_animations.punch_animation.curves[6].channel_offset = 5;
			defined_animations.punch_animation.curves[6].keyframes_count = 3;
			defined_animations.punch_animation.curves[6].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[6].keyframes[0] = ((KeyFrame) { 1, -Tau/4.0f, 0, 0 });
			defined_animations.punch_animation.curves[6].keyframes[1] = ((KeyFrame) { 15, 0, 0, 0 });
			defined_animations.punch_animation.curves[6].keyframes[2] = ((KeyFrame) { 30, -Tau/4.0f, 0, 0 });

			defined_animations.punch_animation.curves[7].transform_index = 6;
			defined_animations.punch_animation.curves[7].channel_offset = 4;
			defined_animations.punch_animation.curves[7].keyframes_count = 3;
			defined_animations.punch_animation.curves[7].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[7].keyframes[0] = ((KeyFrame) { 1, -Tau/6.0f, 0, 0 });
			defined_animations.punch_animation.curves[7].keyframes[1] = ((KeyFrame) { 15, -Tau/4.0f, 0, 0 });
			defined_animations.punch_animation.curves[7].keyframes[2] = ((KeyFrame) { 30, -Tau/6.0f, 0, 0 });

			defined_animations.punch_animation.curves[8].transform_index = 7;
			defined_animations.punch_animation.curves[8].channel_offset = 4;
			defined_animations.punch_animation.curves[8].keyframes_count = 3;
			defined_animations.punch_animation.curves[8].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[8].keyframes[0] = ((KeyFrame) { 1, -Tau/4.0f, 0, 0 });
			defined_animations.punch_animation.curves[8].keyframes[1] = ((KeyFrame) { 15, 0, 0, 0 });
			defined_animations.punch_animation.curves[8].keyframes[2] = ((KeyFrame) { 30, -Tau/4.0f, 0, 0 });

			defined_animations.punch_animation.curves[9].transform_index = 8;
			defined_animations.punch_animation.curves[9].channel_offset = 3;
			defined_animations.punch_animation.curves[9].keyframes_count = 2;
			defined_animations.punch_animation.curves[9].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[9].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.punch_animation.curves[9].keyframes[1] = ((KeyFrame) { 30, 0, 0, 0 });

			defined_animations.punch_animation.curves[10].transform_index = 9;
			defined_animations.punch_animation.curves[10].channel_offset = 3;
			defined_animations.punch_animation.curves[10].keyframes_count = 2;
			defined_animations.punch_animation.curves[10].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[10].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.punch_animation.curves[10].keyframes[1] = ((KeyFrame) { 30, 0, 0, 0 });

			defined_animations.punch_animation.curves[11].transform_index = 11;
			defined_animations.punch_animation.curves[11].channel_offset = 3;
			defined_animations.punch_animation.curves[11].keyframes_count = 2;
			defined_animations.punch_animation.curves[11].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[11].keyframes[0] = ((KeyFrame) { 1, 0.3f, 0, 0 });
			defined_animations.punch_animation.curves[11].keyframes[1] = ((KeyFrame) { 30, 0.3f, 0, 0 });

			defined_animations.punch_animation.curves[12].transform_index = 12;
			defined_animations.punch_animation.curves[12].channel_offset = 3;
			defined_animations.punch_animation.curves[12].keyframes_count = 2;
			defined_animations.punch_animation.curves[12].keyframes = malloc(2 * sizeof(KeyFrame));
			defined_animations.punch_animation.curves[12].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0 });
			defined_animations.punch_animation.curves[12].keyframes[1] = ((KeyFrame) { 30, 0, 0, 0 });
		}

		//Kick Animation
		{
			defined_animations.kick_animation.looped = true;
			defined_animations.kick_animation.animation_length = 30;
			defined_animations.kick_animation.curves_count = 2;
			defined_animations.kick_animation.curves = malloc(sizeof(AnimationCurve) * defined_animations.kick_animation.curves_count);

			defined_animations.kick_animation.curves[0].transform_index = 8;
			defined_animations.kick_animation.curves[0].channel_offset = 3;
			defined_animations.kick_animation.curves[0].keyframes_count = 3;
			defined_animations.kick_animation.curves[0].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.kick_animation.curves[0].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.kick_animation.curves[0].keyframes[1] = ((KeyFrame) { 15, -Tau/4, 0, 0, 0, 0 });
			defined_animations.kick_animation.curves[0].keyframes[2] = ((KeyFrame) { 30, 0, 0, 0, 0, 0 });

			defined_animations.kick_animation.curves[1].transform_index = 2;
			defined_animations.kick_animation.curves[1].channel_offset = ROTY;
			defined_animations.kick_animation.curves[1].keyframes_count = 4;
			defined_animations.kick_animation.curves[1].keyframes = malloc(3 * sizeof(KeyFrame));
			defined_animations.kick_animation.curves[1].keyframes[0] = ((KeyFrame) { 1, 0, 0, 0, 0, 0 });
			defined_animations.kick_animation.curves[1].keyframes[1] = ((KeyFrame) { 7, -Tau/12, 0, 0, 0, 0 });			
			defined_animations.kick_animation.curves[1].keyframes[2] = ((KeyFrame) { 15, Tau/8, 0, 0, 0, 0 });
			defined_animations.kick_animation.curves[1].keyframes[3] = ((KeyFrame) { 30, 0, 0, 0, 0, 0 });			
		}		
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

	//Init MeshDemo
	{
		//Load FontSet
		{
			FILE* file_pointer = open_file("Assets/font_set", "r");
			read_bytes(font_set, 8, char_dict_count, file_pointer);
			close_file(file_pointer);
		}

		//Load Meshes
		{
			// cube_mesh = LoadMeshWithUVindices("Assets/cube.obj");
			// conan_mesh = LoadMeshWithUVindices("Assets/conan_importable2.obj");
			// guy_mesh = LoadMeshWithUVindices("Assets/guysmooth.obj");
			// teapot_mesh = LoadMesh("Assets/teapot.obj");
			// face_mesh = LoadMeshWithUVindices("Assets/face_textured.obj");
			
			FILE* file_pointer = open_file("Assets/mesh_data", "rb");
			seek_position(file_pointer, 0L, SEEK_END);
			int file_size = ftell(file_pointer);
			rewind(file_pointer);
			read_bytes(mesh_arena, file_size, 1, file_pointer);
			close_file(file_pointer);
			arena_write_index = file_size;

			conan_mesh = GetMeshFromArena(conan_arena_index);
			guy_mesh = GetMeshFromArena(guy_arena_index);
			cube_mesh = GetMeshFromArena(cube_arena_index);
			teapot_mesh = GetMeshFromArena(teapot_arena_index);
			face_mesh = GetMeshFromArena(face_arena_index);
			cube2_mesh = LoadMeshWithUVindices("Assets/cube2.obj");
			bigfist_mcpunchydude_mesh = LoadMeshWithUVindices("Assets/bigfist_mcpunchydude.obj");
			RecalculateNormals(&bigfist_mcpunchydude_mesh);
			bigfist_mcpunchydude_mesh = GetMeshFromArena(FillMeshArena(bigfist_mcpunchydude_mesh));

			ship_mesh = LoadMesh("Assets/ship.obj");
			RecalculateNormals(&ship_mesh);
			ship_mesh = GetMeshFromArena(FillMeshArena(ship_mesh));			
			//PrintMesh(guy_mesh);
		}

		// FillMeshArena(cube_mesh);
		// FillMeshArena(teapot_mesh);
		// FillMeshArena(guy_mesh);
		// FillMeshArena(face_mesh);
		// FillMeshArena(conan_mesh);

		// FILE* file_pointer = open_file("Assets/mesh_data", "wb");
		// write_bytes(mesh_arena,arena_write_index,1, file_pointer);
		// close_file(file_pointer);
		//PrintMeshArenaData(conan_arena_index);
		//PrintIndexedMesh(teapot_arena_index);

		//HeaderSerializeCubeMesh();
		//Load textures
		{
			FILE* file_pointer;
			int width, height;

			//guy_texture
			{
				file_pointer = open_file("Assets/guy.texture2", "rb");
				width = 1024, height = 1024;
				uint* pixels = malloc(sizeof(uint) * width * height);

				read_bytes(pixels, 4, width * height, file_pointer);
				guy_texture.width = width;
				guy_texture.height = height;
				guy_texture.pixels = pixels;
				close_file(file_pointer);
			}
			
			//conan_texture
			{
				file_pointer = open_file("Assets/conan.texture", "rb");
				width = 2048, height = 2048;
				uint* pixels = malloc(sizeof(uint) * width * height);

				read_bytes(pixels, 4, width * height, file_pointer);
				conan_texture.width = width;
				conan_texture.height = height;
				conan_texture.pixels = pixels;	
				close_file(file_pointer);		
			}

			//conan_normals
			{
				file_pointer = open_file("Assets/conan_normals.texture", "rb");
				width = 2048, height = 2048;
				uint* pixels = malloc(sizeof(uint) * width * height);

				read_bytes(pixels, 4, width * height, file_pointer);
				conan_normals.width = width;
				conan_normals.height = height;
				conan_normals.pixels = pixels;	
				close_file(file_pointer);		
			}

			//face_texture
			{
				file_pointer = open_file("Assets/face.texture", "rb");
				width = 1024, height = 1024;
				uint* pixels = malloc(sizeof(uint) * width * height);

				read_bytes(pixels, 4, width * height, file_pointer);
				face_texture.width = width;
				face_texture.height = height;
				face_texture.pixels = pixels;	
				close_file(file_pointer);		
			}

			//block_texture
			{
				file_pointer = open_file("Assets/block.texture", "rb");
				width = 200, height = 200;
				uint* pixels = malloc(sizeof(uint) * width * height);

				read_bytes(pixels, 4, width * height, file_pointer);
				block_texture.width = width;
				block_texture.height = height;
				block_texture.pixels = pixels;	
				close_file(file_pointer);		
			}

			//cube2normals_texture
			{
				file_pointer = open_file("Assets/cube2normals.texture", "rb");
				width = 1024, height = 1024;
				uint* pixels = malloc(sizeof(uint) * width * height);

				read_bytes(pixels, 4, width * height, file_pointer);
				cube2normals_texture.width = width;
				cube2normals_texture.height = height;
				cube2normals_texture.pixels = pixels;	
				close_file(file_pointer);		
			}

			//bigfist_mcpunchydude_texture
			{
				file_pointer = open_file("Assets/bigfist_mcpunchydude.texture", "rb");
				width = 1024, height = 1024;
				uint* pixels = malloc(sizeof(uint) * width * height);

				read_bytes(pixels, 4, width * height, file_pointer);
				bigfist_mcpunchydude_texture.width = width;
				bigfist_mcpunchydude_texture.height = height;
				bigfist_mcpunchydude_texture.pixels = pixels;	
				close_file(file_pointer);					
				
			}	


			//Load Character Icons
			{
				{
					file_pointer = open_file("Assets/bigfist_mcpunchydude_icon.texture", "rb");
					width = 100, height = 100;
					uint* pixels = malloc(sizeof(uint) * width * height);

					read_bytes(pixels, 4, width * height, file_pointer);
					bigfist_mcpunchydude_icon.width = width;
					bigfist_mcpunchydude_icon.height = height;
					bigfist_mcpunchydude_icon.pixels = pixels;	
					close_file(file_pointer);	
				}

				{
					file_pointer = open_file("Assets/jeffrey_icon.texture", "rb");
					width = 100, height = 100;
					uint* pixels = malloc(sizeof(uint) * width * height);

					read_bytes(pixels, 4, width * height, file_pointer);
					jeffrey_icon.width = width;
					jeffrey_icon.height = height;
					jeffrey_icon.pixels = pixels;	
					close_file(file_pointer);	
				}

				{
					file_pointer = open_file("Assets/maestro_icon.texture", "rb");
					width = 100, height = 100;
					uint* pixels = malloc(sizeof(uint) * width * height);

					read_bytes(pixels, 4, width * height, file_pointer);
					maestro_icon.width = width;
					maestro_icon.height = height;
					maestro_icon.pixels = pixels;	
					close_file(file_pointer);	
				}

				{

					file_pointer = open_file("Assets/dr_meroink_icon.texture", "rb");
					width = 100, height = 100;
					uint* pixels = malloc(sizeof(uint) * width * height);

					read_bytes(pixels, 4, width * height, file_pointer);
					dr_meroink_icon.width = width;
					dr_meroink_icon.height = height;
					dr_meroink_icon.pixels = pixels;	
					close_file(file_pointer);
				}


				character_icons[BigfistMcPunchydude] = bigfist_mcpunchydude_icon;
				character_icons[Jeffrey] = jeffrey_icon;
				character_icons[DrMeroink] = dr_meroink_icon;
				character_icons[Maestro] = maestro_icon;				
			}				
		}
	}

	// Init SkinnedMeshDemo
	{
		skinned_demo.camera = (Transform){ -1, { 0, 0, -50 }, { 0, 0, 0 }, { 1, 1, 1 } };
		skinned_demo.mesh = guy_mesh;
		
		skinned_demo.skeleton = LoadTransformHierarchy("Assets/avatar");
		skinned_demo.skeleton.joints[4].position.z = -.2f;
		skinned_demo.skeleton.joints[6].position.z = -.2f;
		skinned_demo.animation_length = 32;
		skinned_demo.has_a_face = false;
		if (skinned_demo.has_a_face)
		{
			//load face
			Mesh face = face_mesh;
			Mesh smile = LoadMesh("Assets/smile.obj");
			Mesh angry_eyes = LoadMesh("Assets/angry_eyes.obj");

			//adjust head vertices
			{
				skinned_demo.mesh.vertices[8].z -= .3f;
				skinned_demo.mesh.vertices[1].z -= .2f;
				skinned_demo.mesh.vertices[21].z -= .2f;

				skinned_demo.mesh.vertices[7].z -= .3f;
				skinned_demo.mesh.vertices[22].z -= .3f;
				skinned_demo.mesh.vertices[14].z -= .3f;
				skinned_demo.mesh.vertices[19].z -= .3f;
				skinned_demo.mesh.vertices[29].z -= .3f;
				skinned_demo.mesh.vertices[32].z -= .3f;
			}

			//Attach face
			skinned_demo.mesh = AppendMesh(skinned_demo.mesh, face);

			//build facial morph targets
			{
				skinned_demo.morphs[0] = malloc(smile.vertices_count*sizeof(v3));
				for (int i = 0; i < smile.vertices_count; i++)
				{
					skinned_demo.morphs[0][i] = smile.vertices[i];
				}

				skinned_demo.morphs[1] = malloc(angry_eyes.vertices_count*sizeof(v3));
				for (int i = 0; i < angry_eyes.vertices_count; i++)
				{
			       skinned_demo.morphs[1][i] = angry_eyes.vertices[i];
				}
			}
		}

		RecalculateNormals(&skinned_demo.mesh);
		////TODO replace with files to load
		int triangle_count = skinned_demo.mesh.indices_count / 3;
		skinned_demo.body_poly_colors = LoadPolygonColors("Assets/skin_poly_colors");

		skinned_demo.body_poly_colors_count = triangle_count;

		SetWeights();

		//build bind matrices
		{
			skinned_demo.bind_matrices = malloc(sizeof(m4x4) * skinned_demo.skeleton.joint_count);
			skinned_demo.bind_matrices_count = skinned_demo.skeleton.joint_count;

			Transform bind_transforms[100]; //TODO re-VLA

			for (int i = 0; i < skinned_demo.bind_matrices_count; i++)
			{
				bind_transforms[i] = InvertTransform(skinned_demo.skeleton.joints[i]);
				skinned_demo.bind_matrices[i] = WorldSpaceMatrix(i, bind_transforms);

				m4x4 m = skinned_demo.bind_matrices[i];
			}
		}

		skinned_demo.transformed_vertices = malloc(sizeof(v3) * skinned_demo.mesh.vertices_count);
		skinned_demo.transformed_vertices_count = skinned_demo.mesh.vertices_count;
		skinned_demo.skeleton.joints[0].position.y = -1;
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

	//Init SplashScreen
	{
		splash.started = false;
		splash.ended = false;
		splash.time = 0;
		splash.alpha = 0;


		//Load SplashScreen Image
		{
			FILE* file_pointer = open_file("Assets/viking_studios_logo", "r");
			int source_width = 1920, source_height = 1080;
			uint* pixels = malloc(sizeof(uint) * source_width * source_height);
			read_bytes(pixels, 4, source_width * source_height, file_pointer);
			splash.logo.width = source_width;
			splash.logo.height = source_height;
			splash.logo.pixels = pixels;

			close_file(file_pointer);

			splash.logo.width = WIDTH;
			splash.logo.height = HEIGHT;

			Color* splashcopy = malloc(source_width*source_height*4);
			memcpy(splashcopy, splash.logo.pixels, source_width*source_height*4);

			
			for (int y = 0; y < HEIGHT; y++)
			for (int x = 0; x < WIDTH; x++)
			{
				float dest_scaled_x = x/(float)WIDTH;
				int source_x = (int)(dest_scaled_x*source_width);

				float dest_scaled_y = y/(float)HEIGHT;
				int source_y = (int)(dest_scaled_y*source_height);				
				splash.logo.pixels[y*WIDTH+x] = splashcopy[source_y*source_width+source_x];
			}
			free(splashcopy);
			splashcopy = NULL;

			splash.x_min = (int)(550/(float)source_width*WIDTH);
			splash.y_min = (int)(125/(float)source_height*HEIGHT);
			splash.x_max = WIDTH - splash.x_min;
			splash.y_max = HEIGHT - splash.y_min;			
		}
	}
}

SDL_Window *window;

void GameLoop()
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
		if(KeyDown(Keys_Add))
			timing.time_scale += .05f;
		if(KeyDown(Keys_Subtract))
			timing.time_scale -= .05f;
	}

	if (!timing.fixed_framerate || (timing.time_since_last_frame >= timing.STANDARD_TIMESTEP))
	{
		//Tick
		{
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
					static Transform camera = {-1,{0,4,-50},{0,0,0},{1,1,1}};
					static Transform object_transform = {-1,{0,0,0},{0,0,0},{1,1,1}};
					static bool init = false;
					static bool capture = false;
					if(!init)
					{
						init = true;
					}



					//Camera Input
					{
						float camera_speed = 10.0f;
						float rotation_speed = 3.0f;
						v3 move_vector = v3_zero;
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

						if(KeyDown(Keys_Space))
							object_transform.rotation.y += timing.STANDARD_TIMESTEP *Tau/5.0f;				
					}

					if(KeyDownFresh(Keys_C))
						capture = !capture;
					
					Clear();
					ClearZBuffer();
					Color color = 0xAAAAAAAA;

					light_rotation+=timing.delta_time/4;
					struct FooStruct
					{
						Bitmap color_map;
						Bitmap normal_map;
						v3 rotation; 
					};

					struct FooStruct foos = {conan_texture,conan_normals,object_transform.rotation};

					light_rotation += timing.delta_time;

					//RenderMesh(cube_mesh, (Transform){-1,2,4,-6,0,0,0,1,1,1}, camera, ShadeColorGouraud, &color);
					//RenderMesh(teapot_mesh, (Transform){-1,6,-8,0,0,0,0,1,1,1}, camera, ShadeColorGouraud, &color);
					//RenderMesh(guy_mesh, (Transform){-1,8,0,0,0,0,0,1,1,1}, camera, ShadeColorGouraud, &color);
					//RenderMesh(face_mesh, (Transform){-1,8,0,0,0,0,0,1,1,1}, camera, ShadeColorGouraud, &color);
					Color colors[3] = {red,green,blue};
					perform_backface_culling = true;
					//DrawSprite(0,0, conan_texture);
					RenderMesh(conan_mesh, object_transform, camera, ShadeTexturedGouraud, &conan_texture);
				} break;
				case AnimationEditor:
				{
					static do_round = false;
					static float float_frame = 0;
					static int frame = 0;
					static bool play = true;
					static int selected_box;
					static HitFrame clipboard;
					#define Translate 0
					#define Scale 1
					static int mode = Translate;
					v2* modifier = NULL;

					if(mode == Translate)
						modifier = &(selected_hitbox_animation.frames[frame].boxes[selected_box].position);
					else if(mode == Scale)
						modifier = &selected_hitbox_animation.frames[frame].boxes[selected_box].size;

					if(KeyDownFresh(Keys_Space))
						play = !play;

					if(!play)
					{
						if(KeyDown(Keys_LCtrl))
						{
							if(KeyDownFresh(Keys_B))
							{
								selected_hitbox_animation.frame_count++;
							}

							if(KeyDownFresh(Keys_R))
							{
								selected_hitbox_animation.frames[frame].hurt_count = 1;
								selected_hitbox_animation.frames[frame].hit_count = 0;

								for (int i = 0; i < MAX_HITBOX_COUNT; i++)
								{								
									selected_hitbox_animation.frames[frame].boxes[i] = (Hitbox){ .position = { 0, 0 }, .size = { 1, 1 } };
								}

							}
							if(KeyDown(Keys_S)) //save
							{
								current_game_state = SaveAnimation;
							}

							if(KeyDown(Keys_C)) //copy frame
								clipboard = selected_hitbox_animation.frames[frame];

							if(KeyDown(Keys_V)) //paste frame
								selected_hitbox_animation.frames[frame] = clipboard;						

							if(KeyDownFresh(Keys_Up))
							{
								if(selected_box < selected_hitbox_animation.frames[frame].hurt_count)
									selected_hitbox_animation.frames[frame].hurt_count++;
								else
									selected_hitbox_animation.frames[frame].hit_count++;
							}
							if(KeyDownFresh(Keys_Down))
							{
								if(selected_box < selected_hitbox_animation.frames[frame].hurt_count)
									selected_hitbox_animation.frames[frame].hurt_count--;
								else
									selected_hitbox_animation.frames[frame].hit_count--;
							}
						}
						else
						{	
							if(KeyDownFresh(Keys_M))
							{
								if(mode == Translate)
									mode = Scale;
								else
									mode = Translate;
							}
							
							do_round = KeyDown(Keys_X);

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

							if(selected_box > selected_hitbox_animation.frames[frame].hit_count + selected_hitbox_animation.frames[frame].hurt_count)
								selected_box = selected_hitbox_animation.frames[frame].hit_count + selected_hitbox_animation.frames[frame].hurt_count;

							if(KeyDown(Keys_Left))
							{
								static float elapsed = 0;
								float initial_delay = .5f;
								float delay = .15f;
								if(KeyDownFresh(Keys_Left) || elapsed > delay) {							
									frame--;
									if(frame < 0)
										frame = selected_hitbox_animation.frame_count-1;
									elapsed = 0;
								}

								elapsed += timing.delta_time;
							}

							if(KeyDown(Keys_Right))
							{
								static float elapsed = 0;
								float initial_delay = .5f;
								float delay = .15f;
								if(KeyDownFresh(Keys_Right) || elapsed > delay) {
									frame++;
									if(frame == selected_hitbox_animation.frame_count)
										frame = 0;
									elapsed = 0;
								}

								elapsed += timing.delta_time;
							}
						}
					}

					

					if(play)
					{
						float_frame += timing.delta_time * timing.TARGET_FRAMERATE;
						if(float_frame >= selected_hitbox_animation.frame_count)
							float_frame = 0;

						frame = (int)float_frame;
					}

					
					static Animation current_animation;
					current_animation = defined_animations.kick_animation;
					v3 transformed_vertices[1000];//guy_mesh.vertices_count

					//Animate
					{
						//Animate Skeleton
						{
							for (int i = 0; i < current_animation.curves_count; i++)
							{
								AnimationCurve curve = current_animation.curves[i];
								int transform_index = curve.transform_index;

								Transform* p = &skinned_demo.skeleton.joints[transform_index];
								float* f = &(*p).position.x + curve.channel_offset;
								AnimateProperty(curve, frame, f);
							}
						}

						skinned_demo.skeleton.joints[0].position.y = 0;
						m4x4 skeleton_matrices[100]; //TODO re-VLA

						//Get Skeleton Matrices
						{
							for (int i = 0; i < skinned_demo.skeleton.joint_count; i++)
							{
								skeleton_matrices[i] = WorldSpaceMatrix(i, skinned_demo.skeleton.joints);
							}
						}

						//Apply Mesh Skinning
						{
							for (int i = 0; i < skinned_demo.mesh.vertices_count; i++)
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

								transformed_vertices[i] = v3_Add(i_a, i_b);
							}
						}

						//Advance Animation Time
						{
							if(skinned_demo.frame < current_animation.animation_length)
								skinned_demo.frame += timing.TARGET_FRAMERATE * timing.delta_time;
							if (current_animation.looped && skinned_demo.frame >= current_animation.animation_length)
								skinned_demo.frame = 0;
						}
					}	


					Clear();
					FillVerticalGradient(black, 0x999999);
					PutPixel_ByPosition(white, WIDTH/2, HEIGHT/2);
					FillRectangle(0xFFAAAAAA, 0, HEIGHT - 60, WIDTH, 60);
					
					int moop = WIDTH/selected_hitbox_animation.frame_count;
					FillRectangle(red, frame*moop+1, HEIGHT - 60, 5, 60);
					for(int i = 0; i < selected_hitbox_animation.frame_count; i++)
					{
						DrawVerticalSegment(black, i * moop, HEIGHT - 60, HEIGHT);

						char foo[3];
						sprintf(foo, "%d", i);
						DrawStringScaled(WrapString(foo), i*moop+6, HEIGHT - 60, 2,white);
					}
					
					light_rotation = Tau/2;
					static Transform guy_transform;
					guy_transform  = (Transform){-1,0,0,0,0,Tau/4,0,1,1,1};
					Mesh mesh = (Mesh) 
					{ 
						.vertices = transformed_vertices, 
						.vertices_count = guy_mesh.vertices_count,
						.indices = (int*) skinned_demo.mesh.indices, 
						.indices_count = skinned_demo.mesh.indices_count,
						.uvs = (v2*) skinned_demo.mesh.uvs, 
						.uvs_count = skinned_demo.mesh.uvs_count,
						.uv_indices = skinned_demo.mesh.uv_indices, 
						.uv_indices_count = skinned_demo.mesh.uv_indices_count,
						.normals = (v3*) skinned_demo.mesh.normals, 
						.normals_count = skinned_demo.mesh.normals_count
					};


					camera_to_clip = (m4x4){PIXELS_PER_UNIT/(float)WIDTH,0,0,0,0,-PIXELS_PER_UNIT/(float)HEIGHT,0,0,0,0,1,0,0,0,0,1};

					ClearZBuffer();
					orthographic = true;
					perform_clipping = false;
					perform_backface_culling = false;
					RenderMeshFromMatrix(mesh, GetMatrix(guy_transform), (Transform){-1,0,0,-10,0,0,0,1,1,1,}, ShadeTexturedGouraud, &guy_texture);
					orthographic = false;

					for (int i = 0; i < selected_hitbox_animation.frames[frame].hurt_count; i++)
					{
						v2 position = selected_hitbox_animation.frames[frame].boxes[i].position;
						position.x -= selected_hitbox_animation.frames[frame].boxes[i].size.x / 2.0f;
						position.y += selected_hitbox_animation.frames[frame].boxes[i].size.y / 2.0f;
						position.x *= +PIXELS_PER_UNIT;
						position.y *= -PIXELS_PER_UNIT;
						position.x += WIDTH / 2;
						position.y += HEIGHT / 2;
						DrawRectangle(blue, position.x, position.y , selected_hitbox_animation.frames[frame].boxes[i].size.x * PIXELS_PER_UNIT, selected_hitbox_animation.frames[frame].boxes[i].size.y * PIXELS_PER_UNIT);
					}

					for (int i = selected_hitbox_animation.frames[frame].hurt_count; i < selected_hitbox_animation.frames[frame].hurt_count + selected_hitbox_animation.frames[frame].hit_count; i++)
					{
						v2 position = selected_hitbox_animation.frames[frame].boxes[i].position;
						position.x -= selected_hitbox_animation.frames[frame].boxes[i].size.x / 2.0f;
						position.y += selected_hitbox_animation.frames[frame].boxes[i].size.y / 2.0f;
						position.x *= +PIXELS_PER_UNIT;
						position.y *= -PIXELS_PER_UNIT;
						position.x += WIDTH / 2;
						position.y += HEIGHT / 2;
						DrawRectangle(red, position.x, position.y , selected_hitbox_animation.frames[frame].boxes[i].size.x * PIXELS_PER_UNIT, selected_hitbox_animation.frames[frame].boxes[i].size.y * PIXELS_PER_UNIT);
					}					

					if(!play)
					{
						if(selected_box < selected_hitbox_animation.frames[frame].hurt_count + selected_hitbox_animation.frames[frame].hit_count)
						{
							v2 position = selected_hitbox_animation.frames[frame].boxes[selected_box].position;
							position.x -= selected_hitbox_animation.frames[frame].boxes[selected_box].size.x / 2.0f;
							position.y += selected_hitbox_animation.frames[frame].boxes[selected_box].size.y / 2.0f;
							position.x *= +PIXELS_PER_UNIT;
							position.y *= -PIXELS_PER_UNIT;
							position.x += WIDTH / 2;
							position.y += HEIGHT / 2;
							DrawRectangle(green, position.x-2, position.y-2, selected_hitbox_animation.frames[frame].boxes[selected_box].size.x * PIXELS_PER_UNIT + 4, selected_hitbox_animation.frames[frame].boxes[selected_box].size.y * PIXELS_PER_UNIT + 4);
						}

						//Draw Handles
						{
							v2 position = selected_hitbox_animation.frames[frame].boxes[selected_box].position;
							position.x *= +PIXELS_PER_UNIT;
							position.y *= -PIXELS_PER_UNIT;
							position.x += WIDTH / 2;
							position.y += HEIGHT / 2;	

							v2 right = (v2){ position.x + 100, position.y};
							v2 up = (v2){position.x, position.y - 100};
							float size = 20;
							float half_size = size/2.0f;
							#define x_handle 1
							#define y_handle 2
							#define center_handle 3
							static int selected_handle = 0;

							RectangleF x_rectangle = { right.x - half_size, right.y - half_size, size, size };
							RectangleF y_rectangle = { up.x - half_size, up.y - half_size, size, size };
							static v2 delta;
							static v2 start_position;
							static v2 start_value;

							if(mousestate.leftbutton_down)
							{
								if(!mousestate.leftbutton_was_down)
								for(int i = 0; i < selected_hitbox_animation.frames[frame].hit_count+selected_hitbox_animation.frames[frame].hurt_count; i++)
								{
									v2 box_position = selected_hitbox_animation.frames[frame].boxes[i].position;
									box_position.x -= selected_hitbox_animation.frames[frame].boxes[i].size.x / 2.0f;
									box_position.y += selected_hitbox_animation.frames[frame].boxes[i].size.y / 2.0f;
									box_position.x *= +PIXELS_PER_UNIT;
									box_position.y *= -PIXELS_PER_UNIT;
									box_position.x += WIDTH / 2;
									box_position.y += HEIGHT / 2;

									Hitbox box = selected_hitbox_animation.frames[frame].boxes[i];
									if(mousestate.position.x > box_position.x && mousestate.position.x < box_position.x + box.size.x*PIXELS_PER_UNIT && mousestate.position.y > box_position.y && mousestate.position.y < box_position.y +box.size.y*PIXELS_PER_UNIT)
									{
										selected_box = i;
										break;
									}
									
								}

								if(selected_handle == 0)
								{
									start_position = mousestate.position;
									start_value = *modifier;
									if(mousestate.position.x > x_rectangle.x && mousestate.position.x < x_rectangle.x + x_rectangle.width && mousestate.position.y > x_rectangle.y && mousestate.position.y < x_rectangle.y + x_rectangle.height)
										selected_handle = 1;
									if(mousestate.position.x > y_rectangle.x && mousestate.position.x < y_rectangle.x + y_rectangle.width && mousestate.position.y > y_rectangle.y && mousestate.position.y < y_rectangle.y + y_rectangle.height)
										selected_handle = 2;
									if(v2_Distance(mousestate.position,position) < 20)
										selected_handle = 3;
								}

								delta = v2_Subtract(mousestate.position, start_position);

								if(selected_handle == x_handle)
								{
									(*modifier).x = start_value.x + delta.x/20.0f;
									if(do_round)
										(*modifier).x = roundf((*modifier).x);
								}
								if(selected_handle == y_handle){
									(*modifier).y = start_value.y - delta.y/20.0f;
									if(do_round)
										(*modifier).y = roundf((*modifier).y);									
								}
								if(selected_handle == center_handle){
									v2 new_position = mousestate.position;
									new_position.x -= WIDTH/2;
									new_position.y -=HEIGHT/2;
									new_position.x/=PIXELS_PER_UNIT;
									new_position.y /=-PIXELS_PER_UNIT;
									*modifier = new_position;
									
									if(do_round)
									{
										(*modifier).x = roundf((*modifier).x);
										(*modifier).y = roundf((*modifier).y);										
									}							
								}
							}
							else
								selected_handle = 0;

							Color x_color = (selected_handle == x_handle) ? white: red;
							Color y_color = (selected_handle == y_handle) ? white: green;
							if(mode == Scale){
								Draw_Circle(cyan,position.x,position.y,20, 8.0f);
								DrawLine(red, position.x, position.y, right.x,right.y);
								DrawLine(green, position.x,position.y,up.x,up.y);								
								FillRectangle(x_color, right.x-half_size,right.y-half_size,size,size);
								FillRectangle(y_color, up.x-half_size,up.y-half_size,size,size);								
							}
							if(mode == Translate){	
								Draw_Circle(cyan,position.x,position.y,20, 8.0f);
								DrawLine(red, position.x, position.y, right.x,right.y);
								DrawLine(green, position.x,position.y,up.x,up.y);
								v2 a = (v2){(float)cos(0*Tau/3)*10,sin(0*Tau/3)*10};
								v2 b = (v2){(float)cos(1*Tau/3)*10,sin(1*Tau/3)*10};
								v2 c = (v2){(float)cos(2*Tau/3)*10,sin(2*Tau/3)*10};
								a.x += right.x;
								a.y += right.y;
								b.x += right.x;
								b.y+=right.y;
								c.x+=right.x;
								c.y+=right.y;
								FillTriangle(x_color, a.x, a.y, b.x, b.y, c.x,c.y);
								a = (v2){(float)cos(-Tau/4+0*Tau/3)*10,sin(-Tau/4+0*Tau/3)*10};
								b = (v2){(float)cos(-Tau/4+1*Tau/3)*10,sin(-Tau/4+1*Tau/3)*10};
								c = (v2){(float)cos(-Tau/4+2*Tau/3)*10,sin(-Tau/4+2*Tau/3)*10};
								a.x += up.x;
								a.y += up.y;
								b.x += up.x;
								b.y+=up.y;
								c.x+=up.x;
								c.y+=up.y;
								FillTriangle(y_color, a.x, a.y, b.x, b.y, c.x,c.y);							
							}
						}
					}
				} break;
				case CurveEditor:
				{
					Clear();
					static bool init = false;

					static int frame;
					static float float_frame;

					static AnimationCurve my_curve;
					static KeyFrame frames[5];
					static Transform object_transform;
					static Transform camera = {-1,{0,4,-50},{0,0,0},{1,1,1}};
					if(!init)
					{
						object_transform = DefaultTransform();
						object_transform.position.x = -25;
						my_curve.transform_index = 1;
						my_curve.channel_offset = 1;
						my_curve.keyframes_count = 5;
						my_curve.keyframes = frames;
						
						my_curve.keyframes[0] = ((KeyFrame) { 1, 0, -1, 0, 1, 0 });
						my_curve.keyframes[1] = ((KeyFrame) { 8, -0.5f, -1, 0, 1, 0 });
						my_curve.keyframes[2] = ((KeyFrame) { 16, 0, -1, 0, 1, 0  });
						my_curve.keyframes[3] = ((KeyFrame) { 24, 0.5f, -1, 0, 1, 0  });
						my_curve.keyframes[4] = ((KeyFrame) { 32, 0, -1, 0, 1, 0  });



						float p = 0.125f;
						my_curve.keyframes[2].right_handle_x = 0;
						my_curve.keyframes[2].right_handle_y = 0;

						my_curve.keyframes[3].left_handle_x= 0;
						my_curve.keyframes[3].left_handle_y= 0;	
						init = true;				
					}

					my_curve.keyframes[0].right_handle_x += mousestate.delta.x / 100;
					my_curve.keyframes[0].right_handle_y -= mousestate.delta.y / 100;

					FillVerticalGradient(white, black);

					//Draw Graph Editor
					{
						static float x_scale_float = 32;
						static float y_scale_float = 32;
						
						int graph_editor_x_scale = (int)x_scale_float;
						int graph_editor_y_scale = (int)y_scale_float;

						//x_scale_float += timing.delta_time*15;

						if(KeyDown(Keys_LAlt))
						{
							x_scale_float += mousestate.scroll_amount *5;
						}

						if(KeyDown(Keys_LShift))
						{
							y_scale_float += mousestate.scroll_amount *5;
						}

						FillRectangle(black,WIDTH/2,0,WIDTH/2,HEIGHT-60);
						
						//Draw Grid
						{	

							FillRectangle(0xFF555555,WIDTH/2,HEIGHT/2-3,WIDTH/2,6);
							FillRectangle(0xFF555555,WIDTH/2-3,0,6,HEIGHT-60);
							
							//Vertical
							for (int i = 0; i < 33; ++i)
							{
								DrawLine(0xFF888888, WIDTH / 2 + i * graph_editor_x_scale, 0, WIDTH / 2 + i * graph_editor_x_scale,HEIGHT-60);
								char message[50];
								sprintf(message, "%d", i+1);
								DrawString(WrapString(message), WIDTH/2+(i*graph_editor_x_scale+3), HEIGHT/2+3);
							}

							//Horizontal
							for (int i = 0; i < 33; ++i)
							{
								DrawLine(0xFF888888, WIDTH / 2, HEIGHT/2 + i*graph_editor_y_scale, WIDTH,HEIGHT/2+i*graph_editor_y_scale);
								DrawLine(0xFF888888, WIDTH / 2, HEIGHT/2 - i*graph_editor_y_scale, WIDTH,HEIGHT/2 - i*graph_editor_y_scale);
								char message[50];
								sprintf(message, "%d", i);
								DrawString(WrapString(message), WIDTH/2+5, HEIGHT/2-(i*graph_editor_y_scale+9));
							}
						}

						//Draw KeyframeCurve
						{
							for (int i = 0; i < my_curve.keyframes_count-1; ++i)
							{
								float x = my_curve.keyframes[i].frame;
								x *= graph_editor_x_scale;
								x += WIDTH / 2;
								float y = my_curve.keyframes[i].value;
								y *= -graph_editor_y_scale;
								y += HEIGHT / 2;

												
								float x2 = my_curve.keyframes[i+1].frame;
								x2 *= graph_editor_x_scale;
								x2 += WIDTH / 2;
								float y2 = my_curve.keyframes[i+1].value;
								y2 *= -graph_editor_y_scale;
								y2 += HEIGHT / 2;

								DrawLine(0x555555, (int)x, (int)y,(int)x2,(int)y2);

								KeyFrame a = my_curve.keyframes[i];
								KeyFrame b = my_curve.keyframes[i+1];
								float duration = b.frame - a.frame;
								#define sample_count 40
								v2 samples[sample_count];
								float step = duration / (sample_count-1);
								for(int i = 0; i < sample_count-1; i++)
								{
									samples[i].x = a.frame+i*step;
									samples[i].y = Sample(a,b,a.frame+i*step);
								}

								samples[sample_count-1].x = b.frame;
								samples[sample_count-1].y = b.value;

								for (int i = 0; i < sample_count-1; ++i)
								{

									float x = samples[i].x;
									x *= graph_editor_x_scale;
									x += WIDTH / 2;
									float y = samples[i].y;
									y *= -graph_editor_y_scale;
									y += HEIGHT / 2;		

									float x2 = samples[i+1].x;
									x2 *= graph_editor_x_scale;
									x2 += WIDTH / 2;
									float y2 = samples[i+1].y;
									y2 *= -graph_editor_y_scale;
									y2 += HEIGHT / 2;						
									DrawLine(white, (int)x, (int)y,(int)x2,(int)y2);
								}
							}
						}

						//Draw Curve Handles
						{
							for (int i = 0; i < my_curve.keyframes_count; ++i)
							{
								float x1 = my_curve.keyframes[i].frame;
								x1 *= graph_editor_x_scale;
								x1 += WIDTH / 2;
								float y1 = my_curve.keyframes[i].value;
								y1 *= -graph_editor_y_scale;
								y1 += HEIGHT / 2;


								float x2 = my_curve.keyframes[i].frame + my_curve.keyframes[i].left_handle_x;
								x2 *= graph_editor_x_scale;
								x2 += WIDTH / 2;
								float y2 = my_curve.keyframes[i].value + my_curve.keyframes[i].left_handle_y;
								y2 *= -graph_editor_y_scale;
								y2 += HEIGHT / 2;

								float x3 = my_curve.keyframes[i].frame + my_curve.keyframes[i].right_handle_x;
								x3 *= graph_editor_x_scale;
								x3 += WIDTH / 2;
								float y3 = my_curve.keyframes[i].value + my_curve.keyframes[i].right_handle_y;
								y3 *= -graph_editor_y_scale;
								y3 += HEIGHT / 2;

								DrawLine(yellow,x1,y1,x2,y2);
								DrawLine(yellow,x1,y1,x3,y3);
								FillCircle(red, (int)x1, (int)y1, 7);
								FillCircle(green,(int)x3,(int)y3,5);
								FillCircle(blue,(int)x2,(int)y2,5);
							}
						}

						FillRectangle(red,WIDTH/2+75,0,2,HEIGHT-60);
					}

					//Draw CharacterPane
					{
						//FillRectangle(green,0,0,WIDTH/2,HEIGHT-65);
						RenderMesh(conan_mesh, object_transform, camera, ShadeTexturedGouraud, &conan_texture);


						//Draw Orientation Indicator
						{
							DrawLine(red, 75, HEIGHT-135, 105, HEIGHT-125);
							DrawLine(green, 75, HEIGHT-135, 75, HEIGHT-175);
							DrawLine(blue, 75, HEIGHT-135, 45, HEIGHT-125);


							DrawCharacterScaled(font_set[23], 108, HEIGHT-125, 1, red);
							DrawCharacterScaled(font_set[24], 72, HEIGHT-188, 1, green);
							DrawCharacterScaled(font_set[25], 35, HEIGHT-125, 1, blue);
						}
					}


					//Draw Timeline
					{
						int animation_frame_count = 32;
						int timeline_height = 60;
						FillRectangle(0xFFAAAAAA, 0, HEIGHT - timeline_height, WIDTH, timeline_height);
						int timeline_frame_width = WIDTH/animation_frame_count;
						FillRectangle(red, frame*timeline_frame_width+1, HEIGHT - timeline_height, 5, timeline_height);
						for(int i = 0; i < animation_frame_count; i++)
						{
							DrawVerticalSegment(black, i * timeline_frame_width, HEIGHT - timeline_height, HEIGHT);

							char frame_number_string[3];
							sprintf(frame_number_string, "%d", i+1);
							DrawStringScaled(WrapString(frame_number_string), i*timeline_frame_width+6, HEIGHT - 10, 1,white);
						}
					}

				} break;
				case SaveAnimation:
				{
					#define max_name_count 20
					#define char_sprite_width 9

					static char file_name[max_name_count];
					static int cursor = 0;
					static float cursor_time;
					static bool draw_cursor = true;
					static float cursor_delay = .5f;
					if(KeyDownFresh(Keys_Escape))
						current_game_state = AnimationEditor;
					for (int i = Keys_A; i < Keys_Z; i++)
					{
						if(KeyDownFresh(i) && cursor < max_name_count)
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

					FillRectangle(0xFF888888, WIDTH/2-2, HEIGHT/2-2, max_name_count * char_sprite_width + 4, 14);
					FillRectangle(0xFFAAAAAA, WIDTH/2, HEIGHT/2, max_name_count * char_sprite_width, 10);
					if(draw_cursor)
						FillRectangle(0xFF555555, WIDTH/2+cursor*char_sprite_width,HEIGHT/2,2,10);
					DrawString(WrapString(file_name), WIDTH/2, HEIGHT/2);
					
					if(KeyDownFresh(Keys_Enter))
					{
						char path[50] = "Assets/";
						strcat(path,file_name);
						FILE* file_pointer = open_file(path, "w");
						write_bytes(&selected_hitbox_animation, sizeof(HitboxAnimation), 1, file_pointer);
						close_file(file_pointer);						
						current_game_state = AnimationEditor;
					}

					cursor_time += timing.delta_time;
					if(cursor_time > cursor_delay){
						draw_cursor = !draw_cursor;
						cursor_time = 0;
					}
				} break;
				case SplashScreenState:
				{
					if (!splash.started)
					{
						Clear();
			            SDL_AudioSpec wav_spec;
			            SDL_AudioSpec obtained_spec;
			            Uint32 wav_count;
			            Uint8 *wav_buffer;

			            SDL_LoadWAV("Assets/preparations.wav", &wav_spec, &wav_buffer, &wav_count);

			            SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, &obtained_spec, 0);            
			            SDL_QueueAudio(device_id, wav_buffer, wav_count);
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
					static bool init = false;
					if (!init)
					{
			            SDL_AudioSpec wav_spec;
			            SDL_AudioSpec obtained_spec;
			            Uint32 wav_count;
			            Uint8 *wav_buffer;

			            //SDL_LoadWAV("Assets/Chiptronical.wav", &wav_spec, &wav_buffer, &wav_count);

			            //SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, &obtained_spec, 0);            
			            //SDL_QueueAudio(device_id, wav_buffer, wav_count);
			            //SDL_PauseAudioDevice(device_id, 0);
						init = true;
					}

					if(KeyDownFresh(Keys_Space))
						current_game_state = MainMenu;

					memcpy(pixels,title_screen_background.pixels, pixel_count*sizeof(uint));

					#define sprite_size 9
					#define press_space_scale 4

					static float t = -Pi/2.0f;
					int center_x = WIDTH / 2;
					float alpha = (float)(sin(t) + 1)/2.0f;
					uint space_color = ((uint)(alpha * 0xAF) << 24) | 0xFFFFFF;
					DrawStringScaled(press_space, center_x - (press_space.length * sprite_size * press_space_scale / 2), HEIGHT - sprite_size*press_space_scale*2, press_space_scale, space_color);

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
					static v2 pos2;
					pos2.x =-2;
					pos2.y =-2;
					static float gravity = 10;
					static v2 velocity;
					static bool grounded;
					static bool was_grounded = false;
					static Transform block_transforms[block_count];
					static bool capture = false;
					static Transform enemy;
					static float enemy_health;
					static bool can_fast_fall;
					static Animation current_animation;
                    static float target_rot_y = 0;
                    static float target_t = 0;
                    static float old_target;

					if(KeyDownFresh(Keys_C))
					{
						capture = !capture;
						printf("capturing: %s", capture ? "true" : "false");
					}

					if(!init)
					{

						player = DefaultTransform();
						player.position.x = -2;
						player.position.y = -1;
						camera = player;
						camera.position.z = -20;
						target_rot_y = Tau / 4.0f;
						player.rotation.y = target_rot_y;
						old_target = target_rot_y;
						target_t =1;
						camera.rotation.x = 0.05f*Tau;
						player_collider.width = 2;
						player_collider.height = 6;
						player_collider.attachment = (v2*)&player.position;
						player_collider.offset.x = 0;
						player_collider.offset.y = 2.5f;
						enemy = (Transform){-1,10,2,0,0,0,0,1,5,1};
						for (int i = 0; i < block_count; ++i)
						{
							block_transforms[i] = DefaultTransform();
							block_colliders[i].attachment = (v2*)&block_transforms[i].position;
							block_transforms[i].position.x = i*2;
							block_transforms[i].scale.x = 2;
							block_transforms[i].scale.z = 4;
							block_colliders[i].width = 2;
							block_colliders[i].height = 1;
						}

						block_transforms[0].position.x=-2;
						block_transforms[0].position.y=-2;
						block_transforms[6].scale.y=3;
						block_transforms[6].position.y=2;
						block_colliders[6].height = 3;
						block_colliders[7].width = 6;
						block_transforms[7].scale.x = 6;
						block_transforms[8].position.y=7;

						block_transforms[block_count-1].position.y=2;
						block_transforms[block_count-1].scale.x = 80;
						block_transforms[block_count-1].position.x += 45;
						block_colliders[block_count-1].width = 80;

						block_transforms[block_count-2].position.y= -5;
						block_transforms[block_count-2].scale.x = 80;
						block_transforms[block_count-2].position.x += 40;
						block_colliders[block_count-2].width = 80;

						skinned_demo.frame = 1;
						current_animation = defined_animations.idle_animation;
						init = true;
						light_rotation  = 0;
						RecalculateNormals(&bigfist_mcpunchydude_mesh);
					}					

					light_rotation +=timing.delta_time;

					//Move Player
                    {
                        float acceleration = 20.0f;
                        float jump_speed = 10;
                        float max_speed = 5;
                        float slide_coefficient = 3.00f;
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

                            if (no_horizontal_input_since_landed){
                            	float slide_scale = slide_coefficient*velocity.x*timing.delta_time;
                                velocity.x -= slide_scale;
                                if(fabs(velocity.x) < .1f)
                                	velocity.x = 0;
                                current_animation = defined_animations.idle_animation;
                            }
                            else if(fabs(velocity.x) > 0)
                            	current_animation = defined_animations.walk_animation;
                            else
                            	current_animation = defined_animations.idle_animation;

                            if (game_pads[0].buttons[1])
                            {
                                velocity.y = jump_speed;
                                current_animation = defined_animations.jump_animation;
                                skinned_demo.frame = 0;
                                for (int i = 0; i < skinned_demo.skeleton.joint_count; ++i)
                                {
                                	skinned_demo.skeleton.joints[i].rotation = (v3)v3_zero;
                                }
                            }

                            static bool button_pressed;
				            static SDL_AudioDeviceID device_id;
						    static SDL_AudioSpec wav_spec;
						    static SDL_AudioSpec obtained_spec;
						    static Uint32 wav_count;
						    static Uint8 *wav_buffer;
				            static bool first = true;
				            if(first) {
				            	device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, &obtained_spec, 0);
				            	first = false;
				            }

                             if (game_pads[0].buttons[2])
                             {
                             	if(!button_pressed)
                                //todo play woosh
                                {

						            SDL_LoadWAV("Assets/woosh.wav", &wav_spec, &wav_buffer, &wav_count);

						            SDL_QueueAudio(device_id, wav_buffer, wav_count);
						            SDL_PauseAudioDevice(device_id, 0);          	
                                }                             	
                                current_animation = defined_animations.punch_animation;
                                skinned_demo.frame = 0;

                                button_pressed = true;
                             }
                             else
                             	button_pressed = false;
                        }
                        else
                        {
                            no_horizontal_input_since_landed = true;
                            velocity.y -= gravity * timing.delta_time;
                            
                            static float last_input_y = 0;
                            
                            //if at jump apex, player can dart toward ground
                            can_fast_fall = velocity.y < 5.3f && velocity.y > 0 && last_input_y > -dead_zone;
                            if(can_fast_fall)
                            {
                            	if(game_pads[0].left_stick.y < -.2f)
                            		velocity.y = -10;
                            }

                            	last_input_y = game_pads[0].left_stick.y;
                            
                            // //fly
                            // velocity.x = game_pads[0].left_stick.x * 10;
                            // velocity.y = game_pads[0].left_stick.y * 10;
                           
                        }

                        float old_x = player.position.x;
                        player.position.x += velocity.x * timing.delta_time;

                        for (int i = 0; i < block_count; i++)
                        {
                            BoxCollider b = block_colliders[i];
                            if (Intersect(player_collider, b))
                            {
                                if (old_x < (*b.attachment).x)
                                {
                                    player.position.x = (*b.attachment).x - (b.width / 2) - ((player_collider.width / 2)+player_collider.offset.x);
                                    velocity.x *= 0.1f;
                                }
                                else if (old_x > (*b.attachment).x)
                                {
                                    player.position.x = (*b.attachment).x + (b.width / 2) + ((player_collider.width / 2)-player_collider.offset.x);
                                    velocity.x *= 0.1f;
                                }
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
                                    player.position.y = (*b.attachment).y - (b.height / 2) - ((player_collider.height / 2)+player_collider.offset.y);
                                    velocity.y *= 0.1f;
                                }
                                else if (old_y > (*b.attachment).y)
                                {
                                    player.position.y = (*b.attachment).y + (b.height / 2) + ((player_collider.height / 2)-player_collider.offset.y);
                                    velocity.y *= 0.1f;
                                    grounded = true;
                                    if(!was_grounded)
                                    {
                                    	//play sound                          	
                                    }
                                }
                            }
                        }


                        if(velocity.x > 0)
                        {
                        	target_rot_y = Tau / 4;
                        }
                        else if(velocity.x < 0)
                        {
                        	target_rot_y = - Tau / 4;
                        }

                        if(target_rot_y != old_target)
                        	target_t = 0;
                        player.rotation.y = Lerp_Float(-target_rot_y, target_rot_y, target_t);
                        target_t += timing.delta_time*5;

                        if(target_t > 1)
                        	target_t = 1;

                        old_target = target_rot_y;

                        was_grounded = grounded;
                    }

					//Animate
					{
						//Animate Skeleton
						{
							for (int i = 0; i < current_animation.curves_count; i++)
							{
								AnimationCurve curve = current_animation.curves[i];
								int transform_index = curve.transform_index;

								Transform* p = &skinned_demo.skeleton.joints[transform_index];
								float* f = &(*p).position.x + curve.channel_offset;
								AnimateProperty(curve, skinned_demo.frame, f);
							}
						}

						skinned_demo.skeleton.joints[0].position.y = 0;
						m4x4 skeleton_matrices[100]; //TODO re-VLA

						//Get Skeleton Matrices
						{
							for (int i = 0; i < skinned_demo.skeleton.joint_count; i++)
							{
								skeleton_matrices[i] = WorldSpaceMatrix(i, skinned_demo.skeleton.joints);
							}
						}

						//Apply Mesh Skinning
						{
							for (int i = 0; i < skinned_demo.mesh.vertices_count; i++)
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

						//Advance Animation Time
						{
							if(skinned_demo.frame < current_animation.animation_length)
								skinned_demo.frame += timing.TARGET_FRAMERATE * timing.delta_time;
							if (current_animation.looped && skinned_demo.frame >= current_animation.animation_length)
								skinned_demo.frame = 0;
						}
					}	

					static bool free_camera = false;

					if(KeyDownFresh(Keys_H))
					{
						free_camera = !free_camera;
					}

					if(free_camera)
					{
						//Camera Input
						{
							float camera_speed = 10.0f;
							float rotation_speed = 2.0f;
							v3 move_vector = v3_zero;
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

							move_vector = Transform_v3(Rotation(0,camera.rotation.y, 0),move_vector);
							move_vector = v3_Scale(move_vector, timing.delta_time);
							camera.position = v3_Add(camera.position, move_vector);			
						}
					}
					else
					{
						float camera_stiffness = 2.5f;
						camera.position.x = Lerp_Float(camera.position.x, player.position.x, camera_stiffness * timing.delta_time);
						camera.position.y = Lerp_Float(camera.position.y, player.position.y + 8, camera_stiffness * timing.delta_time);
					}

					//Render
					{
						static bool is_3D = true;
						if(KeyDownFresh(Keys_B))
							is_3D = !is_3D;

						FillHorizontalGradient(cyan, Darker(Darker(blue)));

						if(is_3D)
						{
							ClearZBuffer();	

							Color colors[] = {red, blue, green, cyan, magenta, yellow, black, white, brown, purple};
							for (int i = 0; i < block_count; ++i)
							{
								RenderMesh(cube_mesh, block_transforms[i], camera, ShadeTexturedFlatShaded, &block_texture);
							}

							Mesh mesh = (Mesh) 
							{ 
								.vertices = skinned_demo.transformed_vertices, 
								.vertices_count = skinned_demo.transformed_vertices_count,
								.indices = (int*) skinned_demo.mesh.indices, 
								.indices_count = skinned_demo.mesh.indices_count,
								.uvs = (v2*) skinned_demo.mesh.uvs, 
								.uvs_count = skinned_demo.mesh.uvs_count,
								.uv_indices = skinned_demo.mesh.uv_indices, 
								.uv_indices_count = skinned_demo.mesh.uv_indices_count,
								.normals = (v3*) skinned_demo.mesh.normals, 
								.normals_count = skinned_demo.mesh.normals_count
							};

							RenderMesh(mesh, player, camera, ShadeTexturedGouraud, &bigfist_mcpunchydude_texture);
							mesh.indices= &(mesh.indices[1584]);
							mesh.indices_count -= 1584;

							mesh.uv_indices= &(mesh.uv_indices[1584]);
							mesh.uv_indices_count -= 1584;
							RenderMesh(mesh, player, camera, ShadeTexturedGouraud, &face_texture);

							RenderMesh(cube_mesh, enemy, camera,ShadeTexturedFlatShaded, &conan_texture);
							Color flag_color = red;
							RenderMesh(cube_mesh, enemy, camera,ShadeSolidColor,&flag_color);
							static float theta = 0;


							static Triangle t;
							t.a.color = red;
							t.b.color = green;
							t.c.color = blue;
							v3 center = (v3){WIDTH/2,HEIGHT/2,0};
							float scale = 190;
							v3 offset = (v3){cos(theta),sin(theta),.4f*(float)sin(Tau/2.0f + theta/10.0f)};

							t.a.position = v3_Add(v3_Scale(offset, scale),center);


							offset = (v3){cos(theta + Tau/3.0f),sin(theta+Tau/3.0f),0};
							t.b.position = v3_Add(v3_Scale(offset, scale),center);
							offset = (v3){cos(theta + 2*Tau/3.0f),sin(theta+2*Tau/3.0f),0};
							t.c.position = v3_Add(v3_Scale(offset, scale),center);
							t.a.uv = (v2){0,1};
							t.b.uv = (v2){1,1};
							t.c.uv = (v2){0,0};
							//RenderVertexTriangle(t, Shade2TexturedUnlit, &conan_texture);

							//RenderVertexTriangle(t, Shade2TexturedUnlit, &conan_texture);			
							//WavyScreen(theta);

							//FillHorizontalGradient(black, white);
							//Noise();
							theta += timing.delta_time*2;

							RenderHitbox((RectangleF){-.5f,-.5f,1,1}, DefaultTransform(), camera, blue);
						}				
						else
						{
							static int unit = 16;
							for (int i = 0; i < block_count; ++i)
							{
								v2 position = *block_colliders[i].attachment;
								position.x += block_colliders[i].offset.x;
								position.y += block_colliders[i].offset.y;								
								position.x-=camera.position.x;
								position.y-=camera.position.y;
								position.x *= unit;
								position.y *= -unit;
								position.x += WIDTH/2;
								position.y += HEIGHT/2;
								float width = block_colliders[i].width*unit;
								float half_width = width/2;
								float height = block_colliders[i].height*unit;
								float half_height = height/2;							
								FillRectangle(blue, position.x-half_width, position.y-half_height, width, height);
								FillRectangle(black, (int)(position.x-5), (int)(position.y-5), 10,10);
							}

							{
								v2 position = {player.position.x,player.position.y};
								position.x += player_collider.offset.x;
								position.y += player_collider.offset.y;
								position.x-=camera.position.x;
								position.y-=camera.position.y;								
								position.x *= unit;
								position.y *= -unit;
								position.x += WIDTH/2;
								position.y += HEIGHT/2;
								float width = player_collider.width*unit;
								float half_width = width/2;
								float height = player_collider.height*unit;
								float half_height = height/2;
								FillRectangle(green, position.x-half_width, position.y-half_height, width, height);

								if(can_fast_fall)
									FillCircle(red, position.x, position.y+height/2, 30);

								FillRectangle(black, (int)(position.x-5), (int)(position.y-5), 10,10);
							}
						}


						char chars[50];
						sprintf(chars, "%f %f %f", player.position.x, player.position.y, player.position.z);
						sprintf(chars, "grounded: %s", was_grounded ? "true" : "false");


						if(capture)
						{
							DrawRectangle(white,region_x-1,region_y-1,region_width+1,region_height+1);
							CaptureScreen();
						}
						DrawString(WrapString(chars),10,500);

						static bool foop = false;
						static bool schoop = false;
						static bool moop = false;
						if(Button("button 1", 50, 50, 170, 50))
							foop = !foop;
						if(Button("button 2", 250, 50, 170, 50))
							schoop = !schoop;						
						if(Button("click me", 450, 50, 170, 50))
							moop = !moop;
						if(foop)
							FillRectangle(red, 100,100,100,100);
						if(schoop)
							FillRectangle(green, 200,100,100,100);	
						if(moop)
							FillRectangle(blue, 300,100,100,100);
					}
				} break;
				case CharacterSelect:
				{
					static int selected_fighter[PLAYER_COUNT];
					static bool fighters_have_been_selected = false;
					static Transform player_transforms[PLAYER_COUNT];
					static bool init = false;
					if(!init)
					{
						init = true;
						for (int i = 0; i < PLAYER_COUNT; ++i)
						{
							player_transforms[i]  = DefaultTransform();
							player_transforms[i].rotation.y = Tau/2;
							player_transforms[i].position.x = i * 8-12;							
						}
					}

					if(!fighters_have_been_selected)
					{
						for (int i = 0; i < PLAYER_COUNT; ++i)
						{
							if(ButtonDownFresh(i, RIGHT))
								selected_fighter[i]++;
							if(ButtonDownFresh(i, LEFT))
								selected_fighter[i]--;
		
							if(selected_fighter[i] < 0)
								selected_fighter[i] += 4;
							selected_fighter[i] %= 4;
						}
					}
					else
					{
						for (int i = 0; i < PLAYER_COUNT; ++i)
						{
							float speed = timing.delta_time*10;
							if(ButtonDown(i, RIGHT))
								player_transforms[i].position.x += speed;
							if(ButtonDown(i, LEFT))
								player_transforms[i].position.x -= speed;
						}
					}

					if(KeyDownFresh(Keys_Space))
						fighters_have_been_selected = !fighters_have_been_selected;
					FillVerticalGradient(0xAAAAAA, black);
					char* fighter_names[4] = {"Bigfist Mcpunchydude", "Jeffrey", "Dr. Meroink", "Maestro"};
					int rect_width = 200;
					int cursor_width = 50;
					for (int i = 0; i < PLAYER_COUNT; ++i)
					{
						
						int x = i * rect_width + WIDTH/2-rect_width*4/2;
						int y = 150;
						FillRectangle(0x660033, x, y, rect_width, rect_width);
						DrawSprite(x, y, character_icons[i]);
						DrawRectangle(black, x, y, rect_width, rect_width);
						DrawStringScaled(WrapString(fighter_names[i]),x, y+rect_width-85, 1, black);
					}

					for (int i = 0; i < PLAYER_COUNT; ++i)
					{
						int left_most = WIDTH/2-(PLAYER_COUNT*rect_width/2);
						int x = left_most + selected_fighter[i] * rect_width+((rect_width-cursor_width)*(i%2));
						int y = 150 + ( (i>1) ? (rect_width-cursor_width) : 0);
						FillRectangle(gameplay_state.player_colors[i], x, y, cursor_width, cursor_width);
						char player_tag[3];
						sprintf(player_tag, "%dP",i+1);
						DrawStringScaled(WrapString(player_tag),x, y, 3, black);
					}

					Mesh meshes[4] = {bigfist_mcpunchydude_mesh, guy_mesh, conan_mesh, cube_mesh};
					Bitmap textures[4] = {bigfist_mcpunchydude_texture, guy_texture, conan_texture, conan_texture};

					Transform camera = DefaultTransform();
					camera.position.z =  -40;
					camera.position.y =  10;

					ClearZBuffer();
					
					for (int i = 0; i < PLAYER_COUNT; ++i)
					{
						RenderMesh(meshes[selected_fighter[i]], player_transforms[i], camera, ShadeTexturedGouraud, &textures[selected_fighter[i]]);
					}

					DrawStringScaled(WrapString("Character Select"), 0, 0, 4,white);
				} break;		
				case SkinnedMesh:
				{
					static bool init = false;
					if(!init)
					{
						init = true;
					}

					light_rotation = Tau/2;
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

			            if (KeyDownFresh(Keys_Q))
			            {
			                skinned_demo.animate_face = !skinned_demo.animate_face;
			            }

						if (KeyDownFresh(Keys_Y))
						{
							skinned_demo.has_a_face = !skinned_demo.has_a_face;
							//BuildGuy();
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
								for (int i = 0; i < defined_animations.walk_animation.curves_count; i++)
								{
									AnimationCurve curve = defined_animations.walk_animation.curves[i];
									int transform_index = curve.transform_index;

									Transform* p = &skinned_demo.skeleton.joints[transform_index];
									float* f = &(*p).position.x + curve.channel_offset;
									AnimateProperty(curve, skinned_demo.frame, f);
								}
							}
						}

						m4x4 skeleton_matrices[100]; //TODO re-VLA

						//Get Skeleton Matrices
						{
							for (int i = 0; i < skinned_demo.skeleton.joint_count; i++)
							{
								skeleton_matrices[i] = WorldSpaceMatrix(i, skinned_demo.skeleton.joints);
							}
						}

						//Apply Mesh Skinning
						{
							for (int i = 0; i < skinned_demo.mesh.vertices_count; i++)
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

			            //Apply Facial Morph Targets
			            {
			                if (skinned_demo.has_a_face && skinned_demo.animate_face)
			                {
			                	#define morph_deltas_count 259
			                    v3 deltas[morph_deltas_count]; //TODO replace magic number with actual length of morph vertex array
			                    for (int i = 0; i < morph_deltas_count; ++i)
			                    {
			                    	deltas[i] = (v3)v3_zero;
			                    }

			                    for (int morph_index = 0; morph_index < morph_count; morph_index++)
			                    {
			                        if (skinned_demo.morphs[morph_index] != NULL)
			                        {
			                            v3* current_morph = skinned_demo.morphs[morph_index];

			                            for (int i = 0; i < morph_deltas_count; ++i)
			                            {
			                            	#define facial_index_offset 266
			                            	v3 point = current_morph[i];
			                            	int vertex_index = i + facial_index_offset;
			                            	Weight_Index weight_index = skinned_demo.weight_indices[vertex_index];
		                            	 	Vec4 weight = skinned_demo.weights[facial_index_offset];

											v3 v_a = Transform_v3(Concatenate(skinned_demo.bind_matrices[weight_index.bone1], skeleton_matrices[weight_index.bone1]), point);
											v3 v_b = Transform_v3(Concatenate(skinned_demo.bind_matrices[weight_index.bone2], skeleton_matrices[weight_index.bone2]), point);
											v3 v_c = Transform_v3(Concatenate(skinned_demo.bind_matrices[weight_index.bone3], skeleton_matrices[weight_index.bone3]), point);
											v3 v_d = Transform_v3(Concatenate(skinned_demo.bind_matrices[weight_index.bone4], skeleton_matrices[weight_index.bone4]), point);

											v_a = v3_Scale(v_a, skinned_demo.weights[i].x);
											v_b = v3_Scale(v_b, skinned_demo.weights[i].y);
											v_c = v3_Scale(v_c, skinned_demo.weights[i].z);
											v_d = v3_Scale(v_d, skinned_demo.weights[i].w);

											v3 i_a = v3_Add(v_a, v_b);
											v3 i_b = v3_Add(v_c, v_d);

											v3 skinned_morph = v3_Add(i_a, i_b);

											deltas[i] = v3_Add(deltas[i],v3_Scale(v3_Subtract(skinned_morph,skinned_demo.transformed_vertices[vertex_index]),skinned_demo.morph_weights[morph_index]*2));
			                            }
			                        }
			                    }

			                    for (int i = 0; i < morph_deltas_count; i++)
			                    {
			                        int vertex_index = i + facial_index_offset;
			                        skinned_demo.transformed_vertices[vertex_index] = v3_Add(skinned_demo.transformed_vertices[vertex_index], deltas[i]);
			                    }
			                }

			                skinned_demo.morph_weights[0] = ((float)cos(skinned_demo.facial_time * 2) + 1) / 2;
			                skinned_demo.morph_weights[1] = ((float)sin(skinned_demo.facial_time * 2) + 1) / 2;

			                skinned_demo.facial_time += timing.delta_time;
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
							.vertices_count = skinned_demo.transformed_vertices_count,
							.indices = (int*) skinned_demo.mesh.indices, 
							.indices_count = skinned_demo.mesh.indices_count,
							.uvs = (v2*) skinned_demo.mesh.uvs, 
							.uvs_count = skinned_demo.mesh.uvs_count,
							.uv_indices = skinned_demo.mesh.uv_indices, 
							.uv_indices_count = skinned_demo.mesh.uv_indices_count,
							.normals = (v3*) skinned_demo.mesh.normals, 
							.normals_count = skinned_demo.mesh.normals_count
						};

						//Clear();
						FillVerticalGradient(black, cyan);
						ClearZBuffer();
						
						Color rgb[3] = {red,green,blue};
						Color skin = 0xFFBB88;
						if(skinned_demo.fill_toggle)
							RenderMesh(mesh, DefaultTransform(), skinned_demo.camera, ShadeVertexColors, &rgb);
						else
						{
							RenderMesh(mesh, DefaultTransform(), skinned_demo.camera, ShadeTexturedGouraud, &guy_texture);
							mesh.indices= &(mesh.indices[1584]);
							mesh.indices_count -= 1584;

							mesh.uv_indices= &(mesh.uv_indices[1584]);
							mesh.uv_indices_count -= 1584;
							RenderMesh(mesh, DefaultTransform(), skinned_demo.camera, ShadeTexturedGouraud, &face_texture);
						}


						ClearZBuffer();
						for(int i = 0; i < skinned_demo.skeleton.joint_count; i++)
						{
							m4x4 joint_matrix = WorldSpaceMatrix(i,skinned_demo.skeleton.joints);
							float scale_factor = .1f;
							joint_matrix.m11 *= scale_factor;
							joint_matrix.m12 *= scale_factor;
							joint_matrix.m13 *= scale_factor;
							joint_matrix.m21 *= scale_factor;
							joint_matrix.m22 *= scale_factor;
							joint_matrix.m23 *= scale_factor;
							joint_matrix.m31 *= scale_factor;
							joint_matrix.m32 *= scale_factor;
							joint_matrix.m33 *= scale_factor;								
							//joint_matrix = Concatenate(joint_matrix, GetMatrix(player));
							RenderMeshFromMatrix(cube_mesh, joint_matrix, skinned_demo.camera, ShadeWhite, NULL);
						}						
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
							v3* position = &gameplay_state.transforms[gameplay_state.players[i].entity_ID].position;
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
							v3 position = gameplay_state.transforms[gameplay_state.players[i].entity_ID].position;
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
						v2 position;
						v2 velocity;
						v2 acceleration;
						float lifetime;

					} Particle;
					Bitmap sprite;
					sprite.width = 10;
					sprite.height = 10;
					uint sprite_pixels[10*10];
					sprite.pixels = sprite_pixels;
					for(int i = 0; i < 100; i++)
					{
						if (i % 3 == 0)
							sprite.pixels[i] = red;
						else if (i % 7 == 0)
							sprite.pixels[i] = yellow;
						else if (i > 50)
							sprite.pixels[i] = yellow;
						else
							sprite.pixels[i] = black;

					}
					#define particle_capacity 10000
					static Particle particles[particle_capacity];

					static int count = 0;
					static bool warmed = false;

					static v2 emitter_position = {0,0};
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
				case PeruseScreenCaptures:
				{
					static bool loaded = false;
					static float current_image = 0;
					static float last_image = -1;
					static bool play = false;
					if(!loaded)
					{
						FILE* file_pointer = open_file("Assets/screen_captures", "rb");
						read_bytes(screen_captures, region_width*region_height*4, frames_to_capture, file_pointer);
						loaded = true;
					}
					if(KeyDownFresh(Keys_Space))
						play = !play;

					if(play)
					{
						current_image += timing.TARGET_FRAMERATE * timing.delta_time;
					}
					else
					{
						float scrub_speed = 10;

						float time_delta = timing.TARGET_FRAMERATE * timing.delta_time * scrub_speed;
						if(KeyDown(Keys_A))
							current_image -= time_delta;
						if(KeyDown(Keys_D))
							current_image += time_delta;

					}

					if((int)current_image >= frames_to_capture)
						current_image = 0;
					if(current_image < 0)
						current_image = frames_to_capture-1;

					//if(current_image != last_image)
					{
						Fill(Darker(Darker(Darker(white))));
						for (int x = 0; x < region_width; ++x)
						{
							for (int y = 0; y < region_height; ++y)
							{
								pixels[(y+region_y)*WIDTH+x+region_x] = screen_captures[(int)current_image][y*region_width+x];
							}
						}
					}

					int scroll_x_start = 50;
					int scroll_x = scroll_x_start + (int)(current_image/frames_to_capture*(WIDTH-100));
					FillRectangle(0xFF555555,scroll_x_start,HEIGHT - 25, WIDTH-100, 10);
					FillCircle(0xFF333333,scroll_x,HEIGHT-20,10);
					last_image = current_image;
				} break;
				case MorphTargetsDemo:
				{
					static Transform camera;
					camera = DefaultTransform();
					camera.position.z = -5;
					static bool draw = false;
					static Transform object_transform = {-1,0,-4,0,0,Tau/2,0,1,1,1};

					static float morph_weights[morph_count];

					#define transformed_vertex_count 259 //face_mesh.vertices_count
					v3 transformed_vertices[transformed_vertex_count];
		            
		            if(true)//Apply Facial Morph Targets
		            {
	                    v3 deltas[transformed_vertex_count];
	                    for (int i = 0; i < morph_deltas_count; ++i)
	                    {
	                    	deltas[i] = (v3)v3_zero;
	                    }

	                    for (int morph_index = 0; morph_index < morph_count; morph_index++)
	                    {
	                        if (skinned_demo.morphs[morph_index] != NULL)
	                        {
	                            v3* current_morph = skinned_demo.morphs[morph_index];

	                            for (int i = 0; i < morph_deltas_count; ++i)
	                            {
	                            	v3 point = current_morph[i];
									deltas[i] = v3_Add(deltas[i],v3_Scale(v3_Subtract(point,face_mesh.vertices[i]), morph_weights[morph_index]*2));
	                            }
	                        }
	                    }

	                    for (int i = 0; i < morph_deltas_count; i++)
	                    {
	                    	#undef facial_index_offset
	                    	#define facial_index_offset 0
	                        int vertex_index = i + facial_index_offset;
	                        transformed_vertices[vertex_index] = v3_Add(face_mesh.vertices[vertex_index], deltas[i]);
	                    }
		            }

					Clear();
					if(Button("Toggle Draw", 32,32, 100, 50))
						draw = !draw;

					static float smile_weight = 0;
					static float angry_eyes_weight = 0;
	                morph_weights[0] = Slider("smile", 0, 1, 32, 128, 300, &smile_weight);
	                morph_weights[1] = Slider("angry eyes", 0, 1, 32,160,100, &angry_eyes_weight);
					
					Mesh to_render = (Mesh)
					{
						.vertices = transformed_vertices,
						.vertices_count = face_mesh.vertices_count,
						.indices = face_mesh.indices,
						.indices_count = face_mesh.indices_count,
						.uvs = face_mesh.uvs,
						.uvs_count = face_mesh.uvs_count,
						.uv_indices = face_mesh.uv_indices,
						.uv_indices_count = face_mesh.uv_indices_count,
						.normals = face_mesh.normals,
						.normals_count = face_mesh.normals_count
					};

						ClearZBuffer();
					if(draw)
					{
						RenderMesh(to_render, object_transform, camera, ShadeTexturedGouraud, &face_texture);
					}
				} break;
				case Credits:
				{
					Clear();
					static float y = 1000;
					char* credits = "!The End\n!Code:\tSpencer Isaacson\nArt:\tSpencer Hunt\nVoices:\tBoth\n\n\n!The Beginning\n!";
					string credits_string = WrapString(credits);

					int column_number  = 0;
					int row_number = 0;
					bool is_title = false;
					bool right_justified = false;
					static int chars_long = 0;
					for (int i = 0; i < credits_string.length; ++i)
					{
						switch(credits_string.characters[i])
						{
							case '!':
							{
								is_title = !is_title;
								if(!is_title)
								{
									row_number += 4;
									column_number = 5;									
								}
								else
								{
									char c = credits_string.characters[i];
									int char_index = i;
									while(c!='\n')
									{
										c= credits_string.characters[char_index++];
									}

									chars_long = char_index-(i+2);									
								}
							} break;
							case '\n':
							{
								column_number = (is_title) ? 0 : 5;
								row_number += 2;
								right_justified = false;
							} break;
							case '\t':
							{
								right_justified = true;
								column_number = 25;
							} break;
							default:
							{
								int scale = (is_title) ? 7 : 3;

								int characters_long= 0;
								int x = 0;

								if(is_title)
								{
									char c = credits_string.characters[i];
									int char_index = i;
									while(c!='\n')
									{
										c= credits_string.characters[char_index++];
									}

									characters_long = char_index-(i+1);
									int text_width = characters_long*9*scale;
									x = WIDTH/2-text_width+(chars_long*9*scale/2);
								}
								else if(right_justified)
								{
										char c = credits_string.characters[i];
										int char_index = i;
										while(c != '\n')
										{
											c= credits_string.characters[char_index++];
										}

										characters_long = char_index-(i+1);
										int text_width = characters_long*9*scale;
										x = WIDTH-text_width-100;
								}
								else
									x = column_number * 9 * scale;
								//Draw Next Character
								{
									char a = tolower(credits_string.characters[i]);
									for (int o = 0; o < char_dict_count; o++)
									{
										if (a == char_dict[o])
										{
											DrawCharacterScaled(font_set[o], x, (int)y + (row_number*9*scale), scale, white);
										}

									}
								}

								column_number++;							
							} break;
						}
					}

					int end_y = -625;
					if(y > end_y)
						y -= timing.delta_time*50;
					else
						y = end_y;

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

    		SDL_UpdateWindowSurface(window);
			timing.time_since_last_frame = 0;
		}
	}

	//Update Timing
	{
		float elapsed = (float)(clock() - timing.previous_time) / (float)CLOCKS_PER_SEC;
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



//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
//Game Controller 1 handler
SDL_Joystick* gGameController = NULL;



int main(int argc, char* argv[])
{
	StartTiming();
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
    EndTiming();
    printf(" to start the game.");
    while (window_is_active) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            switch(event.type)
        	{
                case SDL_QUIT:
                {
                    window_is_active = false;
                } break;
                case SDL_JOYAXISMOTION:
                {

                    if( event.jaxis.axis == 0 )
                    {
                    	game_pads[event.jaxis.which].left_stick.x = (float)(event.jaxis.value / 32767.0f);
                    }
                    else if( event.jaxis.axis == 1 )
                    {
                        game_pads[event.jaxis.which].left_stick.y = -(float)(event.jaxis.value / 32767.0f);
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

                case SDL_MOUSEMOTION:
                {
                	SDL_MouseMotionEvent mouse_event = event.motion;
            		mousestate.position = (v2){mouse_event.x,mouse_event.y};
            		mousestate.delta = (v2){mouse_event.xrel,mouse_event.yrel};
                } break;    
                case SDL_MOUSEWHEEL:
                {
            		mousestate.scroll_amount = event.wheel.y;
                } break;    
                case SDL_MOUSEBUTTONDOWN:
                {
                	SDL_MouseButtonEvent mouse_event = event.button;
                	if(mouse_event.button == SDL_BUTTON_LEFT)
                	{
                		mousestate.leftbutton_down = true;
                		mousestate.position = (v2){mouse_event.x,mouse_event.y};
                	}
                } break;
                case SDL_MOUSEBUTTONUP:
                {
                	SDL_MouseButtonEvent mouse_event = event.button;
                	if(mouse_event.button == SDL_BUTTON_LEFT)
                	{
                		mousestate.leftbutton_down = false;
                		mousestate.position = (v2){mouse_event.x,mouse_event.y};
                	}
                } break;                       
        		default:
        			break;
        	}
        }

        GameLoop();
        mousestate.delta = (v2){0,0};
		mousestate.leftbutton_was_down = mousestate.leftbutton_down;
		mousestate.scroll_amount = 0;
    }

    return 0;
}