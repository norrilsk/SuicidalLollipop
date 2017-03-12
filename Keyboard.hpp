#ifndef _KEYBOARD
#define _KEYBOARD
#include <SDL2/SDL.h>
#include <string>

class Keyboard
{
	const Uint8* keyarray = NULL;
public:
	Keyboard();
	void update();
	bool operator [] (SDL_Scancode);
	~Keyboard();
};
#endif
