#pragma once
#include "../unit.hpp"

#include <memory/operations.hpp>
#include <wow/offsets.hpp>

namespace wow::objects::detail
{
	template <>
	inline memory::address get_name_ptr<objects::unit>(const memory::address base)
	{
		const auto name_pointer = memory::read<memory::address>(base + wow::offsets::name_cache::unit_name_ptr_offset1);
		return memory::read<memory::address>(name_pointer + wow::offsets::name_cache::unit_name_ptr_offset2);
	}

	template <>
	inline std::string load_name<objects::unit>(const memory::address base)
	{
		return memory::read<std::string>(detail::get_name_ptr<unit>(base));
	}
}
