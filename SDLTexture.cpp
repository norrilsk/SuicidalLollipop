#include <SDL2/SDL_image.h>
#include "SDLTexture.hpp"
#include "Error.hpp"

SDLTexture::~SDLTexture()
{
	if(was_loaded && !was_copied)
		SDL_DestroyTexture(texture);
}

void SDLTexture::load(SDL_Renderer* rend, const char * path)
{
	renderer = rend;
	SDL_Surface *img = IMG_Load(path);
	if(img == nullptr)
		throw(newError2(OTHER, "texture upload failed"));
	texture = SDL_CreateTextureFromSurface(rend, img);
	SDL_FreeSurface(img);
	if(texture == nullptr)
		throw(newError2(OTHER, "texture convert failed"));
}

SDLTexture::SDLTexture(SDL_Renderer* rend, const char * path)
{
	load(rend, path);
}

void SDLTexture::draw(int x, int y)
{
	draw(x, y, w, h);
}

void SDLTexture::draw(int x, int y, int w, int h)
{
	SDL_Rect rec;
	rec.x = x, rec.y = y, rec.w = w, rec.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &rec);
}
