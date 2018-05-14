#pragma once
#include <entities/object.hpp>

#include <entities/detail/object.hpp>
#include <entities/fwd.hpp>

namespace wow::entities
{
	/*template <typename Object>
	object::object(memory::address base, const Object& obj)
		: base_(base)
		, guid_(detail::load_object_guid(base))
		, name_(obj.load_name()) 
	{
		this->throw_if_invalid("[entities::object::{ctor}] Invalid object");
	}*/
}
