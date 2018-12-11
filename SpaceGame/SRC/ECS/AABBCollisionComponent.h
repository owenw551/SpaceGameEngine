#pragma once

#include "SDL.h"
#include "Components.h"
#include <cassert>

/*
* AABBCollisionComponent is a component that holds data for rectangular AABB collisions
* 
*	std::string tag;					to allow entities to collide with each other based on CollisionComponent "type"
*	TransformComponent *transform;		to update collider based on postion
*	SDL_Rect collisionRect;				rectangle for collision, can be different size to the object
*	int xOffset, yOffset = 0;			where the collider is relative to 
*	bool customFixedSize = false;
*	bool isStatic;
*
*
*/


class AABBCollisionComponent : public Component
{
private:
	
	std::string tag;
	TransformComponent *transform;
	SDL_Rect collisionRect;
	int xOffset, yOffset = 0;
	bool customFixedSize = false;
	bool isStatic;

public:

	AABBCollisionComponent(std::string newTag, bool isFixed)
		: tag(newTag), isStatic(isFixed)
	{}

	AABBCollisionComponent(int xOff, int yOff, int width, int height, std::string newTag, bool fixedPosition, bool fixedCustomSize = true)
	{
		xOffset = xOff;
		yOffset = yOff;
		tag = newTag;
		collisionRect.w = width;
		collisionRect.h = height;
		customFixedSize = fixedCustomSize;
		isStatic = fixedPosition;
	}

	void init() override
	{
		assert(owner->hasComponent<TransformComponent>());

		transform = &owner->getComponent<TransformComponent>();

		if (!customFixedSize)
		{
			collisionRect.x = (int)transform->getx();
			collisionRect.y = (int)transform->gety();
			collisionRect.w = transform->getw();
			collisionRect.h = transform->geth();
		}
	}

	virtual void update() override
	{
		if (!isStatic)
		{
			collisionRect.x = static_cast<int>(transform->getx() + xOffset);
			collisionRect.y = static_cast<int>(transform->gety() + yOffset);
		}
	}

	const SDL_Rect& getRect() const { return collisionRect; }

	std::string getTag() const { return tag; }


};
