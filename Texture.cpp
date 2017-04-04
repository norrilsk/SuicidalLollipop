#include "Texture.hpp"
#include "Loger.hpp"

extern Loger logfile;

Texture::Texture()
{
}
Texture::Texture(const char* path)
{
	loadTexture(path);
}
void Texture::loadTexture(const char* path)
{
	image = IMG_Load(path); //  ��������� ��������
	isloaded = true;
	if (image== NULL) 
	{
		logfile << "IMG_Load: " << IMG_GetError() << std::endl;
		isloaded = false;
	}
	if (!isloaded)
		throw(newError(BINDING_UNLOADED));

	glGenTextures(1,&id);
	glBindTexture(GL_TEXTURE_2D, id);

	GLuint Mode = GL_RGB;
	if (image->format->BytesPerPixel == 4)  // ���� ���� ������������, ������� ��
		Mode = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode,
	             GL_UNSIGNED_BYTE, image->pixels); // �������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // ���� ���������� ���������� ������� ��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	                GL_LINEAR_MIPMAP_LINEAR);   // ��������� ��������� ������� � ������� �����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D); // ����������� �������� �������� �������
}
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture()
{
}

void Texture::freeTexture()
{
	glDeleteTextures(1, &id);
}
