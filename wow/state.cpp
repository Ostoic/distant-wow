#include "state.hpp"
#include "process.hpp"
#include "offsets.hpp"

#include <distant/memory/virtual_memory.hpp>

namespace wow
{
	bool ingame()
	{
		return distant::memory::read<bool>(wow::process(), wow::offsets::game_state::ingame);
	}
}