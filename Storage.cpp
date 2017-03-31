#include "Storage.hpp"

void Storage::get_display(Room * room, std::vector<DrawableObject *> & store)
{
	room->getAllObjects(store);
}

StorageIndex Storage::addNPC(const std::string & path_to_mash)
{
	if(mash.find(path_to_mash) == mash.end()) //Если меш ещё не существует создаем
		mash[path_to_mash] = MashObject(path_to_mash);
	npcs.push_back(NPC(&mash[path_to_mash]));
	return npcs.size() - 1;
}

StorageIndex Storage::addObject3D (const std::string & path_to_mash)
{
	if(mash.find(path_to_mash) == mash.end())//Если меш ещё не существует создаем
		mash[path_to_mash] = MashObject(path_to_mash);
	objects3d.push_back(Object3D(&mash[path_to_mash]));
	return objects3d.size() - 1;
}

StorageIndex Storage::addMovableObject (const std::string & path_to_mash)
{
	if(mash.find(path_to_mash) == mash.end())//Если меш ещё не существует создаем
		mash[path_to_mash] = MashObject(path_to_mash);
	movable_objects.push_back(MovableObject(&mash[path_to_mash]));
	return movable_objects.size() - 1;
}

StorageIndex Storage::addRoom(const std::string & path_to_mash)
{
	if(mash.find(path_to_mash) == mash.end())//Если меш ещё не существует создаем
		mash[path_to_mash] = MashObject(path_to_mash);
	rooms.push_back(Room(&mash[path_to_mash]));
	return rooms.size() - 1;
}

Storage::~Storage()
{

}

Storage::Storage()
{

}
