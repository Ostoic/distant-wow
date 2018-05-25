#include "command_manager.hpp"

namespace commands
{
	command_manager::command_manager(const std::initializer_list<command_info> commands)
		: commands_(commands)
	{}

	command_manager::const_iterator 
		command_manager::begin() const
	{
		return commands_.begin();
	}

	command_manager::iterator 
		command_manager::begin()
	{
		return commands_.begin();
	}

	command_manager::const_iterator 
		command_manager::end() const
	{
		return commands_.end();
	}

	command_manager::iterator command_manager::end()
	{
		return commands_.end();
	}

	const command_manager::command_info& 
		command_manager::operator[](const std::string& text) const
	{
		for (const auto& command : commands_)
			if (command.is_synonym(text))
				return command;

		throw std::out_of_range("Invalid command");
	}

	bool command_manager::is_command(const std::string& text) const
	{
		for (const auto& command : commands_)
			if (command.is_synonym(text))
				return true;

		return false;
	}
}