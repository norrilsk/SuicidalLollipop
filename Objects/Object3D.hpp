#ifndef _OBJECT3D
#define _OBJECT3D
#include "DrawableObject.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <cmath>
#include "MashObject.hpp"
#include <string>
class Object3D : public DrawableObject
{
private:
	glm::mat4 Model(); // Возвращает матрицу модели 
protected:
	glm :: dvec3 coord = glm :: dvec3 (-20, 0, 0);//абсолютные координаты 
	glm :: dmat3 A = glm :: dmat3x3( glm :: dvec3 (1, 0, 0),  glm :: dvec3 (0, 1, 0),  glm :: dvec3 (0, 0, 1)); //направление прямо, направление налево, направление вверх
	glm :: dvec3  &ex = A[0];
	glm :: dvec3  &ey = A[1];
	glm :: dvec3  &ez = A[2];
	MashObject *model;
public:
	void draw(int);
	void draw() { draw(0); }
	void set(glm :: dvec3, glm :: dvec3, glm :: dvec3); //установка coord, ex, ez
	void set(glm :: dvec3, glm :: dvec3); //установка coord, ex
	void set(glm :: dvec3);//установка coord
	glm :: dvec3 getPosition();
	glm :: dvec3 getLookDirection();
	glm :: dvec3 getUpperDirection();
	Object3D(const Object3D &);
	Object3D();
	Object3D(MashObject *);
	~Object3D();
};
#endif

