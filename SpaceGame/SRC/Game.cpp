#include "Game.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "Map.h"
#include "Vector2D.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Game::Game()
{
}

Game::~Game()
{
}

//Initialise SDL
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	screenWidth = width;
	screenHeight = height;
	scemanager.setScreenWidth(screenWidth);
	scemanager.setScreenHeight(screenHeight);

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Susbsytems Initialised" << std::endl;
		window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if (window)
		{
			std::cout << "Window Creation Successful" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer Creation Succesful" << std::endl;
		}
		Game::isRunning = true;
	}
	else
	{
		Game::isRunning = false;
	}
}

//called when exiting the game
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

//currently checks whether the quit button is pressed
void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		Game::isRunning = false;
		break;

	default:
		break;
	}
}