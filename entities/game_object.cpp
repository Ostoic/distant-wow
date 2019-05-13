#include "game_object.hpp"

#include "unit.hpp"
#include "detail/game_object.hpp"
#include "object_manager.hpp"

#include "../memory/operations.hpp"
#include "../offsets.hpp"

namespace distant::wow::entities
{
//public:
	memory::address game_object::descriptors_base() const
	{
		return descriptors_base_;
	}

	uint game_object::display_id() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::display_id);
	}

	optional_ref<unit> game_object::owner() const
	{
		this->update_data();
		const auto creator_guid = memory::read_offset(descriptors_base_, offsets::game_object_descriptors::created_by);

		object_manager<unit> manager;
		const auto it = manager.find(creator_guid);

		if (it != manager.end())
			return *it;

		return {};
	}

	wow::flags game_object::flags() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::flags);
	}

	wow::flags game_object::other_flags() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::other_flags);
	}

	wow::flags game_object::dynamic_flags() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::dynamic_flags);
	}

	wow::uint game_object::level() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::level);
	}

	wow::uint game_object::faction() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::faction);
	}

	float game_object::parent_rotation() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::parent_rotation);
	}

	void game_object::set_flags(const wow::flags flags)
	{
		this->update_data();
		memory::write(descriptors_base_ + offsets::game_object_descriptors::flags, flags);
	}

	void game_object::change_owner(const unit& new_owner)
	{
		this->update_data();
		memory::write(descriptors_base_ + offsets::game_object_descriptors::created_by, new_owner.guid());
	}

//{ctor}:
	game_object::game_object(const memory::address base)
		: object(base) {}

//private:
	memory::address game_object::get_name_ptr() const
	{
		const auto ptr = memory::read_offset(base_, wow::offsets::name_cache::go_name_ptr_offset1);
		return memory::read_offset(ptr, wow::offsets::name_cache::go_name_ptr_offset2);
	}

	void game_object::update_data() const
	{
		if (descriptors_base_ == 0)
			descriptors_base_ = memory::read_offset(base_, offsets::object::object_descriptors);
		//this->get_all_descriptors();
	}

	geometry::vector game_object::get_position() const
	{
		return memory::read_offset(base_, offsets::object::go_position);
	}

}
