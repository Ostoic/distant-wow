#include "state.hpp"
#include "process.hpp"
#include "offsets.hpp"

#include "../memory/operations.hpp"

namespace wow
{
	bool ingame()
	{
		if (!wow::process() || !wow::process().is_active()) 
			return false;

		return memory::read_offset(wow::offsets::game_state::ingame);
	}

	bool logged_in()
	{
		if (!wow::process() || !wow::process().is_active())
			return false;

		return memory::read_offset(wow::offsets::game_state::logged_in);
	}
}