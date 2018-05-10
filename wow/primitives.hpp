#pragma once

#include <boost/winapi/basic_types.hpp>

#include <iostream>
#include <variant>
#include <optional>

namespace wow
{
	using dword = boost::winapi::DWORD_;
	using flags = dword;
	using uint = unsigned int;
	using byte = char;

	template <typename T>
	using optional_ref = std::optional<std::reference_wrapper<T>>;

	struct guid
	{
		unsigned long low;
		unsigned long high;

		guid() noexcept;

		constexpr guid(unsigned long low, unsigned long high) noexcept;

		explicit constexpr guid(std::int64_t guid) noexcept;
	};

	constexpr bool operator==(const guid& lhs, const guid& rhs) noexcept;
	constexpr bool operator!=(const guid& lhs, const guid& rhs) noexcept;

	std::ostream& operator<<(std::ostream& stream, const guid& guid);
}

#include "impl/primitives.hxx"
