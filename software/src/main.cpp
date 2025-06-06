#include "game.hpp"
#include "engine.hpp"
#include <utils.hpp>
#include "scenes.hpp"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int ret = 0;

	utils::log::info("Starting Dance Arcade...");
	try
	{
		Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

		utils::log::info("Dance Arcade started successfully!");

		engine.load_scene(home_scene(engine));
		engine.set_current_scene("Home");

		engine.run();
	}
	catch (const std::exception &e)
	{
		utils::log::error(e.what());
		utils::log::error("Failed to start Dance Arcade");
		ret = 1;
	}
	catch (...)
	{
		utils::log::error("An unknown error occurred");
		utils::log::error("Failed to start Dance Arcade");
		ret = 1;
	}

	if (ret == 0)
		utils::log::info("Exited good.");
	else
		utils::log::info("Edited badly.");
	return ret;
}
