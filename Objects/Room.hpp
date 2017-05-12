#ifndef _ROOM
#define _ROOM

#include <set>
#include "../Storage.hpp"
#include "NPC.hpp"
#include "../PhysicalEngine.hpp"
#include<climits>

class Room : public Object3D
{
	std::set <StorageIndex> objects3d;
	std::set <StorageIndex> movable_objects;
	std::set <StorageIndex> npc;
	std::set <StorageIndex> light_sources;
	PhysicalEngine physics;
	Storage * storage;
public:
	Room();
	Room(Model* model, Storage *);
	~Room();
	size_t numberOfObjects();//число объектов
	size_t numberOfLights();//число источников света
	size_t numberOfMovableObjects();// число двигающихся обЪектов
	void getAllMovablObjects(MovableObject**); 
	void getAllObjects(Object3D**); 
	void getAllLights(LightSource**); 
	void addObject3D(StorageIndex);
	void addMovableObject(StorageIndex);
	void addNPC(StorageIndex);
	void addLightSource(StorageIndex);
	void setPhysics(bool isEnabled, double g = DBL_MAX);// включим физикку
	void ApplyPhysics(double dt) { physics.ApplyPhysics(dt); }
};
#endif


