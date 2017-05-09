#include "Camera.hpp"
#include <glm/glm.hpp>
Camera::Camera()
{
}

void Camera::Look()
{
	view = glm::lookAt(glm::vec3(coord),  glm::vec3(coord + ex), glm::vec3(ez));
	/*Первые 3 - координаты позиции глаза налюдателя, вторые 3 - координаты точки, распологающейся в центре экрана,
	третьи 3 - направление вектора, задающего поворот сцены.*/
}
Camera::~Camera()
{
}

const double &Camera::WtoH()
{
	return wtoh;
}

const double &Camera::FOV()
{
	return fov;
}

const double &Camera::nearSurface()
{
	return zNear;
}

const double &Camera::farSurface()
{
	return zFar;
}

void Camera::setView(double FOV, double WtoH, double nearSurface, double farSurface)
{
	fov  = FOV;
	wtoh = WtoH;
	zNear = nearSurface;
	zFar  = farSurface;
	projection = glm::perspective(fov,wtoh, zNear, zFar);
}

void Camera::setRoom(StorageIndex ind)
{
	current_room = ind;
}

StorageIndex Camera::getRoom()
{
	return current_room;
}

