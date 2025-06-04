#include "engine.hpp"

static void render_background(SDL_Renderer *renderer, std::vector<SceneObject> &obj)
{
	if (!renderer || obj.empty())
		return;

	for (SceneObject &object : obj)
	{
		if (!object.texture || !object.visible)
			continue;

		SDL_Rect dstRect = {
			object.x,
			object.y,
			object.width,
			object.height};
		SDL_RenderCopy(renderer, object.texture, NULL, &dstRect);
	}
}
static void render_scene(SDL_Renderer *renderer, std::vector<SceneObject> &obj)
{
	if (!renderer || obj.empty())
		return;

	for (SceneObject &object : obj)
	{
		if (!object.texture || !object.visible)
			continue;

		SDL_Rect dstRect = {
			object.x,
			object.y,
			object.width,
			object.height};
		SDL_RenderCopy(renderer, object.texture, NULL, &dstRect);
	}
}

static void render_ui(SDL_Renderer *renderer, std::vector<SceneObject> &obj)
{
	if (!renderer || obj.empty())
		return;

	for (SceneObject &object : obj)
	{
		if (!object.texture || !object.visible)
			continue;

		SDL_Rect dstRect = {
			object.x,
			object.y,
			object.width,
			object.height};
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
