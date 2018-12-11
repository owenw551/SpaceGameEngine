//#pragma once
//
//#include "SDL.h"
//#include "Components.h"
//#include <iostream>
//#include "..\AssetManager.h"
//
//
//
//  ******************
//  *NO LONGER IN USE*
//  ******************
//	Used to manage adding tiles into the game
//
//class TileComponent : public Component
//{
//private:
//
//	AssetManager& assetManager;
//	SDL_Texture *texture;
//	SDL_Rect srcRect;
//	SDL_Rect destRect;
//	Vector2D position;
//	Camera* camera;
//	std::string id;
//
//public:
//
//	TileComponent(int xPos, int yPos, int srcX, int srcY, int width, int height, int s, std::string newid, Camera* camerap, AssetManager& assetManagerRef)
//		: assetManager(assetManagerRef)
//	{
//		position.setx((float)xPos);
//		position.sety((float)yPos);
//
//		destRect.x = xPos;
//		destRect.y = yPos;
//
//		srcRect.x = srcX;
//		srcRect.y = srcY;
//
//		destRect.w = srcRect.w = width * s;
//		destRect.h = srcRect.h = height * s;
//
//		id = newid;
//		camera = camerap;
//		texture = assetManager.GetTexture(id);
//	}
//
//	~TileComponent()
//	{
//		SDL_DestroyTexture(texture);
//	}
//
//	void update() override
//	{
//		destRect.x = static_cast<int>(position.getx()) - camera->cameraRect.x;
//		destRect.y = static_cast<int>(position.gety()) - camera->cameraRect.y;
//	}
//
//	void draw() override
//	{
//		TextureManager::Draw(texture, srcRect, destRect);
//	}
//
//};
