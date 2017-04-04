//#include "GLfunc.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "Loger.hpp"
#include "GarbageCollector.hpp"

using namespace std;

Loger logfile;
GarbageCollector finish;

struct SDLWindow
{
	SDL_Window *window;
	int h = 480;
	int w = 640;
}window;

SDL_Renderer* renderer;

void DealWithError(Error err)
{
	if((err.getType() != NONE) && (err.getType() != QUIT))
		cerr << err.getMessage()<< endl;
	if(err.getType() != LOGFILE)
		logfile << err.getMessage() << endl;
}

void SDL_init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw(newError(SDL));
	finish.add(SDL_QUIT);
	window.window = SDL_CreateWindow("Utility", 100, 100, window.w, window.h, SDL_WINDOW_SHOWN);
	if(window.window == nullptr)
		throw(newError(SDL));
	finish.add(SDL_DestroyWindow, window.window);
	renderer =  SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr)
		throw(newError(SDL));
	finish.add(SDL_DestroyRenderer, renderer);
}


int main()
{
	try
	{
		logfile.open("Log/UtilityLog.txt");
		SDL_init();
	}
	catch (Error err)
	{
		DealWithError(err);
	}
	catch (...)
	{
		DealWithError(newError(OTHER));
	}
	return 0;
}