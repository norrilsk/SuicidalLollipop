#include <iostream>
#include <SDL2/SDL.h>
#include <unordered_map>
#define UTILITY

#include "Loger.hpp"
#include "Storage.hpp"
#include "SDLTexture.hpp"
#include "Objects/Objects.hpp"

using namespace std;

Loger logfile;

Storage storage;

struct SDLWindow
{
	SDL_Window *window;
	int h = 480;
	int w = 640;
	unordered_map <string, StorageIndex> textures;
	SDL_Renderer* renderer;
	void init();
	void draw();
}window;

void SDLWindow::init()
{
	textures["cat"] = storage.addSDLTexture(renderer, "Source/Textures/cat.jpg");
}

void SDLWindow::draw()
{
	(storage.sdlTexture(textures["cat"])).draw(0,0);
	SDL_RenderPresent(renderer);
}


void finish()
{
	SDL_DestroyWindow(window.window);
	SDL_DestroyRenderer(window.renderer);
}

void DealWithError(Error err)
{
	if((err.getType() != NONE) && (err.getType() != QUIT))
		cerr << err.getMessage()  << endl;
	if(err.getType() != LOGFILE)
		logfile << err.getMessage() << endl;
}

void SDL_init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw(newError(SDL));
	atexit(SDL_Quit);
	window.window = SDL_CreateWindow("Utility", 100, 100, window.w, window.h, SDL_WINDOW_SHOWN);
	if(window.window == nullptr)
		throw (newError(SDL));
	window.renderer =  SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(window.renderer == nullptr)
	{
		SDL_DestroyWindow(window.window);
		throw (newError(SDL));
	}
	atexit(finish);
}


void MainLoop()
{
	while(true)
	{
		window.draw();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					throw(newError(QUIT));
				default:
					break;
			}
		}
	}
}


int main()
{
	try
	{
		logfile.open("Log/UtilityLog.txt");
		SDL_init();
		window.init();
		MainLoop();
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