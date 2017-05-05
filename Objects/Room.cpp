#include "Room.hpp"
#include "LightSource.hpp"
#include "NPC.hpp"
#include "Portal.hpp"

Room::Room()
{
}


Room::~Room()
{
}

void Room::getAllObjects(Object3D ** store)
{
	int i = 0;
	for(StorageIndex ind : npc)
		store[i++] = &(storage->npc(ind));
	for(StorageIndex ind: movable_objects)
		store[i++] = &(storage->movableObject(ind));
	for(StorageIndex ind: objects3d)
		store[i++] = &(storage->object3d(ind));
}

void Room::getAllLights(LightSource **  store)
{
	int i = 0;
	for(StorageIndex ind: light_sources)
		store[i++] = &(storage->lightSource(ind));
}

void Room::getAllPortals(Portal ** store)
{
	int i = 0;
	for(StorageIndex ind: portals)
		store[i++] = &(storage->portal(ind));
}


Room::Room(Model *model, Storage * str) : Object3D(model)
{
	storage = str;
}

void Room::addObject3D(StorageIndex ind)
{
	objects3d.insert(ind);
}

void Room::addMovableObject(StorageIndex ind)
{
	movable_objects.insert(ind);
}

void Room::addNPC(StorageIndex ind)
{
	npc.insert(ind);
}

void Room::addLightSource(StorageIndex ind)
{
	light_sources.insert(ind);
}

void Room::addPortal(StorageIndex ind)
{
	portals.insert(ind);
}

size_t Room::numberOfPortals()
{
	return portals.size();
}

size_t Room::numberOfLights()
{
	return light_sources.size();
}

size_t Room::numberOfObjects()
{
	return objects3d.size() + movable_objects.size() + npc.size();
}





