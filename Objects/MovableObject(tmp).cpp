#include "MovableObject.hpp"
#include <iostream> //TODO delete
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

void MovableObject:: rotateAbslute(glm :: dvec3 rotation)
{
	
}

void MovableObject:: rotateRelative(glm :: dvec3 rotation)
{
	ex /= sqrt(glm:: dot(ex, ex));
	ey /= sqrt(glm:: dot(ey, ey));
	ez /= sqrt(glm:: dot(ez, ez));
	if(glm::dot(rotation, rotation) == 0)//если нам не нужно крутиться экономим операции
		return;
	double tetta = sqrt(glm:: dot(rotation, rotation));
	double cost= cos(tetta);
	double sint = sin(tetta);
	double x = rotation.x, y = rotation.y, z = rotation.z; 
	rotation /= tetta;
	glm::dmat3 M	(cost + (1.0 - cost) * x * x, 		(1.0 - cost) * y * x + sint * z, 	(1.0 - cost) * z * x - sint * y, //первый столбец матрицы поворота 
				(1.0 - cost) * y * x - sint * z, 	cost + (1.0 - cost) * y * y,		(1.0 - cost) * z * y + sint * x, //второй
				(1.0 - cost) * z * x + sint * y,	(1.0 - cost) * z * y - sint * x,	cost + (1.0 - cost) * z * z); //третий Спасибо Wikipedia
	glm::dmat3 B  =  M * A; 
	A = B;
	std ::cout << glm:: dot(ey, ey) << std ::endl;
}


MovableObject::~MovableObject()
{
}
