#ifndef _SHADER
#define _SHADER
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#define _GLheader
#ifdef _WIN32
#include <Windows.h>
#endif
#ifndef _GLEWINCLUDE
#define _GLEWINCLUDE
#include <GL/glew.h>
#include <GL/glu.h>
#endif
#include<glm/glm.hpp>
struct shader_data
{
public:
	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 MVP;
	glm::mat4 MV;
	glm::vec4 CameraPos;
	glm::vec4 CameraLook;
	glm::vec4 LightPosition_worldspace[100];
	glm::vec4 LightColor[100];
	glm::vec4 LightDirection[100];
	glm::vec4 external_portals[300];//координаты + нормаль к порталам в другие комнаты
	glm::vec4 internal_portals[300];//координаты + нормаль к своим порталам
	float LightPower[100];
	float cos_angle[100];
	float ambient_power;
	unsigned int number_of_external_portals;
	unsigned int number_of_internal_portals;
	unsigned int number_of_lights;
	unsigned int textures_enabled; //флаги
	unsigned int source_type[100];//   0-конус 1 - точечный 2 - плоский
};
class Shaders
{
	std::map<GLuint, GLuint> shaderid; // Карта соответствия между типо шейдера в GL и ID шейдера
	GLuint programid; // ID программы
	GLuint ssbo;
	std::vector<GLuint> type; // вектор типов всех существующих щейдеров
	 int ssboBindingPoint = -1;
public:
	/*Загрузка Шейдеров
	1й элемент пары - путь к программе шейдера
	2й элемент пары - тип шейдера GL */
	void Load(std::vector<std::pair<std::string, GLuint> >& ShadersPaths, int =-1);
	GLuint Id(GLuint shaderType) { return shaderid.at(shaderType); } // возвращает ID по указанному типу шейдера
	Shaders(std::vector<std::pair<std::string, GLuint> >& shaderPaths, int   = -1); // аналогично LOAD
	void ssboUpdate(shader_data*);
	void useProgram() { glUseProgram(programid); };
	void setTextureSampler(int); //устанавливает текстурный  шаблон
	void store(int num, const char *name);
	void store(float num, const char *name);
	void store(glm::vec3 vec, const char *name);
	Shaders();
	~Shaders();
};
#endif