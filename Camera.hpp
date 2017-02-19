#ifndef _CAMERA
#define _CAMERA
#include <cmath>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
class Camera
{
private:
	double x, y, z; //координаты камеры
	double angleX, angleY; // положение камеры в пространстве (углы) DEGREES (ГРАДУСЫ)!!!
	double height;//рост камеры;
	double PlayerSpeed;// Скорость игрока
public:
	void Look(); // функция установки позиции камеры
	void MoveForward(); // движение вперед
	void MoveBackward(); // движение назад
	void MoveRight(); // движение вправо
	void MoveLeft(); // движение влево 
	void ChangePlayerSpeed(double speed);// изменяет скорость игрока
	void RotaterRightLeft(double angleX1);// Вращает камеру вправо/влево input:угол в ГРАДУСАХ!!
	void RotateHighDown(double angleY1);// Вращает камеру вверх/вниз input: угол в ГРАДУСАХ
	Camera();
	Camera(double x, double y, double z, double height, double PlayerSpeed, double AngleX, double AngleY); // x,y,z,height, PlayerSpeed angleX,AngleY
	~Camera();
};

#endif