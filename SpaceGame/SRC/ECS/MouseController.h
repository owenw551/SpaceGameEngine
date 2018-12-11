#pragma once
#include "Components.h"
#include "../Game.h"
#include "../Camera.h"
#include <iostream>

/*Component to deal with mouse input
* Only temporary as aiming to remove so entities follow the Command pattern.
* Currently allows the player controlled objecto to rotate and accelerate, and affect the camera
*
*   AccelerationComponent *acceleration;	to affect acceleration
*	SpriteComponent *sprite;				to change sprite (not currently added in yet)
*	TransformComponent *transform;			to affect angle 
*	Camera *camera;							to affect camera
*	float acclerationMagnitude = 0.2f;		to affect how much the object accelerates by
*	int mousex, mousey;						to store mouse position on screen
*	bool rightmousedown;					to help with input handling
*/


class MouseController : public Component
{
private:
	AccelerationComponent *acceleration;
	SpriteComponent *sprite;
	TransformComponent *transform;
	Camera *camera;
	float acclerationMagnitude = 0.3f;
	int mousex, mousey;
	bool rightmousedown;

public:
	MouseController(Camera* cameraptr) : camera(cameraptr)
	{}

	void init() override
	{
		assert(owner->hasComponent<TransformComponent>());
		transform = &owner->getComponent<TransformComponent>();
		sprite = &owner->getComponent<SpriteComponent>();
		acceleration = &owner->getComponent<AccelerationComponent>();
	}


	void update() override
	{

		//Set Angle of entity
		if (Game::event.type == SDL_MOUSEMOTION)
		{
			//Get mouse position
			SDL_GetMouseState(&mousex, &mousey);
			
		}
	
		//Change angle by calculating the vector between the mouse and the player, and then calculate the angle relative to the vertical
		float xforvec = (float(mousex + camera->cameraRect.x) - transform->getx());
		float yforvec = (float(mousey + camera->cameraRect.y) - transform->gety());
		Vector2D vec(xforvec, yforvec);
		transform->setAngle(vec.angleRelativeToVertical());

		//Get whether mouse is down or up, then update acceleration accordingly;
		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (Game::event.button.button)
			{
				case SDL_BUTTON_RIGHT :
					rightmousedown = true;
					break;

				default :
					break;
			}
		}

		if (Game::event.type == SDL_MOUSEBUTTONUP)
		{
			switch (Game::event.button.button)
			{
				case SDL_BUTTON_RIGHT:
					rightmousedown = false;
				default:
					break;
			}
		}

		if (rightmousedown)
		{
			Vector2D vecfromAngle(transform->getangle());
			acceleration->setAcc(vecfromAngle.getx() * acclerationMagnitude, vecfromAngle.gety() * acclerationMagnitude);
		}
		else
		{
			acceleration->getAccelerationVector().Zero();
		}


	}
	
};