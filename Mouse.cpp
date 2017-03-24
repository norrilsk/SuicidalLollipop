#include "Mouse.hpp"
#include "GLfunc.hpp"

Mouse::Mouse()
{
	X = int(Gl :: WinW)/ 2;
	Y = int(Gl :: WinH)/ 2;
	sensity = 20;
	SDL_WarpMouseInWindow(Gl :: window, X , Y); // устанавливает позицию курсора(X, Y);
}

void Mouse :: centre() 
{ 
	X = int(Gl :: WinW)/ 2;
	Y = int(Gl :: WinH)/ 2;
	SDL_WarpMouseInWindow(Gl :: window, X , Y);
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
