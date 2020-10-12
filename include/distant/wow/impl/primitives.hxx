#pragma once
#include "../primitives.hpp"

#include <iomanip>

#include <distant/types.hpp>

namespace distant::wow
{
//{ctor}:
	inline guid::guid() noexcept
		: low(0), high(0)
	{}

	constexpr guid::guid(const unsigned long low, const unsigned long high) noexcept
		: low(low), high(high) 
	{}

	constexpr guid::guid(const std::int64_t guid)noexcept
		: low( 
			distant::make_dword(
				distant::get_byte<0>(guid),
				distant::get_byte<1>(guid),
				distant::get_byte<2>(guid),
				distant::get_byte<3>(guid)
			)
		)
		, high(
			distant::make_dword(
				distant::get_byte<4>(guid),
				distant::get_byte<5>(guid),
				distant::get_byte<6>(guid),
				distant::get_byte<7>(guid)
			)
		) 
	{}

//free:
	constexpr bool operator==(const guid& lhs, const guid& rhs) noexcept
	{
		return (lhs.low == rhs.low && lhs.high == rhs.high);
	}

	constexpr bool operator!=(const guid& lhs, const guid& rhs) noexcept
	{
		return !operator==(lhs, rhs);
	}

	template <typename CharT, typename TraitsT>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const guid& guid)
	{
		const auto f = stream.flags();

		stream << std::hex;
		stream << std::setfill('0') << std::setw(sizeof(guid));
		stream << guid.high << guid.low;
		stream.flags(f);
		return stream;
	}

	template <typename CharT, typename TraitsT>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const flags& flags)
	{
		const auto f = stream.flags();

		stream << std::hex;
		stream << std::setfill('0') << std::setw(sizeof(guid));
		stream << static_cast<dword>(flags);
		stream.flags(f);
		return stream;
	}
}
