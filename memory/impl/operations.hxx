#pragma once
#include "../operations.hpp"

#include <type_traits>

#include <distant/error/windows_error.hpp>
#include <error/game_error.hpp>

#include <wow/primitives.hpp>
#include <wow/process.hpp>

#include <distant/memory/virtual_memory.hpp>

namespace memory
{
	template <typename T>
	T read(const address address, const std::size_t size)
	{
		return distant::memory::read<T>(wow::process(), address, size);
	}

	template <typename T>
	T read_offset(offset<T> offset)
	{
		return memory::read<T>(offset);
	}

	template <typename T>
	T read_offset(address base, offset<T> offset)
	{
		return memory::read<T>(base + offset);
	}

	template <typename T>
	void write(const address address, const T& data)
	{
		if (!wow::process().is_active())
			throw error::game_error("[memory::write] Process is not running");

		distant::memory::write(wow::process(), address, data);
	}
} // namespace memory
