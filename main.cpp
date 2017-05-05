#include <iostream>

#include "GameEngine.hpp"
#include "Game.hpp"

using namespace std;


int main(int argc, char **argv)
{
	GameEngine env(argc, argv); //создаем движек
	Game game; //создаем нашу игру
	env.start(&game); //запускаем игру на движке
	return 0;
}
