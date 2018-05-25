#include "object.hpp"

#include <memory/operations.hpp>

#include <wow/offsets.hpp>

#include "detail/object.hpp"
#include "detail/unit.hpp"
#include "detail/player.hpp"
#include "detail/game_object.hpp"  // Keep for detail::load_name<game_object>

#include "player.hpp"
#include "game_object.hpp"

namespace wow::entities
{
//const interface:
	memory::address object::base() const noexcept
	{
		return this->base_;
	}

	std::string object::name() const
	{
		return memory::read<std::string>(this->get_name_ptr(), 64);
	}

	geometry::vector object::position() const noexcept
	{
		return this->get_position();
	}

	wow::guid object::guid() const noexcept
	{
		return this->guid_;
	}

	bool object::valid() const noexcept
	{
		return detail::valid_base_address(this->base_) && (this->guid_ != wow::guid{});
	}

	object::operator bool() const noexcept
	{
		return this->valid();
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
	{
		this->throw_if_invalid("[entities::object::{ctor}] Invalid object");
	}

//protected:
	void object::throw_if_invalid(const std::string& message) const
	{
		if (!this->valid())
			throw error::memory_disparity(message);
	}

	geometry::vector object::get_position() const
	{
		// Read position vector from memory.
		return memory::read_offset(this->base_, wow::offsets::object::position);
	}

//free:
	bool is_valid(const object& obj)
	{
		return obj.valid();
	}

	bool operator==(const object& lhs, const object& rhs)
	{
		return lhs.base() == rhs.base() && lhs.guid() == rhs.guid();
	}

	bool operator!=(const object& lhs, const object& rhs)
	{
		return !(lhs == rhs);
	}
} // namespace wow
