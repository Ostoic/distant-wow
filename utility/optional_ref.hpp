#pragma once

#include <optional>
#include <type_traits>

namespace utility
{
	template <typename T>
	using optional_ref = std::optional<std::reference_wrapper<T>>;
}
