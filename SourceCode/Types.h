typedef struct
{
	int length;
	char* characters;
} string;

typedef struct Vec2
{
	float x, y;
} Vec2;

typedef struct Vec2i
{
	int x, y;
} Vec2i;

typedef struct Vec3
{
	float x, y, z;
} Vec3;

typedef struct Vec3i
{
	int x, y, z;
} Vec3i;

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

#define Color unsigned int
typedef struct Triangle
{
	Vec3 a, b, c;
	Color color;
	float brightness;
	Vec2 a_uv, b_uv, c_uv;
} Triangle;

typedef struct TriangleSmall
{
	Vec3 a, b, c;
} TriangleSmall;

typedef struct TriangleIndices
{
	int a, b, c;
} TriangleIndices;

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
	int normals_length;
	Vec3* normals;
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