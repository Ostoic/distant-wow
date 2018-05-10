#pragma once

#include <string>
#include <exception>

namespace error
{
	class game_error : public std::exception
	{
	public:
		explicit game_error(const std::string& message)
			: exception(message.c_str()) {}

		explicit game_error(const char *message)
			: exception(message) {}
	};

	class memory_disparity : public std::exception
	{
	public:
		explicit memory_disparity(const std::string& message)
			: exception(message.c_str()) {}

		explicit memory_disparity(const char *message)
			: exception(message) {}
	};
}
