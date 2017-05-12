#include "Room.hpp"
#include "LightSource.hpp"

Room::Room()
{
	physics = PhysicalEngine(this);
}


Room::~Room()
{
}

size_t Room::numberOfLights()
{
	return light_sources.size();
}

size_t Room::numberOfObjects()
{
	return objects3d.size() + movable_objects.size() + npc.size();
}
size_t Room::numberOfMovableObjects()
{
	return movable_objects.size();
}
void Room::getAllMovablObjects(MovableObject** store)
{
	int i = 0;
	for (StorageIndex ind : movable_objects)
		store[i++] = &(storage->movableObject(ind));
}
void Room::getAllObjects(Object3D ** store)
{
	int i = 0;
	for (StorageIndex ind : npc)
		store[i++] = &(storage->npc(ind));
	for (StorageIndex ind : movable_objects)
		store[i++] = &(storage->movableObject(ind));
	for (StorageIndex ind : objects3d)
		store[i++] = &(storage->object3d(ind));
}

void Room::getAllLights(LightSource ** store)
{
	int i = 0;
	for (StorageIndex ind : light_sources)
		store[i++] = &(storage->lightSource(ind));
}
Room::Room(Model *model, Storage * str) : Object3D(model)
{
	physics = PhysicalEngine(this);
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

void Room::setPhysics(bool isEnabled, double g)
{
	if (g != DBL_MAX)
	{
		physics.setg(g);
	}
	physics.setRoom(this);
	physics.setPhysics(isEnabled);
}




