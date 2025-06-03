#include "engine.hpp"

static void render_background(SDL_Renderer *renderer, Scene *scene)
{
	if (!renderer)
		return;

	(void)scene;

	SDL_SetRenderDrawColor(renderer, 50, 100, 150, 255);
	SDL_RenderClear(renderer);
}
static void render_scene(SDL_Renderer *renderer, Scene *scene)
{
	(void)scene;
	if (!renderer)
		return;
}

static void render_ui(SDL_Renderer *renderer, TTF_Font *font)
{
	if (!renderer)
		return;

	int x = 100;
	int y = 100;

	SDL_Color color = {255, 255, 255, 255}; // White
	SDL_Surface *textSurface = TTF_RenderText_Blended(font, "Welcome to the dance arcade", color);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect dstRect = {x, y, textSurface->w, textSurface->h};
	SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
}

void Engine::render(Scene *scene)
{
	if (!scene)
	{
		return;
	}

	render_background(renderer, scene);
	render_scene(renderer, scene);
	render_ui(renderer, font);

	SDL_RenderPresent(renderer);
}
