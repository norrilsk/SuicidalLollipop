#ifndef _OBJECT3D
#define _OBJECT3D
#include "DrawableObject.hpp"
class Object3D :
	public DrawableObject
{
public:
	void draw();
	Object3D();
	~Object3D();
};
#endif

