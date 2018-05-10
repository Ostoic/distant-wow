#pragma once

#include <iostream>

#include "object.hpp"
#include "game_object.hpp"
#include "unit.hpp"
#include "player.hpp"

namespace wow::objects
{
	template <typename Object>
	struct object_dump
	{
	public:
		explicit object_dump(const Object& object) noexcept;

		const Object& object;
	};

	template <typename Object>
	struct descriptor_dump
	{
		explicit descriptor_dump(const Object& object) noexcept;

		const Object& object;
	};

	template <typename Object>
	object_dump<Object> make_object_dump(const Object& object) noexcept;

	template <typename Object>
	object_dump<Object> make_descriptor_dump(const Object& object) noexcept;

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const object_dump<Object>& dump);

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const descriptor_dump<Object>& dump);
}

namespace wow
{
	template <typename Object>
	using object_dump = objects::object_dump<Object>;

	template <typename Object>
	using descriptor_dump = objects::descriptor_dump<Object>;

	using objects::make_object_dump;
	using objects::make_descriptor_dump;
}

#include "impl/object_dump.hxx"
