#ifndef _GAME
#define _GAME
#include "Objects/Objects.hpp"
#include "GLfunc.hpp"
class Game
{
	Player player;
	unsigned long long GameTime = 0;
	void checkKeyboard(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события клавиатурры
	void checkMouse(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события мыши
	public:
	void next(unsigned int dt);// произвести все основные игровые операции. Параметр - время с момента предыдущего запуска
	void setCamera();//устанавливаем необходимое положение камеры
	Game();
	~Game();
};

#endif
