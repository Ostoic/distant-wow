#pragma once

#include <chrono>

#include "../geometry/vector.hpp"
#include "../memory/address.hpp"
#include "../primitives.hpp"
#include "../offsets.hpp"

#include "types.hpp"
#include "detail/object_cache.hpp"

namespace distant::wow::entities
{
	namespace detail { void update_cache(memory::address base); }

	class object
	{
	public: // const interface
		virtual std::size_t display_id() const = 0;

		std::string name() const;

		memory::address base() const noexcept;

		geometry::vector position() const;

		object_type type() const;

		wow::guid guid() const noexcept;

		bool valid() const noexcept;

		bool is_active() const;
		bool is_disabled() const;

		explicit operator bool() const noexcept;

	public: // mutator interface
		void teleport(const geometry::vector& location);

		void change_name(const std::string& name);

	public: // {ctor}
		object() = default;
		explicit object(memory::address base);

		object(object&&) = default;
		object(const object&) = default;

		object& operator=(const object&) = default;
		object& operator=(object&&) = default;

		virtual ~object() = default;

	protected:
		virtual wow::geometry::vector get_position() const;

		virtual memory::address get_name_ptr() const = 0;

		void throw_if_invalid(const std::string& message) const;

		// Todo: It's possible that in the object_manager loop, update_data is called on an object that is not the same as the old.
		// Todo: Check guids to see if they are still compatible. Throw it out somehow if it's not?
		virtual void update_data() const = 0;

	private:
		template <typename T>
		friend class object_iterator;

		friend void detail::update_cache(memory::address base);

	protected: // data
		memory::address base_;
		wow::guid		guid_;
		object_type		type_;
	};

	template <class Object>
	bool is_valid(const Object& obj)
	{
		return obj.valid();
	}

	template <class Object>
	memory::address base_of(const Object& object) noexcept
	{
		if constexpr (std::is_convertible_v<Object, memory::address>)
			return object;
		else 
			return object.base();
	}

	template <class Object>
	wow::guid guid_of(const Object& object)
	{
		const auto base = base_of(object);
		return memory::read_offset(base, offsets::object::guid);
	}

	template <class Object>
	bool is_disabled(const Object& object)
	{
		return memory::read_offset(base_of(object), offsets::object::disabled) == false;
	}

	bool operator==(const object& lhs, const object& rhs);
	bool operator!=(const object& lhs, const object& rhs);


} // namespace distant::wow::entities

namespace distant::wow
{
	using entities::object;
}