#pragma once
#include <objects/object.hpp>

#include <objects/detail/object.hpp>
#include <objects/fwd.hpp>

namespace objects
{
	/*template <typename Object>
	object::object(memory::address base, const Object& obj)
		: base_(base)
		, guid_(detail::load_object_guid(base))
		, name_(obj.load_name()) 
	{
		this->throw_if_invalid("[objects::object::{ctor}] Invalid object");
	}*/
}
