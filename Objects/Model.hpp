#ifndef _MODEL
#define _MODEL


#include <vector>
#include <glm/glm.hpp>
#include "../Texture.hpp"
#include "MashObject.hpp"

class Model
{
	std::vector <Texture> textures;
	std::vector <MashObject> mash;
	int activeMash =-1;
	int activeTexture =-1;
	void addMash(const std::string &);
	void addTexture(const std::string &);
	bool is_textures();
public:
	Model(){};
	~Model(){};
	Model(const std::string &);
	void setActiveTexture(int ind);

	void setActiveMash(int ind);
	bool is_drawable();

	void draw(glm::mat4, int);
};


#endif
