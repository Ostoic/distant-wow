#pragma once

#include <memory/operations.hpp>
#include "../object.hpp"

#include <memory>
#include <unordered_map>

namespace wow::entities::detail
{
	std::unordered_map<memory::address, std::unique_ptr<entities::object>>& object_cache();

	bool is_cached(memory::address base);

	template <typename Object>
	Object& cache_get(const memory::address base)
	{
		if (!detail::is_cached(base))
			throw std::logic_error("[object_cache::get] Unable to reference object not in the cache");

		return *reinterpret_cast<Object*>(detail::object_cache()[base].get());
	}


	void update_cache(memory::address base);

	template <typename Object>
	bool cache_object(const memory::address base)
	{
		detail::object_cache().insert({ base, std::make_unique<Object>(base) }); 
		return true;
	}

	bool cache_object(memory::address base);
}
