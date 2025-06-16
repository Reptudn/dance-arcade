#include "utils.hpp"
#include "game.hpp"

// ANSI color codes
#define COLOR_RESET "\033[0m"
#define COLOR_INFO "\033[1;32m"	   // Bright Green
#define COLOR_ERROR "\033[1;31m"   // Bright Red
#define COLOR_WARNING "\033[1;33m" // Bright Yellow
#define COLOR_DEBUG "\033[1;34m"   // Bright Blue

void utils::log::info(const std::string &message)
{
	std::cout << COLOR_INFO << "[INFO] " << message << COLOR_RESET << std::endl;
}

void utils::log::error(const std::string &message)
{
	std::cerr << COLOR_ERROR << "[ERROR] " << message << COLOR_RESET << std::endl;
}

void utils::log::warning(const std::string &message)
{
	std::cerr << COLOR_WARNING << "[WARNING] " << message << COLOR_RESET << std::endl;
}

void utils::log::debug(const std::string &message)
{
	if (DEBUG)
		std::cout << COLOR_DEBUG << "[DEBUG] " << message << COLOR_RESET << std::endl;
}