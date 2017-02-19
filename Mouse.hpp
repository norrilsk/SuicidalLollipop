#ifndef _MOUSE
#define _MOUSE
#include "Camera.hpp"
//#include "GLfunc.hpp"
class Mouse
{
private:
	int X, Y, Sensity; // Координаты положения мыши, чувствительность

public:
	void MouseMotion(int x, int y); // движение мыши, передавать абсолютную координату
	void ChangeSensity(int Sens); // Изменить чувствительность
	Mouse(int x, int y, int Sens);
	Mouse();
	
	~Mouse();
};
#endif