#include "AssetManager.h"
#include "TextureManager.h"

AssetManager::AssetManager(Manager& manref) : man(manref)
{}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textureMap.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textureMap[id];
}