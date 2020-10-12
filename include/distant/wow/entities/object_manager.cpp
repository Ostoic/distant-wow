#include "object_manager.hpp"

#include "detail/object_cache.hpp"

namespace distant::wow::entities
{
	player& local_player()
	{
		const auto base = local_base();
		if (!detail::is_cached(base))
			detail::cache_object<player>(base);
		else
			detail::update_cache(base);

		return detail::cache_get<player>(base);
	}

	wow::memory::address local_base()
	{
		auto base = memory::read<memory::address>(wow::offsets::local_player::base);
		base = memory::read<memory::address>(base + wow::offsets::local_player::base_ptr1);
		return memory::read<memory::address>(base + wow::offsets::local_player::base_ptr2);
	}

}