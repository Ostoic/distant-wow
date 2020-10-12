#include "state.hpp"
#include "process.hpp"
#include "offsets.hpp"

#include "memory/operations.hpp"

namespace distant::wow
{
	bool ingame()
	{
		if (!attached())
			return false;

		return memory::read_offset(wow::offsets::game_state::ingame);
	}

	bool logged_in()
	{
		if (!attached())
			return false;

		return memory::read_offset(wow::offsets::game_state::logged_in);
	}

	bool attached()
	{
		return wow::process().is_active();
	}

}