#include <GL/gl.h>
#include <GL/freeglut.h>

#ifndef _GLheader
	#define _GLheader
	namespace Gl
	{
		double WinW; //Ширина окна
		double WinH; //Высота окна
		void init(int *argc, char **argv); //Инициализация всего что нужно для старта glut
		void start(); //собственно запуск окна glut
		void display(); //фуннкция - отрисовщик окна
		void reshape(); //функция срабатывающая при изменении размера окна
	}
#endif
