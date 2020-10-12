#pragma once

#include "../memory/address.hpp"
#include "object_iterator.hpp"
#include "player.hpp"
#include "types.hpp"

#include "object_filters.hpp"
#include "movement_controller.hpp"

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

		bool valid() const noexcept;

		void clear() noexcept;

		template <typename Function, typename FilterPredicate = filters::identity>
		void for_each(Function apply, FilterPredicate pred = filters::identity{});

		template <typename Function, typename FilterPredicate = filters::identity>
		void for_each(Function apply, FilterPredicate pred = filters::identity{}) const;

		iterator find(const std::string& name)	 const;
		iterator find(memory::address	 base)	 const;
		iterator find(wow::guid		     guid)	 const;

		template <class Object>
		bool contains(const Object&	   object) const;

		bool contains(const std::string& name) const;
		bool contains(memory::address	 base) const;
		bool contains(wow::guid		     guid) const;

		memory::address base() const;

		movement_controller default_movement_controller() const;
		movement_controller current_movement_controller() const;

		guid local_guid() const noexcept;
		uint map_id() const noexcept;

		const object& operator[](memory::address base) const;

	public: // {ctor}
		object_manager();

	private: // data
		memory::address base_;
		memory::address movement_globals_;
		guid local_guid_;
		uint map_id_;
	};

	template <class Object>
	bool is_cached(const Object& object)
	{
		return detail::is_cached(base_of(object));
	}

	player& local_player();

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
