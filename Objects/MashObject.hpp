#ifndef _MASHOBJECT
#define _MASHOBJECT
#include<vector>
#include<string>
#include<glm/vec3.hpp>
#include<glm/vec2.hpp>
#include<fstream>
#ifdef _WIN32
#include <Windows.h>
#endif
#ifndef _GLEWINCLUDE
#define _GLEWINCLUDE
#include <GL/glew.h>
#include <GL/glu.h>
#endif 
#include "../Texture.hpp"
#include<glm/glm.hpp>
/* TODO:
На данном этапе не способен определять тип ошибки, планируется добавление в дальнейшем
*/
class MashObject 
{
private:
	std::vector <GLuint> vbo;
	std::vector < glm::vec3 >  vertices; // координаты вершин
	GLuint vao = 0;
	bool drawable = false;
	bool itexture = false;
	bool inormals = false;
	bool *deletable;
	double R = 0;// Радиус окружающей сферы;
	glm::dvec3 Center;// Центер окружающей сферы
	glm::dvec3 maxCoord = glm::dvec3(-DBL_MAX, -DBL_MAX, -DBL_MAX); // углы коробки
	glm::dvec3 minCoord = glm::dvec3(DBL_MAX, DBL_MAX, DBL_MAX);
	glm::dvec4 box[8];
public:
	bool is_drawable() { return drawable; }//  Рисуем ли я? Ж)
	bool is_textures() { return !((itexture == false) || (!drawable)); } // есть ли текстуры
	bool is_normals() { return drawable && inormals; } // есть ли нормали
	std::vector< glm::vec3 >& get_vertices() { return vertices; }
	void draw(Texture* = nullptr); // Нарисовать меня
	void parser(const std::string&); // создает объект из obj файла, передать путь к obj файлу
	double getR() { return R; }
	glm::dvec4 getMaxBoxVertex() { return glm::dvec4(maxCoord, 1); }
	glm::dvec4 getMinBoxVertex() { return glm::dvec4(minCoord, 1); }
	glm::dvec4* getBox(){ if (maxCoord == glm::dvec3(-DBL_MAX, -DBL_MAX, -DBL_MAX))  return nullptr; else return &box[0]; }
	glm::dvec3 getSphereCenter();

	MashObject();
	MashObject(const std::string&);
	MashObject(const MashObject &);

	~MashObject();
};

#endif