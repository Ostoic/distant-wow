#pragma once

#include <string>

#include <fmt/core.h>

namespace distant::wow::utility
{
	namespace detail
	{

#pragma warning(disable: 4996)
		// Credit: Kim Thomas on youtube
		// convert from const char* to const wchar_t*
		std::wstring to_str(const char* mbstr, const std::size_t size)
		{
			if (mbstr == nullptr || size == 0)
				return L"";

			std::mbstate_t state; // conversion state

			const char* p = mbstr;

			// get the number of characters
			// when successfully converted
			// http://en.cppreference.com/w/cpp/string/multibyte/mbsrtowcs
			std::size_t clen = std::mbsrtowcs(nullptr, &p, 0 /* ignore */, &state);

			// + 1 is redundant because
			// std::wstring manages terminating null character

			// failed to calculate
			// the character length of the converted string
			if (clen == 0 || clen == static_cast<size_t>(-1))
				return L""; // empty wstring

			// reserve clen characters,
			// wstring reserves +1 character
			std::wstring rlt(clen, L'\0');

			std::size_t converted = std::mbsrtowcs(&rlt[0], &mbstr, rlt.size(), &state);

			// conversion failed
			if (converted == static_cast<std::size_t>(-1))
				return L""; // empty string
			return rlt;
		}

		// convert from const wchar_t* to const char*
		std::string to_str(const wchar_t* wcstr, std::size_t size)
		{
			if (wcstr == nullptr || size == 0)
				return ""; // empty string

			std::mbstate_t state{};

			const wchar_t* p = wcstr;

			// wcsrtombs - [wide char string] to [multi byte string]
			// http://en.cppreference.com/w/cpp/string/multibyte/wcsrtombs
			std::size_t clen = std::wcsrtombs(NULL, &p, 0, &state);
			// +1 is redundant, because
			// std::string manages terminating null character

			// cannot determine or convert to const char*
			if (clen == 0 || clen == static_cast<std::size_t>(-1))
				return ""; // empty string

			std::string rlt(clen, '\0');

			std::size_t converted =
				std::wcsrtombs(&rlt[0], &wcstr, rlt.size(), &state);

			if (converted == static_cast<std::size_t>(-1))
				return ""; // return empty string
			return rlt;
		}

		std::size_t length(const char* string)
		{
			return std::strlen(string);
		}

		std::size_t length(const wchar_t* string)
		{
			return std::wcslen(string);
		}
#pragma warning(default: 4996)
	}

	template <class TargetType, class String>
	TargetType string_cast(String&& string)
	{
		if constexpr (std::is_constructible_v<TargetType, String>)
			return TargetType{std::forward<String>(string)};

		else if constexpr (!std::is_class_v<String>)
			return detail::to_str(std::forward<String>(string), detail::length(string));

		else 
			return detail::to_str(std::forward<String>(string).c_str(), string.size());
	}
}