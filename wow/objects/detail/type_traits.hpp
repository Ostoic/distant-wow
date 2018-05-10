#pragma once

#include "../fwd.hpp"
#include "../types.hpp"

namespace wow::objects::detail
{
	template <typename T>
	constexpr object_type type_to_enum() noexcept;

	template <>
	constexpr object_type type_to_enum<objects::object>() noexcept
	{
		return object_type::object;
	}

	template <>
	constexpr object_type type_to_enum<objects::unit>() noexcept
	{
		return object_type::unit;
	}

	template <>
	constexpr object_type type_to_enum<objects::player>() noexcept
	{
		return object_type::player;
	}

	template <>
	constexpr object_type type_to_enum<objects::game_object>() noexcept
	{
		return object_type::game_object;
	}
}
