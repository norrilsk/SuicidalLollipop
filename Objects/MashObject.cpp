#include "MashObject.hpp"
#include <glm/glm.hpp>
#include"../GLfunc.hpp"
void MashObject::parser(const std::string& file_path)
{
	itexture = true;
	inormals = true;
	path = file_path; // Открываем obj файл
	std::ifstream forread;
	forread.open(file_path);
	if (!forread.is_open())
		return;
	std::vector < glm::vec3 >  time_vertices; // координаты вершины
	std::vector < glm::vec2 >  time_uvs; //текстурная координата вершины
	std::vector < glm::vec3 >  time_normals;// координаты нормали
	std::vector <long int > time_vertexIndices, time_uvIndices, time_normalIndices; // идексы координат, текстур, нормалей
	long int vertexindex, uvindex, normalindex;
	std::string lineHeader = ""; //строка в которую будем счтьывать	
	while (!forread.eof())  // парсим файл
	{
		forread >> lineHeader;
		if (lineHeader == "v") //координаты верщины
		{
			glm::vec3 vertex; // временный вектор координаты вершины
			forread >> vertex.x >> vertex.y >> vertex.z;
			time_vertices.push_back(vertex);
			continue;
		}
		if (lineHeader == "vt") // текстурная координата вершины
		{
			glm::vec2 uv; // временный вектор текстуры
			forread >> uv.x >> uv.y;
			time_uvs.push_back(uv);
			continue;
		}
		if (lineHeader == "vn") // вектор нормали
		{
			glm::vec3 normal;// временный вектор нормали
			forread >> normal.x >> normal.y >> normal.z;
			time_normals.push_back(normal);
			continue;
		}
		if (lineHeader == "f")
		{
			size_t stringsize;
			for (int s = 0; s < 3; s++)
			{
				std::string VTN[3];// вершина, текстура , нормаль
				forread >> lineHeader;
				stringsize = lineHeader.length();
				size_t i = 0;
				while (lineHeader[i] != '/')
				{
					VTN[0].push_back(lineHeader[i]);
					i++;
				}
				i++;
				int j = 0;
				while (lineHeader[i] != '/')
				{
					VTN[1].push_back(lineHeader[i]);
					j++;
					i++;
				}
				i++;
				j = 0;
				while (i < stringsize)
				{
					VTN[2].push_back(lineHeader[i]);
					j++;
					i++;
				}

				vertexindex = strtol(VTN[0].c_str(), NULL, 10);
				if (vertexindex == 0)
					return;
				uvindex = strtol(VTN[1].c_str(), NULL, 10);
				if (uvindex == 0)
					itexture = false;
				normalindex = strtol(VTN[2].c_str(), NULL, 10);
				if (normalindex == 0)
					inormals = false;
				time_vertexIndices.push_back(vertexindex);
				time_uvIndices.push_back(uvindex);
				time_normalIndices.push_back(normalindex);

			}

		}

	}

	forread.close();
	size_t VerSize = time_vertexIndices.size();
	for (unsigned int i = 0; i < VerSize; i++) // обрабатываем считанные данные
	{
		vertexindex = time_vertexIndices[i];
		glm::vec3 vertex = time_vertices[vertexindex - 1];
		glm::vec3 vcolor;////////time color 
		vcolor.x = 1.0f;
		vcolor.y = 0.7f;
		vcolor.z = (float)(0.3f + (0.4 * rand()) / RAND_MAX);
		verColor.push_back(vcolor);//end time color
		vertices.push_back(vertex);
		uvindex = time_uvIndices[i];
		if (uvindex != 0)
		{
			glm::vec2 uv = time_uvs[uvindex - 1];
			uvs.push_back(uv);
		}
		normalindex = time_normalIndices[i];
		if (normalindex != 0)
		{
			glm::vec3 normal = time_normals[normalindex - 1];
			normals.push_back(normal);
		}

	}
	bind();
}
void MashObject::bind()
{
	// Сначала генерируем OpenGL буфер и сохраняем указатель на него в vertexbuffer
	vbo.resize(2); // устанавливаем количество VBO
	glGenBuffers(2, &vbo[0]);
	// Биндим буфер
	glGenTextures(textureNum, textureArray); // TODO :: (glDeleteTextures(texturesNum, textureArray));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	
	// Предоставляем наши вершины в OpenG
	glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	if (!is_textures())
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*verColor.size(), &verColor[0], GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*uvs.size(), &uvs[0], GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao); // создать VAO
	glBindVertexArray(vao);// Bind VAO


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO

	if ((itexture == false) || (texture ==NULL) || (texture->is_loaded() == false))
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO */
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		for (int i = 0; i < textureNum; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureArray[i]);
			texture->bind();// TODO:: texture[i]
		}

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO */
	}
	glBindVertexArray(0); // unbind VAO
	drawable = true;
	return;
}
void MashObject::draw()
{
	if (!drawable)
		return;
	glBindVertexArray(vao);
	
	glEnableVertexAttribArray(0);
	if (!is_textures())
		glEnableVertexAttribArray(1);
	else
		glEnableVertexAttribArray(2);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size()); //Начиная с вершины 0 и рисуем N штук. Всего => 1 треугольник

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	return;
}
void MashObject::loadTexture(Texture* texture_src)
{
	texture = texture_src;
}
MashObject::MashObject()
{
	
}
MashObject::MashObject(std::string& file_path, Texture * texture_src)
{
	parser(file_path);
	loadTexture(texture_src);
}

MashObject::MashObject(std::string& file_path)
{
	parser(file_path);
}
MashObject::~MashObject()
{

}
