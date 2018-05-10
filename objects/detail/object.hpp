#pragma once

#include <wow/primitives.hpp>
#include <objects/types.hpp>
#include <memory/address.hpp>

namespace objects::detail
{
	memory::address next_object_base(memory::address base);

	object_type load_object_type(memory::address base);

	wow::guid load_object_guid(memory::address base);

	bool valid_base_address(memory::address base);
}
