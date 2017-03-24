#ifndef _GAME
#define _GAME
#include "Objects/Objects.hpp"
#include "GLfunc.hpp"
#include <vector>
class Game
{
	enum GAME_STATE
	{
		NORMAL,
		PAUSED
	}game_state = NORMAL;
	Player player;
	std::vector<NPC> npc;// 
	unsigned long long GameTime = 0;
	void checkKeyboard(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события клавиатурры
	void checkMouse(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события мыши
	void normal_next(unsigned int dt);//в случае если игра идет в нормальном режиме
	void paused_next(unsigned int dt);//в случае если игра приостановлена
public:
	void start();
	void next(unsigned int dt);// произвести все основные игровые операции. Параметр - время с момента предыдущего запуска
	void setCamera();//устанавливаем необходимое положение камеры
	void pause(); //приостановить игру
	void goon(); //продолжить игру
	Game();
	~Game();
};

#endif
