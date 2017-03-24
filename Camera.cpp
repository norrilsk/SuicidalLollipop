#include "Camera.hpp"
#include <iostream>
#include "GLfunc.hpp"
Camera::Camera()
{
}

void Camera::Look()
{
	Gl::View = glm::lookAt(glm::vec3(coord),  glm::vec3(coord + ex), glm::vec3(ez));
	/*Первые 3 - координаты позиции глаза налюдателя, вторые 3 - координаты точки, распологающейся в центре экрана,
	третьи 3 - направление вектора, задающего поворот сцены.*/
}
Camera::~Camera()
{
}
