#ifndef _STORAGE
#define _STORAGE

#include <vector>
#include <map>

typedef size_t StorageIndex;

class Room;
class NPC;
class MovableObject;
class Object3D;
class Model;
class DrawableObject;
class SDLTexture;
class SDL_Renderer;

class Storage
{
	std::vector <Room> rooms;
	std::vector <NPC> npcs;
	std::vector <MovableObject>  movable_objects;
	std::vector <Object3D>  objects3d;
	std::vector <SDLTexture> sdl_textures;
	std::map <std::string, Model> model;
public:
	Storage();
	~Storage();
	StorageIndex addNPC(const std::string &);
	StorageIndex addSDLTexture(SDL_Renderer*, const std::string &);
	StorageIndex addObject3D  (const std::string &);
	StorageIndex addMovableObject (const std::string &);
	StorageIndex addRoom (const std::string &);
	NPC& npc(StorageIndex);
	Object3D& object3d(StorageIndex);
	Room& room (StorageIndex);
	MovableObject& movableObject(StorageIndex);
	SDLTexture& sdlTexture(StorageIndex);
};


#endif
