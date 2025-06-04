#include "utils.hpp"

// calculates depending on the tex width and height where the center is
Vector2 utils::transform::get_screen_center(int screen_width, int screen_height, int tex_width, int tex_height)
{
	int center_x = (screen_width - tex_width) / 2;
	int center_y = (screen_height - tex_height) / 2;
	return {center_x, center_y};
}