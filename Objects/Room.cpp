#include "Room.hpp"
#include "../GLfunc.hpp"
#include "../Storage.hpp"


Room::Room()
{
}


Room::~Room()
{
}

void Room::getAllObjects(std::vector<DrawableObject *> & store)
{
	for(StorageIndex ind : npc)
		store.push_back((DrawableObject *) &(Gl::storage.npc(ind)));
	for(StorageIndex ind: movable_objects)
		store.push_back((DrawableObject *) &(Gl::storage.movableObject(ind)));
	for(StorageIndex ind: objects3d)
		store.push_back((DrawableObject *) &(Gl::storage.object3d(ind)));
}

Room::Room(Model *model) : Object3D(model)
{

}

void Room::addObject3D(size_t ind)
{
	objects3d.insert(ind);
}

void Room::addMovableObject(size_t ind)
{
	movable_objects.insert(ind);
}

void Room::addNPC(size_t ind)
{
	npc.insert(ind);
}


