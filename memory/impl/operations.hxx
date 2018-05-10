#pragma once
#include "../operations.hpp"

#include <type_traits>

#include <main.h>
#include <distant/error/windows_error.hpp>
#include <error/game_error.hpp>

#include <wow/primitives.hpp>
#include <wow/process.hpp>

namespace memory
{
	namespace detail
	{
		// Plain-Old-Data type implementation for memory::read
		template <typename T>
		struct read_impl
		{
			T operator()(const address address) const
			{
				T buffer = T{};

				if (!ReadProcessMemory(wow::process().handle().native_handle(),
				                       reinterpret_cast<boost::winapi::LPCVOID_>(static_cast<wow::dword>(address)), &buffer,
				                       sizeof(T), nullptr))
				{
					if (!wow::process().is_active())
						throw error::game_error("[memory::read<pod>] Process is not running");
					throw distant::windows_error("[memory::read<pod>()] ReadProcessMemory failed");
				}

				return buffer;
			}
		}; // struct read_impl 

		// std::string implementation for memory::read
		template <>
		struct read_impl<std::string>
		{
			static constexpr auto default_length = 100;

			std::string operator()(const address address, const std::size_t size = default_length) const
			{
				std::string buffer(size, 0);

				if (!ReadProcessMemory(wow::process().handle().native_handle(),
				                       reinterpret_cast<boost::winapi::LPCVOID_>(static_cast<wow::dword>(address)), buffer.data(),
				                       buffer.size(), nullptr))
				{
					if (!wow::process().is_active())
						throw error::game_error("[memory::read<std::string>] Process is not running");
					throw distant::windows_error("[memory::read<std::string>] ReadProcessMemory failed");
				}

				return buffer.c_str();
			}
		}; // struct read_impl 

		// memory::address implementation for memory::read
		template <>
		struct read_impl<address>
		{
			address operator()(const address address) const
			{
				wow::dword buffer;

				if (!ReadProcessMemory(
					wow::process().handle().native_handle(),
					reinterpret_cast<boost::winapi::LPCVOID_>(static_cast<wow::dword>(address)),
					&buffer,
					sizeof(buffer),
					nullptr
				))
				{
					if (!wow::process().is_active())
						throw error::game_error("[memory::read<memory::address>] Process is not running");
					throw distant::windows_error("[memory::read<memory::address>] ReadProcessMemory failed");
				}

				return memory::address{buffer};
			}
		}; // struct read_impl 

		// Plain-Old-Data type implementation for memory::write
		template <typename T = std::enable_if_t<std::is_pod<T>::value, T>>
		struct write_impl
		{
			void operator()(const address address, const T& data) const
			{
				T buffer = data;

				if (!WriteProcessMemory(wow::process().handle().native_handle(),
				                        reinterpret_cast<boost::winapi::LPVOID_>(static_cast<wow::dword>(address)), &buffer,
				                        sizeof(T), nullptr))
				{
					if (!wow::process().is_active())
						throw error::game_error("[memory::write<pod>] Process is not running");
					throw distant::windows_error("[memory::write<pod>()] WriteProcessMemory failed");
				}
			}
		}; // struct write_impl 

		// Plain-Old-Data type implementation for memory::read
		template <>
		struct write_impl<address>
		{
			void operator()(const address address, const memory::address data) const
			{
				const auto buffer = static_cast<wow::dword>(data);

				if (!WriteProcessMemory(wow::process().handle().native_handle(),
				                        reinterpret_cast<boost::winapi::LPVOID_>(static_cast<wow::dword>(address)), &buffer,
				                        sizeof(wow::dword), nullptr))
				{
					if (!wow::process().is_active())
						throw error::game_error("[memory::read<memory::address>] Process is not running");
					throw distant::windows_error("[memory::write<memory::address>()] WriteProcessMemory failed");
				}
			}
		}; // struct write_impl 

		// std::string implementation for memory::write
		template <>
		struct write_impl<std::string>
		{
			// const ref write (copies input string)
			void operator()(const address address, const std::string& data) const
			{
				const auto& copy = data;
				if (!WriteProcessMemory(wow::process().handle().native_handle(),
				                        reinterpret_cast<boost::winapi::LPVOID_>(static_cast<wow::dword>(address)), copy.data(),
				                        copy.size() + 1, nullptr))
				{
					if (!wow::process().is_active())
						throw error::game_error("[memory::write<std::string>] Process is not running");
					throw distant::windows_error("[memory::write<std::string>()] WriteProcessMemory failed");
				}
			}

			// move write (uses input string buffe)
			void operator()(const address address, std::string& data) const
			{
				if (!WriteProcessMemory(wow::process().handle().native_handle(),
				                        reinterpret_cast<boost::winapi::LPVOID_>(static_cast<wow::dword>(address)), data.data(),
				                        data.size() + 1, nullptr))
				{
					if (!wow::process().is_active())
						throw error::game_error("[memory::write<std::string>] Process is not running");
					throw distant::windows_error("[memory::write<std::string>()] WriteProcessMemory failed");
				}
			}
		}; // struct write_impl 
	} // namespace detail

	template <typename T>
	T read(const address address)
	{
		return detail::read_impl<T>{}(address);
	}

	template <typename T>
	T read(const address address, std::size_t size)
	{
		return detail::read_impl<T>{}(address, size);
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
	void write(const address address, T& data)
	{
		detail::write_impl<T>{}(address, data);
	}

	template <typename T>
	void write(const address address, const T& data)
	{
		detail::write_impl<T>{}(address, data);
	}
}
