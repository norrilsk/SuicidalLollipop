#include "Game.hpp"

Game :: Game()
{	
}

void Game :: checkKeyboard(glm::dvec3& playerMovement, glm::dvec3& playerRotation)
{
	Gl :: keyboard.update();
	if(Gl::keyboard[SDL_SCANCODE_W])
	{
		playerMovement += glm :: dvec3(10.0 , 0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_S])
	{
		playerMovement += glm :: dvec3(-10.0, 0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_A])
	{
		playerMovement += glm :: dvec3(0, 10.0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_D])
	{
		playerMovement += glm :: dvec3(0, -10.0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_UP])
	{
		playerRotation += glm :: dvec3(0, -1, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_DOWN])
	{
		playerRotation += glm :: dvec3(0, 1, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_LEFT])
	{
		playerRotation += glm :: dvec3(0, 0, 1);
	}
	if(Gl::keyboard[SDL_SCANCODE_RIGHT])
	{
		playerRotation += glm :: dvec3(0, 0, -1);
	}
	if(Gl::keyboard[SDL_SCANCODE_ESCAPE])
	{
		Gl::Quit();
	}
}

void Game :: checkMouse(glm::dvec3& playerMovement, glm::dvec3& playerRotation)
{
	glm::dvec2 mouseMotion = Gl :: mouse.getMovement();
	if(glm::length(mouseMotion) > 1e-9)//если курсор сместился
	{
		glm::dvec3 omega(0, mouseMotion.y, -mouseMotion.x); //переход от экранных координат к собственным с поворотом на 90 градусов по часовой
		omega *= 1.0; //модуль угловой скорости
		playerRotation += omega;
	}
}
void Game::start()
{
	StorageIndex room = Gl::storage.addRoom("Source/Room0.txt");
	player.setRoom(room);
	StorageIndex npc = Gl ::storage.addNPC("Source/SnowMan.txt");
	Gl::storage.room(room).addNPC(npc);
}
void Game :: normal_next(unsigned int dt)
{
	GameTime += dt;
	glm::dvec3 playerMovement(0, 0, 0);//движение игрока
	glm::dvec3 playerRotation(0, 0, 0);//угловая скорость игрока
	checkKeyboard(playerMovement, playerRotation);//проверяем устройства ввода-вывода
	checkMouse(playerMovement, playerRotation);
	Gl :: mouse.centre();
	player.moveRelative(0.2*playerMovement*(dt/1000.0));//и двигаем игрока
	player.rotateRelative(glm::dvec3(0, playerRotation.y, 0), (dt/1000.0));
	player.rotateAbsolute(glm::dvec3(0, 0,  playerRotation.z), (dt/1000.0));
}

void Game :: paused_next(unsigned int dt)
{	
}

void Game :: next(unsigned int dt)
{
	switch(game_state)
	{
	case NORMAL:
		normal_next(dt);
		break;
	case PAUSED:
		paused_next(dt);
		break;
	}
	std::vector<DrawableObject *> to_render;
	Gl::storage.room(player.getRoom()).getAllObjects(to_render);
	for(DrawableObject * obj: to_render)
		Gl::renderingQueue.push(obj);
	Gl::renderingQueue.push(&Gl::storage.room(player.getRoom()));
}
 
void Game::pause()
{
	game_state = PAUSED;
}
 
void Game::goon()
{
	game_state = NORMAL;
}

void Game :: setCamera()
{
	Gl :: camera.set(player.getPosition() + glm :: dvec3(0, 0, 0), player.getLookDirection(), player.getUpperDirection());
}

Game :: ~Game()
{
}
