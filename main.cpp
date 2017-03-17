#include <iostream>

#include "GLfunc.hpp"
#include "Game.hpp"
using namespace std;
Game game;

void DealWithError(Error err)
{
	switch (err.getType())
	{
	case SDL:
		cout << SDL_GetError() << endl; //Выводим сообщение об ошибке
		break;
	case QUIT:
		cout <<"Sucsessful finish"<<endl;
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	try
	{
		Gl :: init(&argc, argv);
		Gl :: start();
		game.start();
		Gl :: MainLoop(); //запускаем главный цикл
	}
	catch (Error err)
	{
		DealWithError(err);
	}
	return 0;
}
