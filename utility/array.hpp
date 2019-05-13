#pragma once

namespace distant::wow::utility
{
	template <typename... Args>
	constexpr auto make_array(Args&&... args) noexcept
	{
		return std::array<std::common_type_t<Args...>, sizeof...(Args)>{std::forward<Args>(args)...};
	}
}
