#ifndef _MODEL
#define _MODEL


#include <vector>
#include <glm/glm.hpp>
#include "../Texture.hpp"
#include "MashObject.hpp"

class Model
{
	std::vector <Texture> textures; //массив текстур
	std::vector <MashObject> mash; //массив меш-обектов
	int activeMash =-1; // индексы в этих масивах
	int activeTexture =-1;
	void addMash(const std::string &); //добавляем меш
	void addTexture(const std::string &); //добавляем текстуру
public:
	Model(){};
	~Model(){};
	Model(const std::string &); //парсерим файл, из которого получаем текстуры и меши
	void setActiveTexture(int ind); //возвкащаем индексы
	void setActiveMash(int ind);
	double getR(); // Возвращает радиус описаной сферы
	glm::dvec4 getMaxBoxVertex();// возвращает координаты угла Коробки
	glm::dvec4 getMinBoxVertex();// возвращает координаты второго угла коробки
	glm::dvec3 getSphereCenter();// возвращает координаты 
	std::vector< glm::vec3 >& get_vertices() { return mash[activeMash].get_vertices(); }
	glm::dvec4* getBox() { return mash[activeMash].getBox(); }
	bool is_drawable();//рисуемо ли?
	bool is_textures();//есть ли текстуры?

	void draw();//отрисовать
};


#endif
