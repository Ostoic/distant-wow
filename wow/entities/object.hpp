#pragma once

#include <chrono>

#include <geometry/vector.hpp>
#include <memory/address.hpp>
#include <wow/primitives.hpp>

#include "types.hpp"
#include "detail/object_cache.hpp"


namespace wow::entities
{
	namespace detail { void update_cache(memory::address base); }

	class object
	{
	public: // const interface
		virtual std::size_t display_id() const = 0;

		const std::string& name() const noexcept;

		memory::address base() const noexcept;

		geometry::vector position() const noexcept;

		wow::guid guid() const noexcept;

		bool valid() const noexcept;

		explicit operator bool() const noexcept;

	public: // mutator interface
		void teleport(const geometry::vector& location);

		virtual void change_name(const std::string& name) = 0;

	public: // {ctor}
		object() = default;
		explicit object(memory::address base);

		object(object&&) = default;
		object(const object&) = default;

		object& operator=(const object&) = default;
		object& operator=(object&&) = default;

		virtual ~object() = default;

	protected:
		explicit object(memory::address base, const unit&);
		explicit object(memory::address base, const player&);
		explicit object(memory::address base, const game_object&);

		virtual geometry::vector get_position() const;

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
		std::string		name_;
	};

	bool is_valid(const object& obj);

	bool operator==(const object& lhs, const object& rhs);
	bool operator!=(const object& lhs, const object& rhs);


} // namespace wow::entities

namespace wow
{
	using entities::object;
}