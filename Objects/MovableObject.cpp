#include "MovableObject.hpp"
MovableObject::MovableObject()
{
}

void MovableObject:: moveAbslute(glm :: dvec3 to)
{
	coord += to;
}

void MovableObject:: moveRelative(glm :: dvec3 to)
{
	 coord += A * to; 
}

MovableObject::~MovableObject()
{
}
