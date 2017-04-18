#include <iostream>
#include "Model.hpp"
#include "../Error.hpp"

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
		throw(newError(FILE_NOT_OPEN));
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
	if(activeTexture >= (int)textures.size())
		activeTexture = (int)textures.size() - 1;
}

void Model::setActiveMash(int ind)
{
	activeMash = ind;
	if(activeMash >= (int)mash.size())
		activeMash = (int)mash.size() - 1;
}

void Model::draw()
{
	if(activeMash < 0)
		throw(newError(OBJ));
	if(!is_textures())//в зависимости от наличия текстур вызываем разные методы отрисовки
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



