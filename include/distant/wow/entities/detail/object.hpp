#pragma once

#include "../../primitives.hpp"
#include "../../memory/address.hpp"
#include "../types.hpp"

namespace distant::wow::entities::detail
{
	memory::address next_object_base(memory::address base);

	object_type load_object_type(memory::address base);

	wow::guid load_object_guid(memory::address base);

	bool valid_base_address(memory::address base);
}
