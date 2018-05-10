#pragma once

#include <memory>

#include "object.hpp"
#include "detail/unit_descriptors.hpp"
#include "types.hpp"

namespace wow::objects
{
	class unit : public object
	{
	public: // observers
		std::size_t display_id() const override;

		optional_ref<unit> owner() const;

		wow::flags flags() const;
		wow::flags other_flags() const;

		wow::uint health() const;
		wow::uint max_health() const;

		wow::uint power() const;
		wow::uint max_power() const;

		virtual bool is_player() const;

		float current_speed() const;
		float active_speed()  const;
		float flight_speed()  const;
		float walk_speed()	  const;
		float swim_speed()	  const;

	public: // mutators
		void change_name(const std::string& new_name) override;

		void change_owner(const object& new_owner);

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
		explicit unit(memory::address base, const player&);

		void update_data() const override;

	private: // implementation functions
		friend class object;

	private: // data
		mutable memory::address descriptors_base_;
	};

	//unit get_target(const unit& u);

} //namespace wow

namespace wow
{
	using objects::unit;
}