#pragma once

#include "game.hpp"
#include <map>
#include <functional>
#include <chrono>
#include <SDL2/SDL_ttf.h>
#include <string>

#define FPS 60

// TODO: Make all SDL_Texrute vectors to a vector of scene objects
struct s_scene_object
{
	std::string name; // name of the object
	SDL_Texture *texture = nullptr; // texture of the object
	SDL_Rect rect = {0, 0, 0, 0}; // rectangle for rendering the object
	bool visible = true; // if the object is visible

	s_scene_object() = delete;
	// s_scene_object(std::string name, SDL_Texture *texture, SDL_Rect rect)
	s_scene_object(std::string name, SDL_Texture *texture)
	{
		this->name = name;
		this->texture = texture;
		// this->rect = rect;
	};
} typedef SceneObject;

struct s_scene
{
	std::string title = "Untitled Scene"; // title of the scene
	s_scene() = delete;
	s_scene(std::string title) = delete;
	s_scene(std::string title, void (*update)())
	{
		this->title = title;
		this->update = update;
	};

	// render: background -> scene -> ui
	std::vector<SDL_Texture *> background = std::vector<SDL_Texture *>(0); // background elements in render order
	std::vector<SDL_Texture *> scene = std::vector<SDL_Texture *>(0);	   // scene elements in render order
	std::vector<SDL_Texture *> ui = std::vector<SDL_Texture *>(0);;	   // ui elements in render order

	bool loaded = false; // if the scene is loaded

	void (*update)(); // main loop of the scene
} typedef Scene;

class Engine
{
public:
	Engine(int width, int height, const char *title);
	~Engine();

	void run();
	bool running;

	void load_scene(Scene *scene);
	void unload_scene(Scene *scene);
	void set_current_scene(std::string name);

	SDL_Texture *load_texture(std::string path);
	SDL_Texture *load_text(std::string text, int size);
	void unload_texture(SDL_Texture *texture);

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;
	// Mix_Music *music;

	Scene *current_scene = nullptr;
	std::map<std::string, Scene*> scenes;
	std::vector<SDL_Texture *> loaded_textures;

	std::chrono::high_resolution_clock::time_point startTime;
	double deltaTime;

	void render(Scene *scene);

	// std::multimap<int, std::function<void()>> callbacks;
};