#ifndef _ROOM
#define _ROOM

#include <set>
#include "../Storage.hpp"
#include "NPC.hpp"

class Room : public Object3D
{
	std::set <StorageIndex> objects3d;
	std::set <StorageIndex> movable_objects;
	std::set <StorageIndex> npc;
	std::set <StorageIndex> light_sources;
	Storage * storage;
public:
	Room();
	Room(Model* model, Storage *);
	~Room();
	void getAllObjects(std::vector<Object3D *> &); //В аргумент будут ДОПИСАНЫ все указатели на обЪекты в комнате
	void getAllLights(std::vector<LightSource *> &); //В аргумент будут ДОПИСАНЫ все указатели на обЪекты в комнате
	void addObject3D(StorageIndex);
	void addMovableObject(StorageIndex);
	void addNPC(StorageIndex);
	void addLightSource(StorageIndex);
};
#endif


