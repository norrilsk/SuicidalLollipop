#ifndef _GAME
#define _GAME
#include "Objects/Objects.hpp"
#include "GLfunc.hpp"
#include <vector>
class Game
{
	Player player;
	std::vector<NPC> npc;// 
	unsigned long long GameTime = 0;
	void checkKeyboard(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события клавиатурры
	void checkMouse(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события мыши
public:
	void start();
	void next(unsigned int dt);// произвести все основные игровые операции. Параметр - время с момента предыдущего запуска
	void setCamera();//устанавливаем необходимое положение камеры
	Game();
	~Game();
};

#endif
