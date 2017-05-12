#ifndef _TRIANGLEPORTAL
#define _TRIANGLEPORTAL

#include "../Storage.hpp"
#include <glm/glm.hpp>

class TrianglePortal
{
	StorageIndex current_room = 0;
	StorageIndex target_room = 0;
	double coef = 1.0; //портальное число
	glm :: dvec3  O, e1, e2, A, B, C;
	glm :: dmat4 M;
public:
	TrianglePortal(){}
	TrianglePortal(glm::dvec3, glm::dvec3, glm::dvec3);//треугольник по 3 точкам
	void setRoom(StorageIndex);//какая комната?
	void setPortalCoef(double);
	StorageIndex getRoom();
	void linckTo(TrianglePortal &);
};


#endif
