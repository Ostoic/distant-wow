#pragma once

#include <distant/process.hpp>

namespace wow
{
	distant::process<>& process();

	void attach_process(distant::process<>&& process);
}
