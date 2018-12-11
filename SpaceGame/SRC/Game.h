#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "SceneManager.h"

//Class to hold data about the game, the renderer and window.
//Also holds the scenemanager which is where the bulk of 

class Game
{
private:
	bool isRunning;
	SDL_Window *window;
	int frameCount = 0;
	int screenWidth = 800;
	int screenHeight = 640;

public:
	SceneManager scemanager;
	static SDL_Renderer *renderer;
	static SDL_Event event;
	//static SDL_Rect camera;


	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void update() { scemanager.update(); }
	void render() { scemanager.render(); }
	void clean(); //memory management, cleans game objects when finished
	void handleEvents();
	bool running() { return isRunning; }

};

