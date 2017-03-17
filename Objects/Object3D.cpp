#include "Object3D.hpp"


Object3D::Object3D()
{
}
Object3D::Object3D(std::string path)
{
	model = MashObject(path);

}
void Object3D::draw()
{
	if (model.isdrawable())
		model.draw();
}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection, glm :: dvec3 upperdirection)
{
	coord = position;
	ex = lookdirection;
	ez = upperdirection;
	if(glm ::dot(ex, ex) != 1.0)
		ex /= sqrt(glm:: dot(ex, ex));
	if(glm ::dot(ex, ex) != 1.0)
		ez /= sqrt(glm:: dot(ez, ez));
	ey = ez*ex;
}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection)
{
	coord = position;
	ex = lookdirection;
	if(glm ::dot(ex, ex) != 1.0)
		ex /= sqrt(glm:: dot(ex, ex));
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
