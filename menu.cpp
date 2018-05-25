#include "menu.hpp"

#include <iostream>

#include "command_parser.hpp"

namespace menu
{
	std::wstring prompt = L">";

	void main_menu()
	{
		std::cout << std::boolalpha;

		while (true)
		{
			std::string input;

			std::wcout << prompt;
			if (!std::getline(std::cin, input))
			{
				std::cerr << "Menu error!\n";
				return;
			}

			parse_command(input);
		}
	}
}
