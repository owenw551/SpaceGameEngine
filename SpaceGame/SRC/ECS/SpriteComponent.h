#pragma once

#include "SDL.h"
#include "Components.h"
#include "..\TextureManager.h"
#include "..\Camera.h"
#include "..\AssetManager.h"
#include <string>
#include <cassert>
#include <iostream>

/*
*	Component to manage what to draw on screen and where to draw it
*
*
*
*   AssetManager& assetManager;  access pointers to textures / load textures
*	TransformComponent *transform; access position and dimension
*	SDL_Texture *texture;	texture from asset manager
*	SDL_Rect srcRect;
*	SDL_Rect destRect;
*	Camera* camera;
*	std::string id;
*	SDL_Point midPoint;
*	bool eXRender;
*	bool originIsCenter;
*	SDL_RendererFlip flip = SDL_FLIP_NONE;
*/

class SpriteComponent : public Component
{
private:
	AssetManager& assetManager;
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	Camera* camera;
	std::string id;
	SDL_Point midPoint;
	bool eXRender;
	bool originIsCenter;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

public:

	SpriteComponent(int srcX, int srcY, int srcW, int srcH, bool EXRender, std::string texid, Camera* cameraptr, AssetManager& assetManagerRef) 
		: assetManager(assetManagerRef), camera(cameraptr), id(texid), eXRender(EXRender)
	{
		srcRect.x = srcX;
		srcRect.y = srcY;
		setTex(texid);
	}

	~SpriteComponent()
	{}

	void init() override
	{
		if(!owner->hasComponent<TransformComponent>())
		{
			owner->addComponent<TransformComponent>();
		}

		transform = &owner->getComponent<TransformComponent>();
		originIsCenter = transform->isCenteredOnOrigin();
		srcRect.w = transform->getw();
		srcRect.h = transform->geth();
		destRect.w = srcRect.w;
		destRect.h = srcRect.h;
	}

	void setRenderSize(int newW, int newH, int newS)
	{
		destRect.w = newW;
		destRect.h = newH;
	}

	void updateRenderSizeFromTransform()
	{
		destRect.w = int(transform->getw()*transform->gets());
		destRect.h = int(transform->geth()*transform->gets());
	}

	void update() override
	{
		if (!originIsCenter)
		{
			destRect.x = static_cast<int>(transform->getx() - (transform->getw() / 2)) - camera->cameraRect.x;
			destRect.y = static_cast<int>(transform->gety() - (transform->geth() / 2)) - camera->cameraRect.y;
		}
		else
		{
			destRect.x = static_cast<int>(transform->getx()) - camera->cameraRect.x;
			destRect.y = static_cast<int>(transform->gety()) - camera->cameraRect.y;
		}
	}
	 
	void draw() override
	{
		if (!eXRender)
		{
			TextureManager::Draw(texture, srcRect, destRect);
		}
		else
		{
			midPoint.x = destRect.x / 2;
			midPoint.y = destRect.y / 2;
			TextureManager::Draw(texture, srcRect, destRect, transform->getangle(), midPoint, flip);
		}
	}
	 
	void setTex(std::string id)
	{
		texture = assetManager.GetTexture(id);
	}


};