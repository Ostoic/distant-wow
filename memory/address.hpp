#pragma once

#include <distant/memory/address.hpp>

namespace memory
{
	using address = distant::address;

	template <typename T>
	class offset 
	{
	public:
		constexpr offset() noexcept = default;

		constexpr offset(const address address) noexcept
			: address_(address) {}

		constexpr operator address() const noexcept
		{
			return address_;
		}

	private:
		address address_;
	};

	template <typename T>
	using function = address;
}
