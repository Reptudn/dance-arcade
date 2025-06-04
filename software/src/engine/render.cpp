#include "engine.hpp"

static void render_background(SDL_Renderer *renderer, std::vector<SceneObject> &obj)
{
	if (!renderer)
		return;

	if (obj.empty())
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Default to black if no textures
		SDL_RenderClear(renderer);
		return;
	}

	for (SceneObject &object : obj)
	{
		if (!object.texture || !object.visible)
			continue;

		SDL_Rect dstRect = object.rect;
		SDL_RenderCopy(renderer, object.texture, NULL, &dstRect);
	}

	SDL_SetRenderDrawColor(renderer, 50, 100, 150, 255);
	SDL_RenderClear(renderer);
}
static void render_scene(SDL_Renderer *renderer, std::vector<SceneObject> &obj)
{
	if (!renderer)
		return;

	if (obj.empty())
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Default to black if no textures
		SDL_RenderClear(renderer);
		return;
	}
	for (SceneObject &object : obj)
	{
		if (!object.texture || !object.visible)
			continue;

		SDL_Rect dstRect = object.rect;
		SDL_RenderCopy(renderer, object.texture, NULL, &dstRect);
	}
}

static void render_ui(SDL_Renderer *renderer, std::vector<SceneObject> &obj)
{
	if (!renderer)
		return;

	if (obj.empty())
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Default to black if no textures
		SDL_RenderClear(renderer);
		return;
	}
	for (SceneObject &object : obj)
	{
		if (!object.texture || !object.visible)
			continue;

		SDL_Rect dstRect = object.rect;
		SDL_RenderCopy(renderer, object.texture, NULL, &dstRect);
	}
}

void Engine::render(Scene *scene)
{
	if (!scene)
	{
		return;
	}

	SDL_RenderClear(renderer);

	render_background(renderer, scene->background);
	render_scene(renderer, scene->scene);
	render_ui(renderer, scene->ui);

	SDL_RenderPresent(renderer);
}
