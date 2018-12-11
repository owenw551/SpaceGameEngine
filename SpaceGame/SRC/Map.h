#pragma once
#include <array>
#include <vector>
#include "ECS/EntityComponentManager.h"
#include "Camera.h"
#include "AssetManager.h"

//Purpose of Map:
//Other than just loading in the tiles, tiles can be accessed through map
//Also Holds Camera Data

class Map
{
private:
	Manager& manager;
	AssetManager& assetManager;
	std::vector< Entity* > mapTiles;
	int currentTilesWide;
	int currentTilesHigh;
	int currentTileWidth;
	int currentTileHeight;
	int currentTotalMapWidth;
	int currentTotalMapHeight;
	int currentScale = 1;
	Camera camera;
	Camera *cameraptr = &camera; //To pass to tiles

public:
	Map(Manager& managerRef, AssetManager& assetManagerRef) : manager(managerRef) , assetManager(assetManagerRef)
	{}

	void loadMap(std::string mapPath, const char* texturePath, int cameraWidth, int cameraHeight); //load in mapfile from assets folder
	Entity* addTile(int xPos, int yPos, int srcX, int srcY);
	void addCollisionToTile(int x, int y); //add a simple AABB collision component to a tile
	Entity& tileAt(int x, int y); //tile accessor
	int getMapWidth() { return currentTotalMapWidth; }
	int getMapHeight() { return currentTotalMapHeight; }
	Camera& getCamera() { return camera; }
	Camera* getCameraPtr() { return cameraptr; }
};
