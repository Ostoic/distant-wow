#pragma once

#include "memory/address.hpp"

namespace objects::detail
{
	template <typename Object>
	memory::address get_name_ptr(memory::address base);

	template <>
	memory::address get_name_ptr<game_object>(memory::address base);

	template <typename Object>
	std::string load_name(memory::address base);

	template <>
	std::string load_name<game_object>(memory::address base);
}

// Implementation:
#include "objects/detail/impl/game_object.hxx"
