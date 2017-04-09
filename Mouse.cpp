#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>
#include "Mouse.hpp"
#include "Error.hpp"

Mouse::Mouse(SDL_Window * win)
{
	window = win;
	if(!window)
		return;
	SDL_GetWindowSize(window, &X, &Y);
	X /= 2;
	Y /= 2;
	sensity = 5;
	SDL_WarpMouseInWindow(window, X , Y); // устанавливает позицию курсора(X, Y);
}

void Mouse :: centre() 
{
	SDL_GetWindowSize(window, &X, &Y);
	X /= 2;
	Y /= 2;
	SDL_WarpMouseInWindow(window, X , Y);
}

std :: pair <int, int>  Mouse :: getPosition()
{
	SDL_PumpEvents();
	SDL_GetMouseState(&X, &Y);
	return std :: make_pair(X, Y);
}

glm :: dvec2  Mouse :: getMovement() 
{
	SDL_PumpEvents();
	int x = X, y = Y;
	SDL_GetMouseState(&X, &Y);
	return glm :: dvec2(X - x, Y - y)/sensity;
}
void Mouse::ChangeSensity(double sense)
{
	if(sense > 0)
		sensity = sense;
	return;
}

Mouse::~Mouse()
{
}
