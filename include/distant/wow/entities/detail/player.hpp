#pragma once

#include "../../memory/address.hpp"

namespace distant::wow::entities::detail
{
	template <typename Object>
	memory::address get_name_ptr(wow::guid guid);

	template <typename Object>
	std::string load_name(wow::guid guid);
}

// Implementation:
#include "impl/player.hxx"
