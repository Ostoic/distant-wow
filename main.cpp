// WoW Memory Tool.cpp : Defines the entry point for the console application.

#include "main.h"
#include "menu.hpp"

#include "utility/meta_string.hpp"
#include <string_view>
#include <distant/privileges.hpp>

namespace program
{
	namespace { constexpr const char* version_string = "distant::wow version 0.0.1"; }
	constexpr std::string_view version = {version_string, utility::string_length(version_string)};
}

int main(int argc, const char* argv[])
{
	std::cout << program::version << "\n\n";
	if (!distant::request_debug_privileges())
		std::cerr << "Unable to acquire debug privileges! Continuing without...\n";

	menu::main_menu();
	return 0;
}
