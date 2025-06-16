#include "song.hpp"
#include <fstream>

void Song::parse_map()
{
	cover = engine.load_texture(path.string() + "/background.png");
	if (!cover)
		throw std::runtime_error("No background image found!");

	std::filesystem::path map_file = path / ".osu"; // TODO: parse different formats later
	if (!std::filesystem::exists(map_file))
		throw std::runtime_error("file does not exist: " + std::string(map_file));

	std::ifstream file(map_file);
	if (!file.is_open())
		throw std::runtime_error("Failed to open map file: " + std::string(map_file));

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
	}

	file.close();
}