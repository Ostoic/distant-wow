#include "player.hpp"

#include <memory/operations.hpp>
#include "detail/player.hpp"
#include "detail/object_manager.hpp"

namespace wow::objects
{
//interface:
	std::size_t player::display_id() const
	{ return 0; }

	bool player::is_player() const
	{ return true; }

	void player::change_name(const std::string& name)
	{
		memory::write<std::string>(
			detail::get_name_ptr<player>(this->guid_),
			name
		);
	}

//{ctor}:
	player::player(const memory::address base)
		: unit(base, *this) {}

//protected {ctor}:
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
