#pragma once

#include "primitives.hpp"

#include <chrono>

namespace wow::time
{
	namespace chrono = std::chrono;
	using clock = chrono::high_resolution_clock;
	using duration = chrono::duration<std::int64_t, std::milli>;
	using time_point = chrono::time_point<clock>;

	time_point timestamp();
	time_point last_action();

	void set_last_action(time_point tick_count);
	void set_timestamp(time_point tick_count);
}
