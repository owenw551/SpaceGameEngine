#pragma once
#include "SceneManager.h"
#include "Map.h"
#include "SDL.h"
#include "ECS/Groups.h"
#include "AssetManager.h"

//Currently the only "real" scene in use, using for debugging

using vecGroup = std::vector<Entity*>;

class GameplayScene : public Scene
{
private:
	AssetManager assetManager;
	Map map;
	Entity* playerptr;
	Camera* camera;
	vecGroup mapCollisionGroup;
	vecGroup tileGroup;
	vecGroup playerGroup;

public:
	GameplayScene(std::string mappath, const char* texturepath, SceneManager& scemanref);

	void update();
	void render();
	void unload() {};


	void load(std::string mappath, const char* texturepath);


};

