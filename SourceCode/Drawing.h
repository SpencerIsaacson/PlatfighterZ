
#define red 0xFFFF0000
#define green 0xFF00FF00
#define blue 0xFF0000FF
#define cyan 0xFF00FFFF
#define magenta 0xFFFF00FF
#define yellow 0xFFFFFF00

#define black 0xFF000000
#define white 0xFFFFFFFF
#define opaque black
#define brown 0xFFA52A2A
#define purple 0xFF800080
#define transparent 0

#define gray 0xFF666666
#define grey gray

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
	for (int i = 0; i < pixel_count; i+=8)
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
	for (int x = 0; x < WIDTH; x++)
		pixels[x] = color;

	for (int y = 1; y < HEIGHT; y++)
		memcpy(&pixels[y*WIDTH], &pixels[(y-1)*WIDTH], 4*WIDTH);
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

void DrawSprite(int x, int y, Bitmap sprite)
{
	int x_min = x;
	int y_min = y;
	int x_max = x + sprite.width;
	int y_max = y + sprite.height;
	Clamp(&x_min,0,WIDTH);
	Clamp(&x_max, x_min, WIDTH);
	Clamp(&y_min,0,HEIGHT);
	Clamp(&y_max, y_min, HEIGHT);

	for (int _y = y_min; _y < y_max; _y++)
	for (int _x = x_min; _x < x_max; _x++)
	{
		{
			pixels[_y*WIDTH+_x] = sprite.pixels[(_y-y)*sprite.width+(_x-x)];
		}
	}
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

Noise()
{
	srand(10);
	for(int i = 0; i < pixel_count; i++)
	{
		byte foo =(byte)((rand()/(double)RAND_MAX) * UCHAR_MAX);;
		Color random_color;
		byte* p = (byte*)&random_color;
		p[0] = foo;
		p[1] = foo;
		p[2] = foo;
		pixels[i] = LerpColor(pixels[i], random_color,.04f);
	}
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

//TODO handle invalid file paths
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
	v3* vertices = malloc(sizeof(v3) * vertex_count);
	v2* uvs = malloc(sizeof(v2) * uv_count);
	int* indices = malloc(sizeof(int) * index_count);
	int* uv_indices = malloc(sizeof(int) * index_count);

	return_mesh.vertices = vertices;
	return_mesh.vertices_count = vertex_count;
	return_mesh.indices = indices;
	return_mesh.indices_count = index_count;
	return_mesh.uvs = uvs;
	return_mesh.uvs_count = uv_count;
	return_mesh.uv_indices = uv_indices;
	return_mesh.uv_indices_count = index_count;
	return_mesh.normals_count = 0;
	return_mesh.normals = NULL;

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
				v3 v = { x, y, z };
				return_mesh.vertices[vertex++] = v;
			} break;
			case 'u': //TODO replace with vt
			{
				token = strtok(NULL, " ");
				float u = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float v = (float)strtod(token, &ptr);
				v2 v2 = { u, v };
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
	v3* vertices = malloc(sizeof(v3) * vertex_count);
	//v2* uvs = malloc(sizeof(v2) * uv_count);
	int* indices = malloc(sizeof(int) * index_count);
	//int* uv_indices = malloc(sizeof(int) * index_count);

	return_mesh.vertices = vertices;
	return_mesh.vertices_count = vertex_count;
	return_mesh.indices = indices;
	return_mesh.indices_count = index_count;
	return_mesh.uvs = NULL;
	return_mesh.uvs_count = 0;
	return_mesh.uv_indices = NULL;
	return_mesh.uv_indices_count = 0;

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
				v3 v = { x, y, z };
				return_mesh.vertices[vertex++] = v;
			} break;
			case 'u': //TODO replace with vt
			{
				token = strtok(NULL, " ");
				float u = (float)strtod(token, &ptr);
				token = strtok(NULL, " ");
				float v = (float)strtod(token, &ptr);
				v2 v2 = { u, v };
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

void DrawHorizontalSegment(Color color, int y, int x1, int x2)
{
	int pixel_row = y * WIDTH;

	for (int i = pixel_row + x1; i <= pixel_row + x2; i++)
	{
		int x = i - pixel_row;
		PutPixel_ByPosition(color, x, y);
	}
}

void DrawVertical(uint color, int x)
{
	for (int i = x; i < pixel_count - WIDTH - x; i += WIDTH)
	{
		pixels[i] = color;
	}
}

void DrawVerticalSegment(uint color, int x, int y1, int y2)
{
	for (int i = x + (y1 * WIDTH); i <= x + (y2 * WIDTH); i += WIDTH)
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

void FillAlphaChannel()
{
	for (int i = 0; i < pixel_count; i++)
	{
		pixels[i] |= opaque;
	}
}

void FillRectangle_Blend(Color color, int x, int y, int width, int height)
{
	for (int _x = 0; _x < width; _x++)
	{
		for (int _y = 0; _y < height; _y++)
		{
			if ((x + _x) >= 0 && (x + _x) < WIDTH && (y + _y) >= 0 && (y + _y) < HEIGHT)
			{
				int index = (y + _y) * WIDTH + (x + _x);
				pixels[index] = BlendColor(color, pixels[index]);
			}
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


void DrawGrid_ScreenSpace(int unit_size)
{
	for (int x = 0; x < WIDTH; x += unit_size)
	{
		DrawVertical(white, x);
	}

	for (int y = 0; y < HEIGHT; y += unit_size)
	{
		DrawHorizontal(white, y);
	}
}

void FillRectangle(uint color, float x, float y, float width, float height)
{
	int x_min = (int)x;
	int y_min = (int)y;
	int x_max = (int)(x+width);
	int y_max = (int)(y+height);
	Clamp(&x_min,0,WIDTH);
	Clamp(&x_max, x_min, WIDTH);
	Clamp(&y_min,0,HEIGHT);
	Clamp(&y_max, y_min, HEIGHT);

	for (int _x = x_min; _x < x_max; _x++)
	{
		for (int _y = y_min; _y < y_max; _y++)
		{
			pixels[_y*WIDTH+_x] = color;
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

void FillEllipse(uint color, float x, float y, float radius_x, float radius_y)
{
	int x_min = (int)roundf(x - radius_x);
	int x_max = (int)roundf(x + radius_x);
	int y_min = (int)roundf(y - radius_y);
	int y_max = (int)roundf(y + radius_y);

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			float dx = _x - x;
			float dy = _y - y;

			bool distance_less_than_radii = dx * dx * radius_y * radius_y + dy * dy * radius_x * radius_x <= radius_x * radius_x * radius_y * radius_y;

			if (distance_less_than_radii)
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

v2 FromBaryCentricSpace(float b1, float b2, float b3, v2 a, v2 b, v2 c)
{
	float v_x, v_y;

	v_x = b1*a.x + b2*b.x + b3*c.x;
	v_y = b1*a.y + b2*b.y + b3*c.y;
	v2 result = {v_x, v_y};
	return result;
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
	char* p = sprite.rows;
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
	char* p = sprite.rows;
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
		for (int o = 0; o < char_dict_count; o++)
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
		for (int o = 0; o < char_dict_count; o++)
		{
			if (a == char_dict[o])
			{
				DrawCharacter(font_set[o], x + i * 9, y);
				//todo break and see how much time is saved
			}

		}
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


#define workspace_size 100000

v3 vertex_workspace[workspace_size];
int index_workspace[workspace_size];
v2 uv_workspace[workspace_size];
int uv_index_workspace[workspace_size];
v3 normals_workspace[workspace_size];
byte brightness[workspace_size];
byte lighting[workspace_size];




Color ShadeWhite(v3 v, int triangle_index, void* dont_use)
{
	return 0xFFFFFFFF;
}

Color ShadeTexturedUnlit(v3 v, int triangle_index, void* texture_pointer)
{
	Bitmap texture = *((Bitmap*)texture_pointer);
	int i = triangle_index*3;

	v2 a_uv = uv_workspace[uv_index_workspace[i+0]];
	v2 b_uv = uv_workspace[uv_index_workspace[i+1]];
	v2 c_uv = uv_workspace[uv_index_workspace[i+2]];

	v2 v_uv = FromBaryCentricSpace(v.x, v.y, v.z, a_uv, b_uv, c_uv);

	v_uv.y = 1-v_uv.y;
	v_uv.x *= texture.width-1;
	v_uv.y *= texture.height-1;
	
	int texture_index = (int)v_uv.y*texture.width+(int)v_uv.x;

	Clamp(&texture_index, 0, texture.width*texture.height - 1);
	return texture.pixels[texture_index];
}

Color ShadeSolidColor(v3 v, int triangle_index, void* color)
{
	return *((Color*)color);
}

Color ShadeColorFlatShaded(v3 v, int triangle_index, void* color)
{
	Color c = *((Color*)color);
	byte* p = (byte*)&c;
	p[0] = brightness[triangle_index] * p[0] / 255;
	p[1] = brightness[triangle_index] * p[1] / 255;
	p[2] = brightness[triangle_index] * p[2] / 255;
	return c;
}

Color ShadeVertexColors(v3 v, int triangle_index, void* colors)
{
	Color result;
	byte* r_p = (byte*)(&result);
    byte* a_p = (byte*)(&(((Color*)colors)[0]));
    byte* b_p = (byte*)(&(((Color*)colors)[1]));
    byte* c_p = (byte*)(&(((Color*)colors)[2]));
	r_p[0] = a_p[0]*v.x+b_p[0]*v.y+c_p[0]*v.z;
	r_p[1] = a_p[1]*v.x+b_p[1]*v.y+c_p[1]*v.z;
	r_p[2] = a_p[2]*v.x+b_p[2]*v.y+c_p[2]*v.z;
	return result;
}

Color ShadePolyColors(v3 v, int triangle_index, void* poly_colors)
{
	return ((Color*)poly_colors)[triangle_index]; //todo fix code to account for triangles being sorted and swapped (that may need to happen in the render function rather than here)
}

Color ShadeColorGouraud(v3 bary, int triangle_index, void* color)
{
	int i = triangle_index*3;

	byte a_l = lighting[index_workspace[i+0]];
	byte b_l = lighting[index_workspace[i+1]];
	byte c_l = lighting[index_workspace[i+2]];

	int ambient = 100;
	if(a_l < ambient)
		a_l = ambient;
	if(b_l < ambient)
		b_l = ambient;	
	if(c_l < ambient)
		c_l = ambient;

	Color a = *((Color*)color), b = *((Color*)color), c = *((Color*)color);

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

Color ShadeTexturedGouraud(v3 v, int triangle_index, void* texture_pointer)
{
	Color result = ShadeTexturedUnlit(v, triangle_index, texture_pointer);
	result = ShadeColorGouraud(v, triangle_index, &result);
	return result;
}

Color ShadeTexturedGouraudColorMasked(v3 v, int triangle_index, void* material)
{

	typedef struct
	{
		Color tint;
		Bitmap color;
		Bitmap mask;
	} Material;

	Material mat = *((Material*)material);

	int i = triangle_index*3;

	v2 a_uv = uv_workspace[uv_index_workspace[i+0]];
	v2 b_uv = uv_workspace[uv_index_workspace[i+1]];
	v2 c_uv = uv_workspace[uv_index_workspace[i+2]];

	v2 v_uv = FromBaryCentricSpace(v.x, v.y, v.z, a_uv, b_uv, c_uv);

	v_uv.y = 1-v_uv.y;
	v_uv.x *= mat.mask.width-1;
	v_uv.y *= mat.mask.height-1;
	
	int texture_index = (int)v_uv.y*mat.mask.width+(int)v_uv.x;

	Clamp(&texture_index, 0, mat.mask.width*mat.mask.height - 1);
	
	Color result = black;
	if(mat.mask.pixels[texture_index] == white)
		result = mat.tint;
	else
		result = ShadeTexturedUnlit(v, triangle_index, &mat.color);

	result = ShadeColorGouraud(v, triangle_index, &result);
	return result;
}

Color ShadeSkinWeights(v3 v, int triangle_index, void* material)
{
	return white;
}

Color ShadeTexturedFlatShaded(v3 v, int triangle_index, void* texture_pointer)
{
	Color result = ShadeTexturedUnlit(v, triangle_index, texture_pointer);
	result = ShadeColorFlatShaded(v, triangle_index, &result);
	return result;
}

float light_rotation = 0;


Color ShadeTexturedNormalMapped(v3 v, int triangle_index, void* shader_state)
{
	typedef struct FooStruct
	{
		Bitmap color_map;
		Bitmap normal_map;
		v3 rotation;
	} FooStruct;

	FooStruct* foos = (FooStruct*)shader_state;



	Bitmap* texture_maps = (Bitmap*)shader_state;
	Bitmap color_map = foos -> color_map;
	Bitmap normal_map = foos -> normal_map;
	v3 rotation  = foos -> rotation;

	int i = triangle_index*3;

	v2 a_uv = uv_workspace[uv_index_workspace[i+0]];
	v2 b_uv = uv_workspace[uv_index_workspace[i+1]];
	v2 c_uv = uv_workspace[uv_index_workspace[i+2]];

	v2 v_uv = FromBaryCentricSpace(v.x, v.y, v.z, a_uv, b_uv, c_uv);
	v2 v_uv_color = v_uv;
	v2 v_uv_normal = v_uv;
	v_uv_normal.y = 1-v_uv.y;
	v_uv_normal.x *= normal_map.width-1;
	v_uv_normal.y *= normal_map.height-1;
	
	int texture_index = (int)v_uv_normal.y*normal_map.width+(int)v_uv_normal.x;

	Clamp(&texture_index, 0, normal_map.width*normal_map.height - 1);
	Color normal_color = normal_map.pixels[texture_index];

	byte* color_channels = (byte*)&normal_color;

	v3 normal;
	normal.x = color_channels[2] / 128.0f - 1;
	normal.y = color_channels[1] / 128.0f - 1;
	normal.z = color_channels[0] / 128.0f - 1;


	v3 backward = { 0,0,-1 };
	v3 light_vector = Transform_v3(Rotation(0, light_rotation, 0), backward);

	float dot = v3_DotProduct(normal, light_vector); //TODO account for transform hierarchies and local space

	if (dot < 0)
	dot = 0;
	byte lighting;
	if (!isnan(dot))//TODO - remove, just a temporary fix
	{
		lighting = (byte)(dot * 255);
	}
	else
		lighting = 0;

	v_uv_color.y = 1-v_uv.y;
	v_uv_color.x *= color_map.width-1;
	v_uv_color.y *= color_map.height-1;
	
	texture_index = (int)v_uv_color.y*color_map.width+(int)v_uv_color.x;

	Clamp(&texture_index, 0, color_map.width*color_map.height - 1);
	Color color = color_map.pixels[texture_index];
	color_channels = (byte*)&color;
	color_channels[0] = lighting * color_channels[0] / 255;
	color_channels[1] = lighting * color_channels[1] / 255;
	color_channels[2] = lighting * color_channels[2] / 255;
	return color;	
}

void RenderTriangle(v3 a, v3 b, v3 c, int triangle_index, Shader shader, void* shader_state)
{
	int x_min = (int)GetMin3(a.x, b.x, c.x);
	int y_min = (int)GetMin3(a.y, b.y, c.y);
	int x_max = (int)GetMax3(a.x, b.x, c.x);
	int y_max = (int)GetMax3(a.y, b.y, c.y);

	Clamp(&x_min, 0, WIDTH-1);
	Clamp(&x_max, 0, WIDTH-1);
	Clamp(&y_min, 0, HEIGHT-1);
	Clamp(&y_max, 0, HEIGHT-1);

	v2 a2 = (v2){a.x,a.y};
	v2 b2 = (v2){b.x,b.y};
	v2 c2 = (v2){c.x,c.y};

	for (int _x = x_min; _x <= x_max; _x++)
	{
		for (int _y = y_min; _y <= y_max; _y++)
		{
			v3 v = ToBarycentricSpace(_x, _y, a2,b2,c2);
			bool in_triangle = !(v.x < 0 || v.y < 0 || v.z < 0);
			if(in_triangle)
			{
				int i = _y * WIDTH + _x;

				//get interpolated z value of current pixel
			    float depth = a.z * v.x + b.z * v.y + c.z * v.z;

				if(depth <= z_buffer[i])
				{
					pixels[i] = shader(v, triangle_index, shader_state);
					z_buffer[i] = depth;
				}
			}
		}
	}	
}

Mesh AppendMesh(Mesh a, Mesh b)
{	
	Mesh c;
	c.normals_count = 0;
	c.uvs_count = a.uvs_count+b.uvs_count;
	c.uv_indices_count = a.uv_indices_count+b.uv_indices_count;
 	c.vertices_count = a.vertices_count+b.vertices_count;
    c.indices_count = a.indices_count+b.indices_count;
    
	c.vertices = malloc(c.vertices_count*sizeof(v3));
    c.indices = malloc(c.indices_count*sizeof(int));
    c.uvs = malloc(c.uvs_count*sizeof(v2));
    c.uv_indices = malloc(c.uv_indices_count*sizeof(int));
    for (int i = 0; i < a.vertices_count; ++i)
    	c.vertices[i] = a.vertices[i];

    for (int i = 0; i < b.vertices_count; ++i)
    	c.vertices[i+a.vertices_count] = b.vertices[i];

    for (int i = 0; i < a.indices_count; ++i)
    	c.indices[i] = a.indices[i];

    for (int i = 0; i < b.indices_count; ++i)
    	c.indices[i+a.indices_count] = b.indices[i] + a.vertices_count;


	for (int i = 0; i < a.uvs_count; ++i)
		c.uvs[i] = a.uvs[i];

    for (int i = 0; i < b.uvs_count; ++i)
    	c.uvs[i+a.uvs_count] = b.uvs[i];


	for (int i = 0; i < a.uv_indices_count; ++i)
		c.uv_indices[i] = a.uv_indices[i];

    for (int i = 0; i < b.uv_indices_count; ++i)
    	c.uv_indices[i+a.uv_indices_count] = b.uv_indices[i]+ a.uvs_count;

    return c;
}

void RecalculateNormals(Mesh* mesh)
{
	if(false)//if((*mesh).normals_count > 0)
	{
		if((*mesh).normals_count != (*mesh).vertices_count)
		{
			(*mesh).normals_count = (*mesh).vertices_count;
			(*mesh).normals = realloc((*mesh).normals, (*mesh).normals_count*sizeof(v3));
		}
	}
	else
	{
		(*mesh).normals_count = (*mesh).vertices_count;
		(*mesh).normals = malloc((*mesh).normals_count*sizeof(v3));
	}

	TriangleIndices* triangles = (TriangleIndices*)(*mesh).indices;
	int triangle_count = (*mesh).indices_count/3;

	for (int i = 0; i < triangle_count; i++)
	{
		TriangleIndices t = triangles[i];
		v3 a = v3_Subtract((*mesh).vertices[t.b], (*mesh).vertices[t.a]);
		v3 b = v3_Subtract((*mesh).vertices[t.c], (*mesh).vertices[t.a]);
		v3 normal = v3_Normalized(v3_CrossProduct(a, b));

		(*mesh).normals[t.a] = v3_Add((*mesh).normals[t.a], normal);
		(*mesh).normals[t.b] = v3_Add((*mesh).normals[t.b], normal);
		(*mesh).normals[t.c] = v3_Add((*mesh).normals[t.c], normal);
	}

	for (int i = 0; i < (*mesh).normals_count; ++i)
		(*mesh).normals[i] = v3_Normalized((*mesh).normals[i]);
}

void DrawUVMap(Mesh mesh, float scale)
{
	for (int i = 0; i < mesh.uv_indices_count; i += 3)
	{
		v2 a = mesh.uvs[mesh.uv_indices[i+0]];
		v2 b = mesh.uvs[mesh.uv_indices[i+1]];
		v2 c = mesh.uvs[mesh.uv_indices[i+2]];

		a.x *= scale;
		a.y *= -scale;
		
		b.x *= scale;
		b.y *= -scale;
		
		c.x *= scale;
		c.y *= -scale;
		
		a.y += scale;
		b.y += scale;
		c.y += scale;

		DrawLine(green, a.x, a.y, b.x, b.y);
		DrawLine(green, b.x, b.y, c.x, c.y);
		DrawLine(green, a.x, a.y, c.x, c.y);
	}

	for (int i = 0; i < mesh.uvs_count; ++i)
	{
		v2 uv = mesh.uvs[i];
		uv.x *= scale;
		uv.y *= -scale;
		uv.y += scale;
		FillRectangle(blue,uv.x-2,uv.y-2,4,4);
	}

}


bool perform_backface_culling = true;
bool perform_clipping = true;
bool orthographic = false;

Triangle render_workspace[workspace_size];

m4x4 ObjectToClipMatrix(Transform object_transform, Transform camera)
{
		//get object transform matrix
		m4x4 object_to_world = GetMatrix(object_transform);

		//get camera matrix
		//TODO simplify getting camera matrix
		Transform camera_position = DefaultTransform();
		Transform camera_rotation = DefaultTransform();
		camera_position.position = v3_NegateVector(camera.position);
		camera_rotation.rotation = v3_NegateVector(camera.rotation);
		m4x4 move = GetMatrix(camera_position);
		m4x4 rotation = GetMatrix(camera_rotation);
		m4x4 world_to_camera = Concatenate(move, rotation);

		m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);
		m4x4 object_to_clip = Concatenate(object_to_camera, camera_to_clip);	
}

void RenderMesh(Mesh mesh, Transform object_transform, Transform camera, Shader shader, void* shader_state) //canonical
{
	int triangle_count = mesh.indices_count / 3;
	TriangleIndices* triangle_workspace = (TriangleIndices*)index_workspace;
	TriangleIndices* uv_triangle_workspace = (TriangleIndices*)uv_index_workspace;
	
	//Fill Triangle Data
	{
		// for (int i = 0; i < triangle_count; ++i)
		// {
		// 	Triangle t;
		// 	t.a.position = mesh.vertices[mesh.indices[i*3]];
		// 	t.b.position = mesh.vertices[mesh.indices[i*3+1]];
		// 	t.c.position = mesh.vertices[mesh.indices[i*3+2]];
		// 	t.a.uv
		// 	render_workspace[i] = t;
		// }
	}

	//Get Working Copy Of Mesh Data
	{
		memcpy(vertex_workspace, mesh.vertices, mesh.vertices_count*sizeof(v3));
		memcpy(index_workspace, mesh.indices, mesh.indices_count*sizeof(int));
		memcpy(uv_workspace, mesh.uvs, mesh.uvs_count*sizeof(v2));
		memcpy(uv_index_workspace, mesh.uv_indices, mesh.uv_indices_count*sizeof(int));
		memcpy(normals_workspace, mesh.normals, mesh.normals_count*sizeof(v3));
		memset(lighting,0,workspace_size);
	}

	//get object transform matrix
	m4x4 object_to_world = GetMatrix(object_transform);

	//get camera matrix
	//TODO simplify getting camera matrix
	Transform camera_position = DefaultTransform();
	Transform camera_rotation = DefaultTransform();
	camera_position.position = v3_NegateVector(camera.position);
	camera_rotation.rotation = v3_NegateVector(camera.rotation);
	m4x4 move = GetMatrix(camera_position);
	m4x4 rotation = GetMatrix(camera_rotation);
	m4x4 world_to_camera = Concatenate(move, rotation);

	m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

	//To Camera Space
	{
		for (int i = 0; i < mesh.vertices_count; i++)
			vertex_workspace[i] = Transform_v3(object_to_camera, vertex_workspace[i]);
	}

	if(perform_backface_culling)
	{
		//Cull Backfaces
		{
			for (int i = 0; i < triangle_count;)
			{
				TriangleIndices t = triangle_workspace[i];
				v3 a = v3_Subtract(vertex_workspace[t.b], vertex_workspace[t.a]);
				v3 b = v3_Subtract(vertex_workspace[t.c], vertex_workspace[t.a]);
				v3 normal = v3_Normalized(v3_CrossProduct(a, b));
				v3 eye = v3_zero;
				v3 from_camera_to_triangle = (v3_Subtract(vertex_workspace[t.a], eye));

				if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
				{
					triangle_workspace[i] = triangle_workspace[--triangle_count];
					uv_triangle_workspace[i] = uv_triangle_workspace[triangle_count];
				}
				else
				{
					v3 backward = { 0,0,-1 };
					v3 light_vector = Transform_v3(Rotation(0, light_rotation, 0), backward);
					float dot = v3_DotProduct(Transform_v3(Rotation(object_transform.rotation.x,object_transform.rotation.y,object_transform.rotation.z), normal), light_vector); //TODO account for transform hierarchies and local space

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
	}

	//To Clip Space
	{
		static float near_plane = 4.0f;
		static float far_plane = 5000;
		static float field_of_view = Tau / 6.0f;

		float aspect_ratio = HEIGHT / (float) WIDTH;
		float zoom = (float)(1 / tan(field_of_view / 2));

		for (int i = 0; i < mesh.vertices_count; i++)
		{
			v3 v = vertex_workspace[i];
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
				uv_triangle_workspace[i] = uv_triangle_workspace[triangle_count];
				brightness[i] = brightness[triangle_count];
			}
			else
				i++;
		}

		//TODO actually cut triangles that are partially clipped, rather than removing triangles that are wholly outside the clip box
	}

	//Perform Lighting
	{
		//TODO make lighting respect camera orientation
		for (int i = 0; i < mesh.normals_count; ++i)
		{
				v3 backward = { 0,0,-1 };
				v3 light_vector = Transform_v3(Rotation(0, light_rotation, 0), backward);
				
				float dot = v3_DotProduct(Transform_v3(Rotation(object_transform.rotation.x,object_transform.rotation.y,object_transform.rotation.z), normals_workspace[i]), light_vector); //TODO account for transform hierarchies and local space

				if (dot < 0)
					dot = 0;

				if (!isnan(dot))//TODO - remove, just a temporary fix
				{
					lighting[i] = (byte)(dot * 255);
				}
				else
					lighting[i] = 0;
		}
	}

	//To Screen Space
	{
		for (int i = 0; i < mesh.vertices_count; i++)
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


void RenderMeshFromMatrix(Mesh mesh, m4x4 object_to_world, Transform camera, Shader shader, void* shader_state) //canonical
{
	int triangle_count = mesh.indices_count / 3;
	TriangleIndices* triangle_workspace = (TriangleIndices*)index_workspace;
	TriangleIndices* uv_triangle_workspace = (TriangleIndices*)uv_index_workspace;
	
	//Fill Triangle Data
	{
		// for (int i = 0; i < triangle_count; ++i)
		// {
		// 	Triangle t;
		// 	t.a.position = mesh.vertices[mesh.indices[i*3]];
		// 	t.b.position = mesh.vertices[mesh.indices[i*3+1]];
		// 	t.c.position = mesh.vertices[mesh.indices[i*3+2]];
		// 	t.a.uv
		// 	render_workspace[i] = t;
		// }
	}
	//Get Working Copy Of Mesh Data
	{
		memcpy(vertex_workspace, mesh.vertices, mesh.vertices_count*sizeof(v3));
		memcpy(index_workspace, mesh.indices, mesh.indices_count*sizeof(int));
		memcpy(uv_workspace, mesh.uvs, mesh.uvs_count*sizeof(v2));
		memcpy(uv_index_workspace, mesh.uv_indices, mesh.uv_indices_count*sizeof(int));
		memcpy(normals_workspace, mesh.normals, mesh.normals_count*sizeof(v3));
		memset(lighting,0,workspace_size);
	}

	//get camera matrix
	//TODO simplify getting camera matrix
	Transform camera_position = DefaultTransform();
	Transform camera_rotation = DefaultTransform();
	camera_position.position = v3_NegateVector(camera.position);
	camera_rotation.rotation = v3_NegateVector(camera.rotation);
	m4x4 move = GetMatrix(camera_position);
	m4x4 rotation = GetMatrix(camera_rotation);
	m4x4 world_to_camera = Concatenate(move, rotation);

	m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

	//To Camera Space
	{
		for (int i = 0; i < mesh.vertices_count; i++)
			vertex_workspace[i] = Transform_v3(object_to_camera, vertex_workspace[i]);
	}

	//Cull Backfaces
	{
		for (int i = 0; i < triangle_count;)
		{
			TriangleIndices t = triangle_workspace[i];
			v3 a = v3_Subtract(vertex_workspace[t.b], vertex_workspace[t.a]);
			v3 b = v3_Subtract(vertex_workspace[t.c], vertex_workspace[t.a]);
			v3 normal = v3_Normalized(v3_CrossProduct(a, b));
			v3 eye = v3_zero;
			v3 from_camera_to_triangle = (v3_Subtract(vertex_workspace[t.a], eye));

			if (v3_DotProduct(normal, from_camera_to_triangle) > 0)
			{
				triangle_workspace[i] = triangle_workspace[--triangle_count];
				uv_triangle_workspace[i] = uv_triangle_workspace[triangle_count];
			}
			else
			{
				v3 backward = { 0,0,-1 };
				v3 light_vector = Transform_v3(Rotation(0, light_rotation, 0), backward);
				float dot = v3_DotProduct(normal, light_vector); //TODO account for transform hierarchies and local space

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

	//To Clip Space
	{
		//TODO replace with projection matrix so you can swap projections at run time (I need an orthographic projection, for instance)
		static float near_plane = 1.0f;
		static float far_plane = 5000;
		static float field_of_view = Tau / 6.0f;

		float aspect_ratio = HEIGHT / (float) WIDTH;
		float zoom = (float)(1 / tan(field_of_view / 2));

		for (int i = 0; i < mesh.vertices_count; i++)
		{
			if(orthographic){
				vertex_workspace[i] = Transform_v3(camera_to_clip, vertex_workspace[i]);
			}
			else //TODO set up a proper perspective projection matrix function so you can still use the camera_to_clip matrix.
			{
				v3 v = vertex_workspace[i];
				v.x /= v.z;
				v.y /= v.z;

				v.x *= aspect_ratio * zoom;
				v.y *= -zoom;
				v.z = 2 * ((v.z - near_plane) / (far_plane - near_plane)) - 1; 
				vertex_workspace[i] = v;
			}
		}
	}

	if(perform_clipping)
	{	
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
					uv_triangle_workspace[i] = uv_triangle_workspace[triangle_count];
					brightness[i] = brightness[triangle_count];
				}
				else
					i++;
			}

			//TODO actually cut triangles that are partially clipped, rather than removing triangles that are wholly outside the clip box
		}
	}

	//Perform Lighting
	{
		//TODO make lighting respect camera orientation
		for (int i = 0; i < mesh.normals_count; ++i)
		{
				v3 backward = { 0,0,-1 };
				v3 light_vector = Transform_v3(Rotation(0, light_rotation, 0), backward);
				
				float dot = v3_DotProduct(Transform_v3(Rotation(object_to_world.m11,object_to_world.m21,object_to_world.m31), normals_workspace[i]), light_vector); //TODO account for transform hierarchies and local space

				if (dot < 0)
					dot = 0;

				if (!isnan(dot))//TODO - remove, just a temporary fix
				{
					lighting[i] = (byte)(dot * 255);
				}
				else
					lighting[i] = 0;
		}
	}

	//To Screen Space
	{
		for (int i = 0; i < mesh.vertices_count; i++)
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


void RenderHitbox(RectangleF rect, Transform object_transform, Transform camera, Color color)
{
	m4x4 object_to_world = GetMatrix(object_transform);

	//get camera matrix
	//TODO simplify getting camera matrix
	Transform camera_position = DefaultTransform();
	Transform camera_rotation = DefaultTransform();
	camera_position.position = v3_NegateVector(camera.position);
	camera_rotation.rotation = v3_NegateVector(camera.rotation);
	m4x4 move = GetMatrix(camera_position);
	m4x4 rotation = GetMatrix(camera_rotation);
	m4x4 world_to_camera = Concatenate(move, rotation);

	m4x4 object_to_camera = Concatenate(object_to_world, world_to_camera);

	PointRectangle point_rect;
	v3* p = (v3*)&point_rect;

	//To Camera Space
	{
		float half_width = rect.width/2;
		float half_height = rect.height/2;
		point_rect.top_left = Transform_v3(object_to_camera, (v3){ rect.x-half_width, rect.y+half_height, 0 });
		point_rect.top_right = Transform_v3(object_to_camera, (v3){ rect.x+half_width, rect.y+half_height, 0 });
		point_rect.bottom_left = Transform_v3(object_to_camera, (v3){ rect.x-half_width, rect.y-half_height, 0 });
		point_rect.bottom_right = Transform_v3(object_to_camera, (v3){ rect.x+half_width, rect.y-half_height, 0 });
	}

	//To Clip Space
	{
		//TODO replace with projection matrix so you can swap projections at run time (I need an orthographic projection, for instance)
		static float near_plane = 1.0f;
		static float far_plane = 5000;
		static float field_of_view = Tau / 6.0f;

		float aspect_ratio = HEIGHT / (float) WIDTH;
		float zoom = (float)(1 / tan(field_of_view / 2));

		for (int i = 0; i < 4; i++)
		{
			v3 v = p[i];
			v.x /= v.z;
			v.y /= v.z;

			v.x *= aspect_ratio * zoom;
			v.y *= -zoom;
			v.z = 2 * ((v.z - near_plane) / (far_plane - near_plane)) - 1; 
			p[i] = v;
		}
	}

	//To Screen Space
	{
		for (int i = 0; i < 4; i++)
		{
			//place origin at center of screen
			p[i].x++;
			p[i].y++;

			//scale space to fill screen
			p[i].x *= WIDTH / 2;
			p[i].y *= HEIGHT / 2;
		}
	}

	v3 center = v3_Divide(v3_Add(point_rect.top_left, point_rect.bottom_right), 2);
	//Rasterize
	{
		DrawLine(color, p[0].x, p[0].y, p[1].x, p[1].y);

		DrawLine(color, p[0].x, p[0].y, p[2].x, p[2].y);
		DrawLine(color, p[2].x, p[2].y, p[3].x, p[3].y);
		DrawLine(color, p[1].x, p[1].y, p[3].x, p[3].y);
		float radius = 3;
		//radius = 100/v3_Distance(object_transform.position, camera.position);
		Color darker = Darker(color);
		FillCircle(darker, p[0].x, p[0].y, radius);
		FillCircle(darker, p[1].x, p[1].y, radius);
		FillCircle(darker, p[2].x, p[2].y, radius);
		FillCircle(darker, p[3].x, p[3].y, radius);
		Draw_Circle(darker, center.x, center.y, 4.5f, 2);
	}	
}

void WavyScreen(float t)
{
	Color* copy = malloc(WIDTH*HEIGHT*4);

	memcpy(copy,pixels,WIDTH*HEIGHT*4);
	for (int y = 0; y < HEIGHT; ++y)
	{
		int shift_x = (int)((sin(t + y/90.0f)+1)*20);

		
		for(int x = 0; x < WIDTH; x++)
		{
			int shift_y = shift_x;
			
			if(shift_x < -x)
				shift_x = -x;

			if(shift_y < -y)
				shift_y = -y;

			Color temp = pixels[y*WIDTH+x];
			pixels[y*WIDTH+x] = copy[((y+shift_y)%HEIGHT)*WIDTH+((x+shift_x)%WIDTH)];
		}
	}

	for (int i = 0; i < pixel_count; ++i)
	{
		PutPixel_ByIndex(LerpColor(pixels[i],blue,.5f), i);
	}

	free(copy);

	int border_size = 40;
	FillRectangle(black, WIDTH-border_size,0,border_size,HEIGHT);
	FillRectangle(black, 0,0,border_size,HEIGHT);

	FillRectangle(black,0,0,WIDTH,border_size);
	FillRectangle(black,0,HEIGHT-border_size,WIDTH,border_size);
}