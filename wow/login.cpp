#include "login.hpp"

#include "constants.hpp"
#include "offsets.hpp"
#include "../memory/operations.hpp"

namespace wow::login
{
	uint queue_position()
	{
		return memory::read_offset(wow::offsets::login_status::queue_position);
	}
}