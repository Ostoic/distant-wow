#pragma once

#include "address.hpp"

namespace memory
{
	template <typename T>
	T read(address);

	template <typename T>
	T read(address, std::size_t);

	template <typename T>
	T read_offset(offset<T> offset);

	template <typename T>
	T read_offset(address base, offset<T> offset);

	template <typename T>
	void write(address, const T&);

	template <typename T>
	void write(address, T&);
}

// Implementation:
#include "impl/operations.hxx"
