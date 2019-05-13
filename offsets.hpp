#pragma once

#include "memory/address.hpp"
#include "geometry/vector.hpp"

#include "primitives.hpp"
#include "entities/types.hpp"

#include <string>

namespace distant::wow::entities
{
	enum class power_type;
	enum class faction;
}

/// @brief WoW version 3.3.5a 12340 addresses and offsets.
/// Todo: Figure out a better way to describe the structure of offsets (tmp? constexpr stuff?)
/// Maybe like: static_addr | offset(0xD4) ? idk
namespace distant::wow::offsets
{
	struct pointer;

	template <typename...>
	struct function;

	constexpr auto client_connection = wow::memory::offset<wow::memory::address>(0x00C79CE0);

	namespace build_info
	{
		constexpr auto version_name	 = wow::memory::offset<std::string>(0x00CABBB8);
		constexpr auto major_version = wow::memory::offset<wow::uint>(0x009F5208);
		constexpr auto minor_version = wow::memory::offset<wow::uint>(0x009F5200);
	}

	namespace login_status
	{
		constexpr auto queue_position	   = memory::offset<wow::uint>(0x00B6A9BC);
		constexpr auto login_screen_status = memory::offset<wow::dword>(0xD41660);
		constexpr auto account_name		   = memory::offset<std::string>(0x00B6AA40);
		constexpr auto realm_name		   = memory::offset<std::string>(0x00C79B9E);
	}

	namespace local
	{
	}

	namespace ui
	{
		constexpr auto followed_unit = memory::offset<wow::guid>(0x00CA11F8);
		constexpr auto current_target = memory::offset<wow::guid>(0x00BD07B0);
		constexpr auto last_target = memory::offset<wow::guid>(0x00BD07B8);
		constexpr auto follow_guid = memory::offset<wow::guid>(0x00CA11F8);
	}

	namespace game_state
	{
		constexpr auto ingame	 = memory::offset<bool>(0xBEBA40);
		constexpr auto logged_in = memory::offset<bool>(0xBD0793);
	}

	namespace directX
	{
		constexpr auto device_static_ptr = memory::offset<pointer>(0x00C5DF88);
		constexpr auto device_ptr_offset = memory::offset<pointer>(0x397C);
		constexpr auto beginscene_offset = memory::offset<pointer>(0xA4);
		constexpr auto endscene_offset   = memory::offset<pointer>(0xA8);
		constexpr auto clear_offset		 = memory::offset<pointer>(0xAC);
	}

	namespace map
	{
		constexpr auto zone_id  = memory::offset<wow::uint>(0x00BD080C);
		constexpr auto map_name = memory::offset<std::string>(0xCE06D0);
	}

	namespace dbc
	{
		constexpr auto area_table		 = memory::address(0x00AD3134);
		constexpr auto character_classes = memory::address(0x00AD3404);
		constexpr auto power_display	 = memory::address(0x00AD43A0);
	}

	namespace local_player
	{
		constexpr auto base		 = memory::offset<memory::address>(0xCD87A8);
		constexpr auto base_ptr1 = memory::offset<memory::address**>(0x34);
		constexpr auto base_ptr2 = memory::offset<memory::address*>(0x24);
		constexpr auto name		 = memory::offset<std::string>(0xC79D18);
	}

	namespace object_manager
	{
		constexpr auto current_mgr	= memory::offset<memory::address>(0x2ED0);
		constexpr auto map_id		= memory::offset<wow::uint>(0xCC);
		constexpr auto tls_index	= memory::offset<memory::address>(0x2C);
		constexpr auto player_guid	= memory::offset<wow::guid>(0xC0);
		constexpr auto first_entry	= memory::offset<entities::object*>(0xAC);
	}

	namespace movement_controller
	{
		// [current_mgr + 0xD4]
		constexpr auto base					  = memory::offset<memory::address>(0xD4);
		constexpr auto default_movement_class = memory::offset<memory::address>(0x11D);
		constexpr auto current_movement_class = memory::offset<memory::address>(0x120);
	}

	namespace object
	{
		constexpr auto vtable = memory::offset<std::vector<function<void>>>(0);
		constexpr auto scale  = memory::offset<float>(0x10); // ?? check

		constexpr auto type   = memory::offset<entities::object_type>(0x14);
		constexpr auto guid   = memory::offset<wow::guid>(0x30);
		constexpr auto next   = memory::offset<entities::object*>(0x3C);

		// what type?
		constexpr auto model = memory::offset<wow::uint>(0xB4);

		constexpr auto disabled = memory::offset<bool>(0xB8);

		constexpr auto power_type_ptr = memory::offset<memory::address>(0xD0);
		constexpr auto power_type	  = memory::offset<entities::power_type>(0x47);

		constexpr auto power = memory::offset<wow::uint>(0xFB4);

		constexpr auto object_descriptors = memory::offset<memory::address>(0x08);
		constexpr auto player_descriptors = memory::offset<memory::address>(0x1198);

		constexpr auto go_position = memory::offset<geometry::vector>(0xE8);
		constexpr auto go_x_coord = memory::offset<float>(0xE8);
		constexpr auto go_y_coord = memory::offset<float>(0xEC);
		constexpr auto go_z_coord = memory::offset<float>(0xF0);

		constexpr auto position = memory::offset<geometry::vector>(0x798);
		constexpr auto x_coord  = memory::offset<float>(0x798);
		constexpr auto y_coord  = memory::offset<float>(0x79C);
		constexpr auto z_coord  = memory::offset<float>(0x7A0);
		constexpr auto rotation = memory::offset<float>(0x7A8);
	}

	namespace item_descriptors
	{
		constexpr auto owner_guid		 = memory::offset<wow::guid>(0);
		constexpr auto container_guid	 = memory::offset<wow::guid>(0x8);
		constexpr auto creator_guid		 = memory::offset<wow::guid>(0x10);
		constexpr auto gift_creator_guid = memory::offset<wow::guid>(0x18);
		constexpr auto stack_count		 = memory::offset<wow::uint>();
		constexpr auto duration			 = memory::offset<wow::uint>();
		constexpr auto charges_left		 = memory::offset<wow::uint>();
		constexpr auto flags			 = memory::offset<wow::flags>();
		constexpr auto enchantment_id	 = memory::offset<wow::uint>();
		constexpr auto item_text_id		 = memory::offset<wow::uint>();
		constexpr auto durability		 = memory::offset<wow::uint>();
		constexpr auto max_durability	 = memory::offset<wow::uint>();
	}

	namespace party
	{
		constexpr auto member1_guid = memory::offset<wow::guid>(0x00BD1948);
		constexpr auto member2_guid = memory::offset<wow::guid>(member1_guid + memory::address(sizeof(wow::guid)));
		constexpr auto member3_guid = memory::offset<wow::guid>(member2_guid + memory::address(sizeof(wow::guid)));
		constexpr auto member4_guid = memory::offset<wow::guid>(member3_guid + memory::address(sizeof(wow::guid)));
		constexpr auto member5_guid = memory::offset<wow::guid>(member4_guid + memory::address(sizeof(wow::guid)));
		constexpr auto leader_guid  = memory::offset<wow::guid>(0x00BD1968);
	}

	namespace unit_descriptors
	{
		//constexpr auto ownership_chunk	 = memory::offset<decltype(entities::detail::unit_descriptors::ownership_chunk)>(0x18);
		constexpr auto charm			 = memory::offset<wow::guid>(0x18);
		constexpr auto summon			 = memory::offset<wow::guid>(0x20);
		constexpr auto critter			 = memory::offset<wow::guid>(0x28);
		constexpr auto charmed_by		 = memory::offset<wow::guid>(0x30);
		constexpr auto summoned_by		 = memory::offset<wow::guid>(0x38);
		constexpr auto created_by		 = memory::offset<wow::guid>(0x40);
		constexpr auto target			 = memory::offset<wow::guid>(0x48);
		constexpr auto channelled_object = memory::offset<wow::guid>(0x50);
		constexpr auto channelled_spell  = memory::offset<wow::guid>(0x58);

		//constexpr auto power_chunk = memory::offset<decltype(entities::detail::unit_descriptors::power_chunk)>(0x60);
		constexpr auto health = memory::offset<wow::uint>(0x60);
		constexpr auto power1 = memory::offset<wow::uint>(0x64); // weird
		constexpr auto power2 = memory::offset<wow::uint>(0x68); // warrior rage * 10
		constexpr auto power3 = memory::offset<wow::uint>(0x6C);
		constexpr auto power4 = memory::offset<wow::uint>(0x70); // rogue energy
		constexpr auto power5 = memory::offset<wow::uint>(0x74);
		constexpr auto power6 = memory::offset<wow::uint>(0x78);
		constexpr auto power7 = memory::offset<wow::uint>(0x7C); // weird
		constexpr auto max_health = memory::offset<wow::uint>(0x80);
		constexpr auto max_power1 = memory::offset<wow::uint>(0x84); // mana
		constexpr auto max_power2 = memory::offset<wow::uint>(0x88); // warrior rage * 10
		constexpr auto max_power3 = memory::offset<wow::uint>(0x8C);
		constexpr auto max_power4 = memory::offset<wow::uint>(0x90); // rogue energy
		constexpr auto max_power5 = memory::offset<wow::uint>(0x94);
		constexpr auto max_power6 = memory::offset<wow::uint>(0x98);
		constexpr auto max_power7 = memory::offset<wow::uint>(0x9C); // rune*10

		constexpr auto facition = memory::offset<entities::faction>(0xDC);
		constexpr auto flags  = memory::offset<wow::flags>(0xEC);
		constexpr auto flags2 = memory::offset<wow::flags>(0xF0);
		constexpr auto display_id = memory::offset<wow::uint>(0x10C);

		//constexpr auto channelled_object = memory::offset<wow::guid>(0x50);
		//constexpr auto channelled_object = memory::offset<wow::guid>(0x50);

		//constexpr auto speed_chunk				= memory::offset<decltype(entities::detail::unit_descriptors::speed_chunk)>(0x814);
		constexpr auto movement_speed_current	= memory::offset<float>(0x814);
		constexpr auto movement_speed_walking	= memory::offset<float>(0x818);
		constexpr auto movement_speed_active	= memory::offset<float>(0x81C);
		// 4 bytes padding
		constexpr auto movement_speed_swimming	= memory::offset<float>(0x824);
		// 8 bytes padding
		constexpr auto movement_speed_flying	= memory::offset<float>(0x82C);

		constexpr auto movement_state = memory::offset<std::array<byte, 4>>(0x7CC);
		// (0 0 0 3) flying
		// (0 0 0 128) default - stop fall
		// (1 0 0 128) run forward
		// (0 0 0 96) levitate
		// (0 1 0 128) walking
	}



	namespace game_object_descriptors
	{
		constexpr auto created_by		= memory::offset<wow::guid >(0x18);
		constexpr auto display_id		= memory::offset<wow::uint >(0x20);
		constexpr auto flags			= memory::offset<wow::flags>(0x24);
		constexpr auto parent_rotation	= memory::offset<float	   >(0x28);
		constexpr auto dynamic_flags	= memory::offset<wow::flags>(0x38);
		constexpr auto faction			= memory::offset<wow::uint >(0x3C);
		constexpr auto level			= memory::offset<wow::uint >(0x40);
		constexpr auto other_flags		= memory::offset<wow::flags>(0x44);
	}

	namespace dynamic_object_descriptors
	{
		constexpr auto caster	  = memory::offset<wow::guid>(0);
		constexpr auto spell_id   = memory::offset<wow::uint>(0xC);
		constexpr auto radius	  = memory::offset<float>(0x10);
		constexpr auto position_x = memory::offset<float>(0x14);
		constexpr auto position_y = memory::offset<float>(0x18);
		constexpr auto position_z = memory::offset<float>(0x1C);
		constexpr auto facing	  = memory::offset<float>(0x20);
		constexpr auto cast_time  = memory::offset<wow::uint>(0x24);
	}

	namespace name_cache
	{
		constexpr auto unit_name_ptr_offset1 = memory::offset<std::string**>(0x964);
		constexpr auto unit_name_ptr_offset2 = memory::offset<std::string*>(0x5C);

		constexpr auto cache_base		  = memory::offset<memory::address>(0xC5D940);
		constexpr auto player_name_mask   = memory::offset<wow::flags>(0x24);
		constexpr auto player_name_base   = memory::offset<pointer>(0x1C);
		constexpr auto player_name_string = memory::offset<std::string>(0x20);

		constexpr auto go_name_ptr_offset1 =
			memory::offset<
				memory::offset<
					memory::offset<std::string>
				>
			> (0x1A4);

		constexpr auto go_name_ptr_offset2 =
			memory::offset<
				memory::offset<std::string>
			> (0x90);
	}

	namespace guild
	{
		constexpr auto roster_start				= memory::offset<memory::address>(0x00C22AE0);
		constexpr auto number_of_members		= memory::offset<wow::uint>(0x00C22AB0);
		constexpr auto number_of_online_members = memory::offset<wow::uint>(0xC22AB4);

		constexpr auto update_roster = memory::offset<function<void()>>(0x005CA9B0);
	}

	namespace time
	{
		// Todo: consider returning std::chrono::time_point
		constexpr auto time_manager		   = memory::address(0xB1D5E4);
		constexpr auto timestamp		   = memory::offset<wow::uint>(time_manager + 0x00B1D618);
		constexpr auto last_hardware_input = memory::offset<wow::uint>(0x00B499A4);
	}

	namespace console
	{
		constexpr auto key				  = memory::offset<wow::byte>(0x00ADBAC4);
		constexpr auto is_active		  = memory::offset<bool>(0xCA1978);
		constexpr auto last_message		  = memory::offset<std::array<char, 400>>(0xCABA58);
		constexpr auto number_of_messages = memory::offset<wow::uint>(0x00CA197C);
	}

	namespace loot_table
	{
		constexpr auto initiate_running_loot_hack = memory::address(0x006DAE60);
		constexpr auto looted_unit = memory::offset<wow::guid>(0x00BFA8D8);
		constexpr auto item_guids = memory::offset<std::array<wow::guid, 18>>(0x00BFA694);
	}

	namespace c_vars
	{
	}

} // namespace distant::wow::offsets
