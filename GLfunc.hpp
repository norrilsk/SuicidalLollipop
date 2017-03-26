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
	#define GLM_FORCE_RADIANS //для ускорения все в радианах
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
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
		extern glm::mat4 Projection; // матрица перспективы
		extern glm::mat4 View; // матрица вида
		void init(int *argc, char **argv); //Инициализация всего что нужно для старта 
		void MainLoop(); //Главный цикл
		void display(); //фуннкция - отрисовщик окна
		void checkGLVersion();//узнаем версию OpenGL и GLSL
		void Quit(); //закрыть и выйти
	}
#endif
