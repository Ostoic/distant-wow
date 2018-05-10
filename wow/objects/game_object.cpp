#include "game_object.hpp"

#include "unit.hpp"
#include "detail/game_object.hpp"
#include "object_manager.hpp"

#include <memory/operations.hpp>
#include <wow/offsets.hpp>

namespace wow::objects
{
//public:
	uint game_object::display_id() const
	{
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::display_id);
	}

	optional_ref<unit> game_object::owner() const
	{
		//this->get_ownership_descriptors();
		const auto creator_guid = memory::read_offset(descriptors_base_, offsets::game_object_descriptors::created_by);

		object_manager<unit> manager;
		const auto it = manager.find(creator_guid);

		if (it != manager.end())
			return *it;

		return {};
	}

	wow::flags game_object::flags() const
	{
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::flags);
	}

	wow::flags game_object::other_flags() const
	{
		return memory::read_offset(descriptors_base_, offsets::game_object_descriptors::other_flags);
	}

	void game_object::set_flags(wow::flags flags)
	{
		memory::write(descriptors_base_ + offsets::game_object_descriptors::flags, flags);
	}

	void game_object::change_owner(const unit& new_owner)
	{
		auto guid = new_owner.guid();
		
		memory::write(descriptors_base_ + offsets::game_object_descriptors::created_by, guid);
	}

	void game_object::change_name(const std::string& name)
	{
		memory::write(detail::get_name_ptr<game_object>(this->base_), this->name_);
		this->name_ = name;
	}

//{ctor}:
	game_object::game_object(const memory::address base)
		: object(base, *this) {}

//private:
	void game_object::update_data() const
	{
		//this->get_all_descriptors();
	}

	geometry::vector game_object::get_position() const
	{
		return memory::read<geometry::vector>(this->base_ + wow::offsets::object::go_x_coord);
	}

}
