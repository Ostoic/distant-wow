#pragma once
#include "../object_manager.hpp"

#include "../../memory/operations.hpp"
#include "../../offsets.hpp"

#include "../object.hpp"
#include "../detail/object_cache.hpp"
#include "../detail/object_manager.hpp"
#include "../detail/object.hpp"

#include <boost/iterator/filter_iterator.hpp>

namespace distant::wow::entities
{
//interface:
	template <typename T>
	std::size_t object_manager<T>::size() const noexcept
	{
		return std::distance(this->begin(), this->end());
		//return std::size(detail::object_cache());
	}

	template <typename T>
	bool object_manager<T>::empty() const noexcept
	{
		return this->size() != 0;
	}

	template <typename T>
	typename object_manager<T>::const_iterator
	object_manager<T>::begin() const
	{
		return const_iterator{memory::read<memory::address>(this->base_ + wow::offsets::object_manager::first_entry)};
	}

	template <typename T>
	typename object_manager<T>::const_iterator
	object_manager<T>::end() const noexcept
	{ return const_iterator{}; }

	template <typename T>
	typename object_manager<T>::iterator
	object_manager<T>::begin()
	{
		return const_iterator{memory::read<memory::address>(this->base_ + wow::offsets::object_manager::first_entry)};
	}
	
	template <typename T>
	typename object_manager<T>::iterator
	object_manager<T>::end() noexcept
	{ return const_iterator{}; }

	template <typename T>
	template <typename Function, typename FilterPredicate>
	void object_manager<T>::for_each(const Function apply, const FilterPredicate pred) const
	{
		const auto end = this->end();
		for (auto first = this->begin(); first != end; ++first)
		{
			const T& element = *first;
			if (pred(element))
				apply(element);
		}
	}

	template <typename T>
	template <typename Function, typename FilterPredicate>
	void object_manager<T>::for_each(const Function apply, const FilterPredicate pred)
	{
		const auto end = this->end();
		for (auto first = this->begin(); first != end; ++first)
		{
			T& element = *first;
			if (pred(element))
				apply(element);
		}
	}


	template <typename T>
	typename object_manager<T>::iterator
	object_manager<T>::find(const std::string& name) const
	{
		return std::find_if(this->begin(), this->end(), [&name](const auto& object)
		{
			return object.name() == name;
		});
	}

	template <typename T>
	typename object_manager<T>::iterator
	object_manager<T>::find(const memory::address base) const
	{
		return std::find_if(this->begin(), this->end(), [&base](const auto& object)
		{
			return object.base() == base;
		});
	}

	template <typename T>
	typename object_manager<T>::iterator
	object_manager<T>::find(const wow::guid guid) const
	{
		return std::find_if(this->begin(), this->end(), [&guid](const auto& object)
		{
			return object.guid() == guid;
		});
	}

	template <typename T>
	template <class Object>
	bool object_manager<T>::contains(const Object& object) const
	{
		return this->contains(base_of(object));
	}

	template <typename T>
	bool object_manager<T>::contains(const std::string& name) const
	{
		return this->find(name) != this->end();
	}

	template <typename T>
	bool object_manager<T>::contains(const memory::address base) const
	{
		return this->find(base) != this->end();
	}

	template <typename T>
	bool object_manager<T>::contains(const wow::guid guid) const
	{
		return this->find(guid) != this->end();
	}

	template <typename T>
	memory::address object_manager<T>::base() const
	{ return this->base_; }

	template <typename T>
	memory::address object_manager<T>::movement_class_base() const
	{
		return memory::read_offset(this->base(), wow::offsets::movement_controller::base);
	}

	template <typename T>
	memory::address object_manager<T>::default_movement_class() const
	{
		return memory::read_offset(
			this->movement_class_base(), wow::offsets::movement_controller::default_movement_class
		);
	}

	template <typename T>
	memory::address object_manager<T>::current_movement_class() const
	{
		return memory::read_offset(
			this->movement_class_base(), wow::offsets::movement_controller::current_movement_class
		);
	}

	template <typename T>
	const object& object_manager<T>::operator[](const memory::address base) const
	{
		return detail::cache_get<object>(base);
	}

//{ctor}
	template <typename T>
	object_manager<T>::object_manager()
		: base_(detail::get_manager()) 
	{
		thread_local memory::address last_base = base_;
		thread_local memory::address last_local_player = local_base();

		// Compare current base with the last one.
		// Clear the cache if they differ.
		if (base_ != last_base)
		{
			if (!detail::valid_base_address(this->base_))
				throw error::memory_disparity("[object_manager::{ctor}] Invalid object_manager base");

			detail::object_cache().clear();
		}

		//const auto current = memory::read<memory::address>(this->base_ + wow::offsets::object_manager::first_entry); 

		// Set the previous object manager's base.
		last_base = base_;
	}

} // namespace distant::wow
