#pragma once
#include <geometry/vector.hpp>

#include <numeric>

namespace geometry
{
	constexpr vector::vector(const float a, const float b, const float c, const float r) noexcept
		: x(a), y(b), z(c), bytes(), rot(r) 
	{}

	constexpr float* vector::begin()
	{ return &x; }

	constexpr float* vector::end() 
	{ return this->begin() + 3; }

	constexpr const float* vector::begin() const
	{ return &x; }

	constexpr const float* vector::end() const
	{ return this->begin() + 3; }

	inline std::ostream& operator<<(std::ostream& stream, const vector& rhs)
	{
		stream << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ") " << rhs.rot;
		return stream;
	}

	inline float distance(const vector& v1, const vector& v2) noexcept
	{
		const vector diff = v1 - v2;
		return std::sqrt(std::inner_product(diff.begin(), diff.end(), diff.begin(), float{}));
	}


}
