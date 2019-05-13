#pragma once

#include "../memory/address.hpp"
#include "object_iterator.hpp"
#include "player.hpp"
#include "types.hpp"

#include "object_filters.hpp"

namespace distant::wow::entities
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

		template <class Object>
		bool contains(const Object&	   object) const;

		bool contains(const std::string& name) const;
		bool contains(memory::address	 base) const;
		bool contains(wow::guid		     guid) const;

		memory::address base() const;
		memory::address movement_class_base() const;
		memory::address default_movement_class() const;
		memory::address current_movement_class() const;

		const object& operator[](memory::address base) const;

		player& local_player();

	public: // {ctor}
		object_manager();

	private: // data
		memory::address base_;
	};

	template <class Object>
	bool is_cached(const Object& object)
	{
		return detail::is_cached(base_of(object));
	}

	//faction local_faction();

	wow::memory::address local_base();

} // namespace distant::wow::entities

namespace distant::wow
{
	using entities::object_manager;
	using entities::local_player;
}

// Implementation:
#include "impl/object_manager.hxx"
