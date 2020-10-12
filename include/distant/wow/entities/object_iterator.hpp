#pragma once

#include <boost/iterator/iterator_facade.hpp>

#include "object.hpp"

#include "detail/type_traits.hpp"
#include "detail/object.hpp"
#include "detail/object_cache.hpp"

namespace distant::wow::entities
{
	template <typename T>
	class object_iterator 
		: public boost::iterator_facade<
			object_iterator<T>,				// CRTP Derivation
			T,								// Value type
			std::input_iterator_tag,		// Traversal category
			T&								// Reference type
		>								
	{
	public: // {ctor}
		object_iterator() noexcept
			: base_(0) {}

		explicit object_iterator(const memory::address base) noexcept
			: base_(base) 
		{
			if (!derives_from(detail::load_object_type(this->base_), detail::type_to_enum<std::decay_t<T>>()))
				this->increment();
			else
				detail::update_cache(this->base_);
		}

		template <typename OtherObject>
		object_iterator(const object_iterator<OtherObject>& other)
			: base_(other.base_) {}

	private: // boost::iterator_facade implementation:
		T& dereference() const
		{
			return *reinterpret_cast<T*>(detail::object_cache()[base_].get());
		}

		template <class OtherObject>
		bool equal(const object_iterator<OtherObject>& other) const noexcept
		{ return base_ == other.base_; }

		void increment()
		{
			memory::address next = base_;
			// Push forward until we hit a cacheable object.
			do
			{
				base_ = next;
				next = detail::next_object_base(base_);

				// If the address is invalid, then we've reached the end.
				if (!detail::valid_base_address(base_))
				{
					next = 0;
					break;
				}

				// We found an object that derives from T.
				if (derives_from(detail::load_object_type(next), detail::type_to_enum<std::decay_t<T>>()))
				{
					detail::update_cache(next);
					break;
				}

			} while (next != base_);

			base_ = next;
		}

	private:
		struct enabler {};

		friend class boost::iterator_core_access;
		template <class> friend class object_iterator;

	private: // data
		memory::address base_;
	};

	template <typename T>
	using const_object_iterator = object_iterator<const T>;

} // namespace distant::wow::entities

