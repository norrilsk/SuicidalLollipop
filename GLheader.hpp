#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/freeglut.h>
#include <SDL2/SDL.h>

#ifndef _GLheader
	#define _GLheader
	namespace Gl
	{
		double WinW; //Ширина окна
		double WinH; //Высота окна
		SDL_Window *window; 
		void init(int *argc, char **argv); //Инициализация всего что нужно для старта glut
		void MainLoop(); //Главный цикл
		void start(); //собственно запуск окна 
		void keydown(SDL_Scancode code);//обработка нажатия кнопки
		void display(); //фуннкция - отрисовщик окна
		void reshape(); //функция срабатывающая при изменении размера окна
	}
#endif
