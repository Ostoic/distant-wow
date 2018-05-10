#pragma once

#include <distant/process.hpp>

namespace wow
{
	distant::process<>& process();

	void set_process(distant::process<>&& process);
}
