#pragma once

#include <memory/address.hpp>
#include "object_iterator.hpp"
#include "player.hpp"
#include "types.hpp"

#include "object_filters.hpp"

namespace wow::entities
{
	template <typename T = entities::object>
	class object_manager
	{
	public: // subtypes
		using iterator = object_iterator<T>;
		using const_iterator = const_object_iterator<T>;

	public: // interface
		const_iterator begin() const;
		const_iterator end() const noexcept;

		iterator begin();
		iterator end() noexcept;

		std::size_t size() const noexcept;
		bool empty() const noexcept;

		template <typename Function, typename FilterPredicate = filters::identity_filter<T>>
		void for_each(Function apply, FilterPredicate pred = filters::identity_filter<T>{});

		template <typename Function, typename FilterPredicate = filters::identity_filter<T>>
		void for_each(Function apply, FilterPredicate pred = filters::identity_filter<T>{}) const;

		iterator find(const std::string& name)	 const;
		iterator find(memory::address	 base)	 const;
		iterator find(wow::guid		     guid)	 const;

		memory::address base() const;

	public: // {ctor}
		object_manager();

	private: // data
		memory::address base_;
	};

	player& local_player();

} // namespace wow::entities

namespace wow
{
	using entities::object_manager;
	using entities::local_player;
}

// Implementation:
#include "impl/object_manager.hxx"
