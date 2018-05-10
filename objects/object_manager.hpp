#pragma once

#include <memory/address.hpp>
#include <objects/object_iterator.hpp>
#include <objects/player.hpp>

#include <optional>

namespace objects
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

} // namespace objects

// Implementation:
#include <objects/impl/object_manager.hxx>
