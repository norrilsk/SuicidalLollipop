#include "GLfunc.hpp"
#include "Game.hpp"
double Gl :: WinW = 640; //Собственно объявляем переменные
double Gl :: WinH = 480;
SDL_Window* Gl :: window; 
Camera Gl :: camera = Camera(); // инициализация камеры
Mouse Gl :: mouse = Mouse();
Keyboard Gl :: keyboard = Keyboard();
double Gl :: FPS = 60;
std::queue <DrawableObject*> Gl::renderingQueue;
Shaders Gl::shaders;
glm::mat4 Gl::Projection;
extern Game game;
glm::mat4 Gl::View;


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
	if(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16) < 0)//ставим размер буфера глубины
		throw(Error(SDL));
	atexit(SDL_Quit);
}

void Gl :: start()
{
	window = SDL_CreateWindow("SuicidalLollipop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)WinW, (int)WinH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);//создание окна
	if(window == NULL)
		throw(Error(SDL));
	if(SDL_GL_CreateContext(window) == NULL) //Создали котекст OpenGl 
		throw(Error(SDL));
	glClearColor(0.0f, 0.0f, 0.9f, 1.0f);//цвет по дефолту
	glClearDepth(1.0); //глубина по дефолту
	glDepthFunc(GL_LESS); //функция для определения глубу
	//glEnable(GL_CULL_FACE); //отключение не лицевых граней
	glEnable(GL_DEPTH_TEST); //разрешаем тест глубины
	SDL_ShowCursor(SDL_DISABLE); //отключаем курсор
	if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0) // True Full screen
		throw(Error(SDL));
	Projection = glm::perspective(1.2217f,float(WinW / WinH), 1.0f, 3000.0f);//70 градусов FOV
	glewInit();// инициализацию Glew , очень важно
	std::vector<std::pair<std::string, GLuint> > ShadersPaths;
	ShadersPaths.push_back(std::make_pair("Shaders/fragmentshader.glsl", GL_FRAGMENT_SHADER));
	ShadersPaths.push_back(std::make_pair("Shaders/vertexshader.glsl", GL_VERTEX_SHADER));
	shaders = Shaders(ShadersPaths);
}

void Gl :: MainLoop()
{
	unsigned int time_per_cycle = 0;
	while(true)
	{
		unsigned int time_start = SDL_GetTicks(); //текущее время SDL в милисекундах
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				Quit();
				break;
			case SDL_WINDOWEVENT:
 				switch(event.window.event)
 				{
 				case SDL_WINDOWEVENT_FOCUS_GAINED:
 					mouse.centre();
					game.goon();
 					break;
 				case SDL_WINDOWEVENT_FOCUS_LOST:
 					mouse.centre();
 					game.pause();
 					break;
 				default:
 					break;
 				}
 				break;
			default:
				break;
			}
		}
		game.next(time_per_cycle);
		game.setCamera();
		display();
		time_per_cycle = (SDL_GetTicks() - time_start);
		if (time_per_cycle < 17)
			SDL_Delay(17 - time_per_cycle);
		time_per_cycle = (SDL_GetTicks() - time_start);
		FPS = 1000.0 / (time_per_cycle);
	}
}

void Gl :: Quit()
{
	throw(Error(QUIT));
}

void Gl :: display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //очищаем экран и буфер глубины
	glLoadIdentity();
	camera.Look();
	while (!renderingQueue.empty())
	{
		renderingQueue.front()->draw();
		renderingQueue.pop();
	} 
	glFlush(); //Отрисовываем
	SDL_GL_SwapWindow(window);
}

