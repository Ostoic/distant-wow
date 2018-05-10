#include <objects/unit.hpp>

#include "../memory/operations.hpp""

#include "detail/unit.hpp"
#include "object_manager.hpp""

namespace objects
{
//public:
	std::size_t unit::display_id() const
	{
		this->update_data();
		return 0;
		//return unit_descriptors_->
	}

	bool unit::is_player() const
	{ return false; }

	optional_object<unit> unit::owner() const
	{
		this->get_ownership_descriptors();
		object_manager<unit> manager;
		const auto it = manager.find(unit_descriptors_->ownership_chunk.created_by);

		if (it != manager.end())
			return *it;
		return {};
	}

	wow::flags unit::flags() const
	{
		this->update_data();
		//return unit_descriptors_->
	}

	wow::flags unit::other_flags() const
	{
		this->update_data();
		//return unit_descriptors_->
	}


	wow::uint unit::health() const
	{
		this->get_power_descriptors();
	}

	wow::uint unit::max_health() const
	{
		this->get_power_descriptors();

	}

	wow::uint unit::power() const
	{
		this->get_power_descriptors();

	}

	wow::uint unit::max_power() const
	{
		this->get_power_descriptors();
		return unit_descriptors_->
	}

	float unit::current_speed() const
	{
		this->get_speed_descriptors();
		return unit_descriptors_->speed_chunk.current_speed;
	}

	float unit::active_speed()	const
	{
		this->get_speed_descriptors();
		return unit_descriptors_->speed_chunk.active_speed;
	}

	float unit::walk_speed() const
	{
		this->get_speed_descriptors();
		return unit_descriptors_->speed_chunk.walk_speed;
	}

	float unit::swim_speed() const
	{
		this->get_speed_descriptors();
		return unit_descriptors_->speed_chunk.swim_speed;
	}

	float unit::flight_speed() const
	{
		this->get_speed_descriptors();
		return unit_descriptors_->speed_chunk.flight_speed;
	}

	void unit::set_current_speed(float speed)
	{
		memory::write(base_ + wow::offsets::unit_descriptors::movement_speed_current, speed);
	}

	void unit::set_active_speed(float speed)
	{
		memory::write(base_ + wow::offsets::unit_descriptors::movement_speed_active, speed);
	}

	void unit::set_flight_speed(float speed)
	{
		memory::write(base_ + wow::offsets::unit_descriptors::movement_speed_flying, speed);
	}

	void unit::set_walk_speed(float speed)
	{
		memory::write(base_ + wow::offsets::unit_descriptors::movement_speed_walking, speed);
	}

	void unit::set_swim_speed(float speed)
	{
		memory::write(base_ + wow::offsets::unit_descriptors::movement_speed_swimming, speed);
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
		this->get_all_descriptors();
		memory::write(
			unit_descriptors_->base  + wow::offsets::unit_descriptors::created_by,
			new_owner.guid()
		);
	}

//{ctor}:
	unit::unit(const memory::address base)
		: object(base, *this) {}

//protected {ctor}:
	unit::unit(const memory::address base, const player& p)
		: object(base, p) {}

	void unit::update_data() const
	{
		this->get_all_descriptors();
	}

//private:
	void unit::get_speed_descriptors() const
	{
		this->check_descriptors_ptr();
		unit_descriptors_->speed_chunk = memory::read<decltype(detail::unit_descriptors::speed_chunk)>(
			base_ + wow::offsets::unit_descriptors::speed_chunk
		);
	}

	void unit::get_power_descriptors() const
	{
		this->check_descriptors_ptr();
		unit_descriptors_->power_chunk = memory::read<decltype(detail::unit_descriptors::power_chunk)>(
			base_ + wow::offsets::unit_descriptors::power_chunk
		);
	}

	void unit::get_ownership_descriptors() const
	{
		this->check_descriptors_ptr();
		unit_descriptors_->ownership_chunk = memory::read<decltype(detail::unit_descriptors::ownership_chunk)>(
			base_ + wow::offsets::unit_descriptors::ownership_chunk
		);
	}

	void unit::check_descriptors_ptr() const
	{
		if (unit_descriptors_ == nullptr)
		{
			unit_descriptors_ = std::make_unique<detail::unit_descriptors>();
			unit_descriptors_->base = memory::read<wow::dword>(base_ + wow::offsets::object::object_descriptors);
		}
	}

	void unit::get_all_descriptors() const
	{
		this->get_speed_descriptors();
		this->get_power_descriptors();
		this->get_ownership_descriptors();
	}
}
