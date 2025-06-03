#include <iostream>

namespace utils
{
	namespace log
	{
		void info(const std::string &message);
		void error(const std::string &message);
		void warning(const std::string &message);
		void debug(const std::string &message);
	} // namespace log
} // namespace utils
