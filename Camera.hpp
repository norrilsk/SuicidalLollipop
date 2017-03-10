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
#include "Objects/MovableObject.hpp"

class Camera : public MovableObject
{
public:
	void Look(); // функция установки позиции камеры
	Camera();
	~Camera();
};

#endif
