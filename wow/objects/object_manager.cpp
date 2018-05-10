#include "object_manager.hpp"

#include "detail/object_cache.hpp"

namespace wow::objects
{
	// Todo: Make it so that the local player is the first object in the cache for efficiency
	player& local_player()
	{
		auto base = memory::read<memory::address>(wow::offsets::local_player::base);
		base = memory::read<memory::address>(base + wow::offsets::local_player::base_ptr1);
		base = memory::read<memory::address>(base + wow::offsets::local_player::base_ptr2);

		if (!detail::is_cached(base))
			detail::cache_object<player>(base);
		else
			detail::update_cache(base);

		return detail::cache_get<player>(base);
	}
}