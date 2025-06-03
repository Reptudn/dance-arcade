#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int ARROW_SPEED = 200; // pixels per second

struct Arrow
{
	SDL_Rect rect;
	float y;
	Arrow(int x, float startY)
	{
		rect = {x, (int)startY, 50, 50};
		y = startY;
	}
	void update(float delta)
	{
		y += ARROW_SPEED * delta;
		rect.y = static_cast<int>(y);
	}
	void draw(SDL_Renderer *renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red arrows
		SDL_RenderFillRect(renderer, &rect);
	}
};

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL could not initialize! " << SDL_GetError() << std::endl;
		return 1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! " << Mix_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("DDR Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Mix_Music *music = Mix_LoadMUS("assets/bgm/music.ogg");
	if (music)
	{
		Mix_PlayMusic(music, 1);
	}
	else
	{
		std::cerr << "Could not load music! " << Mix_GetError() << std::endl;
	}

	std::vector<Arrow> arrows;
	Uint32 lastSpawn = SDL_GetTicks();
	Uint32 lastTime = SDL_GetTicks();
	bool running = true;

	while (running)
	{
		Uint32 current = SDL_GetTicks();
		float delta = (current - lastTime) / 1000.0f;
		lastTime = current;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running = false;
		}

		// Spawn arrow every second
		if (current - lastSpawn > 1000)
		{
			arrows.emplace_back(375, -50.0f); // Spawn in the center
			lastSpawn = current;
		}

		// Update arrow positions
		for (auto &arrow : arrows)
		{
			arrow.update(delta);
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw arrows
		for (auto &arrow : arrows)
		{
			arrow.draw(renderer);
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(16); // ~60 FPS
	}

	Mix_FreeMusic(music);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}
