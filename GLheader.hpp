#ifdef _WIN32
#include<windows.h>
#endif

#include<GL\gl.h> // Библиотека OpenGL
#include <GL\glu.h> // Библиотека GLU
#include <SDL2\SDL.h> // Библиотека SDL 2

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
	void Quit(); //закрыть и выйти
}
#endif