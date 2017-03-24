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
#include "Objects/MovableObject.hpp"

class Camera : public MovableObject
{
public:
	void Look(); // функция установки позиции камеры
	Camera();
	~Camera();
};

#endif
