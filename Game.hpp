#ifndef _GAME
#define _GAME
#include "Objects/Objects.hpp"
#include "GameTemplate.hpp"
#include "GameEngine.hpp"
#include "Timer.hpp"
#include <vector>
class Game : public GameTemplate
{
	enum GAME_STATE
	{
		NORMAL,
		PAUSED
	}game_state = NORMAL;
	Player player;
	double GameTime = 0;
	Timer timer;
	void checkKeyboard(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события клавиатурры
	void checkMouse(glm::dvec3& playerMovement, glm::dvec3& playerRotation);//обрабатываем события мыши
	void normal_next(double);//в случае если игра идет в нормальном режиме
	void paused_next(double);//в случае если игра приостановлена
public:
	void start() override;
	void next() override;// произвести все основные игровые операции. Параметр - время с момента предыдущего запуска
	void focusLost() override; //приостановить игру
	void focusGained() override; //продолжить игру
	Game();
	~Game();
};

#endif
