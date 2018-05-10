#pragma once

#include <memory/operations.hpp>
#include "../object.hpp"

#include <memory>
#include <unordered_map>

namespace wow::objects::detail
{
	std::unordered_map<memory::address, std::unique_ptr<objects::object>>& object_cache();

	template <typename Object>
	Object& cache_get(memory::address base);

	void update_cache(memory::address base);
	
	bool is_cached(memory::address base);

	template <typename Object>
	bool cache_object(memory::address base);

	bool cache_object(memory::address base);
}

// Function templates impl:
#include "impl/object_cache.hxx"
