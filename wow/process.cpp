#include "process.hpp"

#include "build.hpp"
#include "../error/game_error.hpp"

namespace wow
{
	distant::process<>& process()
	{
		static distant::process<> wow_process;
		return wow_process;
	}

	void attach_process(distant::process<>&& process)
	{
		//if (is_process_supported(process))
			//throw error::memory_disparity("[wow::attach_process] WoW version not supported");

		wow::process() = std::move(process);
	}
}