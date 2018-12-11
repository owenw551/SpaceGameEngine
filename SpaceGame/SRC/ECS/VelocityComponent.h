#pragma once
#include "Components.h"
#include "..\Vector2D.h"
#include <cassert>
/*
*   Component to add to entities if they need to move
*	TransformComponent *transform;  to alter position
*	Vector2D velocity;				to hold direction and 
*	float speedScalar;				to scale speed according to size
*	float maxSpeed;					to cap how fast objects can travel
*	float minimumSpeed = 0.02f;		allows entities to come to a more definite stop
*/


class VelocityComponent : public Component
{
private:
	TransformComponent *transform;
	Vector2D velocity;
	float speedScalar;
	float maxSpeed;
	float minimumSpeed = 0.02f;

public:
	VelocityComponent()
	{
		speedScalar = 1;
		maxSpeed = 5;
		velocity.setx(0);
		velocity.sety(0);
	}


	VelocityComponent(float xVel, float yVel, float speed, float maxspeed)
	{
		speedScalar = speed;
		maxSpeed = maxspeed;
		velocity.setx(xVel);
		velocity.sety(yVel);
	}

	float getVelx() { return velocity.getx(); }
	float getVely() { return velocity.gety(); }
	void setVelx(const float newVelx) {  velocity.setx(newVelx); }
	void setVely(const float newVely) {  velocity.sety(newVely); }


	Vector2D& getVelocityVector()
	{
		return velocity;
	}

	void setVel(float newx, float newy)
	{
		velocity.setx(newx);
		velocity.sety(newy);
	}

	void init() override
	{
		assert(owner->hasComponent<TransformComponent>());
		transform = &owner->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (velocity.magnitude() > maxSpeed)
		{
			velocity.scaleToMagnitude(maxSpeed);
		}
		if (velocity.magnitude() < minimumSpeed)
		{
			velocity * 0;
		}
		transform->getPositionVector() += velocity;
	}

};