#include "Room.hpp"


Room::Room()
{
}


Room::~Room()
{
}

void Room::getAllObjects(std::vector<Object3D *> & store)
{
	for(StorageIndex ind : npc)
		store.push_back((Object3D *) &(storage->npc(ind)));
	for(StorageIndex ind: movable_objects)
		store.push_back((Object3D *) &(storage->movableObject(ind)));
	for(StorageIndex ind: objects3d)
		store.push_back((Object3D *) &(storage->object3d(ind)));
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


