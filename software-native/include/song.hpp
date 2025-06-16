#pragma once

#include <iostream>
#include <vector>
#include <filesystem>

#include "game.hpp"
#include "engine.hpp"
#include "arrow.hpp"

struct s_difficulty
{
	int value;
	std::string name;
	std::filesystem::path path; // path to the file to parse for this difficulty
	int scroll_speed;
	int difficulty;									   // 1-10 scale
	std::vector<Arrow> arrows = std::vector<Arrow>(0); // arrows for this difficulty
} typedef Difficulty;

class Song
{
public:
	Song(std::string path, Engine &engine);
	~Song();

private:
	Engine &engine;

	std::string title;
	std::string artist;
	std::string audio;
	SDL_Texture *cover;
	std::filesystem::path path;										   // path to the song folder
	std::vector<Difficulty> difficulties = std::vector<Difficulty>(0); // difficulties for this song
	int bpm = -1;
	int length = -1; // in seconds

	void parse_map();
};