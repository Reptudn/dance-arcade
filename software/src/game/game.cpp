#include "game.hpp"
#include "engine.hpp"
#include "utils.hpp"

Game::Game(Engine &engine)
{
	top_left = engine.load_texture("../assets/images/top_left_arrow.png");
	top_right = engine.load_texture("../assets/images/top_right_arrow.png");
	stomp = engine.load_texture("../assets/images/stomp_arrow.png");
	bottom_left = engine.load_texture("../assets/images/bottom_left_arrow.png");
	bottom_right = engine.load_texture("../assets/images/bottom_right_arrow.png");
}

Game::~Game() {}

void Game::load_songs(const std::filesystem::path &path, Engine &engine)
{
	// auto now = std::chrono::high_resolution_clock::now();
	utils::log::info("Loading songs from path: " + path.string());

	for (const auto &entry : std::filesystem::directory_iterator(path))
	{
		if (entry.is_directory())
		{
			try
			{
				utils::log::info("Loading song from directory: " + entry.path().string());
				songs.emplace_back(entry.path().string(), engine);
			}
			catch (std::exception &e)
			{
				std::cerr << "Error loading song: " << e.what() << std::endl;
				throw std::runtime_error("Failed to load songs");
			}
		}
	}
	utils::log::info("Loaded all songs from path: " + path.string());
}