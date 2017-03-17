#include "GLfunc.hpp"
#include "Game.hpp"
double Gl :: WinW = 640; //Собственно объявляем переменные
double Gl :: WinH = 480;
SDL_Window* Gl :: window; 
float Gl :: a, Gl :: b,  Gl ::c;
Camera Gl :: camera = Camera(); // инициализация камеры
Mouse Gl :: mouse = Mouse();
Keyboard Gl :: keyboard = Keyboard();
double Gl :: FPS = 60;
extern Game game;

void Gl::drawCube(float xrf, float yrf, float zrf){
	glTranslatef(0.0f, 0.0f, -7.0f);	// Сдвинуть вглубь экрана

	glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z

	glBegin(GL_QUADS);		// Рисуем куб

	glColor3f(0.0f, 1.0f, 0.0f);		// Синяя сторона (Верхняя)
	glVertex3f( 1.0f, 1.0f, -1.0f);		// Верхний правый угол квадрата
	glVertex3f(-1.0f, 1.0f, -1.0f);		// Верхний левый
	glVertex3f(-1.0f, 1.0f,  1.0f);		// Нижний левый
	glVertex3f( 1.0f, 1.0f,  1.0f);		// Нижний правый

	glColor3f(1.0f, 0.5f, 0.0f);		// Оранжевая сторона (Нижняя)
	glVertex3f( 1.0f, -1.0f,  1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f,  1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

	glColor3f(1.0f, 0.0f, 0.0f);		// Красная сторона (Передняя)
	glVertex3f( 1.0f,  1.0f, 1.0f);		// Верхний правый угол квадрата
	glVertex3f(-1.0f,  1.0f, 1.0f);		// Верхний левый
	glVertex3f(-1.0f, -1.0f, 1.0f);		// Нижний левый
	glVertex3f( 1.0f, -1.0f, 1.0f);		// Нижний правый

	glColor3f(1.0f,1.0f,0.0f);			// Желтая сторона (Задняя)
	glVertex3f( 1.0f, -1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f,  1.0f, -1.0f);	// Нижний левый
	glVertex3f( 1.0f,  1.0f, -1.0f);	// Нижний правый

	glColor3f(0.0f,0.0f,1.0f);			// Синяя сторона (Левая)
	glVertex3f(-1.0f,  1.0f,  1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f,  1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f(-1.0f, -1.0f,  1.0f);	// Нижний правый

	glColor3f(1.0f,0.0f,1.0f);			// Фиолетовая сторона (Правая)
	glVertex3f( 1.0f,  1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f( 1.0f,  1.0f,  1.0f);	// Верхний левый
	glVertex3f( 1.0f, -1.0f,  1.0f);	// Нижний левый
	glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

	glEnd();	// Закончили квадраты

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
	glEnable(GL_DEPTH_TEST); //разрешаем тест глубины
	glShadeModel(GL_SMOOTH); //Cглаживание 
	glMatrixMode(GL_PROJECTION); //указывает что мы быдем работь с матрицей проекций
		glLoadIdentity(); //Использует указанную матрицу
		gluPerspective(70.0 * WinH / WinW, WinW / WinH, 0.01, 2000.0); // угол обзора по y, x/y, плижайшая и дальняя плоскости отсечения
	glMatrixMode(GL_MODELVIEW); // переходим в режим работы с 3d
	SDL_ShowCursor(SDL_DISABLE); //отключаем курсор
	if(SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0) // True Full screen
		throw(Error(SDL));
	MainLoop(); //запускаем главный цикл
}

void Gl :: MainLoop()
{
	unsigned int time_per_cycle = 0;
	while(true)
	{
		//a += 1.0;
		//b += 1.0;
		//c += 1.5;
		unsigned int time_start = SDL_GetTicks(); //текущее время SDL в милисекундах
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				Quit();
				break;
			default:
				break;
			}
		}
		game.next(time_per_cycle);
		game.setCamera();
		display();
		time_per_cycle = (SDL_GetTicks() - time_start);
		
		// :: cout << FPS << std :: endl;
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
	drawCube(a, b, c);
	glFlush(); //Отрисовываем
	SDL_GL_SwapWindow(window);
}
