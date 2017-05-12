#include <iostream>
#include "Storage.hpp"
#include "Objects/NPC.hpp"
#include "Objects/Room.hpp"
#include "SDLTexture.hpp"
#include "Error.hpp"
#include "Objects/LightSource.hpp"
#include "Objects/Portal.hpp"

StorageIndex Storage::addNPC(const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end()) //Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	npcs.emplace_back(&model[path_to_model]);
	return (npcs.size() - 1) * NumberOfTypes + NPCInd;
}

StorageIndex Storage::addObject3D (const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	objects3d.emplace_back(&model[path_to_model]);
	return (objects3d.size() - 1) * NumberOfTypes + Object3DInd;
}

StorageIndex Storage::addMovableObject (const std::string & path_to_model)
{
	if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	movable_objects.emplace_back(&model[path_to_model]);
	return (movable_objects.size() - 1) * NumberOfTypes + MovableObjectInd;
}

StorageIndex Storage::addRoom(const std::string & path_to_model)
{
if(model.find(path_to_model) == model.end())//Если меш ещё не существует создаем
		model[path_to_model] = Model(path_to_model);
	rooms.emplace_back(&model[path_to_model], this);
	return (rooms.size() - 1) * NumberOfTypes + RoomInd;
}

StorageIndex Storage::addSDLTexture(SDL_Renderer* renderer,const std::string & path)
{
	sdl_textures.emplace_back(renderer, path.c_str());
	return (sdl_textures.size() - 1) * NumberOfTypes + SDLTextureInd;
}

StorageIndex Storage::addLightSource(const SourceType& type)
{
	light_sources.emplace_back(type);
	return (light_sources.size() - 1)*NumberOfTypes + LightSourceInd;
}

StorageIndex Storage::addPortal(const std::string & path)
{
	portals.push_back(Portal());
	std::vector<glm::dvec3> coord = {glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0), glm::dvec3(-1, 0.0, -1)}; //TODO написать парсер здесь
	portals.back().createPottal(3, coord.data(), indexOf("firstRoom"));
	return (portals.size() - 1)*NumberOfTypes + PortalInd;
}



Storage::~Storage()
{

}

Storage::Storage()
{

}

NPC &Storage::npc(StorageIndex ind)
{
	return npcs[ind/NumberOfTypes];
}

NPC &Storage::npc(const std::string & name)
{
	return npc(nick_names.at(name));
}

Object3D &Storage::object3d(StorageIndex ind)
{
	return objects3d[ind/NumberOfTypes];
}

Object3D &Storage::object3d(const std::string & name)
{
	return object3d(nick_names.at(name));
}

Room &Storage::room(StorageIndex ind)
{
	return rooms[ind/NumberOfTypes];
}

Room &Storage::room(const std::string & name)
{
	return room(nick_names.at(name));
}

MovableObject &Storage::movableObject(StorageIndex ind)
{
	return movable_objects[ind/NumberOfTypes];
}

MovableObject &Storage::movableObject(const std::string & name)
{
	return movableObject(nick_names.at(name));
}

SDLTexture &Storage::sdlTexture(StorageIndex ind)
{
	return sdl_textures[ind/NumberOfTypes];
}

SDLTexture &Storage::sdlTexture(const std::string & name)
{
	return sdlTexture(nick_names.at(name));
}

LightSource &Storage::lightSource(StorageIndex ind)
{
	return light_sources[ind / NumberOfTypes];
}
LightSource &Storage::lightSource(const std::string & name)
{
	return lightSource(nick_names.at(name));
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
			std::string filePath, name;
			int mash, tex;
			in >> filePath;
			StorageIndex ind = addRoom(filePath);
			double g;
			in >> g;
			room(ind).setPhysics((g != 0), g);
			in >> mash >> tex;
			room(ind).setActiveMash(mash);
			room(ind).setActiveTexture(tex);
			in >> name;
			create_nickname(name, ind);
		}
		else if(str == "OBJ3D")
		{
			std::string filePath, name;
			int mash, tex;
			glm::dvec3 position, look, up;
			StorageIndex objroom;
			in >> filePath;
			StorageIndex ind = addObject3D(filePath);
			in >>look.x >> look.y >> look.z >> up.x >> up.y >> up.z >>position.x >> position.y >> position.z;
			object3d(ind).set(position, look, up);
			in >> objroom;
			rooms[objroom].addObject3D(ind);
			in >> mash >> tex;
			object3d(ind).setActiveMash(mash);
			object3d(ind).setActiveTexture(tex);
			in >> name;
			create_nickname(name, ind);
		}
		else if(str == "MOVOBJ")
		{
			std::string filePath, name;
			int mash, tex;
			glm::dvec3 position, look, up;
			StorageIndex objroom;
			in >> filePath;
			StorageIndex ind = addMovableObject(filePath);
			in >>look.x >> look.y >> look.z >> up.x >> up.y >> up.z >>position.x >> position.y >> position.z;
			movableObject(ind).set(position, look, up);
			in >> objroom;
			rooms[objroom].addMovableObject(ind);
			in >> mash >> tex;
			movableObject(ind).setActiveMash(mash);
			movableObject(ind).setActiveTexture(tex);
			in >> name;
			create_nickname(name, ind);
		}
		else if(str == "NPC")
		{
			std::string filePath, name;
			int mash, tex;
			glm::dvec3 position, look, up;
			StorageIndex objroom;
			in >> filePath;
			StorageIndex ind = addNPC(filePath);
			in >>look.x >> look.y >> look.z >> up.x >> up.y >> up.z >>position.x >> position.y >> position.z;
			npc(ind).set(position, look, up);
			in >> objroom;
			rooms[objroom].addNPC(ind);
			in >> mash >> tex;
			npc(ind).setActiveMash(mash);
			npc(ind).setActiveTexture(tex);
			in >> name;
			create_nickname(name, ind);
		}
		else if (str == "LIGHTSOURCE")
		{
			std::string source_type,name;
			StorageIndex objroom;
			glm::dvec3 position, look;
			glm::vec3 color;
			float power, angle;
			in >> source_type;
			SourceType type = SPHERIC;
			if (source_type == "CONIC")
			{
				type = CONIC;
			}
			else if (source_type == "SPHERIC")
			{
				type = SPHERIC;
			}
			else if (source_type == "PARALLEL")
			{
				type = PARALLEL;
			}
			StorageIndex ind = addLightSource(type);
			in >> look.x >> look.y >> look.z >> position.x >> position.y >> position.z >> color.x >> color.y >> color.z;
			lightSource(ind).set(position, look);
			lightSource(ind).setColor(color);
			in >> power >> angle;
			lightSource(ind).setPower(power);
			lightSource(ind).setAngle(angle);
			in >> objroom;
			rooms[objroom].addLightSource(ind);
			in >> name;
			create_nickname(name, ind);
		}


	}
}

void Storage::create_nickname(const std::string & name, StorageIndex ind)
{
	nick_names[name] = ind;
}

StorageIndex Storage::indexOf(const std::string & name)
{
	return nick_names.at(name);
}





