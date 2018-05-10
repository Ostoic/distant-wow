#pragma once
#include "../object_dump.hpp"

namespace wow::objects
{
	template <typename Object>
	object_dump<Object>::object_dump(const Object& object) noexcept
		: object(object)
	{}

	template <typename Object>
	descriptor_dump<Object>::descriptor_dump(const Object& object) noexcept
		: dump<Object>(object)
	{}

	template <typename Object>
	object_dump<Object> make_object_dump(const Object& object) noexcept
	{
		return object_dump<Object>(object);
	}

	template <typename Object>
	descriptor_dump<Object> make_descriptor_dump(const Object& object) noexcept
	{
		return descriptor_dump<Object>(object);
	}

	namespace detail
	{
		template <typename CharT, typename TraitsT>
		void dump_to_stream(std::basic_ostream<CharT, TraitsT>& stream, const objects::game_object& object)
		{
			stream
				<< "Game object:\n"
				<< "Name: " << object.name() << '\n'
				<< "Base: " << object.base() << '\n'
				<< "Display id: " << object.display_id() << '\n';

			stream << "Created by: ";
			if (object.owner().has_value())
				stream << object.owner()->get().name() << '\n';
			else
				stream << "nobody\n";

			stream 
				<< "Flags: " << object.flags() << '\n'
				<< "Other flags: " << object.other_flags() << '\n';
		}

		template <typename CharT, typename TraitsT>
		void dump_to_stream(std::basic_ostream<CharT, TraitsT>& stream, const objects::unit& object)
		{
			stream
				<< "Unit:\n"
				<< "Name: " << object.name() << '\n'
				<< "Base: " << object.base() << '\n'
				<< "Display id: " << object.display_id() << '\n';

			stream << "Owner: ";
			if (object.owner().has_value())
				stream << object.owner()->get().name() << '\n';
			else
				stream << "nobody\n";

			stream 
				<< "Flags: " << object.flags() << '\n'
				<< "Other flags: " << object.other_flags() << '\n';
		}

		template <typename CharT, typename TraitsT>
		void dump_to_stream(std::basic_ostream<CharT, TraitsT>& stream, const wow::player& player)
		{
			dump_to_stream(stream, static_cast<const wow::unit&>(player));
		}
	}

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const object_dump<Object>& dump)
	{
		detail::dump_to_stream(stream, dump.object);
		return stream;
	}

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const descriptor_dump<Object>& dump)
	{
		detail::dump_to_stream(stream, dump.object);
		return stream;
	}
}
