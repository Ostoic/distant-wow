#include "time.hpp"

#include "offsets.hpp"
#include "../memory/operations.hpp"

namespace wow::time
{
	std::int64_t os_get_async_time_ms()
	{
		
	}

	time_point timestamp()
	{
		const auto count = memory::read_offset(offsets::time::timestamp);
		return time_point(duration(count));
	}

	time_point last_action();

	void set_last_action(time_point tick_count);
	void set_timestamp(time_point tick_count);
}