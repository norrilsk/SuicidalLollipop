#ifndef _ROOM
#define _ROOM

#include <set>
#include "../Storage.hpp"
#include "Object3D.hpp"


class Room : public Object3D
{
	std::set <StorageIndex> objects3d;
	std::set <StorageIndex> movable_objects;
	std::set <StorageIndex> npc;
	std::set <StorageIndex> light_sources;
	std::set <StorageIndex> portals;
	float ambient_power = 0.15f;
	Storage * storage;
public:
	Room();
	Room(Model* model, Storage *);
	~Room();
	size_t numberOfObjects();//число объектов
	size_t numberOfLights();//число источников света
	size_t numberOfPortals();//число источников порталов
	void getAllObjects(Object3D **); //по указаному адресу будут записаны все указатели на объекты в комнате
	void getAllLights(LightSource **); //по указаному адресу будут записаны все указатели на источники света в комнате
	void getAllPortals(Portal **); //по указаному адресу будут записаны все указатели на порталы в комнате
	void addObject3D(StorageIndex);
	void addMovableObject(StorageIndex);
	void addNPC(StorageIndex);
	void addLightSource(StorageIndex);
	void addPortal(StorageIndex);
	float &ambientPower(){ return ambient_power;}//дефолтный уровень освещенности
};
#endif


