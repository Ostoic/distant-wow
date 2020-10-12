#pragma once

#include "fwd.hpp"

#include <optional>
#include <ostream>
#include <string_view>
#include <type_traits>

namespace distant::wow::entities
{
	enum class object_type
	{
		local			= 0,
		item			= 1,
		container		= 2,
		unit			= 3,
		player			= 4,
		game_object		= 5,
		dynamic_object	= 6,
		corpse			= 7,
		object			= 8,
	};

	constexpr std::string_view to_string(const object_type type) noexcept
	{
		switch (type)
		{
		case object_type::local: 
			return "local";

		case object_type::item:
			return "item";

		case object_type::container: 
			return "container";

		case object_type::unit: 
			return "unit";

		case object_type::player: 
			return "player";

		case object_type::game_object: 
			return "game_object";

		case object_type::dynamic_object: 
			return "dynamic_object";

		case object_type::corpse: 
			return "corpse";

		case object_type::object:
			return "object";
		}

		return "object";
	}

	std::ostream& operator<<(std::ostream& stream, const object_type type)
	{
		stream << to_string(type);
		return stream;
	}

	constexpr bool derives_from(const object_type derived, const object_type base) noexcept
	{
		if (base == derived)
			return true;

		if (derived != object_type::unit && derived != object_type::player && derived != object_type::game_object)
			return false;

		switch (base)
		{
		case object_type::object:
			return true;

		case object_type::unit:
				return derived == object_type::player;
		}

		return false;
	}

	template <typename T>
	constexpr bool type_match(object_type) noexcept
	{
		return false;
	}

	template <>
	constexpr bool type_match<object>(object_type t) noexcept
	{
		return t == object_type::object;
	}

	template <>
	constexpr bool type_match<unit>(object_type t) noexcept
	{
		return t == object_type::unit;
	}

	template <>
	constexpr bool type_match<player>(object_type t) noexcept
	{
		return t == object_type::player;
	}

	template <>
	constexpr bool type_match<game_object>(object_type t) noexcept
	{
		return t == object_type::game_object;
	}
}
