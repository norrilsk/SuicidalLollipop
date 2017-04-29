#ifndef _SCREENREC
#define _SCREENREC
#include"Shaders.hpp"
#include<string>
class ScreenRec
{
	Shaders shaders;
	GLuint vao = 0, fbo = 0, tex = 0;
public:
	ScreenRec(int w, int h, const std::string& frShName, const std::string& verShName);
	void bind();
	void unbind();
	void draw(std::vector<std::pair<std::string, int>>* = nullptr, std::vector<std::pair<std::string, float>>* = nullptr, std::vector<std::pair<std::string, glm::vec3>>* =nullptr, GLuint = 0);
	GLuint getTexture() { return tex; }
	ScreenRec();
	~ScreenRec();
};
#endif

