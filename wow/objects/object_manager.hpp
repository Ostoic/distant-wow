#pragma once

#include <memory/address.hpp>
#include "object_iterator.hpp"
#include "player.hpp"
#include "types.hpp"

namespace wow::objects
{
	template <typename T = objects::object>
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

		template <typename Function, typename FilterPredicate>
		void for_each(Function apply, FilterPredicate pred);

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

} // namespace wow::objects

namespace wow
{
	using objects::object_manager;
	using objects::local_player;
}

// Implementation:
#include "impl/object_manager.hxx"
