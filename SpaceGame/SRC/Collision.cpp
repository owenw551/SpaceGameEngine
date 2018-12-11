#include "Collision.h"
#include "ECS\AABBCollisionComponent.h"
#include <iostream>

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const AABBCollisionComponent& colA, const AABBCollisionComponent& colB)
{
	if(AABB(colA.getRect(), colB.getRect()))
	{
		std::cout << colA.getTag() << " hit " << colB.getTag() << std::endl;
		return true;
	}
	return false;
}
