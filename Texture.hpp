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
public:
	Texture();
	Texture(const char * path); // вызывает loadTexture
	/* пожадуйста до бинда включите нужный вам VBO с помощью   glBindBuffer 
	bind */
	void bind(); // биндит текстурку 
	~Texture();
	bool is_loaded() { return isloaded; } // я загружена?
	void loadTexture(const char * path);// Загрузка Текстуры
	void freeTexture(); //удаление текстуры
};
#endif;
