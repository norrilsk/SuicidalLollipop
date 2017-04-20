#include <iostream>
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



void MovableObject:: rotateAbsolute(glm :: dvec3 tetta)
{
	double fi = glm::length(tetta);
	glm :: dmat3 Omega(0, tetta.z, -tetta.y, //первый столбец
						-tetta.z, 0, tetta.x, //второй
						tetta.y, -tetta.x, 0);//третий. ЭТО GLM
	if(fi > 0.15)
	{
		Omega = RotationMatrix(fi, tetta / fi);
		A = Omega * A;
	}
	else
		A += Omega * A;
	ex /= glm:: length(ex);
	ey /= glm:: length(ey);
	ez /= glm:: length(ez);
}

void MovableObject:: rotateRelative(glm :: dvec3 tetta)
{
	double fi = glm::length(tetta);
	glm :: dmat3 Omega(	0, tetta.z, -tetta.y, //первый столбец
						-tetta.z, 0, tetta.x, //второй
						tetta.y, -tetta.x, 0);//третий. ЭТО GLM
	if(fi > 0.15)
	{
		Omega = RotationMatrix(fi, tetta / fi);
		A = A *Omega ;
	}
	else
		A += A*Omega;
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

glm::dmat3 MovableObject::RotationMatrix(double fi, glm::dvec3 e)
{
	double cosfi = cos(fi), sinfi = sin(fi);
	return glm::dmat3(cosfi + e.x*e.x*(1 - cosfi),          e.x*e.y*(1 - cosfi) + e.z*sinfi,         e.x*e.z*(1 - cosfi) - e.y*sinfi,
	                   e.x*e.y*(1 - cosfi) - e.z*sinfi,     cosfi + e.y*e.y*(1 - cosfi),             e.z*e.y*(1 - cosfi) + e.x*sinfi,
	                   e.x*e.z*(1 - cosfi) + e.y*sinfi,     e.y*e.z*(1 - cosfi) - e.x*sinfi,         cosfi + e.z*e.z*(1 - cosfi));
}
