#include <iostream>
#include "GraphicEngine.hpp"
#include"Objects/Room.hpp"

GraphicEngine::GraphicEngine(int w, int h, bool OpenGl, Loger *logfile, Camera *camera): cam(camera), GlMode(OpenGl)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)//начальная инициализация SDL
	{
		throw(newError(SDL));
	}

	SDL_inited = true;
	SDL_DisplayMode DisMode; //параметры экрана
	SDL_GetDesktopDisplayMode(0 , &DisMode); //получаем парраметры экрана
	WinW = w, WinH = h;
	if(w <= 0 || h <= 0)
		WinW = WinH = INT_MAX;
	WinW = std::min(DisMode.w, WinW); //получаем размеры экрана
	WinH = std::min(DisMode.h, WinH);
	if((WinW <= 0) || (WinH <= 0))
	{
		WinW = 	1280; //если не удалось ставим HD
		WinH = 720;
	}
	int flags = IMG_INIT_JPG | IMG_INIT_PNG; // флаги sdl_image
	int initted = IMG_Init(flags); // инициализация sdl_image
	if ((initted & flags) != flags)
		throw (newError2(OTHER, "IMG_Init: Failed to init required jpg and png support!\n" + std::string("IMG_Init: ") + IMG_GetError() + std::string("\n")));
	SDLimage_inited = true;
	window = SDL_CreateWindow("SuicidalLollipop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)WinW, (int)WinH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);//создание окна
	if(w * h <= 0)
	{
		if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0) // True Full screen
			throw(newError(SDL));
	}
	if(window == NULL)
		throw(newError(SDL));
	//if(OpenGl)
	{
		if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0) //создали двойноой буфер
			throw(newError(SDL));
		if(SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) < 0) //ставим глубину цвета
			throw(newError(SDL));
		if(SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) < 0) //ставим глубину цвета
			throw(newError(SDL));
		if(SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) < 0) //ставим глубину цвета
			throw(newError(SDL));
		if(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16) < 0)//ставим размер буфера глубины
			throw(newError(SDL));
		if (SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) < 0)
			throw(newError(SDL));
		if (SDL_GL_CreateContext(window) == NULL) //Создали котекст OpenGl
			throw (newError(SDL));
		glClearColor(0.0f, 0.0f, 0.9f, 1.0f);//цвет по дефолту
		glClearDepth(1.0); //глубина по дефолту
		glClearStencil(0);//буфер граней по дефолту
		glDepthFunc(GL_LESS); //функция для определения глубу
		//glEnable(GL_CULL_FACE); //отключение не лицевых граней
		glEnable(GL_DEPTH_TEST); //разрешаем тест глубины
		glEnable(GL_TEXTURE_2D);// включаем 2D текстуры
		SDL_ShowCursor(SDL_DISABLE); //отключаем курсор
		glEnable(GL_MULTISAMPLE); //Включили мультисемплинг для лучшего сглаживания (правда ценой большей нагрузки на GPU)
		if(glewInit() != GLEW_OK)// инициализацию Glew , очень важно
			throw(newError(GL));
		check_GL_version(logfile);//проверяем что у нас стоит нужная версия OpenGL
		std::vector<std::pair<std::string, GLuint> > ShadersPaths;
		ShadersPaths.push_back(std::make_pair("Shaders/fragmentshader.glsl", GL_FRAGMENT_SHADER));//файл фрагментного шейдера
		ShadersPaths.push_back(std::make_pair("Shaders/vertexshader.glsl", GL_VERTEX_SHADER));//файл вершинного шейдера
		shaders = Shaders(ShadersPaths);//Подключаем шейдеры
	}

}

GraphicEngine::~GraphicEngine()
{
	if(SDL_inited)
		SDL_Quit();
	if(SDLimage_inited)
		IMG_Quit();
	if(window != nullptr)
		SDL_DestroyWindow(window);
}

void GraphicEngine::check_GL_version(Loger *logfile)
{
	if(logfile)
	{
		*logfile << "Software checking:" << std::endl;
		*logfile << "\tOpenGL version and drivers:\t\t" << glGetString(GL_VERSION) << std::endl;
		*logfile << "\tName of the GPU: \t\t\t" << glGetString(GL_RENDERER) << std::endl;
		*logfile << "\tShading language version and drivers:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION)
		         << std::endl;
	}
	if(!GLEW_VERSION_3_3)
		throw(newError2(OTHER, "Your OpenGl version is out of date. Version 3.3 or higher is required"));
}

void GraphicEngine::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT); //очищаем экран и буфер глубины
	if(GlMode)
	{
		cam->Look();
		glm::mat4 VP = cam->Projection() * cam->View();
		while (!renderingQueueGl.empty())
		{
			Object3D *obj = renderingQueueGl.front();
			if (obj->is_drawable())
			{
				glm::mat4 MVP = VP * obj->ModelMat(); // Возвращает матрицу модели;
				shaders.useProgram();
				shaders.store_MVP(&MVP[0][0]);
				shaders.store_int(obj->has_textures(), TEXTURES_ENABLED);
				shaders.store_int(0, TEXTURE_SAMPLER);
				obj->draw();
			}
			renderingQueueGl.pop();
		}
		SDL_GL_SwapWindow(window);
	}
}

void GraphicEngine::addToRender(Object3D * obj)
{
	renderingQueueGl.push(obj);
}

void GraphicEngine::addToRender(Object2D * obj)
{
	renderingQueueSDL.push(obj);
}

void GraphicEngine::portalRendering(Storage * storage)
{
	std::vector <Object3D *> vec;
	Room &room = storage->room(cam->getRoom());
	room.getAllObjects(vec);
	for (Object3D *obj : vec)
	{
		addToRender(obj);
	}
	addToRender(&room);
}
