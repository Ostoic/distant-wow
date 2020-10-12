#pragma once

#include "../../memory/operations.hpp"
#include "../object.hpp"

#include "../../error/game_error.hpp"

#include <memory>
#include <unordered_map>

#include <fmt/core.h>

namespace distant::wow::entities::detail
{
	std::unordered_map<memory::address, std::unique_ptr<entities::object>>& object_cache();

	bool is_cached(memory::address base);

	template <typename Object>
	Object& cache_get(const memory::address base)
	{
		if (!detail::is_cached(base))
			throw error::memory_disparity("[entities::cache_get] Unable to reference entity not in the cache");

		const auto& cached_object = detail::object_cache()[base].get();
		Object* obj = dynamic_cast<Object*>(cached_object);
		if (obj == nullptr)
		{
			throw error::invalid_object_downcast("hey"
				//fmt::format(
				//	"[entities::cache_get] Unable to downcast object ({}, {}) to given type", 1, 2
				//	//cached_object->name(), to_string(cached_object->type())
				//)
			);
		}

		return *obj;
	}

	void update_cache(memory::address base);

	template <typename Object>
	bool cache_object(const memory::address base)
	{
		detail::object_cache().insert({base, std::make_unique<Object>(base)}); 
		return true;
	}

	bool cache_object(memory::address base);
}
