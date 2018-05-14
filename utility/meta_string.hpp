#pragma once

#include <utility>

namespace utility
{
	constexpr std::size_t string_length(const char* string)
	{
		std::size_t count = 0;
		for (unsigned int i = 0; string[i] != 0; ++i)
			count++;

		return count;
	}
}
