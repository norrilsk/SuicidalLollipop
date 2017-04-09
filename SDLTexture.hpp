#ifndef _SDLTEXTURE
#define _SDLTEXTURE

#include <SDL2/SDL.h>

class SDLTexture
{
	SDL_Texture* texture = nullptr;
	int w = 0;
	int h = 0;
	SDL_Renderer * renderer= nullptr;
	bool *deletable;

	bool is_drawable();
public:
	SDLTexture();
	SDLTexture(SDL_Renderer*, const char *);
	SDLTexture(const SDLTexture &);
	int width() {return w;}
	int hight() {return h;}
	void draw(int x, int y);
	void draw(int x, int y, int w, int h);
	void load(SDL_Renderer*, const char *);
	~SDLTexture();
};


#endif
