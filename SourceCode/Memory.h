#pragma once

#define megabyte (1024*1024)

#define CURRENT_GAMESTATE_INDEX 0
#define GAMESTATES_INDEX 160
#define GAMESTATES_LENGTH 20
#define ENTITIES_INDEX (1*megabyte)
#define ENTITIES_LENGTH 100
#define MATRICES_INDEX (10*megabyte)
#define MATRICES_LENGTH 1024
#define TEXTURES_INDEX (MATRICES_INDEX+(MATRICES_LENGTH*sizeof(m4x4)))
#define TEXTURES_LENGTH 1024
#define SPLASH_INDEX 40*megabyte
#define AUDIO_INDEX 45*megabyte
#define TOTAL_MEMORY_LENGTH (50*megabyte)
unsigned char memory[TOTAL_MEMORY_LENGTH];