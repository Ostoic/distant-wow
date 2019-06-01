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
			return 0;

		// Get pointer to current object manager.
		const auto client_conn = memory::read_offset(offsets::client_services::client_connection);

		// Dereferencing the given pointer returns object manager's address.
		return memory::read_offset(client_conn, offsets::object_manager::current_mgr);
	}
}
