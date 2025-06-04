#include <iostream>

struct s_vector2
{
	int x;
	int y;
} typedef Vector2;

namespace utils
{
	namespace log
	{
		void info(const std::string &message);
		void error(const std::string &message);
		void warning(const std::string &message);
		void debug(const std::string &message);
	} // namespace log

	namespace transform
	{
		Vector2 get_screen_center(int screen_width, int screen_height, int tex_width, int tex_height);
	} // namespace transform
} // namespace utils
