#pragma once

#include "game.hpp"
#include <map>
#include <functional>
#include <chrono>
#include <SDL2/SDL_ttf.h>
#include <string>

#define FPS 60

struct s_scene
{
	std::string title;

	s_scene(std::string title, void (*update)())
	{
		this->title = title;
		this->update = update;
	};

	// render: background -> scene -> ui
	std::vector<SDL_Texture *> background; // background elements in render order
	std::vector<SDL_Texture *> scene;	   // scene elements in render order
	std::vector<SDL_Texture *> ui;		   // ui elements in render order

	void (*update)(); // main loop of the scene
} typedef Scene;

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

	Scene *current_scene = nullptr;
	std::map<std::string, Scene> scenes;
	std::vector<SDL_Texture *> loaded_textures;

	std::chrono::high_resolution_clock::time_point startTime;
	double deltaTime;

	void render(Scene *scene);
	void load_scene(Scene *scene);
	void unload_scene(Scene *scene);

	SDL_Texture *load_texture(std::string path);
	void unload_texture(SDL_Texture *texture);

	// std::multimap<int, std::function<void()>> callbacks;
};