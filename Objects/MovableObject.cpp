#include "MovableObject.hpp"

MovableObject::MovableObject(Model* model):Object3D(model)
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
	if(glm::length(omega) < 1e-9)//если нам не нужно крутиться экономим операции
		return;
	glm :: dmat3 Omega(0, omega.z, -omega.y, //первый столбец
						-omega.z, 0, omega.x, //второй
						omega.y, -omega.x, 0);//третий. ЭТО GLM
	A += Omega * A * dt;
	ex /= glm:: length(ex);
	ey /= glm:: length(ey);
	ez /= glm:: length(ez);
}

void MovableObject:: rotateRelative(glm :: dvec3 omega, double dt)
{
	if(glm::length(omega) < 1e-9)//если нам не нужно крутиться экономим операции
		return;
	glm :: dmat3 Omega(	0, omega.z, -omega.y, //первый столбец
						-omega.z, 0, omega.x, //второй
						omega.y, -omega.x, 0);//третий. ЭТО GLM
	A += A*Omega * dt;
	ex /= glm:: length(ex);
	ey /= glm:: length(ey);
	ez /= glm:: length(ez);
}


MovableObject::~MovableObject()
{
}

MovableObject::MovableObject()
{
}
