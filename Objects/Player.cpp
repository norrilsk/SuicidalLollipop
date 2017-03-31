#include "Player.hpp"

Player::Player()
{
}


Player::~Player()
{
}



StorageIndex Player::getRoom()
{
	return current_room;
}

void Player::setRoom(StorageIndex ind)
{
	current_room = ind;
}

