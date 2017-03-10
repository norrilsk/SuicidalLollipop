#include "Camera.hpp"
#include <iostream>

Camera::Camera()
{
}

void Camera::Look()
{
	//std :: cout << ex.x << " " << ex.y << " " << ex.z <<std :: endl;
	gluLookAt(coord.x, coord.y, coord.z,  coord.x + ex.x,  coord.y + ex.y,  coord.z + ex.z, ez.x, ez.y, ez.z);
	/*Первые 3 - координаты позиции глаза налюдателя, вторые 3 - координаты точки, распологающейся в центре экрана,
	третьи 3 - направление вектора, задающего поворот сцены.*/
}
Camera::~Camera()
{
}
