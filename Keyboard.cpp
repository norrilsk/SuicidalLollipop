#include "Keyboard.hpp"

Keyboard :: Keyboard()
{
}
void Keyboard :: update()
{
	SDL_PumpEvents();
	keyarray = SDL_GetKeyboardState(NULL);
}

bool Keyboard :: operator [] (SDL_Scancode sim)
{
	return (keyarray)? keyarray[sim]: false;
}

Keyboard :: ~Keyboard()
{
}
