#pragma once

#include "unit.hpp"

#include <memory>
#include <string>

namespace wow::entities
{
	class game_object : public object
	{
	public: // observer
		std::size_t display_id() const override final;

		// consider returning guid which can be used as a key/search in the object manager?
		optional_ref<unit> owner() const;

		wow::flags flags() const;
		wow::flags other_flags() const;

	public: // mutators

		void set_flags(wow::flags flags);

		void change_owner(const unit& new_owner);

		void change_name(const std::string& name) override final;

	public: // {ctor}
		explicit game_object(memory::address base);

	protected:
		void update_data() const override;

		geometry::vector get_position() const override final;

	private:
		friend class object;

	protected: // data
		mutable memory::address descriptors_base_;
	};
}

namespace wow
{
	using entities::game_object;
}
