#include "GameTemplate.hpp"


void GameTemplate::set_ptr(GameEngine * engine, Mouse * mouse1, Keyboard * key, Storage * str, Camera * cam)
{
	game_engine = engine;
	mouse = mouse1;
	keyboard = key;
	storage = str;
	camera = cam;
}
