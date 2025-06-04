#pragma once

class Engine;

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
	std::string name;				// name of the object
	SDL_Texture *texture = nullptr; // texture of the object
	bool visible = true;			// if the object is visible
	int x = 0;						// x position of the object
	int y = 0;						// y position of the object
	int width = 0;					// width of the object
	int height = 0;					// height of the object
	double rotation = 0.0;			// rotation of the object

	s_scene_object() = default;
	s_scene_object(std::string name) : name(name) {}
	s_scene_object(SDL_Texture *texture) : texture(texture) {}
	// s_scene_object(std::string name, SDL_Texture *texture, SDL_Rect rect)
	s_scene_object(std::string name, SDL_Texture *texture) : name(name), texture(texture) {}
	s_scene_object(std::string name, SDL_Texture *texture, int x, int y, int width, int height, double rotation) : name(name), texture(texture), x(x), y(y), width(width), height(height), rotation(rotation) {}
} typedef SceneObject;

// TODO: make this an abstract class so scenes can derive from it with custom constructor and destructor
struct s_scene
{
	std::string title = "Untitled Scene"; // title of the scene
	s_scene() = default;
	s_scene(std::string title) = delete;
	s_scene(
		std::string title,
		void (*update)(Engine &engine, SDL_Event &event),
		void (*init)(Engine &engine),
		void (*destroy)(Engine &engine),
		void (*on_set_as_curr_scene)(Engine &engine))
	{
		this->title = title;
		this->update = update;
		this->destroy = destroy;
		this->init = init;
		this->on_set_as_curr_scene = on_set_as_curr_scene;
	};

	// TODO: store them all sorted in one map by key and ordered by render prio

	// render: background -> scene -> ui
	std::vector<SceneObject> background = std::vector<SceneObject>(0); // background elements in render order
	std::vector<SceneObject> scene = std::vector<SceneObject>(0);	   // scene elements in render order
	std::vector<SceneObject> ui = std::vector<SceneObject>(0);		   // ui element in render order

	bool loaded = false; // if the scene is loaded

	void (*update)(Engine &engine, SDL_Event &event) = nullptr; // main loop of the scene
	void (*init)(Engine &engine) = nullptr;						// called when the scene is loaded
	void (*destroy)(Engine &engine) = nullptr;					// called when the scenes is unloaded
	void (*on_set_as_curr_scene)(Engine &engine) = nullptr;		// called when the scene is set as current scene
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
	const Uint8 *state;

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;
	// Mix_Music *music;

	Scene *current_scene = nullptr;
	std::map<std::string, Scene *> scenes;
	std::vector<SDL_Texture *> loaded_textures;

	std::chrono::high_resolution_clock::time_point startTime;
	double deltaTime;

	void render(Scene *scene);

	// std::multimap<int, std::function<void()>> callbacks;
};