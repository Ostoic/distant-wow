#pragma once

#include <objects/fwd.hpp>

namespace objects
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

	constexpr bool derives_from(object_type derived, object_type base) noexcept
	{
		if (base == derived)
			return true;

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

	enum class classes
	{
		warrior = 1,
		paladin = 2,
		hunter = 3,
		rogue = 4,
		priest = 5,
		shaman = 7,
		mage = 8,
		warlock = 9,
		druid = 11
	};
}
