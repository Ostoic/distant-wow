#pragma once

#include <distant/memory/address.hpp>

namespace memory
{
	using address = distant::address;

	template <typename T>
	class offset : public distant::address
	{
	public:
		constexpr offset() noexcept = default;

		constexpr offset(const address address) noexcept
			: distant::address(address) {}
	};

	template <typename T>
	using function = address;
}
