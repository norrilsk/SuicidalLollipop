#include "Storage.hpp"
#include "Objects/NPC.hpp"
#include "Objects/Room.hpp"
#include "SDLTexture.hpp"
#include "Error.hpp"

StorageIndex Storage::addNPC(const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end()) //Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	npcs.emplace_back(NPC(&model[path_to_model]));
	return npcs.size() - 1;
}

StorageIndex Storage::addObject3D (const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	objects3d.emplace_back(Object3D(&model[path_to_model]));
	return objects3d.size() - 1;
}

StorageIndex Storage::addMovableObject (const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	movable_objects.emplace_back(MovableObject(&model[path_to_model]));
	return movable_objects.size() - 1;
}

StorageIndex Storage::addRoom(const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	rooms.emplace_back(Room(&model[path_to_model], this));
	return rooms.size() - 1;
}

StorageIndex Storage::addSDLTexture(SDL_Renderer* renderer,const std::string & path)
{
	sdl_textures.emplace_back(SDLTexture(renderer, path.c_str()));
	return sdl_textures.size() - 1;
}

Storage::~Storage()
{

}

Storage::Storage()
{

}

NPC &Storage::npc(StorageIndex ind)
{
	return npcs[ind];
}

Object3D &Storage::object3d(StorageIndex ind)
{
	return objects3d[ind];
}

Room &Storage::room(StorageIndex ind)
{
	return rooms[ind];
}

MovableObject &Storage::movableObject(StorageIndex ind)
{
	return movable_objects[ind];
}

SDLTexture &Storage::sdlTexture(StorageIndex ind)
{
	return sdl_textures[ind];
}

void Storage::loadWorld(const char * path)
{
	std::ifstream in(path);
	if(!in.is_open())
		throw(newError2(FILE_NOT_OPEN, path));
	while(!in.eof())
	{
		std::string str;
		in >> str;
		if(str == "ROOM")
		{
			std::string path;
			in >> path;
		}

	}
}
