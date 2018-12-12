#include "GameplayScene.h"
#include "ECS/Components.h"
#include <iostream>
#include "Collision.h"
#include "Game.h"

GameplayScene::GameplayScene(std::string mappath, const char* texturepath, SceneManager& scemanref) : Scene(scemanref), assetManager(manager), map(manager, assetManager)
{
	load(mappath, texturepath);
}

void GameplayScene::load(std::string mappath, const char* texturepath)
{

	//load map
	int w = sceneManager.getScreenWidth();
	int h = sceneManager.getScreenHeight();
	map.loadMap(mappath, texturepath, w, h);

	//load player texture
	assetManager.AddTexture("Player", "Assets/ship.png");

	//add player
	Entity& newPlayer = manager.addEntity();
	newPlayer.addComponent<TransformComponent>(100.0f, 100.0f, 16, 32, 1.0f);
	newPlayer.addComponent<VelocityComponent>(0.0f, 0.0f, 1.0f, 5.0f);
	newPlayer.addComponent<AccelerationComponent>(0.0f, 0.0f, 1.0f, 5.0f);
	newPlayer.addComponent<SpriteComponent>(0, 0, 16, 32, true,  "Player" , map.getCameraPtr(), assetManager);
	newPlayer.addComponent<MouseController>(map.getCameraPtr());
	newPlayer.addToGroup(PLAYER_GROUP);

	playerptr = &newPlayer;
	camera = &map.getCamera();

	//set groups
	mapCollisionGroup = (manager.getGroup(DEBUG_MAP_COLLISION_GROUP));
	tileGroup = (manager.getGroup(TILE_GROUP));
	playerGroup = (manager.getGroup(PLAYER_GROUP));

	
}

void GameplayScene::update()
{
	/*Vector2D prevPos = playerptr->getComponent<TransformComponent>().getPositionVector();*/
	static int frameCount = 0;
	manager.update();
	manager.refresh();
	frameCount++;
	//check for collisions with tiles with collision components, currently disabled
	/*for (auto& a : mapCollisionGroup)
	{
		if (Collision::AABB(playerptr->getComponent<CollisionComponent>(), a->getComponent<CollisionComponent>()))
		{
			std::cout << "collision" << std::endl;
			playerptr->getComponent<TransformComponent>().setPos(prevPos.getx(), prevPos.gety());
		}
	}*/
	//update camera
	camera->cameraRect.x = (int)(playerptr->getComponent<TransformComponent>().getx() - camera->midpointX);
	camera->cameraRect.y = (int)(playerptr->getComponent<TransformComponent>().gety() - camera->midpointY);
	if (!(camera->mapSmallerThanScreen))
	{
		if (camera->cameraRect.x < 0)
		{
			camera->cameraRect.x = 0;
		}

		if (camera->cameraRect.y < 0)
		{
			camera->cameraRect.y =0 ;
		}

		if (camera->cameraRect.x > camera->maxX)
		{
			camera->cameraRect.x = camera->maxX;
		}

		if (camera->cameraRect.y > camera->maxY)
		{
			camera->cameraRect.y = camera->maxY;
		}
	}
}

void GameplayScene::render()
{
	SDL_RenderClear(Game::renderer);
	for (auto& t : tileGroup)
	{
		t->draw();
	}
	for (auto& t : playerGroup)
	{
		t->draw();
	}
	SDL_RenderPresent(Game::renderer);
}
