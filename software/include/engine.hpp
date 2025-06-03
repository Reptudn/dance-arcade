#pragma once

#include "game.hpp"
#include <map>
#include <functional>
#include <chrono>
#include <SDL2/SDL_ttf.h>

#define FPS 60

class Engine
{
public:
	Engine(int width, int height, const char *title);
	~Engine();

	void run();
	bool running;

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	TTF_Font *font;
	// Mix_Music *music;

	std::chrono::high_resolution_clock::time_point startTime;
	double deltaTime;

	void render();

	// std::multimap<int, std::function<void()>> callbacks;
};