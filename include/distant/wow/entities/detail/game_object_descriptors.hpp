#pragma once

#include "../../primitives.hpp"
#include "../../memory/address.hpp"

namespace distant::wow::entities::detail
{
	struct game_object_descriptors
	{
		memory::address base; // 0x00

		struct 
		{
			wow::guid created_by; // 0x18
			wow::uint display_id; // 0x20
			wow::flags flags; // 0x24
			float parent_rotation; // 0x28

		} ownership_chunk;

		wow::byte other_flags; // 0x44
	};
}
