#ifndef _ENGINE
#define _ENGINE

#include <iostream>
#include <SDL2/SDL.h>
#include <queue>
#include "Objects/Object2D.hpp"
#include "Camera.hpp"
#include "Storage.hpp"
#include "Shaders.hpp"
#include "Loger.hpp"

class GraphicEngine
{
	int WinW; //Ширина окна. Здесь мы говорим что только собираемся обЪявить эти переменные
	int WinH; //Высота окна
	SDL_Window *window = nullptr;
	bool SDL_inited = false;
	bool SDLimage_inited = false;
	bool GlMode = false;
	std::queue <Object3D*> renderingQueueGl;// очередь отрисовки Gl
	std::queue <Object2D*> renderingQueueSDL;// очередь отрисовки SDL
	Shaders shaders;
	void check_GL_version(Loger * logfile);
	Camera * cam;
public:
	GraphicEngine(int w, int h, bool OpenGl, Loger *logfile, Camera *camera);//передаем камеру, параметры окна (если 0 - Fullscrean)
	void portalRendering(Storage * storage); //общет сцены методом портального рендеринга
	void addToRender(Object3D *); //добавляем объекты в очередь отрисовки
	void addToRender(Object2D *);
	void display(); //запускаем отрисовку
	SDL_Window * getWindow(){return window;}
	~GraphicEngine();

};


#endif
