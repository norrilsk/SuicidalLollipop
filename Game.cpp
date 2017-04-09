#include "Game.hpp"

Game :: Game()
{	
}

void Game :: checkKeyboard(glm::dvec3& playerMovement, glm::dvec3& playerRotation)
{
	(*keyboard).update();
	if((*keyboard)[SDL_SCANCODE_W])
	{
		playerMovement += glm :: dvec3(10.0 , 0, 0);
	}
	if((*keyboard)[SDL_SCANCODE_S])
	{
		playerMovement += glm :: dvec3(-10.0, 0, 0);
	}
	if((*keyboard)[SDL_SCANCODE_A])
	{
		playerMovement += glm :: dvec3(0, 10.0, 0);
	}
	if((*keyboard)[SDL_SCANCODE_D])
	{
		playerMovement += glm :: dvec3(0, -10.0, 0);
	}
	if((*keyboard)[SDL_SCANCODE_UP])
	{
		playerRotation += glm :: dvec3(0, -1, 0);
	}
	if((*keyboard)[SDL_SCANCODE_DOWN])
	{
		playerRotation += glm :: dvec3(0, 1, 0);
	}
	if((*keyboard)[SDL_SCANCODE_LEFT])
	{
		playerRotation += glm :: dvec3(0, 0, 1);
	}
	if((*keyboard)[SDL_SCANCODE_RIGHT])
	{
		playerRotation += glm :: dvec3(0, 0, -1);
	}
	if((*keyboard)[SDL_SCANCODE_ESCAPE])
	{
		game_engine->Quit();
	}
}

void Game :: checkMouse(glm::dvec3& playerMovement, glm::dvec3& playerRotation)
{
	glm::dvec2 mouseMotion = mouse->getMovement();
	if(glm::length(mouseMotion) > 1e-9)//если курсор сместился
	{
		glm::dvec3 omega(0, mouseMotion.y, -mouseMotion.x); //переход от экранных координат к собственным с поворотом на 90 градусов по часовой
		omega *= 1.0; //модуль угловой скорости
		playerRotation += omega;
	}
}
void Game::start()
{
	StorageIndex room = storage -> addRoom("Source/Room0.txt");
	player.setRoom(room);
	StorageIndex npc = storage -> addNPC("Source/SnowMan.txt");
	storage -> room(room).addNPC(npc);
}
void Game :: normal_next(double dt)
{
	GameTime += dt;
	glm::dvec3 playerMovement(0, 0, 0);//движение игрока
	glm::dvec3 playerRotation(0, 0, 0);//угловая скорость игрока
	checkKeyboard(playerMovement, playerRotation);//проверяем устройства ввода-вывода
	checkMouse(playerMovement, playerRotation);
	mouse -> centre();
	player.moveRelative(playerMovement*dt);//и двигаем игрока
	player.rotateRelative(glm::dvec3(0, playerRotation.y, 0), (dt));
	player.rotateAbsolute(glm::dvec3(0, 0,  playerRotation.z), (dt));
}

void Game :: paused_next(double dt)
{	
}

void Game :: next()
{
	camera -> set(player.getPosition(), player.getLookDirection(), player.getUpperDirection()); //устанавливаем камеру
	camera -> setRoom(player.getRoom());
	game_engine -> renderScene(); //и отрисовываем все;

	double dt = timer.count();
	timer.restart();
	switch(game_state)
	{
	case NORMAL:
		normal_next(dt);
		break;
	case PAUSED:
		paused_next(dt);
		break;
	}
}

void Game::goon()
{
	game_state = NORMAL;
}


Game :: ~Game()
{
}

void Game::focusLost()
{
	game_state = PAUSED;
}

void Game::focusGained()
{
	game_state = NORMAL;
}
