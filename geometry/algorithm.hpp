#pragma once

#include "vector.hpp"

namespace geometry
{
	float magnitude_squared(const vector& vector) noexcept;

	float magnitude(const vector& vector) noexcept;

	void normalize(vector& vector) noexcept;

	constexpr float distance_squared(const vector& lhs, const vector& rhs);

	constexpr float distance(const vector& lhs, const vector& rhs);
} // namespace geometry

// Impl
#include "impl/algorithm.hxx"
