#pragma once
#include "../algorithm.hpp"

#include <numeric>
#include <algorithm>

namespace geometry
{
	inline float magnitude_squared(const vector& vector) noexcept
	{
		return std::inner_product(vector.begin(), vector.end(), vector.begin(), float(0));
	}

	inline float magnitude(const vector& vector) noexcept
	{
		return std::sqrt(magnitude_squared(vector));
	}

	inline void normalize(vector& vector) noexcept
	{
		const auto magnitude = geometry::magnitude(vector);
		std::transform(vector.begin(), vector.end(), vector.begin(), [magnitude](auto component)
		{
			return component / magnitude;
		});
	}

	constexpr float distance_squared(const vector& lhs, const vector& rhs)
	{
		const auto diff = rhs - lhs;
		return magnitude_squared(diff);
	}

	constexpr float distance(const vector& lhs, const vector& rhs)
	{
		return std::sqrt(distance_squared(lhs, rhs));
	}
}
