#pragma once

#include <distant/memory/address.hpp>

namespace memory
{
	using address = distant::address;

	template <typename T>
	using offset = address;

	template <typename T>
	using function = address;
}
