#include "ScreenRec.hpp"
#include"Error.hpp"
#include<GL/glew.h>
using namespace std;

ScreenRec::ScreenRec()
{

}
ScreenRec::ScreenRec(int w, int h, const std::string& frShName, const std::string& verShName)
{
	glBindVertexArray(0);
	std::vector<std::pair<std::string, GLuint> > ShadersPaths;
	ShadersPaths.push_back(std::make_pair(frShName, GL_FRAGMENT_SHADER));//���� ������������ �������
	ShadersPaths.push_back(std::make_pair(verShName, GL_VERTEX_SHADER));//���� ���������� �������					
	shaders.Load(ShadersPaths); 		//���������� �������
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	glm::vec3 ver[6] = { glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f) };
	glm::vec2 uv[6] = { glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) };
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), ver, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), uv, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glGenFramebuffers(1, &fbo);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw( newError2(SHADER,"Framebuffer is not complete!"));
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void ScreenRec::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}
void ScreenRec::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void ScreenRec::draw(vector<pair<string, int>>* data_int, vector<pair<string, float>>* data_float, vector<pair<string, glm::vec3>>* data_vec, GLuint texture)
{
//	glClearColor(1.0f, 0.0f, 1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
//	
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	if (!texture)
		glBindTexture(GL_TEXTURE_2D, tex);
	else
		glBindTexture(GL_TEXTURE_2D, texture);
	glEnableVertexAttribArray(1);
	shaders.useProgram();
	shaders.setTextureSampler(0);
	if (data_int)
	{
		for (auto m : *data_int)
		{
			shaders.store(m.second, m.first.c_str());
		}
	}
	if (data_float)
	{
		for (auto m : *data_float)
		{
			shaders.store(m.second, m.first.c_str());
		}
	}
	if (data_vec)
	{
		for (auto m : *data_vec)
		{
			shaders.store(m.second, m.first.c_str());
		}
	}
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}
ScreenRec::~ScreenRec()
{
}
