#pragma once
#include "SDL.h"

//currently caters for AABB collisions, will add other types soon

class AABBCollisionComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& rectB);
	static bool AABB(const AABBCollisionComponent& colA, const AABBCollisionComponent& colB);
};