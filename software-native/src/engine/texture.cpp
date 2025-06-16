#include <filesystem>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "utils.hpp"
#include "engine.hpp"

SDL_Texture *Engine::load_texture(std::string path)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == nullptr)
	{
		if (std::filesystem::exists(path))
			utils::log::error("Failed to load texture from path: " + path + " - " + std::string(SDL_GetError()));
		else
			utils::log::error("Texture file does not exist: " + path);
		running = false;
		throw std::runtime_error("Failed to load texture: " + path);
		return nullptr;
	}

	loaded_textures.emplace_back(texture);
	utils::log::info("Loaded texture: " + path);
	return texture;
}

SDL_Texture *Engine::load_text(std::string text, int size)
{
	if (!font)
	{
		utils::log::error("Font is not loaded, cannot create texture from text.");
		running = false;
		throw std::runtime_error("Font is not loaded, cannot create texture from text.");
		return nullptr;
	}

	(void)size;

	SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255, 255});
	if (!surface)
	{
		utils::log::warning("Failed to create surface from text: " + std::string(TTF_GetError()));
		return nullptr;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture)
	{
		utils::log::warning("Failed to create texture from surface: " + std::string(SDL_GetError()));
		return nullptr;
	}

	loaded_textures.emplace_back(texture);
	utils::log::info("Created texture from text: " + text);
	return texture;
}

void Engine::unload_texture(SDL_Texture *texture)
{
	if (!texture)
		return;

	SDL_DestroyTexture(texture);
	auto it = std::find(loaded_textures.begin(), loaded_textures.end(), texture);
	if (it != loaded_textures.end())
	{
		loaded_textures.erase(it);
	}
	utils::log::info("Unloaded texture!");
}