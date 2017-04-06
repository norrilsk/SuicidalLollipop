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

public:
	Room();
	Room(Model* model);
	~Room();
	void getAllObjects(std::vector<DrawableObject *> &);
	void addObject3D(StorageIndex);
	void addMovableObject(StorageIndex);
	void addNPC(StorageIndex);
};
#endif


