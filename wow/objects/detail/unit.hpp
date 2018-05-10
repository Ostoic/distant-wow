#pragma once

#include <memory/address.hpp>

namespace wow::objects::detail
{
	template <typename Object>
	memory::address get_name_ptr(memory::address base);

	template <typename Object>
	std::string load_name(memory::address base);
}

#include "impl/unit.hxx"
