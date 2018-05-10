#pragma once

#include <memory/address.hpp>

namespace objects::detail
{
	template <typename Object>
	memory::address get_name_ptr(memory::address base);

	template <typename Object>
	std::string load_name(memory::address base);
}

#include <objects/detail/impl/unit.hxx>
