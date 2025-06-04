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

#include "song.hpp"

class Engine;

class Game
{
public:
	Game() = default;
	Game(Engine &engine);
	~Game();

	void load_songs(const std::filesystem::path &path, Engine &engine);

private:
	float scroll_speed;
	std::vector<Song> songs;

	SDL_Texture *top_left;
	SDL_Texture *top_right;
	SDL_Texture *stomp;
	SDL_Texture *bottom_left;
	SDL_Texture *bottom_right;

	int curr_song_index = -1;
	Song *curr_song = nullptr;
};