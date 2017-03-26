#include <GL/glew.h>
#include <SDL2/SDL_quit.h>
#include "Error.hpp"
#define __DEBUG
Error :: Error()
{
	type = NONE;
}

Error::Error(ErrorType error, const char * file, int line)
{
	this->file = std::string(file);
	this->line = line;
	type = error;
}

Error::Error(ErrorType error, std::string info, const char *file, int line)
{
	this->file = std::string(file);
	this->line = line;
	type = error;
	meta = info;
}

std::string Error::getMessage()
{
    std::string res;
	switch(type)
	{
		case SHADER:
			res =std::string("Shader error :") + get_glInfo() + meta;
			break;
		case SDL:
			res = std::string("SDL error :") + SDL_GetError() + meta;
			break;
		case QUIT:
			res ="Program ended\t" + meta;
			break;
        case LOGFILE:
            res ="Logfile didn't load\t" + meta;
			break;
		case GL:
			res ="OpenGl error : " + get_glInfo() + meta;
			break;
		case UNKNOWN:
			res ="Unknown error occurred\n" + meta;
			break;
		case NONE:
			res = meta;
			break;
		case OTHER:
			res = meta;
			break;
	}
	if(type == NONE || type == QUIT)
		return res;
#ifdef __DEBUG
	return res + "\n  (call from file " + file + " : " + std::to_string(line) + ")";
#else
	return res;
#endif
}


std::string Error::get_glInfo()
{
	std::string res;
	GLenum error = glGetError();
	switch(error)
	{
		case GL_INVALID_ENUM:
			res = " enumeration parameter is not a legal enumeration for the function.";
			break;
		case GL_INVALID_VALUE:
			res = " value parameter is not a legal value the function.";
			break;
		case GL_INVALID_OPERATION:
			res = " invalid operation.";
			break;
		case GL_STACK_UNDERFLOW:
			res = " the stack is already at its lowest point.";
			break;
		case GL_OUT_OF_MEMORY:
			res = " the memory cannot be allocated.";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			res = "  attempt to read from or write/render to a framebuffer that is not complete.";
			break;
		case GL_NO_ERROR:
			break;
		default:
			res = " unknown OpenGl error (code " + std::to_string(error) + ")";
			break;
	}
	return res;
}
