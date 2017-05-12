#ifndef _PHYSICALENGINE
#define _PHYSICALENGINE
#include <stack>
#include <vector>
#include<glm/glm.hpp>
class Object3D;
class MovableObject;
class Room;
class PhysicalEngine
{
private:
	double g = 9.8;
	bool physics = false;
	Room* room =nullptr;
	std::vector<MovableObject*> agents;
	std::vector<Object3D*> targets;
	std::stack<std::pair<Object3D*, MovableObject*>> collidingObjects;

	void CheckCollisions();
	glm::dvec3 box_sphere(glm::dvec3*, glm::dvec3, double R);
public:	
	void ApplyPhysics(double dt);
	PhysicalEngine(Room* _room) :room(_room) {};
	void setRoom(Room*_room) { room = _room; }
	PhysicalEngine();
	void setg(double G) { g = G; }
	double getg() { return g; }
	void setPhysics(bool ph) { physics = ph; }
	~PhysicalEngine();
};
#endif
