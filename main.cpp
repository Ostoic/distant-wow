// WoW Memory Tool.cpp : Defines the entry point for the console application.

#include "main.h"

#include <thread>
#include <optional>

#include <wow/process.hpp>
#include <wow/ui.hpp>
#include <wow/state.hpp>
#include <wow/build.hpp>
#include <wow/offsets.hpp>
#include <wow/objects/all.hpp>
#include <wow/objects/display_ids.hpp>

#include <boost/sml.hpp>
#include <boost/iterator/filter_iterator.hpp>

#include <distant.hpp>

#include <mutex>

distant::process<> get_wow_choice()
{
	//namespace sml = boost::sml;

	using process = distant::process<>;
	using distant::snapshot;

	try
	{
		auto proc_list = distant::snapshot<process>().as<std::vector>([](const auto& proc)
		{
			return wow::is_process_supported(proc);
		});

		std::cout << "WoW Process ids:\n";
		for (const auto& process : proc_list)
			std::cout << "(" << process.id() << ", " << distant::memory::read<std::string>(process, wow::offsets::local_player::name, 16) << ")\n";
		std::cout << std::endl;

		const auto find_pid = [&proc_list](const auto pid)
		{
			return std::find_if(proc_list.begin(), proc_list.end(), [pid](const auto& proc)
			{
				return proc.id() == pid;
			});
		};

		const auto good_input = [](auto& pid)
		{
			std::cout << "Select a WoW process: ";
			std::cin >> pid;
			return std::cin.good();
		};

		std::size_t pid = 0;
		auto found = proc_list.end();

		while (!good_input(pid) || (found = find_pid(pid)) == proc_list.end())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::size_t>::max(), '\n');
		}

		auto& wow = *found;

		std::cout << "Wow process " << wow.id() << " chosen with path: " << wow.file_path() << '\n';
		return std::move(wow);
	}
	catch (std::system_error& e)
	{
		std::cout << e.what() << " (" << e.code() << ")\n";
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	return {};
}

struct fishing_bobber_predicate
{
	bool operator()(const wow::game_object& obj) const
	{
		return obj.name() == "Fishing Bobber";
	}
};

template <typename T>
void test_f(memory::offset<T> offset)
{

}

int main()
{
	auto t = memory::offset<int>(0);

	test_f(t);

	std::cout << std::boolalpha;

	while (true)
	{
		wow::attach_process(get_wow_choice());
		if (!wow::process().is_active())
		{
			std::cout << "Process not running.\n";
			continue;
		}

		if (!wow::ingame())
		{
			std::cout << "Not ingame.\n";
			continue;
		}

		try
		{
			auto version = memory::read_offset(wow::offsets::build_info::version_name);

			const auto& local_player = wow::local_player();
			std::cout << wow::make_object_dump(local_player);

			wow::object_manager<wow::game_object>{}
				.for_each([](wow::game_object& obj)
			{
				std::cout << wow::make_object_dump(obj);
				//obj.change_owner(local_player);
				//obj.set_flags(0);

				//std::cout << "Now owned by " << obj.owner()->get().name() << "\n\n";
			}, fishing_bobber_predicate{});
			
			/*
			const auto closest_lamp_it = std::min_element(begin, end, [&local_player](const auto& unit1, const auto& unit2)
			{
				const auto local_pos = local_player.position();
				return geometry::distance(local_pos, unit1.position()) < geometry::distance(local_pos, unit2.position());
			});

			if (closest_lamp_it != end)
			{
				std::cout << "Closest lamp post:\n";
				auto& closest_lamp = *closest_lamp_it;
				closest_lamp.change_owner(local_player);
				std::cout << "Owner: " << ((closest_lamp.owner()) ? closest_lamp.owner()->get().name() : "None") << '\n';
			}*/

			//wow::ui::interact(objects::local_player());
			
			std::cout << "Cache size: " << wow::object_manager<wow::unit>().size() << '\n';
		}
		catch (error::game_error& e) // Game issue: process crashed, not ingame, etc
		{
			std::cout << "Game error: " << e.what() << '\n';
		}
		catch (error::memory_disparity& e)
		{
			std::cout << "Memory disparity: " << e.what() << '\n';
		}
		catch (distant::windows_error& e) // system api issue
		{
			std::cout << e << '\n';
		}

		std::cout << '\n';
	}

	return 0;
}
