#include "unit.hpp"

#include <memory/operations.hpp>

#include "detail/unit.hpp"
#include "object_manager.hpp"

namespace wow::entities
{
//public:
	std::size_t unit::display_id() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::display_id);
	}

	bool unit::is_player() const
	{ return false; }

	optional_ref<unit> unit::owner() const
	{
		this->update_data();
		const auto creator_guid = memory::read_offset(descriptors_base_, offsets::unit_descriptors::created_by);

		object_manager<unit> manager;
		const auto it = manager.find(creator_guid);

		if (it != manager.end())
			return *it;
		return {};
	}

	wow::flags unit::flags() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::flags);
	}

	wow::flags unit::other_flags() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::flags2);
	}


	wow::uint unit::health() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::health);
	}

	wow::uint unit::max_health() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::max_health);
	}

	wow::uint unit::power() const
	{
		this->update_data();
		return 0;
	}

	wow::uint unit::max_power() const
	{
		this->update_data();
		return 0;
	}

	float unit::current_speed() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_current);
	}

	float unit::active_speed()	const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_active);
	}

	float unit::walk_speed() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_walking);
	}

	float unit::swim_speed() const
	{
		this->update_data();
		return memory::read_offset(descriptors_base_, offsets::unit_descriptors::movement_speed_swimming);
	}

	float unit::flight_speed() const
	{
		this->update_data();
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
	void unit::change_name(const std::string& new_name)
	{
		memory::write(
			detail::get_name_ptr<unit>(base_),
			new_name
		);
	}

	void unit::change_owner(const object& new_owner)
	{
		this->update_data();
		memory::write(
			descriptors_base_ + offsets::unit_descriptors::created_by,
			new_owner.guid()
		);
	}

//{ctor}:
	unit::unit(const memory::address base)
		: object(base, *this), descriptors_base_(0) {}

//protected {ctor}:
	unit::unit(const memory::address base, const player& p)
		: object(base, p), descriptors_base_(0) {}

	void unit::update_data() const
	{
		if (descriptors_base_ == 0)
			descriptors_base_ = memory::read_offset(base_, offsets::object::object_descriptors);
	}

//private:
}
