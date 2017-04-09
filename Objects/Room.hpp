#ifndef _ROOM
#define _ROOM

#include <set>
#include "../Storage.hpp"
#include "NPC.hpp"

class Room : public Object3D
{
	std::set <size_t> objects3d;
	std::set <size_t> movable_objects;
	std::set <size_t> npc;
	Storage * storage;
public:
	Room();
	Room(Model* model, Storage *);
	~Room();
	void getAllObjects(std::vector<Object3D *> &); //В аргумент будут ДОПИСАНЫ все указатели на обЪекты в комнате
	void addObject3D(StorageIndex);
	void addMovableObject(StorageIndex);
	void addNPC(StorageIndex);
};
#endif


