#include "Mouse.hpp"
#include "GLfunc.hpp"

Mouse::Mouse(int x, int y, int Sens)
{
	X = x;
	Y = y;
	if ((x < 0) || (y < 0))
	{
		x = 320;
		y = 240;
	}
	
	SDL_WarpMouseInWindow(Gl :: window, x, y); // устанавливает позицию курсора
}
Mouse::Mouse()
{
	X = 320;
	Y = 240;
	Sensity = 20;
	SDL_WarpMouseInWindow(Gl :: window,320, 240); // устанавливает позицию курсора(X, Y);
}

void Mouse::MouseMotion(int x, int y)
{
	Gl::camera.RotaterRightLeft((X - x) / Sensity); // вращает камеру по Х
	Gl::camera.RotateHighDown((Y - y) / Sensity); // вращает камеру по У
	SDL_WarpMouseInWindow(Gl :: window,320, 240); // устанавливает позицию курсора(X, Y); // устанавливает позицию курсора
	return;
}
void Mouse::ChangeSensity(int sense)
{
	sense < 0 ? Sensity = 20 : Sensity = sense;
	return;
}

Mouse::~Mouse()
{
}
