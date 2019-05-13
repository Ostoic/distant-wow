#include "process.hpp"

#include "build.hpp"
#include "error/game_error.hpp"

namespace distant::wow
{
	distant::process<>& process()
	{
		static distant::process<> wow_process;
		return wow_process;
	}

	void attach_process(const std::uint32_t process_id)
	{
		return attach_process(distant::process<>{process_id});
	}

	void attach_process(distant::process<>&& process)
	{
		if (!process || !process.is_active())
			throw distant::winapi_error("[wow::attach_process] Invalid process");

		if (!is_process_supported(process))
			throw error::memory_disparity("[wow::attach_process] WoW version not supported");

		wow::process() = std::move(process);
	}

	void reset_process() noexcept
	{
		wow::process() = {};
	}
}