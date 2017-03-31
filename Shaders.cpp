#include "Shaders.hpp"
#include"Error.hpp"


Shaders::Shaders()
{
}

Shaders::Shaders(std::vector<std::pair<std::string, GLuint> >& shaderPaths)
{
	Load(shaderPaths);
}

void Shaders::Load(std::vector<std::pair<std::string, GLuint> >& shaderPaths)
{
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
			throw(newError(SHADER));
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
		throw(newError(SHADER));
	//GLuint colour_loc = glGetUniformLocation(programid, "inputColour");
	glUseProgram(programid); ////add, CHECK
	//glUniform4f(colour_loc, 1.0f, 0.0f, 0.0f, 1.0f);

	for (GLuint shaderType : type)
	{
		glDeleteShader(shaderid[shaderType]); // удаляем шйдеры (все легально)
	}
}
void Shaders::store_MVP(void* src)
{
	GLint matrix = glGetUniformLocation(programid, "MVP"); // создаем ID для матрицы
	glUniformMatrix4fv(matrix, 1, GL_FALSE, (const GLfloat *)src); // информируем шейдер о нашей матрице
}
Shaders::~Shaders()
{
}
