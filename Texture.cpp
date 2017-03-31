#include "Texture.hpp"
#include "Loger.hpp"

extern Loger logfile;

Texture::Texture()
{
}
Texture::Texture(const char* path)
{
	loadTexture(path);
}
void Texture::loadTexture(const char* path)
{
	image = IMG_Load(path); //  загружаем картинку
	isloaded = true;
	if (image== NULL) 
	{
		const char* log = IMG_GetError();
		logfile << "IMG_Load: " << IMG_GetError() << std::endl;
		isloaded = false;
	}
}
void Texture::bind()
{
	if (!isloaded)
		throw(newError(BINDING_UNLOADED));
	
	GLuint Mode = GL_RGB;
	if (image->format->BytesPerPixel == 4)  // если есть прозрачность, включим ее
		Mode = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, 
		GL_UNSIGNED_BYTE, image->pixels); // загрузим картинку
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // если текстурные координаты выходят за  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_LINEAR_MIPMAP_LINEAR);   // установим обработку близких и далеких изображений
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D); // сгенерируем текстуры меньшего размера
}

Texture::~Texture()
{
}
