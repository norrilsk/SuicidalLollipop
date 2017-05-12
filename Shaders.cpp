#include "Shaders.hpp"
#include"Error.hpp"
#include "Loger.hpp"
#include <cstring>

extern Loger logfile;
Shaders::Shaders()
{
}

Shaders::Shaders(std::vector<std::pair<std::string, GLuint> >& shaderPaths, int ssbobindingpoint)
{
	Load(shaderPaths, ssbobindingpoint);
}

void Shaders::Load(std::vector<std::pair<std::string, GLuint> >& shaderPaths, int ssbobindingpoint)
{
	ssboBindingPoint = ssbobindingpoint;
	for (std::pair<std::string, GLuint> shader : shaderPaths)
	{
		std::ifstream in(shader.first); //файл шейдера
		if (!in.is_open())
			throw(newError(SHADER));
		in.seekg(0, in.end);// перейдем в конец файла
		unsigned int lenght = (unsigned int)in.tellg();// на какой мы позиции?
		in.seekg(0, in.beg);
		char* fileData = new char[lenght + 1];
		in.read(fileData, lenght); // считываем файл в 1 строку
		fileData[lenght] = '\0';
		in.close();
		shaderid[shader.second] = glCreateShader(shader.second);//создаем шейдер
		if (shaderid[shader.second] == 0)
			throw(newError(SHADER));
		glShaderSource(shaderid[shader.second], 1, (const char **)&fileData, nullptr);// 1- количество сток
		glCompileShader(shaderid[shader.second]);// скомпилируем шейдер
		GLint status;
		glGetShaderiv(shaderid[shader.second], GL_COMPILE_STATUS, &status);// проверим компиляцию
		if (status == GL_FALSE)
		{
			GLchar forlog[2048];
			glGetShaderInfoLog(shaderid[shader.second], 2048, nullptr, forlog);
			throw(newError2(SHADER, std::string(forlog) + "\n" + shader.first));
		}
		type.push_back(shader.second);
	}
	programid = glCreateProgram();// связать программу щейдера с ID
	for (GLuint shaderType : type)
	{
		glAttachShader(programid, shaderid[shaderType]); // привязываем шейдеры
	}
	glLinkProgram(programid);// линкуем программу щейдеров
	GLint status;
	glGetProgramiv(programid, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLchar forlog[2048];
		glGetProgramInfoLog(programid,2048,nullptr,forlog);
		throw(newError2(SHADER, std::string(forlog) + "\n"));
	}
	if (ssbobindingpoint > -1)
	{
		glGenBuffers(1, &ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ssbobindingpoint, ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(shader_data), nullptr, GL_STREAM_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	
	glUseProgram(programid); ////add, CHECK
							 //glUniform4f(colour_loc, 1.0f, 0.0f, 0.0f, 1.0f);

	for (GLuint shaderType : type)
	{
		glDeleteShader(shaderid[shaderType]); // удаляем шйдеры (все легально)
	}
}

void Shaders::ssboUpdate(shader_data* data)
{
	if (ssboBindingPoint < 0)
		return;
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);

	memcpy(p, data, sizeof(struct shader_data));
	//	((shader_data *)p)->LightPosition_worldspace[1] = glm::vec3(1, 1, 1);
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void Shaders::setTextureSampler(int sampler)
{
	GLuint ID = glGetUniformLocation(programid, "textureSampler");
	glUniform1i(ID, sampler);
}
Shaders::~Shaders()
{
}
void Shaders::store(int num, const char *name)
{
	GLint ID = glGetUniformLocation(programid, name);
	glUniform1i(ID, num); // информируем шейдер о нашем числе
}


void Shaders::store(glm::vec3 vec, const char *name)
{
	GLint ID = glGetUniformLocation(programid, name);
	glUniform3f(ID, vec.x, vec.y, vec.z); // информируем шейдер о нашем векторе
}

void Shaders::store(float num, const char *name)
{
	GLint ID = glGetUniformLocation(programid, name);

	glUniform1f(ID, num); // информируем шейдер о нашем числе
}