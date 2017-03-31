#ifndef _ROOM
#define _ROOM

#include <set>
#include "NPC.hpp"
class Room : public Object3D
{
	std::set <size_t> objects3d;
	std::set <size_t> movable_objects;
	std::set <size_t> npc;

public:
	Room();
	Room(MashObject* mash);
	~Room();
	void getAllObjects(std::vector<DrawableObject *> &);
	void addObject3D(size_t);
	void addMovableObject(size_t);
	void addNPC(size_t);
};
#endif


