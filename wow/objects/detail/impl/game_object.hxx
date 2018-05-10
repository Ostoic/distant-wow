#pragma once
#include "../game_object.hpp"

#include "memory/operations.hpp"
#include "wow/offsets.hpp"

namespace wow::objects::detail
{
	template <>
	inline memory::address get_name_ptr<objects::game_object>(const memory::address base)
	{
		const auto ptr = memory::read<memory::address>(base + wow::offsets::name_cache::go_name_ptr_offset1);
		return memory::read<memory::address>(ptr + wow::offsets::name_cache::go_name_ptr_offset2);
	}

	template <>
	inline std::string load_name<objects::game_object>(const memory::address base)
	{
		return memory::read<std::string>(detail::get_name_ptr<objects::game_object>(base));
	}
}
