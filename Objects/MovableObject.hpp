#ifndef _MOVABLEOBJECT
#define _MOVABLEOBJECT
#include "Object3D.hpp"
class MovableObject : public Object3D
{
public:
	void moveAbsolute(glm :: dvec3);//относительный переход в абсолютных координатах
	void moveRelative(glm :: dvec3);//относительный переход в собственных координатах
	void rotateAbsolute(glm :: dvec3 omega, double dt);//относительный поворот в абсолютных координатах
	void rotateRelative(glm :: dvec3 omega, double dt);//относительный поворот в сщбственных координатах (если нужно выполняет последовательное)
	MovableObject();
	~MovableObject();
};
#endif

