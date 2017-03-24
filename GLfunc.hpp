#ifndef _GLheader
	#define _GLheader
	#ifdef _WIN32
	#include <Windows.h>
	#endif
	#ifndef _GLEWINCLUDE
	#define _GLEWINCLUDE
	#include <GL/glew.h>
	#include <GL/glu.h>
	#endif 
	#include <SDL2/SDL.h>
	#include <stdlib.h>
	#include <utility>
	#include <queue>
	#include <glm/glm.hpp>
	#include <iostream> //В целях дебага TODO delete in release
	#include "Error.hpp"
	#include "Camera.hpp"
	#include "Mouse.hpp"
	#include "Keyboard.hpp"
	#include "Shaders.hpp"
	namespace Gl
	{
		extern double WinW; //Ширина окна. Здесь мы говорим что только собираемся обЪявить эти переменные
		extern double WinH; //Высота окна
		extern SDL_Window *window;
		extern Camera camera; // Наша камера
		extern Mouse mouse;
		extern Keyboard keyboard;
		extern double FPS;
		extern std::queue <DrawableObject*> renderingQueue;// очередь отрисовки
		extern Shaders shaders;
		void init(int *argc, char **argv); //Инициализация всего что нужно для старта 
		void MainLoop(); //Главный цикл
		void start(); //собственно запуск окна 
		void display(); //фуннкция - отрисовщик окна
		void reshape(); //функция срабатывающая при изменении размера окна
		void Quit(); //закрыть и выйти
	}
#endif
