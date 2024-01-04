typedef struct
{
	bool started;
	bool ended;
	float time;
	float alpha;
	Bitmap logo;
	int x_min, x_max, y_min, y_max;
} Splash;

void splash_update()
{
	if (!stplashtes.started)
	{
		//todo clean this mess up. only load stuff once
		stplashtes.started = false;
		stplashtes.ended = false;
		stplashtes.time = 0;
		stplashtes.alpha = 0;		

        SDL_AudioSpec wav_spec;
        SDL_AudioSpec obtained_spec;
        Uint32 wav_count;

        Uint8 *wav_buffer = (Uint8*)&memory[AUDIO_INDEX];

        printf("AUDIO_INDEX: %d\n", AUDIO_INDEX);
        SDL_LoadWAV("Assets/preparations.wav", &wav_spec, &wav_buffer, &wav_count);
        FILE*fp=fopen("Assets/real_data","wb");
        fwrite(memory,TOTAL_MEMORY_LENGTH,1, fp);
        fclose(fp);

        SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, &obtained_spec, 0);            
        SDL_QueueAudio(device_id, wav_buffer, wav_count);
        SDL_PauseAudioDevice(device_id, 0);

		Clear();
		stplashtes.started = true;
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
			
			if(stplashtes.alpha > 0)
			{
				memcpy(pixels, stplashtes.logo.pixels, total_bytes);

				for (int y = stplashtes.y_min; y < stplashtes.y_max; y++)
				for (int x = stplashtes.x_min; x < stplashtes.x_max; x++)
				{
					//todo try branchless
					int i = y * WIDTH + x;
					if (pixels[i] != black)
					{
						uint r = (pixels[i] & 0xFF0000) >> 16;
						uint g = (pixels[i] & 0xFF00) >> 8;
						uint b = pixels[i] & 0xFF;

						r = (uint)(r*stplashtes.alpha);
						r <<= 16;
						g = (uint)(g*stplashtes.alpha);
						g <<= 8;
						b = (uint)(b*stplashtes.alpha);
						pixels[i] = r | g | b;
					}
				}
			}
			else
				Clear();
		}

		elapsed_time += timing.delta_time;
	}

	//Animate
	{
		stplashtes.time += timing.delta_time;
		if (stplashtes.time > 2 && stplashtes.time < 7 && stplashtes.alpha < 1)
		{
			stplashtes.alpha += timing.delta_time / 5;
			if (stplashtes.alpha > 1)
				stplashtes.alpha = 1;
		}
		else if (stplashtes.time > 8  && stplashtes.alpha > 0)
		{
			stplashtes.alpha -= timing.delta_time;
			if (stplashtes.alpha < 0)
				stplashtes.alpha = 0;
		}
		else if (stplashtes.time > 10.5f)
		{
			if (!stplashtes.ended)
			{
				SwitchState(TitleScreen);
				stplashtes.ended = true;
			}
			else
			{
				stplashtes.time = 0;
				stplashtes.ended = false;
				stplashtes.started = false;
			}
		}					
	}
}

