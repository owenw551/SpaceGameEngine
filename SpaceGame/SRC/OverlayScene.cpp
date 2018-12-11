#include "OverlayScene.h"
#include "Game.h"
#include <iostream>

OverlayScene::OverlayScene(SceneManager & scemanref, Scene* sceneOverlayed)
	: Scene(scemanref), overScene(sceneOverlayed)
{
	overlayRect.x = overlayRect.w = 0;
	overlayRect.w = sceneManager.getScreenWidth();
	overlayRect.h = sceneManager.getScreenHeight();
	std::cout << "Paused" << std::endl;
}

//pop off scene if the p button is pressed.
void OverlayScene::update()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_p:
			sceneManager.unloadScene();
			break;
		default:
			break;
		}
	}
}

void OverlayScene::render()
{
	//render 
	overScene->render();
}