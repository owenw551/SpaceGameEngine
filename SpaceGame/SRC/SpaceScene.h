#pragma once

#include "SceneManager.h"
#include "SDL.h"
#include "ECS/Groups.h"
#include "AssetManager.h"
#include "Map.h"

using vecGroup = std::vector<Entity*>;

class SpaceScene : public Scene
{
	AssetManager assetManager;
	Entity* playerptr;
	Camera* camera;
	vecGroup mapCollisionGroup;
	vecGroup tileGroup;
	vecGroup playerGroup;

public:
	SpaceScene(std::string mappath, const char* texturepath, SceneManager& scemanref);

	void update();
	void render();
	void unload() {};


	void load(std::string mappath, const char* texturepath);


};