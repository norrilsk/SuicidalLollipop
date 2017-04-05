#include <iostream>

#include "GLfunc.hpp"
#include "Game.hpp"
#include "Loger.hpp"
using namespace std;
Game game;
Loger logfile;

void DealWithError(Error err)
{
	if((err.getType() != NONE) && (err.getType() != QUIT))
		cerr << err.getMessage()<< endl;
    if(err.getType() != LOGFILE)
        logfile << err.getMessage() << endl;
}

int main(int argc, char **argv)
{
	try
	{
		logfile.open("Log/GameLog.txt");
		Gl :: init(&argc, argv);
		game.start();
		Gl :: MainLoop(); //запускаем главный цикл
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
