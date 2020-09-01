
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

void Clear()
{
	memset(pixels, 0, pixel_count * sizeof(uint));
}

Color Darker(Color color)
{
	Color r = (color & red ^ black) >> 17 << 16;
	Color g = (color & (green ^ black)) >> 9 << 8;
	Color b = (color & blue ^ black) >> 1;
	return black | r | g | b;
}

#define Z_BUFFER_UNSET 9001
void ClearZBuffer()
{
	for (int i = 0; i < pixel_count; i+=8) //in groups of 8 to hint to the compiler to vectorize/SIMD the loop
	{
		z_buffer[i+0] = Z_BUFFER_UNSET;
		z_buffer[i+1] = Z_BUFFER_UNSET;
		z_buffer[i+2] = Z_BUFFER_UNSET;
		z_buffer[i+3] = Z_BUFFER_UNSET;
		z_buffer[i+4] = Z_BUFFER_UNSET;
		z_buffer[i+5] = Z_BUFFER_UNSET;
		z_buffer[i+6] = Z_BUFFER_UNSET;
		z_buffer[i+7] = Z_BUFFER_UNSET;							
	}
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

void PutPixel_ByPosition(Color color, int x, int y)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		pixels[y * WIDTH + x] = color;
}

void PutPixel_ByIndex(Color color, int i)
{
	if (i >= 0 && i < pixel_count)
		pixels[i] = color;
}

void DrawHorizontalSegment(Color color, int y, int x1, int x2)
{
	int pixel_row = y * WIDTH;

	for (int i = pixel_row + x1; i <= pixel_row + x2; i++)
	{
		int x = i - pixel_row;
		PutPixel_ByPosition(color, x, y);
	}
}


Color LerpColor(Color a, Color b, float t)
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

void DrawSprite(int _x, int _y, Bitmap sprite)
{
	for (int x = 0; x < sprite.width; ++x)
	{
		for (int y = 0; y < sprite.height; ++y)
		{
			PutPixel_ByPosition(sprite.pixels[y*sprite.width+x], x+_x, y+_y);
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

Vec3 CameraSpaceToClipSpace(Vec3 v)
{
	Vec4 v_4 = { v.x, v.y, v.z, 1 };
	v_4 = Transform_v4(camera_to_clip, v_4); //Projection

	v.x = v_4.x;
	v.y = v_4.y;
	v.z = v_4.z;

	if (v_4.w != 0)
	{
		v.x /= v_4.w;
		v.y /= v_4.w;
		v.z /= v_4.w;
	}

	return v;
}

Vec3 ClipSpaceToScreenSpace(Vec3 v)
{
	//place origin at center of screen
	v.x++;
	v.y++;

	//scale space to fill screen
	v.x *= WIDTH / 2;
	v.y *= HEIGHT / 2;

	return v;
}

void FillVerticalGradient(Color color1, Color color2)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		Color color = LerpColor(color1, color2, y / (float)HEIGHT);
		int o = y*WIDTH;
		Color* p = &pixels[o];
		Color* p_end = &pixels[o+WIDTH];
		while(p < p_end)
			*p++ = color;
	}
}

void FillHorizontalGradient(Color color1, Color color2)
{
	for (int x = 0; x < WIDTH; x++)
	{
		Color color = LerpColor(color1, color2, x / (float)WIDTH);
		pixels[x] = color;
	}

	for (int y = 1; y < HEIGHT; y++)
		memcpy(&pixels[y*WIDTH], &pixels[(y-1)*WIDTH], 4*WIDTH);

}

Color BlendColor(Color s, Color d)
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

void DrawHorizontal(Color color, int y)
{
	for (int i = y * WIDTH; i < y * WIDTH + WIDTH; i++)
		PutPixel_ByIndex(color, i);
}

void DrawLine(Color color, float x1, float y1, float x2, float y2)
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

void DrawRectangle(Color color, float x, float y, float width, float height)
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

void FillRectangle_Blend(Color color, int x, int y, int width, int height)
{
	for (int _x = 0; _x < width; _x++)
	{
		for (int _y = 0; _y < height; _y++)
		{
			PutPixel_ByPosition(BlendColor(color, pixels[(y + _y) * WIDTH + (x + _x)]), _x + x, _y + y);
		}
	}
}

void  DrawHorizontal_Blend(Color color, int y)
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

void FillFlatBottom(Color color, int bottom, int left, int right, int top, int middle)
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

void FillFlatTop(Color color, int top, int left, int right, int bottom, int middle)
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

void FillTriangle(Color color, int x1, int y1, int x2, int y2, int x3, int y3)
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

void FillTriangle_VertexColors(Vec3 a, Vec3 b, Vec3 c, Color a_color, Color b_color, Color c_color)
{
	int x_min = (int)GetMin3(a.x, b.x, c.x);
	int y_min = (int)GetMin3(a.y, b.y, c.y);
	int x_max = (int)roundf(GetMax3(a.x, b.x, c.x));
	int y_max = (int)roundf(GetMax3(a.y, b.y, c.y));

	Vec2 a2 = {a.x,a.y};
	Vec2 b2 = {b.x,b.y};
	Vec2 c2 = {c.x,c.y};

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			Vec3 v = ToBarycentricSpace(_x, _y, a2, b2, c2);
			bool in_triangle = !(v.x < 0 || v.y < 0 || v.z < 0);
			if (in_triangle)
			{
				Color d_color = LerpColor(c_color, a_color, v.x);
				Color e_color = LerpColor(a_color, b_color, v.y);
				Color f_color = LerpColor(e_color, d_color, v.z);
				int i = _y*WIDTH+_x;

				//TODO get correct z_buffer value
				float d_z = Lerp_Float(c.z, a.z, v.x);
				float e_z = Lerp_Float(a.z, b.z, v.y);
				float f_z = Lerp_Float(e_z, d_z, v.z);

				if (_x >= 0 && _x < WIDTH && _y >= 0 && _y < HEIGHT && f_z < z_buffer[i])
				{
					z_buffer[i] = f_z;
					pixels[i] = f_color;
				}
			}
		}
	}
}

void FillTriangle_Texture(Vec2 a, Vec2 b, Vec2 c, Vec2 a_uv, Vec2 b_uv, Vec2 c_uv, Bitmap texture)
{
	int x_min = (int)GetMin3(a.x, b.x, c.x);
	int y_min = (int)GetMin3(a.y, b.y, c.y);
	int x_max = (int)roundf(GetMax3(a.x, b.x, c.x));
	int y_max = (int)roundf(GetMax3(a.y, b.y, c.y));


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
				
				Clamp(&texture_index, 0, texture.width*texture.height - 1);				
				Color color_from_texture = texture.pixels[texture_index];
				PutPixel_ByPosition(color_from_texture, _x, _y);
			}
		}
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


#define workspace_size 50000

Vec3 vertex_workspace[workspace_size];
int index_workspace[workspace_size];
Vec2 uv_workspace[workspace_size];
Vec3 normals_workspace[workspace_size];
byte brightness[workspace_size];
byte lighting[workspace_size];

typedef struct Shader
{
	Color (*function)();
} Shader;

Shader ShadeSolidColor;
Shader ShadeVertexColors;
Shader ShadePolyColors;
Shader ShadeTexturedUnlit;
Shader ShadeGouraud;
Shader ShadeWhite;
Color (*ShadeMagoo)();
Color ReturnWhite(Vec3 v, int triangle_index, void* dont_use)
{
	return 0xFFFFFFFF;
}

Color ReturnTextureValue(Vec3 v, int triangle_index, Bitmap* texture_pointer)
{
	Bitmap texture = *texture_pointer;
	int i = triangle_index*3;
	Vec2 a_uv = uv_workspace[index_workspace[i+0]];
	Vec2 b_uv = uv_workspace[index_workspace[i+1]];
	Vec2 c_uv = uv_workspace[index_workspace[i+2]];


	Vec2 v_uv = FromBaryCentricSpace(v.x, v.y, v.z, a_uv, b_uv, c_uv);

	while(v_uv.y > 1)
		v_uv.y--;

	while(v_uv.x > 1)
		v_uv.x--;

	v_uv.x *= texture.width-1;
	v_uv.y *= texture.height-1;

	int texture_index = (int)v_uv.y*texture.width+(int)v_uv.x;

	Clamp(&texture_index, 0, texture.width*texture.height - 1);				
	Color color_from_texture = texture.pixels[texture_index];
	return color_from_texture;
}

Color ReturnColor(Vec3 v, int triangle_index, Color* color)
{
	return *color;
}

Color ReturnColor2(Vec3 v, int triangle_index, Color* color)
{
	Color c = *color;
	byte* p = (byte*)&c;
	p[0] = brightness[triangle_index] * p[0] / 255;
	p[1] = brightness[triangle_index] * p[1] / 255;
	p[2] = brightness[triangle_index] * p[2] / 255;
	return c;
}

Color VertexColor(Vec3 v, int triangle_index, Color* bo)
{
	Color result;
	byte* r_p = (byte*)(&result);
    byte* a_p = (byte*)(&bo[0]);
    byte* b_p = (byte*)(&bo[1]);
    byte* c_p = (byte*)(&bo[2]);
	r_p[0] = a_p[0]*v.x+b_p[0]*v.y+c_p[0]*v.z;
	r_p[1] = a_p[1]*v.x+b_p[1]*v.y+c_p[1]*v.z;
	r_p[2] = a_p[2]*v.x+b_p[2]*v.y+c_p[2]*v.z;
	return result;
}

Color PolyColor(Vec3 v, int triangle_index, Color* poly_colors)
{
	return poly_colors[triangle_index]; //todo fix code to account for triangles being sorted and swapped (that may need to happen in the render function rather than here)
}

Color Gouraud(Vec3 bary, int triangle_index, Color* color)
{
	int i = triangle_index*3;

	byte a_l = lighting[index_workspace[i+0]];
	byte b_l = lighting[index_workspace[i+1]];
	byte c_l = lighting[index_workspace[i+2]];

	Color a = *color, b = *color, c = *color;

	byte* p = (byte*)&a;
	p[0] = (a_l) * p[0] / 255;
	p[1] = (a_l) * p[1] / 255;
	p[2] = (a_l) * p[2] / 255;
	p = (byte*)&b;
	p[0] = (b_l) * p[0] / 255;
	p[1] = (b_l) * p[1] / 255;
	p[2] = (b_l) * p[2] / 255;
	p = (byte*)&c;
	p[0] = (c_l) * p[0] / 255;
	p[1] = (c_l) * p[1] / 255;
	p[2] = (c_l) * p[2] / 255;	

    Color result;
    byte* r_p = (byte*)(&result);
    byte* a_p = (byte*)(&a);
    byte* b_p = (byte*)(&b);
    byte* c_p = (byte*)(&c);

    r_p[0] = a_p[0] * bary.x + b_p[0] * bary.y + c_p[0] * bary.z;
    r_p[1] = a_p[1] * bary.x + b_p[1] * bary.y + c_p[1] * bary.z;
    r_p[2] = a_p[2] * bary.x + b_p[2] * bary.y + c_p[2] * bary.z;
	return result;
}


void InitShaders()
{
	ShadeSolidColor.function = &ReturnColor2;
	ShadeVertexColors.function = &VertexColor;
	ShadePolyColors.function = &PolyColor;
	ShadeGouraud.function = &Gouraud;
	ShadeTexturedUnlit.function = &ReturnTextureValue;
	ShadeWhite.function = &ReturnWhite;
}

float light_rotation = 0;
Triangle triangle_workspace[50000];


void RenderTriangle(Vec3 a, Vec3 b, Vec3 c, int triangle_index, Shader shader, void* shader_state)
{
	int x_min = (int)GetMin3(a.x, b.x, c.x);
	int y_min = (int)GetMin3(a.y, b.y, c.y);
	int x_max = (int)(GetMax3(a.x, b.x, c.x));
	int y_max = (int)(GetMax3(a.y, b.y, c.y));

	Clamp(&x_min, 0, WIDTH-1);
	Clamp(&x_max, 0, WIDTH-1);
	Clamp(&y_min, 0, HEIGHT-1);
	Clamp(&y_max, 0, HEIGHT-1);

	Vec2 a2 = (Vec2){a.x,a.y};
	Vec2 b2 = (Vec2){b.x,b.y};
	Vec2 c2 = (Vec2){c.x,c.y};

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			Vec3 v = ToBarycentricSpace(_x, _y, a2,b2,c2);
			bool in_triangle = !(v.x < 0 || v.y < 0 || v.z < 0);
			if(in_triangle)
			{
				int i = _y * WIDTH + _x;

				//TODO get correct z_buffer value
				float d_z = Lerp_Float(c.z, a.z, v.x);
				float e_z = Lerp_Float(a.z, b.z, v.y);
				float f_z = Lerp_Float(e_z, d_z, v.z);


				pixels[i] = (f_z >= z_buffer[i]) ? pixels[i] : shader.function(v, triangle_index, shader_state);
				z_buffer[i] = (f_z >= z_buffer[i]) ? z_buffer[i] : f_z;
			}
		}
	}	
}

void RenderMesh(Mesh mesh, Transform object_transform, Transform camera, Shader shader, void* shader_state) //canonical
{
	int triangle_count = mesh.indices_length / 3;

	memcpy(vertex_workspace, mesh.vertices, mesh.vertices_length*sizeof(Vec3));
	memcpy(index_workspace, mesh.indices, mesh.indices_length*sizeof(int));
	memcpy(uv_workspace, mesh.uvs, mesh.uvs_length*sizeof(Vec2));
	memcpy(normals_workspace, mesh.normals, mesh.normals_length*sizeof(Vec3));

	TriangleIndices* triangle_workspace = (TriangleIndices*)index_workspace;

	//get object transform matrix
	m4x4 object_to_world = GetMatrix(object_transform);

	//get camera matrix
	//TODO simplify getting camera matrix
	Transform camera_position = DefaultTransform();
	Transform camera_rotation = DefaultTransform();
	camera_position.position = NegateVector(camera.position);
	camera_rotation.rotation = NegateVector(camera.rotation);
	m4x4 move = GetMatrix(camera_position);
	m4x4 rotation = GetMatrix(camera_rotation);
	m4x4 world_to_camera = Concatenate(move, rotation);

	m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

	//To Camera Space
	{
		for (int i = 0; i < mesh.vertices_length; i++)
			vertex_workspace[i] = Transform_v3(object_to_camera, vertex_workspace[i]);
	}

	//Cull Backfaces
	{
		for (int i = 0; i < triangle_count;)
		{
			TriangleIndices t = triangle_workspace[i];
			Vec3 a = v3_Subtract(vertex_workspace[t.b], vertex_workspace[t.a]);
			Vec3 b = v3_Subtract(vertex_workspace[t.c], vertex_workspace[t.a]);
			Vec3 normal = v3_Normalized(CrossProduct(a, b));
			Vec3 eye = v3_zero;
			Vec3 from_camera_to_triangle = (v3_Subtract(vertex_workspace[t.a], eye));

			if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
				triangle_workspace[i] = triangle_workspace[--triangle_count];
			else
			{
				Vec3 backward = { 0,0,-1 };

				float dot = v3_DotProduct(normal, Transform_v3(Rotation(0, light_rotation, 0), backward));

				if (dot < 0)
					dot = 0;

				if (!isnan(dot))//TODO - remove, just a temporary fix
					brightness[i] = (unsigned char)(dot * 255);
				else
					brightness[i] = 0;
				i++;					
			}
		}
	}

	//Perform Lighting
	{
		for (int i = 0; i < mesh.normals_length; ++i)
		{
				Vec3 backward = { 0,0,-1 };

				float dot = v3_DotProduct(normals_workspace[i], Transform_v3(Rotation(0, light_rotation, 0), backward));

				if (dot < 0)
					dot = 0;

				if (!isnan(dot))//TODO - remove, just a temporary fix
					lighting[i] = (byte)(dot * 255);
				else
					lighting[i] = 0;
		}
	}

	//To Clip Space
	{
		static float near_plane = 1.0f;
		static float far_plane = 5000;
		static float field_of_view = Tau / 6.0f;

		float aspect_ratio = HEIGHT / (float) WIDTH;
		float zoom = (float)(1 / tan(field_of_view / 2));

		for (int i = 0; i < mesh.vertices_length; i++)
		{
			Vec3 v = vertex_workspace[i];
			v.x /= v.z;
			v.y /= v.z;

			v.x *= aspect_ratio * zoom;
			v.y *= -zoom;
			v.z = 2 * ((v.z - near_plane) / (far_plane - near_plane)) - 1; 
			vertex_workspace[i] = v;
		}
	}

	//Perform Clipping
	{
		for (int i = 0; i < triangle_count;)
		{
			TriangleIndices t = triangle_workspace[i];

			bool is_left_clipped = vertex_workspace[t.a].x < -1 && vertex_workspace[t.b].x < -1 && vertex_workspace[t.c].x < -1;
			bool is_right_clipped = vertex_workspace[t.a].x > 1 && vertex_workspace[t.b].x > 1 && vertex_workspace[t.c].x > 1;
			bool is_bottom_clipped = vertex_workspace[t.a].y < -1 && vertex_workspace[t.b].y < -1 && vertex_workspace[t.c].y < -1;
			bool is_top_clipped = vertex_workspace[t.a].y > 1 && vertex_workspace[t.b].y > 1 && vertex_workspace[t.c].y > 1;					
			bool is_near_clipped = vertex_workspace[t.a].z < -1 && vertex_workspace[t.b].z < -1 && vertex_workspace[t.c].z < -1;
			bool is_far_clipped = vertex_workspace[t.a].z  > 1 && vertex_workspace[t.b].z > 1 && vertex_workspace[t.c].z > 1;

			if(is_left_clipped || is_right_clipped || is_top_clipped || is_bottom_clipped || is_near_clipped ||is_far_clipped)
			{
				triangle_workspace[i] = triangle_workspace[--triangle_count];
				brightness[i] = brightness[triangle_count];
			}
			else
				i++;
		}

		//TODO actually cut triangles that are partially clipped, rather than removing triangles that are wholly outside the clip box
	}

	//To Screen Space
	{
		for (int i = 0; i < mesh.vertices_length; i++)
		{
			//place origin at center of screen
			vertex_workspace[i].x++;
			vertex_workspace[i].y++;

			//scale space to fill screen
			vertex_workspace[i].x *= WIDTH / 2;
			vertex_workspace[i].y *= HEIGHT / 2;
		}
	}

	//Rasterize
	{
		for (int i = 0; i < triangle_count; ++i)
		{
			TriangleIndices t = triangle_workspace[i];
			RenderTriangle(vertex_workspace[t.a], vertex_workspace[t.b], vertex_workspace[t.c], i, shader, shader_state);
		}
	}
}

void RenderTexturedMesh(Mesh mesh, Transform object_transform, Transform camera, Bitmap texture)
{
	//if (mesh.indices?.Length > 0) //TODO?
	{
		size_t triangle_count = mesh.indices_length / 3;

		//fill triangle list
		{
			int i;
			for (i = 0; i < triangle_count; i++)
			{
				triangle_workspace[i].a = mesh.vertices[mesh.indices[i * 3 + 0]];
				triangle_workspace[i].b = mesh.vertices[mesh.indices[i * 3 + 1]];
				triangle_workspace[i].c = mesh.vertices[mesh.indices[i * 3 + 2]];
				triangle_workspace[i].a_uv = mesh.uvs[mesh.uv_indices[i * 3 + 0]];
				triangle_workspace[i].b_uv = mesh.uvs[mesh.uv_indices[i * 3 + 1]];
				triangle_workspace[i].c_uv = mesh.uvs[mesh.uv_indices[i * 3 + 2]];
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
				Triangle t = triangle_workspace[i];

				//To Camera Space
				{
					t.a = Transform_v3(object_to_camera, t.a);
					t.b = Transform_v3(object_to_camera, t.b);
					t.c = Transform_v3(object_to_camera, t.c);
				}

				triangle_workspace[i] = t;
			}

			//cull backfaces and perform lighting
			{
				size_t remaining_count = triangle_count;
				for (int i = 0; i < triangle_count; i++)
				{
				label:
					if (i == remaining_count) //TODO verify no off by one error
						break;
					Triangle t = triangle_workspace[i];
					Vec3 a = v3_Subtract(t.b, t.a);
					Vec3 b = v3_Subtract(t.c, t.a);
					Vec3 normal = v3_Normalized(CrossProduct(a, b));

					Vec3 from_camera_to_triangle = v3_Normalized(v3_Subtract(t.a, camera.position));

					if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
					{
						SwapTriangles(triangle_workspace, i, remaining_count - 1);
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
							t.brightness = (byte)(dot * 255);
							triangle_workspace[i] = t;
						}

						float light = t.brightness / 255.0f;

						uint r = ((t.color & red) ^ black) >> 16;
						uint g = ((t.color & green) ^ black) >> 8;
						uint b = (t.color & blue) ^ black;

						r = (uint)(r * light);
						g = (uint)(g * light);
						b = (uint)(b * light);

						t.color = r << 16 | g << 8 | b | black;
						triangle_workspace[i] = t;
					}
				}

				triangle_count = remaining_count;
			}

			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangle_workspace[i];
				t.a = CameraSpaceToClipSpace(t.a);
				t.b = CameraSpaceToClipSpace(t.b);
				t.c = CameraSpaceToClipSpace(t.c);
				triangle_workspace[i] = t;
			}

			//Perform Clipping
			{
				for (int i = 0; i < triangle_count; i++)
				{
					my_label:
					if (i == triangle_count)
						break;					
					Triangle t = triangle_workspace[i];
					bool is_left_clipped = t.a.x < -1 && t.b.x < -1 && t.c.x < -1;
					bool is_right_clipped = t.a.x > 1 && t.b.x > 1 && t.c.x > 1;
					bool is_bottom_clipped = t.a.y < -1 && t.b.y < -1 && t.c.y < -1;
					bool is_top_clipped = t.a.y > 1 && t.b.y > 1 && t.c.y > 1;					
					bool is_near_clipped = t.a.z < -1 && t.b.z < -1 && t.c.z < -1;
					bool is_far_clipped = t.a.z  > 1 && t.b.z > 1 && t.c.z > 1;

					if(is_left_clipped || is_right_clipped || is_top_clipped || is_bottom_clipped)
					{
						triangle_workspace[i] = triangle_workspace[triangle_count-1];
						triangle_count--;
						goto my_label;
					}
				}

				//TODO actually cut triangles that are partially clipped, rather than removing triangles that are wholly outside the clip box
				//TODO near and far clipping (for some reason the clip coordinates are "wrong")
			}

			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangle_workspace[i];
				t.a = ClipSpaceToScreenSpace(t.a);
				t.b = ClipSpaceToScreenSpace(t.b);
				t.c = ClipSpaceToScreenSpace(t.c);
				triangle_workspace[i] = t;
			}				
		}

		//sort triangles by depth painter's algorithm YAY!
		{
			SortByDepth(triangle_workspace, triangle_count);
		}

		//rasterize
		{
			for (int i = 0; i < triangle_count; i++)
			{
				Triangle t = triangle_workspace[i];
				Vec2 a = { t.a.x, t.a.y };
				Vec2 b = { t.b.x, t.b.y };
				Vec2 c = { t.c.x, t.c.y };

				FillTriangle_Texture(a, b, c, t.a_uv, t.b_uv, t.c_uv, texture);
			}
		}
	}
}