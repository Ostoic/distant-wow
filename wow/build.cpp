#include "build.hpp"

#include "offsets.hpp"
#include <distant/memory/virtual_memory.hpp>

#include <sstream>

namespace wow
{
	bool is_process_supported(const distant::process<distant::process_rights::vm_read>& process)
	{
		try
		{
			const auto version_name  = distant::memory::read<std::string>(process, wow::offsets::build_info::version_name, 17);
			const auto major_version = distant::memory::read<std::string>(process, wow::offsets::build_info::major_version, 5);
			const auto minor_version = distant::memory::read<std::string>(process, wow::offsets::build_info::minor_version, 5);

			std::stringstream result;
			result << version_name << " " << major_version << " (" << minor_version << ")";
			return supported_build == result.str();
		}
		catch (distant::windows_error&) {}

		return false;
	}
}