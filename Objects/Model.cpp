#include <iostream>
#include "Model.hpp"
#include "../Error.hpp"
#include "../GLfunc.hpp"

void Model::addMash(const std::string & path)
{
	mash.push_back(MashObject(path));
}

void Model::addTexture(const std::string &path)
{
	textures.push_back(Texture(path.c_str()));
}

Model::Model(const std::string &path)
{
	std::ifstream in;
	in.open(path);
	if (!in.is_open())
		throw(newError(OBJ));
	std::string str;
	while(!in.eof())
	{
		in >> str;
		if(str == "OBJ")
		{
			in >> str;
			addMash(str);
		}
		if(str == "TEX")
		{
			in >> str;
			addTexture(str);
		}
	}
	if(mash.size() > 0)
		activeMash = 0;
	if(textures.size() > 0)
		activeTexture = 0;
	in.close();
}



void Model::setActiveTexture(int ind)
{
	activeTexture = ind;
	if(activeTexture >= textures.size())
		activeTexture = (int)textures.size() - 1;
}

void Model::setActiveMash(int ind)
{
	activeMash = ind;
	if(activeMash >= mash.size())
		activeMash = (int)mash.size() - 1;
}

void Model::draw(glm::mat4 ModelMat, int NUM)
{
	if(activeMash < 0)
		throw(newError(OBJ));
	glm::mat4 MVP = Gl::Projection * Gl::View*ModelMat;
	Gl::shaders.useProgram();
	Gl::shaders.store_MVP(&MVP[0][0]);
	Gl::shaders.store_int(is_textures(), TEXTURES_ENABLED);
	Gl::shaders.store_int(NUM, TEXTURE_SAMPLER);
	if(activeTexture < 0)
		mash[activeMash].draw();
	else
		mash[activeMash].draw(&textures[activeTexture]);
}

bool Model::is_drawable()
{
	return (activeMash >=  0) && mash[activeMash].is_drawable();
}

bool Model::is_textures()
{
	return is_drawable() && (activeTexture >= 0) && (mash[activeMash].is_textures());
}



