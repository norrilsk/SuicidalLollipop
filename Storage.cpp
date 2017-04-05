#include "Storage.hpp"

void Storage::get_display(Room * room, std::vector<DrawableObject *> & store)
{
	room->getAllObjects(store);
}

StorageIndex Storage::addNPC(const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end()) //Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	npcs.push_back(NPC(&model[path_to_model]));
	return npcs.size() - 1;
}

StorageIndex Storage::addObject3D (const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	objects3d.push_back(Object3D(&model[path_to_model]));
	return objects3d.size() - 1;
}

StorageIndex Storage::addMovableObject (const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	movable_objects.push_back(MovableObject(&model[path_to_model]));
	return movable_objects.size() - 1;
}

StorageIndex Storage::addRoom(const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	rooms.push_back(Room(&model[path_to_model]));
	return rooms.size() - 1;
}

Storage::~Storage()
{

}

Storage::Storage()
{

}
