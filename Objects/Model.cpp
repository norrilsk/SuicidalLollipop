#include "Model.hpp"
#include "../Error.hpp"

void Model::loadMash(const std::string &path)
{
	mash.parser(path);
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
	std::string file_path;
	in >> file_path;
	mash.parser(file_path);
	file_path.clear();
	while(!in.eof())
	{
		in >> file_path;
		textures.push_back(Texture(file_path.c_str()));
	}
	if(textures.size() > 0)
	{
		activeTexture = 0;
	}
	in.close();
}



void Model::setActiveTexture(int ind)
{
	activeTexture = ind;
	if(activeTexture >= textures.size())
		activeTexture = (int)textures.size() - 1;
}

void Model::draw()
{
	if(activeTexture < 0)
		mash.draw();
	else
		mash.draw(&textures[activeTexture]);
}

bool Model::is_drawable()
{
	return mash.is_drawable();
}

bool Model::is_textures()
{
	return (activeTexture >= 0) && (mash.is_textures());
}

