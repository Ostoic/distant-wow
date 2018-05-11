#include "object.hpp"

#include <memory/operations.hpp>

#include <wow/offsets.hpp>

#include "detail/object.hpp"
#include "detail/unit.hpp"
#include "detail/player.hpp"
#include "detail/game_object.hpp"  // Keep for detail::load_name<game_object>

#include "player.hpp"
#include "game_object.hpp"

namespace wow::objects
{
//const interface:
	const std::string& object::name() const noexcept
	{
		return this->name_;
	}

	memory::address object::base() const noexcept
	{
		return this->base_;
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
		memory::write<geometry::vector>(this->base_ + wow::offsets::object::x_coord, location);
	}

//{ctor}:
	object::object(const memory::address base)
		: base_(base)
		, guid_(detail::load_object_guid(base))
	{
		this->throw_if_invalid("[objects::object::{ctor}] Invalid object");
	}

//protected:
	void object::throw_if_invalid(const std::string& message) const
	{
		if (!this->valid())
			throw error::memory_disparity(message);
	}

	object::object(const memory::address base, const unit& obj)
		: base_(base)
		, guid_(detail::load_object_guid(base))
		, name_(detail::load_name<unit>(base)) 
	{}

	object::object(const memory::address base, const player& obj)
		: base_(base)
		, guid_(detail::load_object_guid(base))
		, name_(detail::load_name<player>(detail::load_object_guid(base)))
	{}

	object::object(const memory::address base, const game_object& obj)
		: base_(base)
		, guid_(detail::load_object_guid(base))
		, name_(detail::load_name<game_object>(base)) 
	{}

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
