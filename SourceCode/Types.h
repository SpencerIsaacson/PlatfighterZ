#define bool char
#define true 1
#define false 0
#define byte unsigned char
#define uint unsigned int

typedef struct
{
	int length;
	char* characters;
} string;

typedef struct v2
{
	float x, y;
} v2;

typedef struct v2i
{
	int x, y;
} v2i;

typedef struct v3
{
	float x, y, z;
} v3;

typedef struct v3i
{
	int x, y, z;
} v3i;

typedef struct
{
	float x, y, z, w;
} Vec4;



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

typedef struct RectangleF
{
	float x,y,width,height;
} RectangleF;

typedef struct PointRectangle
{
	v3 top_left;
	v3 top_right;
	v3 bottom_left;
	v3 bottom_right;
} PointRectangle;

typedef struct
{
	v2 position;
	v2 size;
} Hitbox;

typedef enum
{
	Inactive,
	Attack,
	Defend,
} HitboxState;

typedef struct 
{
	int state_frame_count;
	int keys[5];
	int values[5];
} HitboxStateAnimation;

typedef struct
{
	int transform_index;
	char channel_offset;
	int keyframes_count;
	KeyFrame keyframes[10];
} AnimationCurve;


#define curves_per_box 4

typedef	struct 
{
	HitboxState state;
	RectangleF rect;
	int animation_length;
	AnimationCurve curves[curves_per_box];
	HitboxStateAnimation hitstate_anim;
} HitboxAnimation;

#define hitbox_count 10
typedef struct
{
	bool looped;
	int animation_length;
	int curves_count;
	AnimationCurve curves[20];
	HitboxAnimation hitframes[hitbox_count];
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

} HitboxAnimationOld;

typedef unsigned int Color;

typedef struct Vertex
{
	v3 position;
	v3 normal;
	v2 uv;
	Color color;
} Vertex;

typedef struct Triangle
{
	Vertex a, b, c;
} Triangle;

typedef struct TriangleMesh
{
	int triangle_count;
	Triangle* triangles;
} TriangleMesh;

typedef struct TriangleIndices
{
	int a, b, c;
} TriangleIndices;

typedef struct Mesh
{
	int vertices_count;
	v3* vertices;
	int indices_count;
	int* indices;
	int uvs_count;
	v2* uvs;
	int uv_indices_count;
	int* uv_indices;
	int normals_count;
	v3* normals;
} Mesh;

typedef struct IndexedMesh
{
	int vertices_count;
	int vertices_offset;
	int indices_count;
	int indices_offset;
	int normals_count;
	int normals_offset;	
	int uvs_count;
	int uvs_offset;
	int uv_indices_count;
	int uv_indices_offset;
	byte data[1];
} IndexedMesh;

typedef struct
{
	int joint_count;
	Transform* joints;
} Skeleton;

typedef struct
{
	int entity_ID;
	Transform transform;
	int selected_character;
	bool defeated;
	int stock;
	float current_health;
	v2 velocity;
	bool grounded;
	bool was_grounded;
} Player;


typedef struct
{
	int width, height;
	uint* pixels;
} Bitmap;

typedef Color (*Shader)(v3 barycentric_point, int triangle_index, void* shader_state);

typedef struct Material
{
	Shader shader;
	void* state;
} Material;

typedef struct Entity
{
	Transform transform;
	IndexedMesh mesh;
	Material material;
} Entity;

typedef struct
{
	string name;
	Bitmap icon;
	Mesh mesh;
	Bitmap texture;
	Bitmap color_mask;
} Fighter;