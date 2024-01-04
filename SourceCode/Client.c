#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#define SDL_MAIN_HANDLED
#include "../Dependencies/SDL_Headers/SDL.h"
#include "Types.h"
#include "Timing.h"
#include "Utilities.h"
#include "Input.h"
//#include "Debug.h"
#include "LinearAlgebra.h"
#include "Drawing.h"
//#include "GUI.h"
//#include "Memory.h"
#include "GameStruct2.c"

bool window_is_active = true;
SDL_Window *window;

int main(int argc, char* argv[])
{
	FILE* file_pointer = fopen("Assets/real_data", "rb");
	fread(memory, megabyte, 50, file_pointer);
	fclose(file_pointer);

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO) < 0)
        return 1;

    //Load Joysticks
    {
        //todo allow plugging in and removing joysticks at runtime
        int joy_count = SDL_NumJoysticks();
        for (int i = 0; i < joy_count; ++i)
        {
			SDL_Joystick* game_controller = SDL_JoystickOpen( i );
	        if( game_controller == NULL )
	        {
	            printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
	        }
        }
    }

    if(argc > 2)
    {
    	WIDTH = strtol(argv[1], NULL, 10);
    	HEIGHT = strtol(argv[2], NULL, 10);
    }
    else
    {
    	WIDTH = 1920;
    	HEIGHT = 1080;
    }
	
	InitViewport(WIDTH, HEIGHT);

    window = SDL_CreateWindow
    (
    	"Game Client", 
		SDL_WINDOWPOS_UNDEFINED,
    	SDL_WINDOWPOS_UNDEFINED, 
    	WIDTH, 
    	HEIGHT,
    	0
    );

	//SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    pixels = SDL_GetWindowSurface(window)->pixels;

    InitTiming();
    InitGame(&g);
    // file_pointer = fopen("Assets/real_data", "wb");
    // fwrite(memory, megabyte, 50, file_pointer);
    // fclose(file_pointer);
    //printf("current_game_state:%x\n", splash_update);

    while (window_is_active) 
    {
    	//Process Events
    	{
			SDL_Event event;
        	while (SDL_PollEvent(&event)) 
        	{
            	switch(event.type)
        		{
                    case SDL_QUIT:
                        window_is_active = false;
                    case SDL_JOYAXISMOTION:
                        if( event.jaxis.axis == 0 )
                        	game_pads[event.jaxis.which].left_stick.x = (float)(event.jaxis.value / 32767.0f);
                        else if( event.jaxis.axis == 1 )
                            game_pads[event.jaxis.which].left_stick.y = -(float)(event.jaxis.value / 32767.0f);
                        break;
                    case SDL_JOYBUTTONDOWN:
    	                if(event.jbutton.type == SDL_JOYBUTTONDOWN)
    	                	game_pads[event.jbutton.which].buttons[event.jbutton.button] = true;
                        break;
                    case SDL_JOYBUTTONUP:
    	                if(event.jbutton.type == SDL_JOYBUTTONUP)
    	                	game_pads[event.jbutton.which].buttons[event.jbutton.button] = false;
                        break;
                    case SDL_MOUSEMOTION:
                    {
                    	SDL_MouseMotionEvent mouse_event = event.motion;
                		mousestate.position = (v2){mouse_event.x,mouse_event.y};
                		mousestate.delta = (v2){mouse_event.xrel,mouse_event.yrel};
                    } break;    
                    case SDL_MOUSEWHEEL:
                        mousestate.scroll_amount = event.wheel.y;
                        break;    
                    case SDL_MOUSEBUTTONDOWN:
                    {
                    	SDL_MouseButtonEvent mouse_event = event.button;
                        
                        if(mouse_event.button == SDL_BUTTON_LEFT)
                            mousestate.leftbutton_down = true;
                        
                        if(mouse_event.button == SDL_BUTTON_RIGHT)
                            mousestate.rightbutton_down = true;

                		mousestate.position = (v2){mouse_event.x,mouse_event.y}; //todo do we need this?
                    } break;
                    case SDL_MOUSEBUTTONUP:
                    {
                    	SDL_MouseButtonEvent mouse_event = event.button;

                        if(mouse_event.button == SDL_BUTTON_LEFT)
                            mousestate.leftbutton_down = false;
                        
                        if(mouse_event.button == SDL_BUTTON_RIGHT)
                            mousestate.rightbutton_down = false;

                		mousestate.position = (v2){mouse_event.x,mouse_event.y}; //todo do we need this?
                    } break;                       
            		default:
            			break;
        		}
        	}
    	}

        PollKeyboard();
        if (!timing.fixed_framerate || (timing.time_since_last_frame >= timing.STANDARD_TIMESTEP))
        {
            //Tick
            {
                timing.frames_since_last_second++;
                Update();
                Render();
                SDL_UpdateWindowSurface(window);
                timing.time_since_last_frame = 0;
            }
        }


        //todo just copy last frame's entire input state
        mousestate.delta = (v2){0,0};
		mousestate.leftbutton_was_down = mousestate.leftbutton_down;
		mousestate.rightbutton_was_down = mousestate.leftbutton_down;
		mousestate.scroll_amount = 0;

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

    return 0;
}