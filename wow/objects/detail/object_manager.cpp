#include "object_manager.hpp"

#include <wow/offsets.hpp>
#include <memory/impl/operations.hxx>

namespace wow::objects::detail
{
	memory::address get_manager()
	{
		// Get pointer to current object manager.
		const auto pointer = memory::read<memory::address>(memory::address(wow::offsets::client_connection));

		// Dereferencing the given pointer returns object manager's address.
		return memory::read<memory::address>(pointer + memory::address(wow::offsets::object_manager::current_mgr));
	}
}
