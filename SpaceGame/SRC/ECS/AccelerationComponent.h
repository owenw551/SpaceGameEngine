#pragma once
#include "Components.h"
#include "..\Vector2D.h"

/*
* AccelerationComponent - added to entity if they need to have force acting on them
*
*   Vector2D acceleration;	            acceleration vector
*	Vector2D restorative;	            vector that points in the opposite direction to velocity
*	VelocityComponent* velocity;	    needed to affect velocity component
*	float accScalar;	                scalar for acceleration
*	float maxAcc; upper		            bound for acceleration
*	float restorativeForce = -0.0f;		change to make object decelerate as if acted on by friction
*
*/

class AccelerationComponent : public Component
{
private:
	Vector2D acceleration;
	Vector2D restorative;
	VelocityComponent* velocity;
	float accScalar;
	float maxAcc;
	float restorativeForce = -0.02f;

public:
	AccelerationComponent(float xAcc, float yAcc, float accScale, float maxAcceleration)
	{
		accScalar = accScale;
		maxAcc = maxAcceleration;
		acceleration.setx(xAcc);
		acceleration.sety(yAcc);
	}

	//getters, setters

	float getAccx() { return acceleration.getx(); }
	float getAccy() { return acceleration.gety(); }
	void setAccx(const float newAccx) { acceleration.setx(newAccx); }
	void setAccy(const float newAccy) { acceleration.sety(newAccy); }


	Vector2D& getAccelerationVector()
	{
		return acceleration;
	}

	void setAcc(float newx, float newy)
	{
		acceleration.setx(newx);
		acceleration.sety(newy);
	}

	void init() override
	{
		if (!owner->hasComponent<VelocityComponent>())
		{
			owner->addComponent<VelocityComponent>();
		}
		velocity = &owner->getComponent<VelocityComponent>();
	}


	//add acceleration to velocity, calculate restorative vector, add restorative vector
	void update() override
	{
		velocity->getVelocityVector() += acceleration;
		restorative.setVec(velocity->getVelx(), velocity->getVely());
		restorative * restorativeForce;
		velocity->getVelocityVector() + restorative;
	}


};