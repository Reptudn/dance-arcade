#include "engine.hpp"
#include <utils.hpp>

Engine::Engine(int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL could not initialize! " << SDL_GetError() << std::endl;
		throw std::runtime_error("SDL initialization failed");
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! " << Mix_GetError() << std::endl;
		throw std::runtime_error("SDL_mixer initialization failed");
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cerr << "Window could not be created! " << SDL_GetError() << std::endl;
		throw std::runtime_error("Window creation failed");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cerr << "Renderer could not be created! " << SDL_GetError() << std::endl;
		throw std::runtime_error("Renderer creation failed");
	}

	if (TTF_Init() < 0)
	{
		utils::log::error("Failed to init TTF");
		throw std::runtime_error("TTF error");
	}

	font = TTF_OpenFont("../assets/fonts/Montserrat-Bold.ttf", 24); // TODO: DONT HARDCODE THIS
	if (!font)
	{
		utils::log::error("Failed to load font with TTF");
		throw std::runtime_error("Failed to load font");
	}

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
		font == nullptr;
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

		// insert the update logic here

		render();

		auto frameEnd = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart).count();

		if (deltaTime < frameDelay)
			SDL_Delay(frameDelay - deltaTime);
	}
	utils::log::info("Done with engine loop");
}