#pragma once

#include "../../memory/address.hpp"
#include "../game_object.hpp"

namespace distant::wow::entities::detail
{
	template <typename Object>
	memory::address get_name_ptr(memory::address base);

	template <>
	memory::address get_name_ptr<entities::game_object>(memory::address base);

	template <typename Object>
	std::string load_name(memory::address base);

	template <>
	std::string load_name<entities::game_object>(memory::address base);
}

// Implementation:
#include "impl/game_object.hxx"
