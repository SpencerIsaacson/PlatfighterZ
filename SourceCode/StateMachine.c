typedef enum
{
	SplashScreen,
	TitleScreen,
	MainMenu,
	Gameplay,
} GameStates;

typedef struct
{
	void (*enter)();
	void (*exit)();
	void (*update)();
} GameState;

#define states ((GameState*)&memory[GAMESTATES_INDEX])
#define current_game_state (*((GameState**)&memory[CURRENT_GAMESTATE_INDEX]))

void SetupState
(
	GameState* state, 
	void (*enter)(), 
	void (*exit)(),
	void (*update)()
)
{
	state->enter = enter;
	state->exit = exit;
	state->update = update;
}

void SwitchState(GameStates state)
{	
	if(current_game_state->exit != NULL)
		current_game_state->exit();

	current_game_state = &states[state];
	
	if(current_game_state->enter != NULL)
		current_game_state->enter();
}

#define stplashtes (*(Splash*)&memory[SPLASH_INDEX])

#include "GameStates/SplashScreen.c"
#include "GameStates/TitleScreen.c"


void InitGame()
{
	SetupState(&states[SplashScreen], NULL, NULL, splash_update);
	SetupState(&states[TitleScreen], NULL, NULL, titlescreen_update);
	SetupState(&states[MainMenu], NULL, NULL, titlescreen_update);
	current_game_state = &states[SplashScreen];

	//Load SplashScreen Image
	{
		Texture* tex = (Texture*)&memory[TEXTURES_INDEX];
		
		FILE* file_pointer = fopen("Assets/viking_studios_logo", "r");
		fseek(file_pointer, 0L, SEEK_END);
		int file_size = ftell(file_pointer);
		rewind(file_pointer);
		fread(tex, 1, file_size, file_pointer);
		fclose(file_pointer);

		Texture* dest = (Texture*)&(tex->pixels[tex->width*tex->height]);

		float aspect = tex->width/(float)tex->height;
		//todo preserve aspect
		for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
		{
			float dest_scaled_x = x/(float)WIDTH;
			int source_x = (int)(dest_scaled_x*tex->width);

			float dest_scaled_y = y/(float)HEIGHT;
			int source_y = (int)(dest_scaled_y*tex->height);


			dest->pixels[y*WIDTH+x] = tex->pixels[source_y*tex->width+source_x];
		}

		stplashtes.logo.pixels = dest->pixels;
		stplashtes.logo.width = WIDTH;
		stplashtes.logo.height = HEIGHT;

		stplashtes.x_min = (int)(550/(float)tex->width*WIDTH);
		stplashtes.y_min = (int)(125/(float)tex->height*HEIGHT);
		stplashtes.x_max = WIDTH - stplashtes.x_min;
		stplashtes.y_max = HEIGHT - stplashtes.y_min;			
	}	
}