#include "engine.hpp"
#include <utils.hpp>

Engine::Engine(int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		throw std::runtime_error("SDL could not initialize: " + std::string(SDL_GetError()));

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		throw std::runtime_error("SDL_mixer could not initialize: " + std::string(Mix_GetError()));

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window)
		throw std::runtime_error("Window could not be created: " + std::string(SDL_GetError()));

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		throw std::runtime_error("Renderer could not be created: " + std::string(SDL_GetError()));

	if (TTF_Init() < 0)
		throw std::runtime_error("Failed to init TTF: " + std::string(TTF_GetError()));

	font = TTF_OpenFont("../assets/fonts/Montserrat-Bold.ttf", 24); // TODO: DONT HARDCODE THIS
	if (!font)
		throw std::runtime_error("Failed to load font with TTF: " + std::string(TTF_GetError()));

	running = true;
	startTime = std::chrono::high_resolution_clock::now();
}

Engine::~Engine()
{
	// if (music)
	// {
	// 	Mix_FreeMusic(music);
	// 	music = nullptr;
	// }

	for (SDL_Texture *texture : loaded_textures)
	{
		if (texture)
			SDL_DestroyTexture(texture);
	}

	unload_scene(current_scene);

	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	if (font)
	{
		TTF_CloseFont(font);
	}

	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void Engine::run()
{
	running = true;

	const int frameDelay = 1000 / FPS;

	auto currTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<double>(currTime - startTime).count();

	while (running)
	{
		auto frameStart = std::chrono::high_resolution_clock::now();

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
				utils::log::info("Running is now false");
			}
		}
		if (!running)
			break;

		if (current_scene)
		{
			if (current_scene->update)
				current_scene->update(e);
			render(current_scene);
		}
		else
		{
			utils::log::warning("No current scene to render, skipping render step.");
			// TODO: display a default no scene message
		}

		auto frameEnd = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();

		if (deltaTime < frameDelay)
			SDL_Delay(frameDelay - deltaTime);
	}
	utils::log::info("Done with engine loop");
}