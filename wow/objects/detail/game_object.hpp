#pragma once

#include <memory/address.hpp>

#include "../game_object.hpp"

namespace wow::objects::detail
{
	template <typename Object>
	memory::address get_name_ptr(memory::address base);

	template <>
	memory::address get_name_ptr<objects::game_object>(memory::address base);

	template <typename Object>
	std::string load_name(memory::address base);

	template <>
	std::string load_name<objects::game_object>(memory::address base);
}

// Implementation:
#include "impl/game_object.hxx"
