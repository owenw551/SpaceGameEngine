#pragma once
#include "Components.h"
#include "../Vector2D.h"

//The basic transform component class holds position and dimensions for an entity.

class TransformComponent : public Component
{
protected:

	Vector2D position;
	int width = 32;
	int height = 32;
	float scale = 1.0f ;
	double angle = 0; //in degrees measured from the vertical
	bool centeredOnOrigin = false;


public:

	TransformComponent()
	{
		position.Zero();
		angle = 0;
	}

	TransformComponent(float xPos, float yPos)
	{
		position.setx(xPos);
		position.sety(yPos);
	}

	TransformComponent(float xPos, float yPos, int w, int h, float s, bool oc = false)
		: width(w), height(h), scale(s), centeredOnOrigin(oc)
	{
		position.setx(xPos);
		position.sety(yPos);
	}


	virtual void init() override
	{
	}


	float getx() { return position.getx(); }
	float gety() { return position.gety(); }
	double getangle() { return angle; }
	int getw() { return width;  }
	int geth() { return height; }
	float gets() { return scale;  }
	bool isCenteredOnOrigin() { return centeredOnOrigin; }

	Vector2D& getPositionVector()
	{
		return position;
	}


	void setPos(float newx, float newy)
	{
		position.setx(newx);
		position.sety(newy);
	}

	void setWidth(int w)
	{
		width = w;
	}

	void setHeight(int h)
	{
		height = h;
	}

	void setScale(float s)
	{
		scale = s;
	}

	void setAngle(double a)
	{
		angle = a;
	}

	void setSizeData(int w, int h, float s)
	{
		width = w;
		height = h;
		scale = s;
	}

	virtual void update() override
	{}

};