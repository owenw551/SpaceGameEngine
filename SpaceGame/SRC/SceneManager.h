#pragma once

#include <vector>
#include <memory>
#include "ECS/EntityComponentManager.h"

class SceneManager;

class Scene
{
protected:
	Manager manager;
	SceneManager& sceneManager;
public:

	Scene(SceneManager& scemanref) : sceneManager(scemanref) {};

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void unload() = 0;
};

class SceneManager
{
private:
	std::vector<std::unique_ptr<Scene>> scenes;
	int screenWidth, screenHeight;
public:
	SceneManager() {}

	template <typename cT, typename... Args>
	Scene& loadScene(Args&&... mArgs)
	{
		Scene* s(new cT(std::forward<Args>(mArgs)...));
		std::unique_ptr<Scene> newScene{ s };
		scenes.emplace_back(std::move(newScene));
		return *s;
	}

	void unloadScene()
	{
		scenes.pop_back();
	}

	void update()
	{
		scenes.back()->update();
	}

	void render()
	{
		scenes.back()->render();
	}

	void setScreenWidth(int w) { screenWidth = w; }
	void setScreenHeight(int h) { screenHeight = h; }

	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }
};