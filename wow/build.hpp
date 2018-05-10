#pragma once

#include <distant/process.hpp>

namespace wow
{
	bool is_process_supported(const distant::process<distant::process_rights::vm_read>& process);

	constexpr auto supported_build = "World of Warcraft 3.3.5 (12340)";
}
