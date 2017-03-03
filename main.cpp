#include <iostream>

#include "GLfunc.hpp"
using namespace std;

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
	}
	catch (Error err)
	{
		DealWithError(err);
	}
	return 0;
}
