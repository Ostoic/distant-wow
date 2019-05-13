#pragma once

#include "object.hpp"

#include <string_view>

namespace distant::wow::entities::filters
{
	template <typename T>
	struct identity_filter
	{
		bool operator()(const T& obj) const
		{
			return true;
		}
	};

	template <typename T>
	struct name_filter
	{
		std::string_view name;
		name_filter() = default;
		explicit name_filter(const std::string_view name) : name(name) {}

		bool operator()(const T& obj) const
		{
			return obj.name() == name;
		}
	};

	template <typename T>
	struct display_id_filter
	{
		wow::uint display_id;
		display_id_filter() : display_id(0) {}
		explicit display_id_filter(const wow::uint id) : display_id(id) {}

		bool operator()(const T& obj) const
		{
			return obj.display_id() == display_id;
		}
	};

	template <typename T>
	struct non_local_filter
	{
		bool operator()(const T& obj) const
		{
			return obj.guid != 
		}
	};
}
