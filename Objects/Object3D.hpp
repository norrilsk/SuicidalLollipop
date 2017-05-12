#ifndef _OBJECT3D
#define _OBJECT3D
#include "DrawableObject.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <cmath>
#include "MashObject.hpp"
#include "Model.hpp"
#include<climits>
#include <string>
class PhysicalProperties // физические свойства обЪекта
{
public:
	double m = DBL_MAX;
	double conservedEnergy = 0.8;
	double ambient_power = 0.07;
	glm::dvec3 velocity = glm::dvec3(0.0, 0.0, 0.0);
	glm::dmat3 J = glm::dmat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	glm::dvec3 MassCenter = glm::dvec3(0, 0, 1);
	glm::dvec3 omega = glm::dvec3(0, 0, 0);
	PhysicalProperties();
	~PhysicalProperties() {};
};
class Object3D : public DrawableObject
{	
protected:
	PhysicalProperties physical_properties;
	glm :: dvec3 coord = glm :: dvec3 (0, 0, 0);//абсолютные координаты
	glm :: dmat3 A = glm :: dmat3x3( glm :: dvec3 (1, 0, 0),  glm :: dvec3 (0, 1, 0),  glm :: dvec3 (0, 0, 1)); //направление прямо, направление налево, направление вверх
	glm :: dvec3  &ex = A[0];
	glm :: dvec3  &ey = A[1];
	glm :: dvec3  &ez = A[2];
	Model *model = nullptr;
public:
	void draw();
	PhysicalProperties& physicalProperties() { return physical_properties; }// возвращает структуру физический свойств
	glm::mat4 ModelMat(); // Возвращает матрицу модели
	void set(glm :: dvec3, glm :: dvec3, glm :: dvec3); //установка coord, ex, ez, не стоит указывать ex == ez или ex*ez == 0
	void set(glm :: dvec3, glm :: dvec3); //установка coord, ex
	void set(glm :: dvec3);//установка coord
	bool is_drawable(); //может ли быть отображен?
	bool has_textures(); //есть ли текстуры?
	void setActiveTexture(int ind);//устанавливаем активную текстуру
	void setActiveMash(int ind);//устанавлиывем активный меш
	double getR(); // Возвращает радиус описаной сферы
	glm::dvec4* getBox() { return model->getBox(); }
	std::vector< glm::vec3 >& get_vertices() { return model->get_vertices(); }
	glm::dvec4 getMaxBoxVertex();// возвращает координаты угла Коробки
	glm::dvec4 getMinBoxVertex();// возвращает координаты второго угла коробки
	glm::dvec3 getSphereCenter();// возвращает координаты 
	glm :: dvec3 getPosition();
	glm :: dvec3 getLookDirection();
	glm :: dvec3 getUpperDirection();
	Object3D(const Object3D &);
	Object3D();
	Object3D(Model *);
	~Object3D();
};
#endif

