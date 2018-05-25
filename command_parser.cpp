#include "command_parser.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <functional>
#include <unordered_map>
#include <locale>
#include <codecvt>

#include <distant/process.hpp>
#include <distant/snapshot.hpp>

#include "utility/type_traits.hpp"
#include "utility/array.hpp"

#include "wow/process.hpp"
#include "wow/build.hpp"
#include "wow/account.hpp"
#include "wow/entities/object_manager.hpp"
#include "wow/entities/object_dump.hpp"
#include "wow/state.hpp"
#include "error/game_error.hpp"
#include "menu.hpp"
#include "command_manager.hpp"

namespace commands
{
	const command_manager command_list = {
		{{"attach"}, 
			"attach <process id>", // usage
			"Attaches the program to the given instance of World of Warcraft." // help
			"If the given process id does not correspond to a supported version of WoW, then an exception will be thrown."
		},

		{{"wow::list", "wows"}, 
			"wow::list", 
			"List all processes that correspond to supported versions of World of Warcraft"
		},

		{{"info::process"}, 
			"info::process", 
			"Displays image name, process id, file path, and various other information about the attached process"
		},

		{{"info::game", "info"}, 
			"info::game", 
			"Displays game statis and information about the attached process"
		},

		{{"dump::target"}, 
			"dump::target [base|descriptors|location|addresses]", 
			"Dumps the specified information about the player's current target to cout"
		},

		{{"dump::local"}, 
			"dump::local [base|descriptors|location|addresses]",
			"Dumps information about the local player to cout"
		},

		{{"synonyms"}, 
			"synonyms <command name>", 
			"Displays a list of synonyms to the given command"
		},

		{{"help"}, 
			"help <command>", 
			"Displays help text for the given command"
		},

		{{"list_commands", "cmds", "command_list", "commands"}, 
			"list_commands", 
			"Displays a list of supported commands"
		},

		{{"supported", "supported_build", "supported_version"},
			"supported_build", 
			"Displays the supported versions of World of Warcraft"
		},
	};

	void attach(const std::uint32_t process_id)
	{
		try
		{
			wow::attach_process(process_id);
			std::wcout << "Attached to process " << wow::process().name() << " (" << process_id << ") successfully.\n";

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			menu::prompt = converter.from_bytes(wow::account::name());
			menu::prompt += L">";
		}

		catch (error::memory_disparity& e)
		{
			std::cout 
				<< "Unable to attach to process with pid = " << process_id << ".\n"
				<< e.what() << '\n';
		}

		catch (distant::windows_error& e)
		{
			std::cout
				<< "Unable to attach to process with pid = " << process_id << ".\n"
				<< e << '\n';
		}
	}

	void help(std::string command)
	{
		if (!command_list.is_command(command))
		{
			std::cout << "No help text for the given command\n";
			return;
		}

		std::cout << "Help text: ";
		std::cout << command_list[command].help << "\n\n";
		std::cout << "Usage: " << command_list[command].usage << '\n';
	}

	void synonyms(std::string command)
	{
		if (!command_list.is_command(command))
		{
			std::cout << "No synonyms for the given command\n";
			return;
		}

		std::cout << "Synonyms: ";
		for (const auto& syn : command_list[command].synonyms)
			std::cout << syn << ", ";
		std::cout << '\n';
	}

	void list_commands()
	{
		std::cout << "Command list: ";
		for (const auto& command : command_list)
			std::cout << command.synonyms[0] << ", ";
		std::cout << '\n';
	}

	void wow_list()
	{
		std::cout << "Support World of Warcraft processes:\n";
		for (const auto& process : distant::snapshot<distant::process<>>{})
		{
			if (wow::is_process_supported(process))
			{
				std::wcout
					<< process.name() << " (" << process.id()
					<< ")\nFile path: " << process.file_path() << "\n"
					<< "Account name: " << distant::memory::read<std::string>(process, wow::offsets::login_status::account_name).c_str() << "\n\n";
			}
		}
	}

	void info_process()
	{
		if (!wow::process())
		{
			std::cerr << "Not attached to any supported instance of World of Warcraft!\n";
			return;
		}

		std::wcout << "Process information:\n"
			<< "Name: " << wow::process().name() << '\n'
			<< "Id: " << wow::process().id() << '\n'
			<< "File path: " << wow::process().file_path() << '\n'
			<< "Is running: " << wow::process().is_active() << '\n'
			<< "Is being debugged: " << wow::process().is_being_debugged() << "\n";
	}

	void info_game()
	{
		if (!wow::process())
		{
			std::cerr << "Not attached to any supported instance of World of Warcraft!\n";
			return;
		}

		std::cout << "**** Game information ****\n"
			<< "Ingame: " << wow::ingame() << '\n'
			<< "Account name: " << wow::account::name() << '\n'
			<< "Local player name: " << wow::entities::local_player().name() << "\n";
	}

	void supported_build()
	{
		std::cout << "Supported build: " << wow::supported_build << "\n";
	}

	void dump_target(std::string command)
	{
		if (!wow::ingame())
		{
			std::cerr << "Not ingame\n";
			return;
		}

		const auto target_opt = wow::entities::local_player().target();
		if (target_opt)
		{
			const auto& target = *target_opt;
			if (command == "base")
			{
				std::cout << wow::entities::make_object_dump(target) << '\n';
			}
			else if (command == "descriptors")
			{

			}
			else if (command == "location")
			{

			}
			else if (command == "addresses")
			{

			}

			// base|descriptors|location|addresses
		}
		else
		{
			std::cerr << "Player does not have a target\n";
			return;
		}
	}
	void dump_local(std::string command)
	{
		if (!wow::ingame())
		{
			std::cerr << "Not ingame\n";
			return;
		}

		if (command == "base")
		{

		}
		else if (command == "descriptors")
		{

		}
		else if (command == "location")
		{

		}
		else if (command == "addresses")
		{

		}

		// base|descriptors|location|addresses
		std::cout << wow::entities::make_object_dump(wow::local_player()) << '\n';
	}
}

template <typename Fn, typename Tuple, std::size_t... Is>
void invoke_command_impl(Fn&& fn, Tuple&& tuple, std::index_sequence<Is...> seq)
{
	using namespace utility;

	fn(
		boost::lexical_cast<function_traits<function_ptr_decay_t<Fn>>::template argument_type<Is>>
			(std::get<Is>(std::forward<Tuple>(tuple)))...
	);
}

template <typename Fn, typename... Strings, 
	typename = std::enable_if_t<
		utility::arity<Fn>() == sizeof...(Strings)
	>>
void invoke_command(Fn&& fn, Strings&&... strings)
{
	invoke_command_impl(
		std::forward<Fn>(fn),
		std::make_tuple(std::forward<Strings>(strings)...),
		std::make_index_sequence<sizeof...(Strings)>{}
	);
}

void parse_tokens(const std::vector<std::string>& tokens)
{
	const auto arity = [](const auto& tokens)
	{
		return tokens.size() - 1;
	};

	const auto& cmd = tokens[0];

	try
	{
		if (commands::command_list["help"].is_synonym(cmd))
		{
			switch (arity(tokens))
			{
			case 0: invoke_command(commands::help, ""); break;
			case 1: invoke_command(commands::help, tokens[1]); break;
			}
		}

		else if (arity(tokens) == 1 && commands::command_list["attach"].is_synonym(cmd))
			invoke_command(commands::attach, tokens[1]);

		else if (commands::command_list["dump::local"].is_synonym(cmd))
		{
			if (arity(tokens) == 0)
				invoke_command(commands::dump_local, "");
			else
				invoke_command(commands::dump_local, tokens[1]);
		}

		else if (commands::command_list["dump::target"].is_synonym(cmd))
		{
			if (arity(tokens) == 0)
				invoke_command(commands::dump_target, "");
			else
				invoke_command(commands::dump_target, tokens[1]);
		}

		else if (commands::command_list["list_commands"].is_synonym(cmd))
			invoke_command(commands::list_commands);

		else if (arity(tokens) == 1 && commands::command_list["synonyms"].is_synonym(cmd))
			invoke_command(commands::synonyms, tokens[1]);

		else if (commands::command_list["wow::list"].is_synonym(cmd))
			invoke_command(commands::wow_list);

		else if (commands::command_list["info::game"].is_synonym(cmd))
			invoke_command(commands::info_game);

		else if (commands::command_list["info::process"].is_synonym(cmd))
			invoke_command(commands::info_process);

		else if (commands::command_list["supported_build"].is_synonym(cmd))
			invoke_command(commands::supported_build);
		
	}

	catch (boost::bad_lexical_cast& e)
	{
		std::cout << "Error: Invalid parameters for the given command\n";
		std::cout << "Usage: " << commands::command_list[cmd].usage << '\n';
	}

	std::cout << '\n';
}

void parse_command(const std::string& command_string)
{
	std::vector<std::string> tokens;

	// A quick whitespace-separator lexing of the command string
	boost::split(tokens, command_string, boost::is_any_of(" "));

	parse_tokens(tokens);
}