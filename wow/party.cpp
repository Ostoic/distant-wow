#include "party.hpp"

#include "offsets.hpp"
#include "../memory/operations.hpp"
#include "objects/object_manager.hpp"

namespace wow::party
{
	optional_ref<player> leader()
	{
		const auto guid = memory::read<wow::guid>(wow::offsets::party::member1_guid);

		object_manager<objects::player> manager;
		const auto it = manager.find(guid);
		if (it != manager.end())
			return *it;

		return {};
	}

	optional_ref<player> member(const uint index)
	{
		wow::guid guid;

		switch (index)
		{
		case 1:
			guid = memory::read<wow::guid>(wow::offsets::party::member1_guid);
			break;

		case 2:
			guid = memory::read<wow::guid>(wow::offsets::party::member2_guid);
			break;

		case 3:
			guid = memory::read<wow::guid>(wow::offsets::party::member3_guid);
			break;

		case 4:
			guid = memory::read<wow::guid>(wow::offsets::party::member4_guid);
			break;

		case 5:
			guid = memory::read<wow::guid>(wow::offsets::party::member5_guid);
			break;

		default: 
			// Todo: raid members
			return {};
		}

		object_manager<player> manager;
		const auto it = manager.find(guid);
		if (it != manager.end())
			return *it;

		return {};
	}

	void change_leader(const objects::player& player)
	{
		memory::write(wow::offsets::party::leader_guid, player.guid());
	}

	void set_member(const uint index, const objects::player& player)
	{
		switch (index)
		{
		case 1:
			memory::write(wow::offsets::party::member1_guid, player.guid());
			break;

		case 2:
			memory::write(wow::offsets::party::member2_guid, player.guid());
			break;

		case 3:
			memory::write(wow::offsets::party::member3_guid, player.guid());
			break;

		case 4:
			memory::write(wow::offsets::party::member4_guid, player.guid());
			break;

		case 5:
			memory::write(wow::offsets::party::member5_guid, player.guid());
			break;

		default:
			// Todo: raid members
			break;
		}

	}
}