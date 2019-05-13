#include "ui.hpp"

namespace distant::wow::ui
{
	void interact(const entities::object& object)
	{

	}

	wow::guid target_guid()
	{
		return memory::read_offset(offsets::ui::current_target);
	}
}