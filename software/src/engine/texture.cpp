#include <filesystem>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "utils.hpp"
#include "engine.hpp"

SDL_Texture *Engine::load_texture(std::string path)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
	if (!texture)
	{
		utils::log::warning("Failed to load texture: " + std::string(SDL_GetError()));
		return nullptr;
	}
	loaded_textures.emplace_back(texture);
	utils::log::info("Loaded texture: " + path);
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