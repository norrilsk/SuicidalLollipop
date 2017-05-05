#include <iostream>
#include "TrianglePortal.hpp"
#include "../Error.hpp"

TrianglePortal::TrianglePortal(glm::dvec3 a, glm::dvec3 b, glm::dvec3 c) : A(a), B(b), C(c)
{
	O = (A + B + C)/3.0;
	e1 = A - O;
	e2 = B - O;
}

void TrianglePortal::linckTo(TrianglePortal & target)
{
	target_room = target.current_room;
	glm::dvec3 e3 = glm::cross(e1, e2), te3 = glm::cross(target.e1, target.e2) * target.coef;
	glm::dmat3 E1(target.e1, target.e2, te3), E1x, E1y, E1z;

	glm::dmat3 A = (glm::dmat3(e1, e2, e3));
	glm::dmat3 B = glm::inverse(glm::dmat3(target.e1, target.e2, te3));

	glm::dmat3 M0 = A * B ;

	M = glm::dmat4(glm::dvec4(M0[0], 0), glm::dvec4(M0[1], 0), glm::dvec4(M0[2], 0), glm::dvec4(target.O - O, 1));

	/*std::cout <<e1.x << " " << e1.y << " " << e1.z << "\n";
	std::cout <<e2.x << " " << e2.y << " " << e2.z << "\n";
	std::cout <<e3.x << " " << e3.y << " " << e3.z << "\n";
	std ::cout <<"\n";

	std::cout <<target.e1.x << " " << target.e1.y << " " << target.e1.z << "\n";
	std::cout <<target.e2.x << " " << target.e2.y << " " << target.e2.z << "\n";
	std::cout <<te3.x << " " << te3.y << " " << te3.z << "\n";
	std ::cout <<"\n";

	std::cout << M[0][0] << "\t" << M[1][0] <<"\t"<<M[2][0] << "\n";
	std::cout << M[0][1] << "\t" << M[1][1] <<"\t"<<M[2][1] << "\n";
	std::cout << M[0][2] << "\t" << M[1][2] <<"\t"<<M[2][2] << "\n";*/


}

void TrianglePortal::setRoom(StorageIndex room)
{
	current_room = room;
}

StorageIndex TrianglePortal::getRoom()
{
	return current_room;
}

void TrianglePortal::setPortalCoef(double value)
{
	coef = value;
}

glm::dvec3 TrianglePortal::operator[](int i) const
{
	if(i == 0)
		return A;
	if(i == 1)
		return B;
	if(i == 2)
		return C;
	throw(newError(OUT_OF_RANGE));
}

double TrianglePortal::zCoef()
{
	return coef;
}


