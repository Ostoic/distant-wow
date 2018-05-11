#pragma once
#include "../operations.hpp"

#include <type_traits>

#include <distant/error/windows_error.hpp>
#include <error/game_error.hpp>

#include <wow/primitives.hpp>
#include <wow/process.hpp>

#include <geometry/vector.hpp>

#include <distant/memory/virtual_memory.hpp>

namespace distant::memory::customize
{
	/// @brief memory::read geometry::vector customization point.
	template <>
	struct read<geometry::vector>
	{
		template <typename AddressT>
		static geometry::vector invoke(const process<vm_read>& process, const address<AddressT> address, const std::size_t size)
		{
			geometry::vector vector = {};
			SIZE_T bytes_read = 0;

			/// Todo: Read until null terminator or threshold
			if (!::ReadProcessMemory(
				process.handle().native_handle(),
				reinterpret_cast<boost::winapi::LPCVOID_>(static_cast<AddressT>(address)),
				vector.data(),
				size,
				&bytes_read
			))
				throw windows_error("[memory::read<geometry::vecto>] ReadProcessMemory failed, " + std::to_string(bytes_read) + " bytes read");

			return vector;
		}
	};
}
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
