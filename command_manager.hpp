#pragma once

#include <vector>
#include <string>

namespace commands
{
	class command_manager
	{
	public:
		struct command_info
		{
			std::vector<std::string> synonyms;
			std::string usage;
			std::string help;

			bool is_synonym(const std::string& text) const
			{
				for (const auto& synonym : synonyms)
					if (synonym == text)
						return true;
				return false;
			}
		};

		using iterator = std::vector<command_info>::iterator;
		using const_iterator = std::vector<command_info>::const_iterator;

	public:
		command_manager(const std::initializer_list<command_info> commands);

		const_iterator begin() const;

		iterator begin();

		const_iterator end() const;

		iterator end();

		const command_info& operator[](const std::string& text) const;

		bool is_command(const std::string& text) const;

	private:
		std::vector<command_info> commands_;
	};
}
