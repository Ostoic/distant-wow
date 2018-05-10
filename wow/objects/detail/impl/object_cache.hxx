#pragma once
#include "../object_cache.hpp"

namespace wow::objects::detail
{
	template <typename Object>
	Object& cache_get(const memory::address base)
	{
		if (!detail::is_cached(base))
			throw std::logic_error("[object_cache::get] Unable to reference object not in the cache");

		return *reinterpret_cast<Object*>(detail::object_cache()[base].get());
	}

	template <typename Object>
	bool cache_object(const memory::address base)
	{ detail::object_cache().insert({base, std::make_unique<Object>(base)}); return true; }
}
