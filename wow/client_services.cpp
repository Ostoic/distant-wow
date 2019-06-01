#include "client_services.hpp"

#include "offsets.hpp"
#include "memory/operations.hpp"

namespace distant::wow::client_services
{
	uint message_count()
	{
		return memory::read_offset(offsets::client_services::num_processed_messages);
	}
}