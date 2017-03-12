#ifndef _GLheader
	#define _GLheader
	#ifdef _WIN32
	#include <Windows.h>
	#endif
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <SDL2/SDL.h>
	#include <stdlib.h>
	#include <utility>
	#include <glm/glm.hpp>
	#include <iostream> //В целях дебага TODO delete in release
	#include "Error.hpp"
	#include "Camera.hpp"
	#include "Mouse.hpp"
	#include "Keyboard.hpp"
	namespace Gl
	{
		extern double WinW; //Ширина окна. Здесь мы говорим что только собираемся обЪявить эти переменные
		extern double WinH; //Высота окна
		extern SDL_Window *window;
		extern Camera camera; // Наша камера
		extern Mouse mouse;
		extern Keyboard keyboard;
		extern double FPS;
		void init(int *argc, char **argv); //Инициализация всего что нужно для старта 
		void MainLoop(); //Главный цикл
		void start(); //собственно запуск окна 
		void display(); //фуннкция - отрисовщик окна
		void reshape(); //функция срабатывающая при изменении размера окна
		void Quit(); //закрыть и выйти
		//TODO delete
		void drawCube(float a, float b, float c);
		extern float a, b, c;
	}
#endif
