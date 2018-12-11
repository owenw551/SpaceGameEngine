#pragma once
#include "SceneManager.h"
#include "SDL.h"

//Scene to pause the game, while still rendering the entities beneath it

class OverlayScene : public Scene
{
private:
	bool active = true;
	Scene* overScene;
	SDL_Rect overlayRect;

public:
	OverlayScene(SceneManager& scemanref, Scene* sceneOverlayed);
	~OverlayScene();

	virtual void update();
	virtual void render();
	virtual void unload() {}
};