#pragma once

#include "../Game.h"
#include "Components.h"
#include <iostream>
#include "../OverlayScene.h"
#include <cassert>


/*Component to deal with keyboard input
* Only temporary as aiming to remove so entities follow the Command pattern.
* Currently allows the player to move based on the keyboard input, and pause the game by loading a pause scene on the scene stack
*
*	SceneManager& sceneManager;			to load on pause screen
*	Scene* currentScene;				to pass to pause scene so it can render the scene behind it
*	float accelerationValue = 0.7f;		scalar for how fast the object moves
*	TransformComponent *transform;		to reset position
*	AccelerationComponent *acc;			to change movement
*/

class KeyboardController : public Component
{
private:
	SceneManager& sceneManager;
	Scene* currentScene;
	float accelerationValue = 0.7f;
	TransformComponent *transform;
	AccelerationComponent *acc;

public:
	KeyboardController(SceneManager& sceManRef, Scene* curScePtr) : sceneManager(sceManRef), currentScene(curScePtr)
	{}

	void init() override
	{
		assert(owner->hasComponent<TransformComponent>() && owner->hasComponent<VelocityComponent>());
		transform = &owner->getComponent<TransformComponent>();
		acc = &owner->getComponent<AccelerationComponent>();
	}

	//handle keyboard events, move the entity up down left or right, reset the game, pause the game
	//not a great way of doing this, just experimenting. will get rid of soon

	void update() override
	{

			if (Game::event.type == SDL_KEYDOWN)
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					acc->setAccy(-accelerationValue);
					break;

				case SDLK_a:
					acc->setAccx(-accelerationValue);
					break;

				case SDLK_s:
					acc->setAccy(accelerationValue);
					break;

				case SDLK_d:
					acc->setAccx(accelerationValue);
					break;

				case SDLK_r:
					transform->setPos(200.0f, 250.0f);
					acc->setAcc(0.0f, 0.0f);
					break;

				case SDLK_p:
					sceneManager.loadScene<OverlayScene>(sceneManager, currentScene);
					break;
				default:
					break;
				}

			if (Game::event.type == SDL_KEYUP)
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:
					acc->setAccy(0.0f);
					break;

				case SDLK_a:
					acc->setAccx(0.0f);
					break;

				case SDLK_s:
					acc->setAccy(0.0f);
					break;

				case SDLK_d:
					acc->setAccx(0.0f);
					break;

				default:
					break;
				}
	}
};