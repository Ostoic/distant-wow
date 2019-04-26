#pragma once
#include <geometry/point.hpp>

#include <numeric>

namespace geometry
{

//class vector
	constexpr vector::vector(const float x, const float y, const float z, const float rotation) noexcept
		: std::array<float, 5>({ x, y, z, 0, rotation })
	{}

//access
	constexpr float vector::x() const noexcept
	{ return this->operator[](0); }

	inline float& vector::x() noexcept
	{ return this->operator[](0); }

	constexpr float  vector::y() const noexcept
	{ return this->operator[](1); }

	inline float& vector::y() noexcept
	{ return this->operator[](1); }

	constexpr float vector::z() const noexcept
	{ return this->operator[](2); }

	inline float& vector::z() noexcept
	{ return this->operator[](2); }

	constexpr float vector::rotation() const noexcept
	{ return this->operator[](4); }

	inline float& vector::rotation() noexcept
	{ return this->operator[](4); }

//free:
	inline std::ostream& operator<<(std::ostream& stream, const vector& rhs)
	{
		stream << "(" << rhs.x() << ", " << rhs.y() << ", " << rhs.z() << ") " << rhs.rotation();
		return stream;
	}
}
