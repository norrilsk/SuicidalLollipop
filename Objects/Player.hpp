#ifndef _PLAYER
#define _PLAYER
#include "MovableObject.hpp"
#include "Room.hpp"
#include "../Storage.hpp"

class Player : public MovableObject
{
	StorageIndex current_room;
public:
	Player();
	~Player();
	void setRoom(StorageIndex);
	StorageIndex getRoom();
};
#endif
