#ifndef _STORAGE
#define _STORAGE

#include <vector>
#include <map>
#include <unordered_map>

typedef size_t StorageIndex;

class Room;
class NPC;
class MovableObject;
class Object3D;
class Model;
class DrawableObject;
class SDLTexture;
struct SDL_Renderer;

class Storage
{
	const int NumberOfTypes = 5;//количество типов с которыми работает хранилище
	const int RoomInd = 0;//их индексы
	const int NPCInd = 1;
	const int MovableObjectInd = 2;
	const int Object3DInd = 3;
	const int SDLTextureInd = 4;
	std::vector <Room> rooms;//контейнеры для элементов
	std::vector <NPC> npcs;
	std::vector <MovableObject>  movable_objects;
	std::vector <Object3D>  objects3d;
	std::vector <SDLTexture> sdl_textures;
	std::map <std::string, Model> model;//контейнер моделей
	std::unordered_map <std::string, StorageIndex> nick_names;//контейнер псевдонимов
public:
	Storage();
	~Storage();

	StorageIndex addNPC(const std::string &);//добавление объекта в хранилище
	StorageIndex addSDLTexture(SDL_Renderer*, const std::string &);
	StorageIndex addObject3D  (const std::string &);
	StorageIndex addMovableObject (const std::string &);
	StorageIndex addRoom (const std::string &);
	StorageIndex indexOf(const std::string &);//получение индекса по псевдониму
	void create_nickname(const std::string &, StorageIndex);//создать псевдоним ВНИМАНИЕ при повторном создании псевдонима перезапись
	void loadWorld(const char *);//загрузить мир из файла (аргумент - путь)
	NPC& npc(StorageIndex);//доступ к элементам хранилища
	NPC& npc(const std::string &);
	Object3D& object3d(StorageIndex);
	Object3D& object3d(const std::string &);
	Room& room (StorageIndex);
	Room& room (const std::string &);
	MovableObject& movableObject(StorageIndex);
	MovableObject& movableObject(const std::string &);
	SDLTexture& sdlTexture(StorageIndex);
	SDLTexture& sdlTexture(const std::string &);
};


#endif
