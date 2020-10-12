#pragma once

#include <memory>

#include "object.hpp"
#include "detail/unit_descriptors.hpp"
#include "types.hpp"

namespace distant::wow::entities
{
	enum class power_type
	{
		mana = 0,
		rage = 1,
		energy = 3,
		rune = 6
	};

	enum class faction
	{
		// alliance
		human = 1,
		dwarf = 3,
		night_elf = 4,
		gnome = 115,
		draenai = 1629,

		// horde
		orc = 2,
		undead = 5,
		tauren = 6,
		troll = 116,
		blood_elf = 1610
	};

	class unit : public object
	{
	public: // observers
		memory::address descriptors_base() const;

		std::size_t display_id() const override;

		optional_ref<unit> owner() const;
		optional_ref<unit> target() const;

		wow::guid target_guid() const;

		wow::flags flags() const;
		wow::flags other_flags() const;

		wow::uint health() const;
		wow::uint max_health() const;

		wow::uint power() const;
		wow::uint max_power() const;

		power_type power_type() const;

		faction faction() const;

		virtual bool is_player() const;

		float current_speed() const;
		float active_speed()  const;
		float flight_speed()  const;
		float walk_speed()	  const;
		float swim_speed()	  const;

	public: // mutators
		void set_owner(const object& new_owner);
		void set_target(const object& new_target);

		// Speed mutators
		void set_current_speed(float speed);
		void set_active_speed(float speed);
		void set_flight_speed(float speed);
		void set_walk_speed(float speed);
		void set_swim_speed(float speed);

	public: // {ctor}
		unit() = default;
		explicit unit(memory::address base);

		unit(unit&&) = default;
		unit(const unit&) = default;

		unit& operator=(const unit&) = default;
		unit& operator=(unit&&) = default;

		virtual ~unit() = default;

	protected:
		memory::address get_name_ptr() const override;

		void update_data() const override;

	private: // implementation functions
		friend class object;

	private: // descriptors
		mutable memory::address descriptors_base_;
	};

	bool is_alliance(faction faction);
	bool is_horde(faction faction);

	//unit get_target(const unit& u);

} //namespace distant::wow

namespace distant::wow
{
	using entities::unit;
}