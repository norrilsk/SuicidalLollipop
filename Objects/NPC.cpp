#include "NPC.hpp"



NPC::NPC()
{
	physical_properties.m = 25;
}

NPC::~NPC()
{
}

NPC::NPC(Model *mash) : MovableObject(mash)
{
	physical_properties.m = 25;
}
