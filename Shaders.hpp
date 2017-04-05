#ifndef _SHADER
#define _SHADER
#include <string>
#include <fstream>
#include <vector>
#include <map>
#define _GLheader
#ifdef _WIN32
#include <Windows.h>
#endif
#ifndef _GLEWINCLUDE
#define _GLEWINCLUDE
#include <GL/glew.h>
#include <GL/glu.h>
#endif

enum integerName
{
	TEXTURES_ENABLED,
	NORMALS_ENABLED,
	TEXTURE_SAMPLER
};

class Shaders
{
	std::map<GLuint,GLuint> shaderid; // Карта соответствия между типо шейдера в GL и ID шейдера
	GLuint programid; // ID программы
	std::vector<GLuint> type; // вектор типов всех существующих щейдеров

public:
	/*Загрузка Шейдеров
	1й элемент пары - путь к программе шейдера
	2й элемент пары - тип шейдера GL */
	void Load(std::vector<std::pair<std::string, GLuint> >& ShadersPaths); 
	GLuint Id(GLuint shaderType) { return shaderid.at(shaderType); } // возвращает ID по указанному типу шейдера
	Shaders(std::vector<std::pair<std::string, GLuint> >& shaderPaths); // аналогично LOAD
	void store_MVP(void*); // Сохраняет матрицу MVP
	void store_int(int,integerName); //сохраняет числа в шейдеры
	void useProgram() { glUseProgram(programid); };
	Shaders();
	~Shaders();
};
#endif
