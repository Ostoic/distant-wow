#pragma once

#include "object.hpp"
#include "object_manager.hpp"

#include <string_view>

namespace distant::wow::entities::filters
{
	struct identity
	{
		template <typename T>
		bool operator()(const T& obj) const
		{
			return true;
		}
	};

	struct name
	{
		std::string_view name_;
		name() = default;
		explicit name(const std::string_view name) : name_(name) {}

		template <typename T>
		bool operator()(const T& obj) const
		{
			return obj.name() == name_;
		}
	};

	struct display_id
	{
		wow::uint display_id_;
		display_id() : display_id(0) {}
		explicit display_id(const wow::uint id) : display_id_(id) {}

		template <typename T>
		bool operator()(const T& obj) const
		{
			return obj.display_id() == display_id_;
		}
	};

	struct non_local
	{
		template <typename T>
		bool operator()(const T& obj) const
		{
			return obj.base() != entities::local_base();
		}
	};
}
