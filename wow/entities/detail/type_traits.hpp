#pragma once

#include "../fwd.hpp"
#include "../types.hpp"

namespace distant::wow::entities::detail
{
	template <typename T>
	constexpr object_type type_to_enum() noexcept;

	template <>
	constexpr object_type type_to_enum<entities::object>() noexcept
	{
		return object_type::object;
	}

	template <>
	constexpr object_type type_to_enum<entities::unit>() noexcept
	{
		return object_type::unit;
	}

	template <>
	constexpr object_type type_to_enum<entities::player>() noexcept
	{
		return object_type::player;
	}

	template <>
	constexpr object_type type_to_enum<entities::game_object>() noexcept
	{
		return object_type::game_object;
	}
}
