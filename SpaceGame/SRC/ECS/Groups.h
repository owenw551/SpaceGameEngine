#pragma once
#include <memory>

//possible groups entities can belong to in the manager class
enum Group : std::size_t
{
	TILE_GROUP,
	PLAYER_GROUP,
	ENEMY_GROUP,
	DEBUG_MAP_COLLISION_GROUP
};