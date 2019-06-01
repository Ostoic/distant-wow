#include "unit.hpp"

#include "../memory/operations.hpp"

#include "detail/unit.hpp"
#include "object_manager.hpp"

namespace distant::wow::entities
{
//public:
	memory::address unit::descriptors_base() const
	{
		return descriptors_base_;
	}

	std::size_t unit::display_id() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::display_id);
	}

	bool unit::is_player() const
	{ return false; }

	optional_ref<unit> unit::owner() const
	{
		const auto creator_guid = memory::read_offset(descriptors_base_, offsets::unit_descriptors::created_by);

		object_manager<unit> manager;
		const auto it = manager.find(creator_guid);

		if (it != manager.end())
			return *it;
		return {};
	}

	optional_ref<unit> unit::target() const
	{
		const auto target_guid = memory::read_offset(descriptors_base_, offsets::unit_descriptors::target);

		object_manager<unit> manager;
		const auto it = manager.find(target_guid);

		if (it != manager.end())
			return *it;

		return {};
	}

	wow::guid unit::target_guid() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::target);
	}

	wow::flags unit::flags() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::flags);
	}

	wow::flags unit::other_flags() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::flags2);
	}

	wow::uint unit::health() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::health);
	}

	wow::uint unit::max_health() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::max_health);
	}

	wow::uint unit::power() const
	{
		const auto power_type = this->power_type();
		const auto power = memory::read_offset(base_ + static_cast<uint>(power_type) * 4, offsets::object::power);
		return (power_type == power_type::rune || power_type == power_type::rage) 
			? power / 10 
			: power;
	}

	wow::uint unit::max_power() const
	{
		const auto power_type = this->power_type();
		return memory::read_offset(descriptors_base_ + static_cast<uint>(power_type) * 4, offsets::unit_descriptors::max_power1);
	}

	power_type unit::power_type() const
	{
		return memory::read_offset(
			memory::read_offset(base_, offsets::object::power_type_ptr), 
			offsets::object::power_type
		);
	}

	faction unit::faction() const
	{
		return memory::read_offset(
			descriptors_base_, offsets::unit_descriptors::facition
		);
	}

	float unit::current_speed() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_current);
	}

	float unit::active_speed()	const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_active);
	}

	float unit::walk_speed() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_walking);
	}

	float unit::swim_speed() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_swimming);
	}

	float unit::flight_speed() const
	{
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_flying);
	}

	void unit::set_current_speed(const float speed)
	{
		memory::write(base_ + offsets::unit_descriptors::movement_speed_current, speed);
	}

	void unit::set_active_speed(const float speed)
	{
		memory::write(base_ + offsets::unit_descriptors::movement_speed_active, speed);
	}

	void unit::set_flight_speed(const float speed)
	{
		memory::write(base_ + offsets::unit_descriptors::movement_speed_flying, speed);
	}

	void unit::set_walk_speed(const float speed)
	{
		memory::write(base_ + offsets::unit_descriptors::movement_speed_walking, speed);
	}

	void unit::set_swim_speed(const float speed)
	{
		memory::write(base_ + offsets::unit_descriptors::movement_speed_swimming, speed);
	}

//public mutators:
	void unit::set_owner(const object& new_owner)
	{
		memory::write(
			descriptors_base_ + offsets::unit_descriptors::created_by,
			new_owner.guid()
		);
	}

	void unit::set_target(const object& new_target)
	{
		memory::write(
			descriptors_base_ + offsets::unit_descriptors::target,
			new_target.guid()
		);
	}

//{ctor}:
	unit::unit(const memory::address base)
		: object(base)
		, descriptors_base_(memory::read_offset(base, offsets::object::object_descriptors)) 
	{}

//protected {ctor}:
	memory::address unit::get_name_ptr() const
	{
		const auto name_pointer = memory::read<memory::address>(base_ + wow::offsets::name_cache::unit_name_ptr_offset1);
		return memory::read<memory::address>(name_pointer + wow::offsets::name_cache::unit_name_ptr_offset2);
	}

	void unit::update_data() const
	{
		//if (descriptors_base_ == 0)
			//descriptors_base_ = memory::read_offset(base_, offsets::object::object_descriptors);
	}

//private:

//free:

	bool is_alliance(faction faction)
	{
		switch (faction)
		{
		case faction::human:
		case faction::dwarf:
		case faction::night_elf:
		case faction::gnome:
		case faction::draenai:
			return true;
		}

		return false;
	}

	bool is_horde(faction faction)
	{
		switch (faction)
		{
		case faction::orc:
		case faction::undead:
		case faction::tauren:
		case faction::troll:
		case faction::blood_elf:
			return true;
		}

		return false;
	}
}
