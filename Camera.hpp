#ifndef _CAMERA
#define _CAMERA
#include <cmath>
	#ifdef _WIN32
	#include <Windows.h>
	#endif
#ifndef _GLEWINCLUDE
#define _GLEWINCLUDE
#include <GL/glew.h>
#include <GL/glu.h>
#endif 
#include <stdlib.h>
#include <set>
#include "Storage.hpp"
#define GLM_FORCE_RADIANS //для ускорения все в радианах
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"Objects/MovableObject.hpp"
#include "Shaders.hpp"

class Camera : public MovableObject
{
	StorageIndex current_room = 0;
	double fov = 1.2217f;
	double wtoh = 16.0/9.0;
	double zNear = 0.04;
	double zFar = 3000;
	glm::mat4 projection = glm::mat4(glm::perspective(fov, wtoh, zNear, zFar));
	glm::mat4 view;
public:
	void Look(); // функция установки позиции камеры
	glm::mat4 Projection() {return projection;}
	glm::mat4 View() {return view;}
	void setRoom(StorageIndex);
	StorageIndex getRoom();
	const double & FOV();
	const double & WtoH();
	const double & nearSurface();
	const double & farSurface();
	void setView(double, double, double, double);//устанавливаем конус зрения в формате fov, x/y, zNear, zFar
	Camera();
	~Camera();
};

#endif
