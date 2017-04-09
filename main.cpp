#include <iostream>

#include "Game.hpp"
#include "GameEngine.hpp"

using namespace std;


int main(int argc, char **argv)
{
	GameEngine env(argc, argv); //создаем движек
	Game game; //создаем нашу игру
	env.start(&game); //запускаем игру на движке
	return 0;
}
