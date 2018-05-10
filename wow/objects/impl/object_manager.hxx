#pragma once
#include "../object_manager.hpp"

#include <memory/operations.hpp>
#include <wow/offsets.hpp>

#include "../object.hpp"
#include "../detail/object_cache.hpp"
#include "../detail/object_manager.hpp"
#include "../detail/object.hpp"

#include <boost/iterator/filter_iterator.hpp>

namespace wow::objects
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
	void object_manager<T>::for_each(Function apply, FilterPredicate pred)
	{
		const auto filter_begin = boost::make_filter_iterator<FilterPredicate>(this->begin(), this->end());
		const auto filter_end	= boost::make_filter_iterator<FilterPredicate>(this->end(),   this->end());
		std::for_each(filter_begin, filter_end, apply);
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
	memory::address object_manager<T>::base() const
	{ return this->base_; }

//{ctor}
	template <typename T>
	object_manager<T>::object_manager()
		: base_(detail::get_manager()) 
	{
		static memory::address last_base = base_;

		// Compare current base with the last one.
		// Clear the cache if they differ.
		if (this->base_ != last_base)
		{
			if (!detail::valid_base_address(this->base_))
				throw error::memory_disparity("[object_manager::{ctor}] Invalid object manager base");

			detail::object_cache().clear();
		}

		//const auto current = memory::read<memory::address>(this->base_ + wow::offsets::object_manager::first_entry); 

		// Set the previous object manager's base.
		last_base = this->base_;
	}

} // namespace wow
