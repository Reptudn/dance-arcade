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
#include <filesystem>
#include <SDL2/SDL_image.h>

enum e_arrow_type
{
	TOP_LEFT,
	TOP_RIGHT,
	STOMP,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
} typedef t_arrow_type;

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

struct s_song
{
	std::string name = "No Name";
	std::string description = "No Description";
	std::filesystem::path path = "";
	SDL_Texture *background = nullptr;
	int length = -1;
} typedef Song;

class Game
{
public:
	Game();
	~Game();

private:
	float scroll_speed;
	std::vector<Song> songs;

	int curr_song_index = -1;
	Song *curr_song = nullptr;
};