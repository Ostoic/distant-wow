#pragma once

#include <iostream>

#include "../entities/object.hpp"
#include "../entities/game_object.hpp"
#include "../entities/unit.hpp"
#include "../entities/player.hpp"

namespace distant::wow::dump
{
	template <typename Object>
	struct object_dump
	{
	public:
		explicit object_dump(const Object& entity) noexcept;

		const Object& entity;
	};

	template <typename Object>
	struct descriptor_dump
	{
		explicit descriptor_dump(const Object& entity) noexcept;

		const Object& object;
	};

	template <typename Object>
	struct location_dump
	{
		explicit location_dump(const Object& object) noexcept;

		const Object& object;
	};

	template <typename Object>
	object_dump<Object> make_object_dump(const Object& object) noexcept;

	template <typename Object>
	descriptor_dump<Object> make_descriptor_dump(const Object& object) noexcept;

	template <typename Object>
	location_dump<Object> make_location_dump(const Object& object) noexcept;

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const object_dump<Object>& dump);

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const descriptor_dump<Object>& dump);
}

namespace distant::wow
{
	template <typename Object>
	using object_dump = dump::object_dump<Object>;

	template <typename Object>
	using descriptor_dump = dump::descriptor_dump<Object>;

	using dump::make_object_dump;
	using dump::make_location_dump;
	using dump::make_descriptor_dump;
}

#include "impl/object_dump.hxx"
