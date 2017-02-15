#include <iostream>
#include "GLheader.hpp"
using namespace std;

void Gl :: init(int *argc, char **argv)
{
	glutInit(argc, argv); //начальная инициализация glut
	WinW = glutGet(GLUT_SCREEN_WIDTH); //получаем размеры экрана
	WinH = glutGet(GLUT_SCREEN_HEIGHT);
	if((!WinW) || (!WinH))
	{
		WinW = 	1280; //если не удалось ставим HD
		WinH = 720;
	}
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE| GLUT_DEPTH |GLUT_ALPHA); //добавляем в наше окно режим RGBA, 2 бувера (отрисовки) (нужны когда есть анимация), буфер глубеныб альфа-канал
	glutInitWindowSize(WinW, WinH); //задаем начальные размеры окна
}

void Gl :: start()
{
	glutCreateWindow("Window"); //открываем окно которое зовут Window
	glutFullScreen(); //переключаем в Full Screen
	glClearColor(0.0, 0.0, 1.0, 1.0);//цвет по дефолту
	glEnable(GL_DEPTH_TEST); //разрешаем тест глубины
	glutSetCursor(GLUT_CURSOR_NONE); //прячем курсор
	glutDisplayFunc(Gl :: display); //Говорим какая ф-я у нас будет отвечать за отрисовку 
	glutMainLoop(); //запускаем главный цикл
}

void Gl :: display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //очищаем экран и буфер глубины
	glutSwapBuffers(); // меняем буферы (наш ушел на видеокарту а к нам вернулся другой)
}

int main(int argc, char **argv)
{
	Gl :: init(&argc, argv);
	Gl :: start();
	return 0;
}
