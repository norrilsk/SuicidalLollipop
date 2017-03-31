#ifndef _STORAGE
#define _STORAGE

#include <vector>
#include <map>
#include "Objects/Room.hpp"
#include "Objects/NPC.hpp"

typedef size_t StorageIndex;

class Storage
{
	std::vector <Room> rooms;
	std::vector <NPC> npcs;
	std::vector <MovableObject>  movable_objects;
	std::vector <Object3D>  objects3d;
	std::map <std::string, MashObject> mash;
public:
	Storage();
	~Storage();
	void get_display(Room *, std::vector<DrawableObject *> &);//возвращает все объекты в комнате
	StorageIndex addNPC(const std::string &);
	StorageIndex addObject3D  (const std::string &);
	StorageIndex addMovableObject (const std::string &);
	StorageIndex addRoom (const std::string &);
	NPC& npc(StorageIndex ind) { return npcs[ind]; }
	Object3D& object3d(StorageIndex ind) { return objects3d[ind]; }
	Room& room (StorageIndex ind) { return rooms[ind]; }
	MovableObject& movableObject(StorageIndex ind) { return movable_objects[ind]; }
};


#endif
