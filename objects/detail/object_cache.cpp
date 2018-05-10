#include <objects/detail/object_cache.hpp>
#include <objects/detail/object.hpp>

#include <objects/game_object.hpp>
#include <objects/player.hpp>

namespace objects::detail
{
	inline std::unordered_map<memory::address, std::unique_ptr<object>>& object_cache()
	{
		static std::unordered_map<memory::address, std::unique_ptr<object>> object_cache = {};
		return object_cache;
	}

	void update_cache(const memory::address base)
	{
		if (is_cached(base))
			object_cache()[base]->update_data();
		else
			cache_object(base);
	}

	bool is_cached(const memory::address base)
	{
		return object_cache().count(base) > 0;
	}

	bool cache_object(const memory::address base)
	{
		const auto type = load_object_type(base);

		switch (type)
		{
			case object_type::player: 
				object_cache().insert({ base, std::make_unique<player>(base) });
				return true;

			case object_type::unit: 
				object_cache().insert({ base, std::make_unique<unit>(base) });
				return true;

			case object_type::game_object: 
				object_cache().insert({ base, std::make_unique<game_object>(base) });
				return true;

			default: return false;
		}
	}
}
