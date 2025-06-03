#include "game.hpp"
#include "engine.hpp"
#include <utils.hpp>

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	int ret = 0;

	utils::log::info("Starting Dance Arcade...");
	try
	{
		Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
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

	utils::log::info("Exited.");
	return ret;
}
