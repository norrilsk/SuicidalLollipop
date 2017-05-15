#include <iostream>
#include "Portal.hpp"

void Portal::createPottal(int N, float * data, StorageIndex room)
{
	current_room = room;
	O = glm::dvec3(0);
	for(int i = 0; i < N*9; i += 9)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i], data[i+1], data[i + 2]), glm::dvec3(data[i + 3], data[i+4], data[i + 5]), glm::dvec3(data[i + 6], data[i+7], data[i + 8])));
		O += glm::dvec3(data[i], data[i+1], data[i + 2]) + glm::dvec3(data[i + 3], data[i+4], data[i + 5]) + glm::dvec3(data[i + 6], data[i+7], data[i + 8]);
	}
	O /= (N*3);
}

void Portal::createPottal(int N, double * data, StorageIndex room)
{
	current_room = room;
	O = glm::dvec3(0);
	for(int i = 0; i < N*9; i += 9)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i], data[i+1], data[i + 2]), glm::dvec3(data[i + 3], data[i+4], data[i + 5]), glm::dvec3(data[i + 6], data[i+7], data[i + 8])));
		O += glm::dvec3(data[i], data[i+1], data[i + 2]) + glm::dvec3(data[i + 3], data[i+4], data[i + 5]) + glm::dvec3(data[i + 6], data[i+7], data[i + 8]);
	}
	O /= (N*3);
}

void Portal::createPottal(int N, glm::vec3 * data, StorageIndex room)
{
	current_room = room;
	O = glm::dvec3(0);
	for(int i = 0; i < N*3; i += 3)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i]), glm::dvec3(data[i + 1]), glm::dvec3(data[i + 2])));
		O += glm::dvec3(data[i]) + glm::dvec3(data[i + 1]) + glm::dvec3(data[i + 2]);
	}
	O /= (N*3);
}

void Portal::createPottal(int N, glm::dvec3 * data, StorageIndex room)
{
	current_room = room;
	O = glm::dvec3(0);
	for(int i = 0; i < N*3; i += 3)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i]), glm::dvec3(data[i + 1]), glm::dvec3(data[i + 2])));
		O += glm::dvec3(data[i]) + glm::dvec3(data[i + 1]) + glm::dvec3(data[i + 2]);
	}
	O /= (N*3);
}

void Portal::linkToPortal(Portal & target)
{
	glm::dvec3 &e1 = main_vector, &e2 = second_vector, &te1 = target.main_vector,  &te2 = target.second_vector;
	glm::dvec3 e3 = glm::cross(e1, e2), te3 = glm::cross(te1, te2);

	glm::dmat3 A = (glm::dmat3(e1, e2, e3));
	glm::dmat3 B = glm::inverse(glm::dmat3(te1, te2, te3));
	glm::dmat3 Matrix = A * B;

	target_room = target.current_room;
	M = glm::dmat4(glm::dvec4(Matrix[0], 0), glm::dvec4(Matrix[1], 0), glm::dvec4(Matrix[2], 0), glm::dvec4(0, 0, 0, 1));

	std::cout <<O.x << " "<< O.y<< " " << O.z  << "\n" <<  (M*glm::dvec4(target.O, 1)).x << " "<< (M*glm::dvec4(target.O, 1)).y<< " " << (M*glm::dvec4(target.O, 1)).z  << "\n";
	M = glm::dmat4(glm::dvec4(Matrix[0], 0), glm::dvec4(Matrix[1], 0), glm::dvec4(Matrix[2], 0), glm::dvec4(glm::dvec3(glm::dvec4(O, 0) - M*glm::dvec4(target.O, 1)), 1));
	std::cout << M[3][0]<<" " << M[3][1]<<" " << M[3][2] << std::endl;
	linked = true;
}

Portal::Portal(int N, float * data, StorageIndex room)
{
	createPottal(N, data, room);
}

Portal::Portal(int N, double * data, StorageIndex room)
{
	createPottal(N, data, room);
}

Portal::Portal(int N, glm::vec3 * data, StorageIndex room)
{
	createPottal(N, data, room);
}

Portal::Portal(int N, glm::dvec3 * data, StorageIndex room)
{
	createPottal(N, data, room);
}

size_t Portal::numberOfSubportals()
{
	return sub_portals.size();
}

TrianglePortal &Portal::operator[](int i)
{
	return sub_portals[i];
}

void Portal::setRoom(StorageIndex room)
{
	current_room = room;
}

StorageIndex Portal::getRoom()
{
	return current_room;
}

StorageIndex Portal::getTarget()
{
	return target_room;
}

void Portal::setVectors(glm::dvec3 vec1, glm::dvec3 vec2)
{
	main_vector = glm::normalize(vec1);
	second_vector = glm::normalize(vec2);
}

void Portal::setVectors(double x, double y, double z, double x2, double y2, double z2)
{
	main_vector = glm::normalize(glm::dvec3(x, y, z));
	second_vector = glm::normalize(glm::dvec3(x2, y2, z2));
}

glm::dmat4 Portal::Matrix()
{
	return M;
}
