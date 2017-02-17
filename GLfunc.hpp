#ifndef _GLheader
	#define _GLheader
	#ifdef _WIN32
	#include <Windows.h>
	#endif
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <SDL2/SDL.h>

	namespace Gl
	{
		extern double WinW; //Ширина окна. Здесь мы говорим что только собираемся обЪявить эти переменные
		extern double WinH; //Высота окна
		extern SDL_Window *window; 
		void init(int *argc, char **argv); //Инициализация всего что нужно для старта glut
		void MainLoop(); //Главный цикл
		void start(); //собственно запуск окна 
		void keydown(SDL_Scancode code);//обработка нажатия кнопки
		void display(); //фуннкция - отрисовщик окна
		void reshape(); //функция срабатывающая при изменении размера окна
		void Quit(); //закрыть и выйти
	}
#endif
