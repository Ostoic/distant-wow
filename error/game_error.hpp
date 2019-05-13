#pragma once

#include <string>
#include <exception>

#include <distant/error/winapi_error.hpp>

namespace distant::wow::error
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

	class invalid_downcast : public std::exception
	{
	public:
		explicit invalid_downcast(const std::string& message)
			: exception(message.c_str()) {}

		explicit invalid_downcast(const char *message)
			: exception(message) {}
	};
}
