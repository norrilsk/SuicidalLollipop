#include "Objects/Portal.hpp"
#include "Game.hpp"
const double PI = 3.14159265359;

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
	game_engine ->loadWorld("Source/World.txt");
	player.setRoom(storage->indexOf("firstRoom"));
	player.set(glm::dvec3(1.0, -1.0, 1.8), glm::dvec3(1.0, -1.0, 0.0),glm::dvec3(0.0,0.0,0.1));
	//storage->movableObject("Soccer_ball").set(glm::dvec3(3.0, 2.0, 1.7), glm::dvec3(1.0, -1.0, 0.0), glm::dvec3(0.0, 0.0, 0.1));
	std::vector<glm::dvec3> coord = {glm::dvec3(1.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0), glm::dvec3(-1, 0.0, -1)};
	Portal p1, p2;
	p1.createPottal(3, coord.data(), storage->indexOf("firstRoom"));
	coord = {glm::dvec3(0.5*1.4142135, 0.5*1.4142135, 0.0), glm::dvec3(0.0, 0.0, 1.0), glm::dvec3(-0.5*1.4142135, -0.5*1.4142135, -1)};
	p2.createPottal(3, coord.data(), storage->indexOf("firstRoom"));
	p1.linkToPortal(p2);
	timer.restart();
}
void Game :: normal_next(double dt)
{
	GameTime += dt;
	storage ->npc("Kolya").moveAbsolute(glm::dvec3(0, 0, 0.003*sin(2*GameTime)));
	if(GameTime > temp)
	{
		++temp;
		storage -> movableObject("cube1").rotateAbsolute(glm::dvec3(0, 0, PI/8));
	}
	glm::dvec3 playerMovement(0, 0, 0);//движение игрока
	glm::dvec3 playerRotation(0, 0, 0);//угловая скорость игрока
	checkKeyboard(playerMovement, playerRotation);//проверяем устройства ввода-вывода
	checkMouse(playerMovement, playerRotation);
	mouse -> centre();
	player.moveRelative(0.2*playerMovement*dt);//и двигаем игрока
	player.rotateRelative(glm::dvec3(0, playerRotation.y, 0)*(dt));
	player.rotateAbsolute(glm::dvec3(0, 0,  playerRotation.z)*(dt));
	glm::dvec3 crd = player.getPosition() - glm::dvec3(0.001, 0.003, 0.003);
	/*storage->movableObject("Soccer_ball").moveRelative(0.2*playerMovement*dt);
	storage->movableObject("Soccer_ball").rotateRelative(glm::dvec3(0, playerRotation.y, 0)*(dt));
	storage->movableObject("Soccer_ball").rotateAbsolute(glm::dvec3(0, 0, playerRotation.z)*(dt));*/
	storage->movableObject("Soccer_ball").set(player.getPosition() + player.getLookDirection()*4.0 + glm::cross(player.getLookDirection(), player.getUpperDirection()));
	Room &room = storage->room("firstRoom");
	room.setPhysics(true, 9.2);
	room.ApplyPhysics(dt);
	

}

void Game :: paused_next(double dt)
{	
}

void Game :: next()
{
	camera -> set(player.getPosition(), player.getLookDirection(), player.getUpperDirection()); //устанавливаем камеру
	camera -> setRoom(player.getRoom());
	game_engine -> renderScene(); //и отрисовываем все;
	
	double dt;
	while ((dt = timer.count()) < 0.016667)
	{

	}
	std::cout << 1 / dt << std::endl;
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
	mouse ->centre();
}
