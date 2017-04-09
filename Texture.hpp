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
	bool isloaded = 0;
	GLuint id;
	bool *deletable;
public:
	Texture();
	Texture(const char * path); // использует  loadTexture
	void bind(); // bind
	~Texture();
	bool is_loaded() { return isloaded; } // я загружена?
	void loadTexture(const char * path);// загружает текстуру, указать путь на картинку
	void freeTexture(); //удаляет текстуры
	Texture (const Texture &);
};
#endif