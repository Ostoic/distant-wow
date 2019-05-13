#pragma once

#include "entities/object.hpp"

namespace distant::wow::ui
{
	void target(const entities::object& object);

	void interact(const entities::object& object);

	wow::memory::address target_base();
	wow::guid target_guid();
} 
