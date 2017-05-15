#ifndef _MOVABLEOBJECT
#define _MOVABLEOBJECT
#include "Object3D.hpp"

class MovableObject : public Object3D
{
	glm::dmat3 RotationMatrix(double fi, glm::dvec3 e); //Вычисление точной матрицы поворота (для вращения на большие углы// )
	glm::dvec3 dPoos; 

public:
	void moveAbsolute(glm :: dvec3);//относительный переход в абсолютных координатах
	void moveRelative(glm :: dvec3);//относительный переход в собственных координатах
	void rotateAbsolute(glm :: dvec3 tetta);//относительный поворот в абсолютных координатах
	void rotateRelative(glm :: dvec3 omega);//относительный поворот в сщбственных координатах (если нужно выполняет последовательное)
	MovableObject(Model *);

	MovableObject();

	~MovableObject();
};
#endif

