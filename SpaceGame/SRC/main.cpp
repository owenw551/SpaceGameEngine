#include "SDL.h"
#include "Game.h"
#include <iostream>
#include "GameplayScene.h"
#include <string>

int main(int argc, char *argv[])
{
	//Gameloop data, currently capped at 60fps. will alter to a more advanced game loop later
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	Game *game = nullptr;
	game = new Game();
	game->init("Hello", 500, 500, 800, 640, false);

	//we need to add an initial scene. once one scene is created we can control the scenes through entities.
	game->scemanager.loadScene<GameplayScene>("Assets/cavemap2.txt", "Assets/cavemap2textures.png", game->scemanager); 

	while (game->running())
	{

		frameStart = SDL_GetTicks(); //SDL_GetTicks() gives number of milliseconds since SDL initialised.

		game->handleEvents(); //get input
		game->update(); //update entities
		game->render(); //draw to screen

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{

			SDL_Delay(frameDelay - frameTime);

		}
	}
	game->clean();
	return 0;
}