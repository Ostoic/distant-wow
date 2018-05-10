#pragma once

#include <iostream>

namespace geometry
{
	// Pod vector data type
	struct vector
	{
		vector() = default;

		constexpr vector(float a, float b, float c, float r = 0.0) noexcept;

		constexpr float* begin();
		constexpr float* end();

		constexpr const float* begin() const;
		constexpr const float* end()   const;

		float x;
		float y;
		float z;
		float bytes;
		float rot;
	};

	constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept
	{ return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z}; }

	constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept
	{ return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z}; }

	float distance(const vector& v1, const vector& v2) noexcept;

	std::ostream& operator<<(std::ostream& stream, const vector& rhs);
} // namespace geometry

#include <geometry/impl/vector.hxx>
