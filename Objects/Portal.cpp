#include "Portal.hpp"

void Portal::createPottal(int N, float * data, StorageIndex room, double * portal_coef)
{
	current_room = room;
	for(int i = 0; i < N*9; i += 9)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i], data[i+1], data[i + 2]), glm::dvec3(data[i + 3], data[i+4], data[i + 5]), glm::dvec3(data[i + 6], data[i+7], data[i + 8])));
		if(portal_coef != NULL)
			sub_portals.back().setPortalCoef(portal_coef[i/9]);
	}
}

void Portal::createPottal(int N, double * data, StorageIndex room, double * portal_coef)
{
	current_room = room;
	for(int i = 0; i < N*9; i += 9)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i], data[i+1], data[i + 2]), glm::dvec3(data[i + 3], data[i+4], data[i + 5]), glm::dvec3(data[i + 6], data[i+7], data[i + 8])));
		if(portal_coef != NULL)
			sub_portals.back().setPortalCoef(portal_coef[i/9]);
	}
}

void Portal::createPottal(int N, glm::vec3 * data, StorageIndex room, double * portal_coef)
{
	current_room = room;
	for(int i = 0; i < N*3; i += 3)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i]), glm::dvec3(data[i + 1]), glm::dvec3(data[i + 2])));
		if(portal_coef != NULL)
			sub_portals.back().setPortalCoef(portal_coef[i/3]);
	}
}

void Portal::createPottal(int N, glm::dvec3 * data, StorageIndex room, double * portal_coef)
{
	current_room = room;
	for(int i = 0; i < N*3; i += 3)
	{
		sub_portals.push_back(TrianglePortal(glm::dvec3(data[i]), glm::dvec3(data[i + 1]), glm::dvec3(data[i + 2])));
		if(portal_coef != NULL)
			sub_portals.back().setPortalCoef(portal_coef[i/3]);
	}
}

void Portal::linkToPortal(Portal & target)
{
	target_room = target.current_room;
	for(size_t i = 0; i < sub_portals.size(); ++i)
		sub_portals[i].linckTo(target.sub_portals[i]);
	linked = true;
}

Portal::Portal(int N, float * data, StorageIndex room, double* portal_coef)
{
	createPottal(N, data, room, portal_coef);
}

Portal::Portal(int N, double * data, StorageIndex room, double* portal_coef)
{
	createPottal(N, data, room, portal_coef);
}

Portal::Portal(int N, glm::vec3 * data, StorageIndex room, double* portal_coef)
{
	createPottal(N, data, room, portal_coef);
}

Portal::Portal(int N, glm::dvec3 * data, StorageIndex room, double* portal_coef)
{
	createPottal(N, data, room, portal_coef);
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