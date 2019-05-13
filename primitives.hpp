#pragma once

#include <boost/winapi/basic_types.hpp>

#include <iostream>
#include <variant>
#include <optional>

namespace distant::wow
{
	using dword = boost::winapi::DWORD_;
	enum class flags : dword {};
	//using flags = dword;

	using uint = unsigned int;
	using byte = char;

	template <class T>
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

	template <typename CharT, typename TraitsT>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const guid& guid);

	template <typename CharT, typename TraitsT>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const flags& flags);
}

#include "impl/primitives.hxx"
