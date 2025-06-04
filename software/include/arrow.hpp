#pragma once

#include <SDL2/SDL.h>
#include <string>

struct s_arrow
{
	int column = -1; // type of the arrow
	int time = -1;
	bool slider = false;
	int end_time = 0;

	SDL_Texture *texture = nullptr; // texture of the arrow
};
typedef s_arrow Arrow;