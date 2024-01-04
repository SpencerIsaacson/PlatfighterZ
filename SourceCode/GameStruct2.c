#include "Debug.h"
#include "GUI.h"
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

#include "Memory.h"
typedef unsigned int Color;

typedef struct
{
	Animation idle_animation;
	Animation walk_animation;
	Animation jump_animation;
	Animation punch_animation;
	Animation kick_animation;
	Animation double_hammer_animation;
} DefinedAnimations;

DefinedAnimations defined_animations;
enum Channels
{
	POSX, POSY, POSZ, ROTX, ROTY, ROTZ, SCALEX, SCALEY, SCALEZ
};

void DrawGrid_ScreenSpace2(int unit_size, v2 offset)
{

	for (int i = 0; i < 128; i ++)
	{
		Color color = (i % 4 == 0) ? 0xAAAAAA : 0x666666;
		int x = i * unit_size + offset.x;
		DrawVertical(color, WIDTH/2+x);
		DrawVertical(color, WIDTH/2+x-(i*unit_size*2));
	}

	for (int i = 0; i < 128; i ++)
	{
		Color color = (i % 4 == 0) ? 0xAAAAAA : 0x666666;
		int y = i * unit_size + offset.y;
		DrawHorizontal(color, HEIGHT/2+y);
		DrawHorizontal(color, HEIGHT/2+y-(i*unit_size*2));
	}
}
typedef struct
{
	int x, y;
	float size;
	int frame;
	v2 offset;
	float float_frame;
	bool play;
	Animation current_animation;
} GameStruct;


GameStruct g;

void InitGame(GameStruct* game)
{
	#include "animations.c_asset"	
	game->x = 0;
	game->y = 0;
	game->size = 64;
	game->offset = (v2){0,0};
	game->frame = 0;
	game->float_frame = 1;
	game->current_animation = defined_animations.kick_animation;

	//Load FontSet
	{
		FILE* file_pointer = fopen("Assets/font_set", "rb");
		fread(font_set, 8, char_dict_count, file_pointer);
		fclose(file_pointer);
	}

}

void Update()
{
	if(KeyDownFresh(Keys_Space))
	{
		printf("foo!");
		g.play = !g.play;
	}

	for (int i = 0; i < hitbox_count; ++i)
	{
		for (int o = 0; o < curves_per_box; ++o)
		{
			float* f = &(g.current_animation.hitframes[i].rect.x) + g.current_animation.hitframes[i].curves[o].channel_offset;
			AnimateProperty(g.current_animation.hitframes[i].curves[o], g.float_frame, f);
		}

		for (int o = 0; o < g.current_animation.hitframes[i].hitstate_anim.state_frame_count; ++o)
		{
			if(g.float_frame >= g.current_animation.hitframes[i].hitstate_anim.keys[o])
			{
				g.current_animation.hitframes[i].state = g.current_animation.hitframes[i].hitstate_anim.values[o];
			}
			else break;
		}
	}

	g.size += mousestate.scroll_amount*4;
	if(mousestate.rightbutton_down)
		g.offset = v2_Add(g.offset,mousestate.delta);

	if(g.play)
		g.float_frame+=.1f;
	if(g.float_frame >= g.current_animation.animation_length+1)
		g.float_frame = 1;
	g.frame = (int)g.float_frame;

}

void Render()
{
	Clear();
	FillAlphaChannel();
	DrawGrid_ScreenSpace2(g.size,g.offset);
	DrawHorizontal(green,HEIGHT/2+g.offset.y);
	DrawVertical(red, WIDTH/2+g.offset.x);
	
	FillRectangle(red, mousestate.position.x-5, mousestate.position.y-5, 10, 10);
	

	//
	{										
		Color colors[3] = { gray, red, blue };
		for (int i = 0; i < hitbox_count; ++i)
		{
			#define boxes g.current_animation.hitframes
			if(boxes[i].state != Inactive)
			{
				RectangleF rect = boxes[i].rect;
				rect.x *= g.size;
				rect.y *= -g.size;
				rect.width *= g.size;
				rect.height *= g.size;
				rect.x += WIDTH/2;
				rect.y += HEIGHT/2;
				rect.x += g.offset.x;
				rect.y += g.offset.y;
				FillRectangle_Blend(Darker(colors[boxes[i].state])^opaque | 0x33000000, rect.x-rect.width/2, rect.y-rect.height/2, rect.width, rect.height);
				Draw_Circle(colors[boxes[i].state], rect.x, rect.y, 4.5f, 2);
				DrawRectangle(colors[boxes[i].state], rect.x-rect.width/2, rect.y-rect.height/2, rect.width, rect.height);
			}
			//#undef boxes
		}								
	}

	typedef enum Floop
	{
		None = 0,
		Top = 0x1,
		Right = 0x2,
		Left = 0x4,
		Bottom = 0x8,
		Top_Left = 0x1|0x4,
		Top_Right = 0x1|0x2,
		Bottom_Left = 0x8|0x4,
		Bottom_Right = 0x8|0x2,
		Center = 0x10
	} Floop;
	static Floop selection = None;
	static Floop highlight = None;
	static v2 initial;
	static RectangleF* foo;
	static RectangleF alt_foo = {0,0,1,1};
	static RectangleF rect;
	highlight = None;
	if(selection == None)
	for (int i = 0; i < hitbox_count; ++i)
	{
		if(boxes[i].state == Inactive)
		{
			continue;
		}

 		foo = &boxes[i].rect;
		v2 pos = mousestate.position;

		rect = *foo;
		rect.x *= g.size;
		rect.y *= -g.size;
		rect.width *= g.size;
		rect.height *= g.size;
		rect.x += WIDTH/2; 
		rect.y += HEIGHT/2;
		rect.x -= rect.width/2;
		rect.y -= rect.height/2;
		rect.x += g.offset.x;
		rect.y += g.offset.y;			

		if(pos.y > (rect.y) && pos.y < (rect.y+rect.height) && pos.x < (rect.x+3) && pos.x > (rect.x-3))
		{
			highlight |= Left;
		}			

		if(pos.y > (rect.y) && pos.y < (rect.y+rect.height) && pos.x < (rect.x+rect.width+3) && pos.x > (rect.x+rect.width-3))
		{
			highlight |= Right;
		}


		if(pos.x > rect.x && pos.x < (rect.x+rect.width) && pos.y < (rect.y+3) && pos.y > (rect.y-3))
		{
			highlight |= Top;
		}

		if(pos.x > rect.x && pos.x < (rect.x+rect.width) && pos.y < (rect.y+rect.height+3) && pos.y > (rect.y+rect.height-3))
		{
			highlight |= Bottom;	
		}

		if(v2_Distance(pos, (v2){rect.x+rect.width/2, rect.y+rect.height/2}) < 10)
		{
			highlight = Center;
		}

		if(highlight)
			break;	
	}

	if(selection == None)
	{
		if(mousestate.leftbutton_down && !mousestate.leftbutton_was_down)
		{
			initial = mousestate.position;
			selection = highlight;
			alt_foo = *foo;
		}
	}

	bool ctrl = KeyDown(Keys_A);

	if(selection)
	{
		char food[40];
		sprintf(food, "selection: %d",selection);
		DrawString(WrapString(food),0,150);
		v2 delta = v2_Subtract(mousestate.position,initial);
		delta.x /= g.size;
		delta.y /= -g.size;
		//char food[40];
		sprintf(food, "delta: { %.2f, %.2f }",delta.x, delta.y);
		DrawString(WrapString(food),32,32);

		if(selection & Right)
		{
			if(ctrl)
				(*foo).width = alt_foo.width + delta.x*2;
			else
			{
				(*foo).width = alt_foo.width + delta.x;
				(*foo).x = alt_foo.x + delta.x/2;
			}
		}
		if(selection & Left)
		{
			if(ctrl)
				(*foo).width = alt_foo.width - delta.x*2;
			else
			{
				(*foo).width = alt_foo.width - delta.x;
				(*foo).x = alt_foo.x + delta.x/2;
			}
		}

		if(selection & Top)
		{
			DrawString(WrapString("top!"),0,250);			
			if(ctrl)
				(*foo).height = alt_foo.height + delta.y*2;
			else
			{
				(*foo).height = alt_foo.height + delta.y;
				(*foo).y = alt_foo.y + delta.y/2;
			}
		}
		
		if(selection & Bottom)
		{
			if(ctrl)
				(*foo).height = alt_foo.height - delta.y*2;
			else
			{
				(*foo).height = alt_foo.height - delta.y;
				(*foo).y = alt_foo.y + delta.y/2;
			}
		}		

		if(selection & Center)
		{
			(*foo).x = alt_foo.x + delta.x;
			(*foo).y = alt_foo.y + delta.y;
		}		
	}

	if(!mousestate.leftbutton_down)
	{
		selection = None;
	}

	if(selection == None)
	{
		if(highlight & Left)
			FillRectangle(red, rect.x-3,rect.y,6,rect.height);
		if(highlight & Right)
			FillRectangle(red, rect.x+rect.width-3,rect.y,6,rect.height);
		if(highlight & Top)
			FillRectangle(red, rect.x,rect.y-3, rect.width,6);
		if(highlight & Bottom)
			FillRectangle(red, rect.x,rect.y+rect.height-3, rect.width,6);
		if(highlight == Center)
			FillCircle(red, rect.x+rect.width/2, rect.y+rect.height/2, 10);
	}
	else
	{
		if(selection & Left)
			FillRectangle(Darker(red), rect.x-3,rect.y,6,rect.height);
		if(selection & Right)
			FillRectangle(Darker(red), rect.x+rect.width-3,rect.y,6,rect.height);
		if(selection & Top)
			FillRectangle(Darker(red), rect.x,rect.y-3, rect.width,6);
		if(selection & Bottom)
			FillRectangle(Darker(red), rect.x,rect.y+rect.height-3, rect.width,6);
		if(selection == Center)
			FillCircle(Darker(red), rect.x+rect.width/2, rect.y+rect.height/2, 10);
	}

	int timeline_height = 60;
	//Draw Timeline
	{
		FillRectangle(0xFFAAAAAA, 0, HEIGHT - timeline_height, WIDTH, timeline_height);
		int timeline_frame_width = WIDTH/g.current_animation.animation_length;
		FillRectangle(red, (g.frame-1)*timeline_frame_width, HEIGHT - timeline_height, 5, timeline_height);
		for(int i = 0; i < g.current_animation.animation_length; i++)
		{
			DrawVerticalSegment(black, i * timeline_frame_width, HEIGHT - timeline_height, HEIGHT);

			char frame_number_string[3];
			sprintf(frame_number_string, "%d", i+1);
			DrawStringScaled(WrapString(frame_number_string), i*timeline_frame_width+6, HEIGHT - 10, 1,white);
		}
	}	
	char frame_foo[3];
	sprintf(frame_foo, "frame: %d", g.frame);
	DrawStringScaled(WrapString(frame_foo), 0, 0, 1, white);
	if(Button("a", WIDTH-(25+20), HEIGHT-(timeline_height+25), 20, 20))
	{
		g.current_animation.animation_length++;
	}
	else if(Button("b", 25, HEIGHT-(timeline_height+25), 20, 20))
	{
		g.current_animation.animation_length--;
	}
}