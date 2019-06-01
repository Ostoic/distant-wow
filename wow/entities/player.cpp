#include "player.hpp"

#include "../memory/operations.hpp"
#include "detail/player.hpp"
#include "detail/object_manager.hpp"

namespace distant::wow::entities
{
//interface:
	bool player::is_player() const
	{ return true; }

//{ctor}:
	player::player(const memory::address base)
		: unit(base) 
	{}

//protected {ctor}:
	memory::address player::get_name_ptr() const
	{
		const auto mask = memory::read<wow::dword>(wow::offsets::name_cache::cache_base + wow::offsets::name_cache::player_name_mask);
		const auto base = memory::read<wow::dword>(wow::offsets::name_cache::cache_base + wow::offsets::name_cache::player_name_base);

		const auto short_guid = memory::address(guid_.low & 0xFFFFFFFF);

		auto offset = 12 * (mask & short_guid);
		auto current = memory::read<memory::address>(base + offset + 8);
		offset = memory::read<wow::dword>(base + offset);

		if ((current & 0x1) == 0x1)
			return 0;
			/*throw error::memory_disparity("[entities::player::get_name_ptr()] Invalid name cache offset");*/

		auto test_guid = memory::read<wow::dword>(current);
		while (test_guid != short_guid)
		{
			current = memory::read<memory::address>(current + offset + 4);

			if ((current & 0x1) == 0x1)
				return 0;
			//throw error::memory_disparity("[entities::player::get_name_ptr()] Invalid name cache offset");

			test_guid = memory::read<wow::dword>(current);
		}

		return current + wow::offsets::name_cache::player_name_string;
	}

	void player::update_data() const
	{
		unit::update_data();

		if (descriptors_base_ == 0)
			descriptors_base_ = memory::read_offset(base_, offsets::object::object_descriptors);
		//if (this->player_descriptors_ != nullptr)
			//this->player_descriptors_.reset();

		//this->get_descriptors();
	}

//private:
	//void player::get_descriptors() const
	//{}

//free:
}
