#include "engine.hpp"
#include "utils.hpp"

void Engine::load_scene(Scene *scene)
{
	if (!scene)
	{
		utils::log::error("Could not load Scene because its null");
		return;
	}

	utils::log::info("Loading Scene " + scene->title + "...");
	current_scene = scene;
	utils::log::info("Loaded Scene " + scene->title + "!");
}

void Engine::unload_scene(Scene *scene)
{
	if (!scene)
	{
		utils::log::error("Could not unload Scene because its null");
		return;
	}

	utils::log::info("Unloading Scene " + scene->title + "...");

	for (SDL_Texture *tex : scene->background)
		unload_texture(tex);
	for (SDL_Texture *tex : scene->scene)
		unload_texture(tex);
	for (SDL_Texture *tex : scene->ui)
		unload_texture(tex);

	current_scene = nullptr;
	utils::log::info("Unloaded Scene " + scene->title + "!");
}