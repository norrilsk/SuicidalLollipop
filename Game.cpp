#include "Game.hpp"
Game :: Game()
{	
}

void Game :: next(unsigned int dt)
{
	GameTime += dt;
	Gl :: keyboard.update();
	glm :: dvec3 move(0, 0, 0);
	if(Gl::keyboard[SDL_SCANCODE_W])
	{
		move += glm :: dvec3(10.0 * dt / 1000.0, 0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_S])
	{
		move += glm :: dvec3(-10.0 * dt / 1000.0, 0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_A])
	{
		move += glm :: dvec3(0, 10.0 * dt / 1000.0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_D])
	{
		move += glm :: dvec3(0, -10.0 * dt / 1000.0, 0);
	}
	if(Gl::keyboard[SDL_SCANCODE_ESCAPE])
	{
		Gl::Quit();
	}
	player.moveRelative(move);
}

void Game :: setCamera()
{
	Gl :: camera.set(player.getPosition() + glm :: dvec3(0, 0, -10), player.getLookDirection(), player.getUpperDirection());
}

Game :: ~Game()
{
}
