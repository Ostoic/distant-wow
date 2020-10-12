#pragma once

#include "vector.hpp"

namespace distant::wow::geometry
{
	template <int Dimension = 2>
	float magnitude_squared(const vector& vector) noexcept;

	template <int Dimension = 2>
	float magnitude(const vector& vector) noexcept;

	void normalize(vector& vector) noexcept;

	template <int Dimension = 2>
	float distance_squared(const vector& lhs, const vector& rhs);

	template <int Dimension = 2>
	float distance(const vector& lhs, const vector& rhs);

} // namespace geometry

// Impl
#include "impl/algorithm.hxx"
