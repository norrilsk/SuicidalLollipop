#include <iostream>
#include "TrianglePortal.hpp"
#include "../Error.hpp"

TrianglePortal::TrianglePortal(glm::dvec3 a, glm::dvec3 b, glm::dvec3 c) : A(a), B(b), C(c)
{
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


