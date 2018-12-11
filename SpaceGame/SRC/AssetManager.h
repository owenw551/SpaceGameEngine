#pragma once
#include <map>
#include <string>
#include "ECS/EntityComponentManager.h"
#include "SDL.h"

//class for loading in textures
// will also (soon) be responsible for loading in entities
//	Manager& man;										to be able to add entities
//	std::map<std::string, SDL_Texture*> textureMap;     to hold one copy of a rquired texture for entities to share


class AssetManager
{
private: 
	Manager& man;
	std::map<std::string, SDL_Texture*> textureMap;

public:
	AssetManager(Manager& manref);
	AssetManager();

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
};