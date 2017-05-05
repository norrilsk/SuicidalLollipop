#ifndef _GAMEENGINE
#define _GAMEENGINE

#include <memory>
#include "Camera.hpp"
#include "GraphicEngine.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Storage.hpp"
#include "GameTemplate.hpp"

class GameEngine
{
	std::unique_ptr<Camera> camera; //Камера
	std::unique_ptr<GraphicEngine> grapher; //Графический движек
	std::unique_ptr<Mouse> mouse; //Мышка
	std::unique_ptr<Keyboard> keyboard; //Клавиатура
	std::unique_ptr<Storage> storage; //хранилище для всех объектов
	Loger logfile; //Лог
	GameTemplate * game; //Класс game методы которого будут вызываться
	void logTrouble(Error &);
	void MainLoop();
public:
	GameEngine(int, char **);
	void start(GameTemplate *); //Запуск игры
	void renderScene();//Отрисовка трехмерной сцены (Не забудьте установить камеру)
	void loadWorld(const char * path);//загрузка всей информации о мире
	void display(); //Выполнить отрисовку (лучше исползовать renderScene)
	void Quit(); //выйти из игры
	~GameEngine();
};


#endif
