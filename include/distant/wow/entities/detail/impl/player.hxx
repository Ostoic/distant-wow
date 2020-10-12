#pragma once
#include "../player.hpp"

#include "../../../memory/operations.hpp"
#include "../../../offsets.hpp"
#include "../../../error/game_error.hpp"

namespace distant::wow::entities::detail
{
	template <>
	inline memory::address get_name_ptr<player>(wow::guid guid)
	{
		const auto mask = memory::read<wow::dword>(wow::offsets::name_cache::cache_base + wow::offsets::name_cache::player_name_mask);
		const auto base = memory::read<wow::dword>(wow::offsets::name_cache::cache_base + wow::offsets::name_cache::player_name_base);

		const auto short_guid = memory::address(guid.low & 0xFFFFFFFF);

		auto offset = 12 * (mask & short_guid);
		auto current = memory::read<memory::address>(base + offset + 8);
		offset = memory::read<wow::dword>(base + offset);

		if ((current & 0x1) == 0x1)
			throw error::memory_disparity("[entities::player::get_name_ptr()] Invalid name cache offset");

		auto test_guid = memory::read<wow::dword>(current);
		while (test_guid != short_guid)
		{
			current = memory::read<memory::address>(current + offset + 4);

			if ((current & 0x1) == 0x1)
				throw error::memory_disparity("[entities::player::get_name_ptr()] Invalid name cache offset");

			test_guid = memory::read<wow::dword>(current);
		}

		return current + wow::offsets::name_cache::player_name_string;
	}

	template <>
	inline std::string load_name<player>(const wow::guid guid)
	{
		return memory::read<std::string>(detail::get_name_ptr<player>(guid));
	}
}
