#pragma once
#include "../object_dump.hpp"

#include "../../../geometry/algorithm.hpp"
#include "../../entities/object_manager.hpp"

namespace wow::dump
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

	template <typename Object>
	location_dump<Object> make_location_dump(const Object& object) noexcept
	{
		return location_dump<Object>(object);
	}

	template <typename Object>
	location_dump<Object>::location_dump(const Object& object) noexcept
		: object(object)
	{}

	namespace detail
	{

		template <typename CharT, typename TraitsT>
		void dump_object(std::basic_ostream<CharT, TraitsT>& stream, const entities::object& object)
		{
			stream
				<< "Name: " << object.name() << '\n'
				<< "Base: " << object.base() << '\n'
				<< "Type: " << "\n"
				<< "Guid: " << object.guid() << '\n';
		}

		template <typename CharT, typename TraitsT>
		void dump_object(std::basic_ostream<CharT, TraitsT>& stream, const wow::player& player)
		{
			dump_object(stream, static_cast<const wow::unit&>(player));
		}

		template <typename CharT, typename TraitsT>
		void dump_descriptors(std::basic_ostream<CharT, TraitsT>& stream, const wow::unit& unit)
		{
			//stream << unit.
		}

		template <typename CharT, typename TraitsT>
		void dump_descriptors(std::basic_ostream<CharT, TraitsT>& stream, const entities::game_object& object)
		{
			stream << "Created by: ";
			if (object.owner().has_value())
				stream << object.owner()->get().name() << '\n';
			else
				stream << "nobody\n";

			stream
				<< "Flags: " << object.flags() << '\n'
				<< "Other flags: " << object.other_flags() << '\n'
				<< "Dynamic flags: " << object.dynamic_flags() << '\n'
				<< "Level: " << object.level() << '\n'
				<< "Faction: " << object.faction() << '\n'
				<< "Parent rotation: " << object.parent_rotation() << '\n';
		}

		template <typename CharT, typename TraitsT>
		void dump_location(std::basic_ostream<CharT, TraitsT>& stream, const entities::object& object)
		{
			const auto pos = object.position();
			stream
				<< "Position: (" << pos.x() << ", " << pos.y() << ", " << pos.z() << ")\n"
				<< "Rotation: " << pos.rotation() << '\n'
				<< "Distance to player: " << geometry::distance(pos, entities::local_player().position()) << '\n';
		}
	}

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const object_dump<Object>& dump)
	{
		detail::dump_object(stream, dump.object);
		return stream;
	}

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const descriptor_dump<Object>& dump)
	{
		detail::dump_descriptors(stream, dump.object);
		return stream;
	}

	template <typename CharT, typename TraitsT, typename Object>
	std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& stream, const location_dump<Object>& dump)
	{
		detail::dump_location(stream, dump.object);
		return stream;
	}
}
