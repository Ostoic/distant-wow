#pragma once

#include "address.hpp"

namespace wow::memory
{
	template <typename T>
	struct offset_value_type;

	template <typename T>
	struct offset_value_type<memory::offset<T>>
	{
		using type = T;
	};

	template <typename T>
	using offset_value_type_t = offset_value_type<memory::offset<T>>::type;
}
