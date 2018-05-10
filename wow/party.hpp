#pragma once

#include <objects/player.hpp>

#include "../optional_object.hpp"

namespace wow::party
{
// observers
	optional_object<objects::player> leader();
	optional_object<objects::player> member(uint index);

// mutators
	void change_leader(const objects::player& player);
	void set_member(uint index, const objects::player& player);
}
