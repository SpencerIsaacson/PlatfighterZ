string title;
string press_space;
Bitmap title_screen_background;

void titlescreen_update()
{
	static bool init = false;
	if (!init)
	{
		init = true;
        SDL_AudioSpec wav_spec;
        SDL_AudioSpec obtained_spec;
        Uint32 wav_count;
        Uint8 *wav_buffer;

        //SDL_LoadWAV("Assets/Chiptronical.wav", &wav_spec, &wav_buffer, &wav_count);

        //SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, &obtained_spec, 0);            
        //SDL_QueueAudio(device_id, wav_buffer, wav_count);
        //SDL_PauseAudioDevice(device_id, 0);

		//Init TitleScreen
		{
			title = WrapString("Platfighter Z");
			press_space = WrapString("Press Space");
			FILE* file_pointer = fopen("Assets/title_screen", "r");
			int width = 1920, height = 1080;

			Texture* tex = (Texture*)&memory[TEXTURES_INDEX];
			Texture* dest = (Texture*)&(tex->pixels[tex->width*tex->height]);
			Texture* dest2 = (Texture*)&(dest->pixels[dest->width*dest->height]);		
			uint* pixels = dest2->pixels;
			fread(pixels, 4, width * height, file_pointer);
			title_screen_background.pixels = pixels;
			title_screen_background.width = width;
			title_screen_background.height = height;

			fclose(file_pointer);		
		}        
	}

	if(KeyDownFresh(Keys_Space))
		SwitchState(MainMenu);

	memcpy(pixels,title_screen_background.pixels, pixel_count*sizeof(uint));

	#define sprite_size 9
	#define press_space_scale 4

	static float t = -Pi/2.0f;
	int center_x = WIDTH / 2;
	float alpha = (float)(sin(t) + 1)/2.0f;
	uint space_color = ((uint)(alpha * 0xAF) << 24) | 0xFFFFFF;
	//todo don't forget to init the fontset!
	DrawStringScaled(press_space, center_x - (press_space.length * sprite_size * press_space_scale / 2), HEIGHT - sprite_size*press_space_scale*2, press_space_scale, space_color);

	t += timing.delta_time;
}

