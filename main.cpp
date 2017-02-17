#include <iostream>
#include "GLheader.hpp"
#include "Error.hpp"
using namespace std;

Error :: Error(ErrorType error)
{
	type = error;
}

Error :: Error()
{
	type = NONE;
}

void Gl :: init(int *argc, char **argv)
{
	SDL_DisplayMode DisMode; //параметры экрана
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)//начальная инициализация SDL
	{
		throw(Error(SDL));
	}
	SDL_GetDesktopDisplayMode(0 , &DisMode); //получаем парраметры экрана
	WinW = DisMode.w; //получаем размеры экрана
	WinH = DisMode.h;
	if((!WinW) || (!WinH))
	{
		WinW = 	1280; //если не удалось ставим HD
		WinH = 720;
	}
	if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0) //создали двойноой буфер
		throw(Error(SDL));
	if(SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) < 0) //ставим глубину цвета
		throw(Error(SDL));
	if(SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) < 0) //ставим глубину цвета
		throw(Error(SDL));
	if(SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) < 0) //ставим глубину цвета
		throw(Error(SDL));
	atexit(SDL_Quit);
}

void Gl :: start()
{
	window = SDL_CreateWindow("SuicidalLollipop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WinW, WinH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);//создание окна
	if(window == NULL)
		throw(Error(SDL));
	if(SDL_GL_CreateContext(window) == NULL) //Создали котекст OpenGl 
		throw(Error(SDL));
	glClearColor(0.0, 0.0, 1.0, 1.0);//цвет по дефолту
	glClearDepth(1.0); //глубина по дефолту
	glDepthFunc(GL_LESS); //функция для определения глубу
	glEnable(GL_DEPTH_TEST); //разрешаем тест глубины
	glMatrixMode(GL_PROJECTION); //указывает что мы быдем работь с матрицей проекций
		glLoadIdentity(); //Использует указанную матрицу
		gluPerspective(70.0 * WinH / WinW, WinW / WinH, 0.1, 1000.0); // угол обзора по y, x/y, плижайшая и дальняя плоскости отсечения
	glMatrixMode(GL_MODELVIEW); // переходим в режим работы с 3d
	SDL_ShowCursor(SDL_DISABLE); //отключаем курсор
	if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0) // True Full screen
		throw(Error(SDL));
	MainLoop(); //запускаем главный цикл
}

void Gl :: MainLoop()
{
	while(true)
	{
		display();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				Quit();
				break;
			case SDL_KEYDOWN:
				keydown(event.key.keysym.scancode);
				break;
			default:
				break;
			}
		}
	}
}

void Gl :: Quit()
{
	SDL_Quit();
	throw(Error(QUIT));
}

void Gl :: keydown(SDL_Scancode code)
{
	switch(code)
	{
	case SDL_SCANCODE_ESCAPE:
		Quit();
		break;
	default:
		break;
	}
}

void Gl :: display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //очищаем экран и буфер глубины
	glFlush(); //Отрисовываем
	SDL_GL_SwapWindow(window);
}

void DealWithErrror(Error err)
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
		DealWithErrror(err);
	}
	return 0;
}
