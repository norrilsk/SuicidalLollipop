#ifndef _TRIANGLEPORTAL
#define _TRIANGLEPORTAL

#include "../Storage.hpp"
#include <glm/glm.hpp>

class TrianglePortal
{
	double coef = 1.0; //портальное число
	glm :: dvec3  O, n, uo, A, B, C;
	glm :: dmat4 M;
public:
	TrianglePortal(){}
	TrianglePortal(glm::dvec3, glm::dvec3, glm::dvec3);//треугольник по 3 точкам в абсолютных координата
	glm::dvec3 operator [] (int) const;//возвращяем вершину
};


#endif
