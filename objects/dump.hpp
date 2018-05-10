#pragma once

#include <iostream>

#include "object.hpp"
#include "game_object.hpp"
#include "unit.hpp"
#include "player.hpp"

namespace objects
{
	template <typename Object>
	struct dump
	{
	public:
		explicit dump(const Object& object) noexcept;

		const Object& object;
	};

	template <typename Object>
	struct descriptor_dump : dump<Object>
	{
		explicit descriptor_dump(const Object& object) noexcept;
	};

	template <typename Object>
	dump<Object> make_dump(const Object& object) noexcept;

	template <typename Object>
	dump<Object> make_descriptor_dump(const Object& object) noexcept;

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const dump<Object>& dump);

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const descriptor_dump<Object>& dump);
}

#include "impl/dump.hxx"
