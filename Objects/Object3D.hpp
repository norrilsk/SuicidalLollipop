#ifndef _OBJECT3D
#define _OBJECT3D
#include "DrawableObject.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <cmath>
#include "MashObject.hpp"
#include "Model.hpp"
#include <string>
class Object3D : public DrawableObject
{
private:
protected:
	glm :: dvec3 coord = glm :: dvec3 (-20, 0, 0);//абсолютные координаты 
	glm :: dmat3 A = glm :: dmat3x3( glm :: dvec3 (1, 0, 0),  glm :: dvec3 (0, 1, 0),  glm :: dvec3 (0, 0, 1)); //направление прямо, направление налево, направление вверх
	glm :: dvec3  &ex = A[0];
	glm :: dvec3  &ey = A[1];
	glm :: dvec3  &ez = A[2];
	Model *model = nullptr;
public:
	void draw();
	glm::mat4 ModelMat(); // Возвращает матрицу модели
	void set(glm :: dvec3, glm :: dvec3, glm :: dvec3); //установка coord, ex, ez
	void set(glm :: dvec3, glm :: dvec3); //установка coord, ex
	void set(glm :: dvec3);//установка coord
	bool is_drawable(); //может ли быть отображен?
	bool has_textures(); //есть ли текстуры?
	glm :: dvec3 getPosition();
	glm :: dvec3 getLookDirection();
	glm :: dvec3 getUpperDirection();
	Object3D(const Object3D &);
	Object3D();
	Object3D(Model *);
	~Object3D();
};
#endif

