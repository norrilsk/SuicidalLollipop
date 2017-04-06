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
public:
	bool is_drawable() { return drawable; }//  Рисуем ли я? Ж)
	bool is_textures() { return !((itexture == false) || (!drawable)); } // есть ли текстуры
	bool is_normals() { return drawable && inormals; } // есть ли нормали
	void draw(Texture* = nullptr); // Нарисовать меня
	void parser(const std::string&); // создает объект из obj файла, передать путь к obj файлу
	MashObject();
	MashObject(const std::string&);
	MashObject(const MashObject &);

	~MashObject();
};

#endif