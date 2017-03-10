#ifndef _MOVABLEOBJECT
#define _MOVABLEOBJECT
#include "Object3D.hpp"
class MovableObject : public Object3D
{
public:
	void moveAbslute(glm :: dvec3);//относительный переход в абсолютных координатах
	void moveRelative(glm :: dvec3);//относительный переход в собственных координатах
	MovableObject();
	~MovableObject();
};
#endif

