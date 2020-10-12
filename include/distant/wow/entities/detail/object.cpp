#include "object.hpp"

#include "../../memory/address.hpp"
#include "../../memory/operations.hpp"
#include "../../offsets.hpp"

#include "../object_manager.hpp"

namespace distant::wow::entities::detail
{
	memory::address next_object_base(const memory::address base)
	{
		return memory::read<memory::address>(base + memory::address(wow::offsets::object::next));
	}

	object_type load_object_type(const memory::address base)
	{
		return memory::read<object_type>(base + memory::address(wow::offsets::object::type));
	}

	wow::guid load_object_guid(const memory::address base)
	{
		return memory::read<wow::guid>(base + memory::address(wow::offsets::object::guid));
	}

	bool valid_base_address(const memory::address base)
	{
		return (base != 0 && (base & 1) == 0);
	}
}
