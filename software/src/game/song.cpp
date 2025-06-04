#include "song.hpp"

Song::Song(std::string path, Engine &engine) : engine(engine)
{
	this->path = std::filesystem::path(path);
	if (!std::filesystem::exists(this->path))
	{
		std::cerr << "Song path does not exist: " << this->path << std::endl;
		return;
	}

	// check if path is a folder that i can enter
	if (!std::filesystem::is_directory(this->path))
	{
		std::cerr << "Song path is not a directory: " << this->path << std::endl;
		return;
	}

	parse_map();
}

Song::~Song()
{
	engine.unload_sound(audio);
	engine.unload_texture(cover);

	for (auto &difficulty : difficulties)
	{
		for (auto &arrow : difficulty.arrows)
		{
			if (arrow.texture)
				engine.unload_texture(arrow.texture);
		}
	}
	difficulties.clear();
}