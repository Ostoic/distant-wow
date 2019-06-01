#include "account.hpp"

#include "memory/operations.hpp"

namespace distant::wow::account
{
	std::string name()
	{
		return memory::read_offset(offsets::login_status::account_name);
	}
}