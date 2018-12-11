#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include "ECS/Components.h"

void Map::loadMap(std::string mapPath, const char* texturePath, int cameraWidth, int cameraHeight)
{
	//Add Texture to AssetManager
	assetManager.AddTexture("MapTiles", texturePath);


	//Set up file read
	std::fstream mapFile(mapPath);
	std::string line;
	char charRead;



	//Load Map Parameters
	int tilesWide;
	int tilesHigh;
	int tileHeight;
	int tileWidth;

	std::getline(mapFile, line);
	line.erase(0, 10);
	tilesWide = std::stoi(line);

	std::getline(mapFile, line);
	line.erase(0, 10);
	tilesHigh = std::stoi(line);

	std::getline(mapFile, line);
	line.erase(0, 10);
	tileWidth = std::stoi(line);

	std::getline(mapFile, line);
	line.erase(0, 11);
	tileHeight = std::stoi(line);

	

	//Give map size data
	currentTilesWide = tilesWide;
	currentTilesHigh = tilesHigh;
	currentTileWidth = tilesWide;
	currentTileHeight = tileHeight;
	currentTotalMapWidth = currentTilesWide * currentTileWidth;
	currentTotalMapHeight = currentTilesHigh * currentTileHeight;

	//Set Camera Parameters
	camera.intitialiseCamera(0, 0, cameraWidth, cameraHeight, currentTotalMapWidth, currentTotalMapHeight, 0, 0);

	//ignore layer header
	mapFile.ignore(9);

	//Load Map Data
	//rectx, recty for where to load on spritesheet
	int rectx;
	int recty;

	for (int ycoord = 0; ycoord < tilesHigh; ycoord++)
	{

		for (int xcoord = 0; xcoord < tilesWide; xcoord++)
		{
			mapFile.get(charRead);
			recty = atoi(&charRead)* tileHeight;

			mapFile.get(charRead);
			rectx = atoi(&charRead)* tileWidth;
			mapTiles.push_back(addTile(xcoord * tileWidth, ycoord * tileHeight, rectx, recty));
			mapFile.ignore();
		}
		mapFile.ignore();
	}

	//Load Collision Data

	mapFile.ignore(9);
	for (int ycoord = 0; ycoord < tilesHigh; ycoord++)
	{

		for (int xcoord = 0; xcoord < tilesWide; xcoord++)
		{
			mapFile.get(charRead);
			if (charRead == '1')
			{
				addCollisionToTile(xcoord, ycoord);
			}
			mapFile.ignore();
		}
		mapFile.ignore();
	}

	mapFile.close();
}


//Creates tile when called
Entity* Map::addTile(int xPos, int yPos, int srcX, int srcY)
{
	Entity& tile(manager.addEntity());
	tile.addComponent<TransformComponent>((float)xPos,(float) yPos, currentTileWidth, currentTileHeight, (float) currentScale, true);
	tile.addComponent<SpriteComponent>(srcX, srcY, currentTileWidth, currentTileHeight, false,  "MapTiles", cameraptr, assetManager);
	//tile.addComponent<TileComponent>(xPos, yPos, srcX, srcY, currentTileWidth, currentTileHeight, 1, "MapTiles", cameraptr, assetManager);
	tile.addToGroup(TILE_GROUP);
	return &tile;
}


void Map::addCollisionToTile(int x, int y)
{
	tileAt(x, y).addComponent<AABBCollisionComponent>("Terrain", true);
	tileAt(x, y).addToGroup(DEBUG_MAP_COLLISION_GROUP);
}

//Allows access to tile at location on map
Entity& Map::tileAt(int x, int y)
{
	return *mapTiles[x + 32 * y];
}