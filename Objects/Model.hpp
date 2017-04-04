#ifndef _MODEL
#define _MODEL


#include <vector>
#include "../Texture.hpp"
#include "MashObject.hpp"

class Model
{
	std::vector <Texture> textures;
	MashObject mash;
	int activeTexture =-1;
	void loadMash(const std::string &);
	void addTexture(const std::string &);
public:
	Model(){};
	~Model(){};
	Model(const std::string &);
	void setActiveTexture(int ind);
	void draw();

	bool is_drawable();

	bool is_textures();
};


#endif
