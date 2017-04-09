#include <SDL2/SDL_image.h>
#include "SDLTexture.hpp"
#include "Error.hpp"


void SDLTexture::load(SDL_Renderer* rend, const char * path)
{
	renderer = rend;
	SDL_Surface *img = IMG_Load(path);
	if(img == nullptr)
		throw(newError2(OTHER, "texture upload failed"));
	texture = SDL_CreateTextureFromSurface(rend, img);
	w =img -> w;
	h = img -> h;
	SDL_FreeSurface(img);
	if(texture == nullptr)
		throw(newError2(OTHER, "texture convert failed"));
	*deletable = true;
}


void SDLTexture::draw(int x, int y)
{
	draw(x, y, w, h);
}

void SDLTexture::draw(int x, int y, int w, int h)
{
	if(!is_drawable())
		throw(newError(BINDING_UNLOADED));
	SDL_Rect rec;
	rec.x = x, rec.y = y, rec.w = w, rec.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &rec);
}

SDLTexture::SDLTexture()
{
	deletable = new bool[1];
	deletable[0] = false;
}

SDLTexture::SDLTexture(SDL_Renderer* rend, const char * path)
{
	deletable = new bool[1];
	deletable[0] = false;
	load(rend, path);
}

SDLTexture::~SDLTexture()
{
	if(*deletable)
		SDL_DestroyTexture(texture);
}

SDLTexture::SDLTexture(const SDLTexture & from)
{
	texture = from.texture;
	w = from.w;
	h = from.h;
	renderer = from.renderer;
	deletable = from.deletable;
	bool tmp = *deletable;
	*deletable = false;
	deletable = new bool[1];
	*deletable = tmp;
}

bool SDLTexture::is_drawable()
{
	return (renderer != nullptr) && (*deletable);
}
