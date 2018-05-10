#include <objects/object_manager.hpp>

#include <objects/detail/object_cache.hpp>

namespace objects
{
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