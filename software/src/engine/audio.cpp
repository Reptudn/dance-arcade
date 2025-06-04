#include "engine.hpp"
#include "utils.hpp"

Mix_Music *Engine::load_music_audio(std::string path, std::string name)
{
	Mix_Music *music = Mix_LoadMUS(path.c_str());
	if (!music)
	{
		utils::log::error("Could not load audio file: " + path);
		return nullptr;
	}
	loaded_music[name] = music;
	utils::log::info("Loaded audio file: " + path);
	return music;
}

Mix_Chunk *Engine::load_chunk_audio(std::string path, std::string name)
{
	Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
	if (!chunk)
	{
		utils::log::error("Could not load audio file: " + path);
		return nullptr;
	}
	loaded_chunks[name] = chunk;
	utils::log::info("Loaded audio file: " + path);
	return chunk;
}

void Engine::play_sound(std::string name, int loops)
{
	auto it = loaded_chunks.find(name);
	if (it != loaded_chunks.end())
	{
		Mix_PlayChannel(-1, it->second, loops);
		utils::log::info("Playing sound: " + name);
		return;
	}
	auto it2 = loaded_music.find(name);
	if (it2 != loaded_music.end())
	{
		Mix_PlayMusic(it2->second, loops);
		utils::log::info("Playing music: " + name);
		return;
	}
	else
	{
		utils::log::error("Music not found: " + name);
	}
}

void Engine::stop_playing(std::string name)
{
	auto it = loaded_music.find(name);
	if (it != loaded_music.end())
	{
		Mix_HaltMusic();
		utils::log::info("Stopped music: " + name);
		return;
	}
	else
	{
		utils::log::error("Music not found: " + name);
	}

	auto it2 = loaded_chunks.find(name);
	if (it2 != loaded_chunks.end())
	{
		Mix_HaltChannel(-1); // Stop all channels
		utils::log::info("Stopped sound: " + name);
	}
	else
	{
		utils::log::error("Sound not found: " + name);
	}
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
}

void Engine::unload_sound(std::string name)
{
	auto it = loaded_music.find(name);
	if (it != loaded_music.end())
	{
		Mix_FreeMusic(it->second);
		loaded_music.erase(it);
		utils::log::info("Unloaded music: " + name);
		return;
	}
	else
	{
		utils::log::error("Music not found: " + name);
	}

	auto it2 = loaded_chunks.find(name);
	if (it2 != loaded_chunks.end())
	{
		Mix_FreeChunk(it2->second);
		loaded_chunks.erase(it2);
		utils::log::info("Unloaded sound: " + name);
		return;
	}
	else
	{
		utils::log::error("Sound not found: " + name);
	}
	if (loaded_music.find(name) == loaded_music.end() && loaded_chunks.find(name) == loaded_chunks.end())
	{
		utils::log::error("Audio not found: " + name);
	}
}