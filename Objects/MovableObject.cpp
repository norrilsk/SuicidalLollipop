#include "MovableObject.hpp"
#include <iostream> //TODO delete
MovableObject::MovableObject()
{
}

void MovableObject:: moveAbsolute(glm :: dvec3 to)
{
	coord += to;
}

void MovableObject:: moveRelative(glm :: dvec3 to)
{
	 coord += A * to; 
}

void MovableObject:: rotateAbsolute(glm :: dvec3 omega, double dt)
{
	if(glm::dot(omega, omega) == 0)//если нам не нужно крутиться экономим операции
		return;
	glm :: dmat3 Omega(0, omega.z, -omega.y, //первый столбец
						-omega.z, 0, omega.x, //второй
						omega.y, -omega.x, 0);//третий. ЭТО GLM
	A += Omega * A * dt;
	ex /= sqrt(glm:: dot(ex, ex));
	ey /= sqrt(glm:: dot(ey, ey));
	ez /= sqrt(glm:: dot(ez, ez));
}

void MovableObject:: rotateRelative(glm :: dvec3 omega, double dt)
{
	if(glm::dot(omega, omega) == 0)//если нам не нужно крутиться экономим операции
		return;
	glm :: dmat3 Omega(	0, omega.z, -omega.y, //первый столбец
						-omega.z, 0, omega.x, //второй
						omega.y, -omega.x, 0);//третий. ЭТО GLM
	A += A*Omega * dt; 
	ex /= sqrt(glm:: dot(ex, ex));
	ey /= sqrt(glm:: dot(ey, ey));
	ez /= sqrt(glm:: dot(ez, ez));
}


MovableObject::~MovableObject()
{
}
