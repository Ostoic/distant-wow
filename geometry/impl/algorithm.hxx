#pragma once
#include "../algorithm.hpp"

#include <numeric>
#include <algorithm>

namespace distant::wow::geometry
{
	template <int Dimension>
	float magnitude_squared(const vector& vector) noexcept
	{
		static_assert(Dimension <= 3, "[wow::geometry::magnitude_squared] Dimension cannot be higher than 3");

		float result = 0;
		for (int i = 0; i < Dimension; i++)
			result += vector[i] * vector[i];

		return result;
	}

	template <int Dimension>
	inline float magnitude(const vector& vector) noexcept
	{
		return std::sqrt(magnitude_squared<Dimension>(vector));
	}

	inline void normalize(vector& vector) noexcept
	{
		const auto magnitude = geometry::magnitude<2>(vector);
		std::transform(vector.begin(), vector.end(), vector.begin(), [magnitude](auto component)
		{
			return component / magnitude;
		});
	}

	template <int Dimension>
	float distance_squared(const vector& lhs, const vector& rhs)
	{
		const auto diff = rhs - lhs;
		return magnitude_squared<Dimension>(diff);
	}

	template <int Dimension>
	float distance(const vector& lhs, const vector& rhs)
	{
		return std::sqrt(distance_squared<Dimension>(lhs, rhs));
	}
}
