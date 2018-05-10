#pragma once

#include "objects/player.hpp"

namespace wow::party
{
// observers
	optional_ref<player> leader();
	optional_ref<player> member(uint index);

// mutators
	void change_leader(const player& player);
	void set_member(uint index, const player& player);
}
