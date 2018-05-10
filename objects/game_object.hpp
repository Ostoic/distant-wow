#pragma once

#include <objects/object.hpp>
#include <objects/types.hpp>
#include <objects/detail/game_object_descriptors.hpp>
#include "../optional_object.hpp"

#include <memory>
#include <string>

namespace objects
{
	class game_object : public object
	{
	public: // observer
		std::size_t display_id() const override final;

		// consider returning guid which can be used as a key/search in the object manager?
		optional_object<unit> owner() const;

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

		void check_descriptors_ptr() const;

		void get_all_descriptors() const;
		void get_ownership_descriptors() const;

	protected: // data
		memory::address descriptors_base_;
		//mutable std::shared_ptr<detail::game_object_descriptors> go_descriptors_;
	};
}
