#pragma once
#include "SDL.h"
#include <iostream>

//Essentially an SDL rect with added data, used to control what is drawn to the screen


struct Camera
{
	SDL_Rect cameraRect;
	int minX, minY;
	int maxX, maxY; // furthest the camera position can be without rendering off screen
	int midpointX, midpointY; //Midpoint of the screen
	bool mapSmallerThanScreen; //so that the camera can be centered on the map if the map is smaller than the screen
	
	void intitialiseCamera(int x, int y, int w, int h, int mapMaxX, int mapMaxY, int mapMinX = 0, int mapMinY = 0)
	{
		cameraRect.x = x;
		cameraRect.y = y;
		cameraRect.w = w;
		cameraRect.h = h;

		midpointX = w / 2;
		midpointY = h / 2; 

		maxX = mapMaxX - w;
		maxY = mapMaxY - h;

		minX = mapMinX;
		minY = mapMinY;

		std::cout << "mapMaxX " << mapMaxX << " MapMaxY  " << mapMaxX << "cameraRect.w  " << cameraRect.w << "  cameraRect.h  " << cameraRect.h <<std::endl;

		std::cout << (mapMaxX < cameraRect.w) << (mapMaxY < cameraRect.h) << std::endl;

		if (mapMaxX < cameraRect.w || mapMaxY < cameraRect.h)
		{ 
			mapSmallerThanScreen = true; 
		}
		else 
		{ 
			mapSmallerThanScreen = false; 
		}

		std::cout << mapSmallerThanScreen << "mapSmallerThanScreen" << std::endl;
	}
};