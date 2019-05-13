#include "object_manager.hpp"


#include "../../offsets.hpp"
#include "../../state.hpp"
#include "../../error/game_error.hpp"
#include "../../memory/operations.hpp"

//#include <wow/offsets.hpp>
//#include <wow/state.hpp>
//#include <error/game_error.hpp>
//#include <memory/impl/operations.hxx>

namespace distant::wow::entities::detail
{
	memory::address get_manager()
	{
		if (!ingame())
			throw error::game_error("[distant::wow::entities::detail::get_manager] Not ingame");

		// Get pointer to current object manager.
		const auto pointer = memory::read_offset(offsets::client_connection);

		// Dereferencing the given pointer returns object manager's address.
		return memory::read_offset(pointer, offsets::object_manager::current_mgr);
	}
}
