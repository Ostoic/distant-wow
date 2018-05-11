#pragma once

#include <iostream>
#include <array>

namespace geometry
{
	/// @brief position vector representing a location and rotation ingame.
	struct vector : std::array<float, 5>
	{
		vector() = default;

		constexpr vector(float x, float y, float z, float rotation = 0.0) noexcept;
		
		constexpr float  x() const noexcept;
				  float& x()	   noexcept;

		constexpr float  y() const noexcept;
				  float& y()	   noexcept;

		constexpr float  z() const noexcept;
				  float& z()	   noexcept; 

		constexpr float  rotation() const noexcept;
				  float& rotation()		  noexcept;
	};

	constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept
	{ return {lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() }; }

	constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept
	{ return {lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() }; }

	std::ostream& operator<<(std::ostream& stream, const vector& rhs);
} // namespace geometry

#include "impl/vector.hxx"
