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
//	Texture *texture = nullptr;
	std::string path = ""; //Путь объекта
	std::vector < glm::vec3 >  vertices; // координаты вершины
	std::vector < glm::vec2 >  uvs; //текстурная координата вершины
	std::vector < glm::vec3 >  normals;// координаты нормали
	std::vector <glm::vec3 > verColor;// цвета вершин, возможно временно
	std::vector <GLuint> vbo;
	GLuint vao = 0;
	bool drawable = false;
	bool itexture = false;
	bool inormals = false;
public:
	bool is_drawable() { return drawable; }//  Рисуем ли я? Ж)
	bool is_textures() { return !((itexture == false) || (!drawable)); } // есть ли текстуры
	bool is_normals() { return drawable && inormals; } // есть ли нормали
	void bind();// биндим мэш обЪект
	void draw(Texture* = nullptr); // Нарисовать меня
	void parser(const std::string&); // создает объект из obj файла, передать путь к obj файлу
	MashObject();
	MashObject(const std::string&);

	~MashObject();
};

#endif