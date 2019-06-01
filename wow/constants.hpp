#pragma once

namespace distant::wow::constants
{
	constexpr float contact_distance  = 0.5f;	// ??
	constexpr float interact_distance = 5.0f;	// the maximum distance for which an object can be interacted with
	constexpr float attack_distance   = 5.0f;   // the maximum distance for auto attacks
	constexpr float inspect_distance  = 28.0f;  // the max distance that inspecting a player is allowed
	constexpr float trade_distance	  = 11.11f; // the max distance that player trades are allowed

	constexpr float sight_range_unit = 50.0f;
	constexpr float default_visibility_continent = 90.0f;  // default visibility distance in the world
	constexpr float default_visibility_instance  = 170.0f; // default visibility distance in instances
	constexpr float default_visibility_bgarenas  = 533.0f; // default visibility distance in bgs and arenas

	constexpr float default_player_bounding_radius = 0.388999998569489f; // default player size
	constexpr float default_player_combat_reach = 1.5f;
	constexpr float min_melee_reach = 2.0f;
	constexpr float nominal_melee_reach = 5.0f;
	constexpr float melee_range = (nominal_melee_reach - min_melee_reach * 2); // center to center for players
}
