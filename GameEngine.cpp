#include <iostream>
#include "GameEngine.hpp"

GameEngine::~GameEngine()
{

}
void GameEngine::logTrouble(Error &err)
{
	if((err.getType() != NONE) && (err.getType() != QUIT))
		std::cerr << err.getMessage()  << std::endl;
	if(err.getType() != LOGFILE)
		logfile << err.getMessage() << std::endl;
}

GameEngine::GameEngine(int argc, char **argv)
{
	logfile.open("Log/GameLog.txt");
	try
	{
		camera = std::unique_ptr<Camera>(new Camera());
		grapher = std::unique_ptr<GraphicEngine>(new GraphicEngine(0, 0, true, &logfile, camera.get()));
		mouse = std::unique_ptr<Mouse>(new Mouse(grapher->getWindow()));
		keyboard = std::unique_ptr<Keyboard>(new Keyboard());
		storage = std::unique_ptr<Storage>(new Storage());
	}
	catch(Error e)
	{
		logTrouble(e);
	}

}

void GameEngine::start(GameTemplate * game)
{
	if (!game)
		throw (newError2(OTHER, "Game not stated"));
	this->game = game;
	game->set_ptr(this, mouse.get(), keyboard.get(), storage.get(), camera.get());
	game->start();
	try
	{
		MainLoop();
	}
	catch(Error e)
	{
		logTrouble(e);
	}
}

void GameEngine::MainLoop()
{
	unsigned int time = SDL_GetTicks();
	while(true)
	{
		game->next();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					Quit();
				case SDL_WINDOWEVENT:
					switch(event.window.event)
					{
						case SDL_WINDOWEVENT_FOCUS_LOST:
							game->focusLost();
							break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
							game->focusGained();
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
	}
}

void GameEngine::Quit()
{
	throw(newError(QUIT));
}

void GameEngine::renderScene(bool show)
{
	grapher -> portalRendering(storage.get());
	if(show)
		grapher ->display();
}

void GameEngine::display()
{
	grapher -> display();
}

