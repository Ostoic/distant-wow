#pragma once
#include "../operations.hpp"

#include <type_traits>

#include <distant/error/winapi_error.hpp>
#include <distant/memory/virtual_memory.hpp>

#include "../../error/game_error.hpp"
#include "../../primitives.hpp"
#include "../../process.hpp"
#include "../../geometry/vector.hpp"

namespace distant::memory
{
	template <>
	struct operations_traits<wow::geometry::vector>
	{
		template <typename AddressT>
		static wow::geometry::vector read(const process<vm_read>& process, const address<AddressT> address, const std::size_t size)
		{
			wow::geometry::vector vector = {};
			SIZE_T bytes_read = 0;

			if (!::ReadProcessMemory(
				process.handle().native_handle(),
				reinterpret_cast<boost::winapi::LPCVOID_>(static_cast<AddressT>(address)),
				vector.data(),
				size,
				&bytes_read
			))
				throw winapi_error("[wow::memory::read<geometry::vector>] ReadProcessMemory failed, " + std::to_string(bytes_read) + " bytes read");

			return vector;
		}

		template <typename AddressT>
		static wow::geometry::vector write(const process<vm_w_op>& process, const address<AddressT> address, const wow::geometry::vector& vector)
		{
			SIZE_T bytes_written = 0;

			if (!::WriteProcessMemory(
				process.handle().native_handle(),
				reinterpret_cast<boost::winapi::LPVOID_>(static_cast<AddressT>(address)),
				vector.data(),
				vector.size(),
				&bytes_written
			))
				throw winapi_error("[wow::memory::write<geometry::vector>] WriteProcessMemory failed, " + std::to_string(bytes_written) + " bytes written");

			return vector;
		}
	};
}

namespace distant::wow::memory
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
		distant::memory::write(wow::process(), address, data);
	}
} // namespace memory
