#ifndef _TEXTURE
#define _TEXTURE 
	#ifndef _GLEWINCLUDE
	#define _GLEWINCLUDE
	#include <GL/glew.h>
	#include <GL/glu.h>
	#endif
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>


class Texture
{
	SDL_Surface *image;
	bool isloaded = 0;
	GLuint id;
public:
	Texture();
	Texture(const char * path); // �������� loadTexture
	/* ���������� �� ����� �������� ������ ��� VBO � �������   glBindBuffer 
	bind */
	void bind(); // ������ ��������� 
	~Texture();
	bool is_loaded() { return isloaded; } // � ���������?
	void loadTexture(const char * path);// �������� ��������
	void freeTexture(); //�������� ��������
};
#endif
