#pragma once

#include "address.hpp"

namespace memory
{
	template <typename T>
	T read(address, std::size_t = sizeof(T));

	template <typename T>
	T read_offset(offset<T> offset);

	template <typename T>
	T read_offset(address base, offset<T> offset);

	template <typename T>
	void write(address, const T&);
}

// Implementation:
#include "impl/operations.hxx"
