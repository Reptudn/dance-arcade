#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Dance Arcade"

// this is only true for now because developing just started
#define DEBUG true

#ifndef DEBUG
#define DEBUG false
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>

struct s_arrow
{
	SDL_Rect rect;
	float y;
	s_arrow(int x, float startY)
	{
		rect = {x, (int)startY, 50, 50};
		y = startY;
	}
	void update(float delta)
	{
		y += 200 * delta;
		rect.y = static_cast<int>(y);
	}
	void draw(SDL_Renderer *renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red arrows
		SDL_RenderFillRect(renderer, &rect);
	}
} typedef Arrow;