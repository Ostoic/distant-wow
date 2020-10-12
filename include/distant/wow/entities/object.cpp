#include "object.hpp"

#include "../memory/operations.hpp"
#include "../offsets.hpp"

#include "detail/object.hpp"
#include "detail/unit.hpp"
#include "detail/player.hpp"
#include "detail/game_object.hpp"  // Keep for detail::load_name<game_object>

#include "player.hpp"
#include "game_object.hpp"

namespace distant::wow::entities
{
//const interface:
	memory::address object::base() const noexcept
	{
		return this->base_;
	}

	std::string object::name() const
	{
		const auto ptr = this->get_name_ptr();
		if (ptr == 0)
			return "";

		return memory::read<std::string>(ptr, 64);
	}

	geometry::vector object::position() const
	{
		return this->get_position();
	}

	object_type object::type() const
	{
		return type_;
	}

	wow::guid object::guid() const noexcept
	{
		return this->guid_;
	}

	bool object::valid() const noexcept
	{
		return detail::valid_base_address(this->base_) && (this->guid_ != wow::guid{});
	}

	bool object::is_active() const
	{
		return !this->is_disabled();
	}

	bool object::is_disabled() const
	{
		return memory::read_offset(base_, offsets::object::disabled) == 0;
	}

	object::operator bool() const noexcept
	{
		return this->valid() && this->is_active();
	}

//mutator interface:
	void object::teleport(const geometry::vector& location)
	{
		memory::write(this->base_ + wow::offsets::object::x_coord, location);
	}

	void object::change_name(const std::string& name)
	{
		memory::write(this->get_name_ptr(), name);
	}

//{ctor}:
	object::object(const memory::address base)
		: base_(base)
		, guid_(detail::load_object_guid(base))
		, type_(detail::load_object_type(base))
	{
		this->throw_if_invalid("[entities::object::{ctor}] Invalid wow object");
	}

//protected:
	void object::throw_if_invalid(const std::string& message) const
	{
		if (!this->valid())
			throw error::memory_disparity(message);
	}

	wow::geometry::vector object::get_position() const
	{
		// Read position vector from memory.
		return memory::read_offset(this->base_, wow::offsets::object::position);
	}

//free:
	bool operator==(const object& lhs, const object& rhs)
	{
		return lhs.base() == rhs.base() && lhs.guid() == rhs.guid();
	}

	bool operator!=(const object& lhs, const object& rhs)
	{
		return !(lhs == rhs);
	}
} // namespace distant::wow
