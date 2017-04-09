#ifndef _GAMETMPLATE
#define _GAMETMPLATE

#include <cstddef>

class GameEngine;
class Keyboard;
class Mouse;
class Storage;
class Camera;

class GameTemplate
{
protected:
	GameEngine *game_engine = nullptr;
	Keyboard *keyboard = nullptr;
	Mouse *mouse = nullptr;
	Storage *storage = nullptr;
	Camera * camera = nullptr;
public:
	GameTemplate(){}
	virtual ~GameTemplate(){}
	virtual void start()= 0; //Вызывается в начале
	virtual void next() = 0; //Вызывается на каждом цикле игры
	virtual void focusLost() = 0; //Вызывается при потере фокуса (переключении приложения)
	virtual void focusGained() = 0;//вызывается при полученни фокуса
	void set_ptr(GameEngine *, Mouse*, Keyboard *, Storage *, Camera *); //Вызывается перед Start создавая инициализирует переменные
};


#endif
