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
	return near;
}

const double &Camera::farSurface()
{
	return far;
}

void Camera::setView(double FOV, double WtoH, double nearSurface, double farSurface)
{
	fov  = FOV;
	wtoh = WtoH;
	near = nearSurface;
	far  = farSurface;
	projection = glm::perspective(fov,wtoh, near, far);
}


