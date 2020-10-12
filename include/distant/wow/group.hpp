#pragma once

#include "entities/player.hpp"

namespace distant::wow::group
{
	class group
	{
	public:
		optional_ref<player> leader();

		wow::uint size() const;

		bool empty() const;
	private:
		std::vector<optional_ref<player>> members_;
	};

// observers
	optional_ref<player> leader();
	optional_ref<player> member(uint index);

// mutators
	void change_leader(const player& player);
	void set_member(uint index, const player& player);
}
