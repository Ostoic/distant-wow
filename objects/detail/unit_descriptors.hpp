#pragma once

#include <wow/primitives.hpp>

namespace objects::detail
{
	struct unit_descriptors
	{
		wow::dword base;

		struct
		{
			wow::guid charm;	// 0x18
			wow::guid summon;	// 0x20
			wow::guid critter;	// 0x28

			wow::guid charmed_by;	// 0x30
			wow::guid summoned_by;	// 0x38
			wow::guid created_by;	// 0x40

			wow::guid target;		  // 0x48
			wow::guid channel_object; // 0x50
			wow::dword channel_spell; // 0x58
		} ownership_chunk;

		struct
		{
			wow::uint health;
			wow::uint power1; // weird
			wow::uint power2; // warrior rage * 10
			wow::uint power3;
			wow::uint power4; // rogue energy
			wow::uint power5;
			wow::uint power6;
			wow::uint power7; // weird
			wow::uint max_health;
			wow::uint max_power1; // weird
			wow::uint max_power2; // warrior rage * 10
			wow::uint max_power3;
			wow::uint max_power4; // rogue energy
			wow::uint max_power5;
			wow::uint max_power6;
			wow::uint max_power7; // weird
		} power_chunk;

		// Movement 
		wow::dword movement_state;
		struct 
		{
			float current_speed;	// 0x814
			float walk_speed;		// 0x818
			float active_speed;		// 0x81C
			wow::byte padding1[4];	// 0x820
			float swim_speed;		// 0x824
			wow::byte padding2[8];	// 0x820
			float flight_speed;		// 0x82C
		} speed_chunk;
	};
}
