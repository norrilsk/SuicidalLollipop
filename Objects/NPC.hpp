#ifndef _NPC
#define _NPC
#include "MovableObject.hpp"
class NPC :
	public MovableObject
{
public:
	NPC();
	NPC(MashObject* mash);
	~NPC();
};
#endif
