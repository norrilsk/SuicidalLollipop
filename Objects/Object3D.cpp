#include "Object3D.hpp"


Object3D::Object3D()
{
}
void Object3D::draw()
{

}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection, glm :: dvec3 upperdirection)
{
	coord = position;
	ex = lookdirection;
	ez = upperdirection;
	if(glm ::dot(ex, ex) != 1.0)
		ex /= ex.length();
	if(glm ::dot(ex, ex) != 1.0)
		ez /= ez.length();
	ey = ez*ex;
}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection)
{
	coord = position;
	ex = lookdirection;
	if(glm ::dot(ex, ex) != 1.0)
		ex /= ex.length();
	ey = ez*ex;
}

void Object3D:: set(glm :: dvec3 position)
{
	coord = position;
}

glm :: dvec3 Object3D:: getPosition()
{
	return coord;
}
glm :: dvec3 Object3D:: getLookDirection()
{
	return ex;
}
glm :: dvec3 Object3D:: getUpperDirection()
{
	return ez;
}

Object3D::~Object3D()
{
}
