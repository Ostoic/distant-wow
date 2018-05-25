#pragma once

#include <distant/process.hpp>

namespace wow
{
	distant::process<>& process();

	void attach_process(std::uint32_t process_id);
	void attach_process(distant::process<>&& process);
}
