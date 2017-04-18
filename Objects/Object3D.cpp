#include <iostream>
#include "Object3D.hpp"

Object3D::Object3D()
{
}
Object3D::Object3D(Model * modell)
{
	model = modell;
}
Object3D::Object3D(const Object3D & obj)
{
	coord = obj.coord;
	A = obj.A;
	ex = A[0];
	ey = A[1];
    ez = A[2];
	model = obj.model;
}
void Object3D::draw()
{
	if (!model->is_drawable())
		return;
	model->draw();
}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection, glm :: dvec3 upperdirection)
{
	coord = position;
	//std::cout <<coord.x << " " << coord.y <<" " << coord.z << std::endl;
	ex = lookdirection;
	ez = upperdirection;
	ex /= glm:: length(ex);
	ez /= glm:: length(ez);
	ey = glm::cross(ez, ex);
}

void Object3D::set(glm :: dvec3 position, glm :: dvec3 lookdirection)
{
	coord = position;
	ex = lookdirection;
	ex /= glm::length(ex);
	ey = glm::cross(ez, ex);
	ey /= glm::length(ey);
	ez = glm::cross(ex, ey);
}
glm::mat4 Object3D::ModelMat()
{
	return glm::mat4(glm::vec4(A[0], 0), glm::vec4(glm::vec3(ey), 0), glm::vec4(glm::vec3(ez), 0), glm::vec4(glm::vec3(coord), 1));
}

void Object3D:: set(glm :: dvec3 position)
{
	coord = position;
}

glm :: dvec3 Object3D:: getPosition()
{
	return coord;
}
glm :: dvec3 Object3D:: getLookDirection()
{
	return ex;
}
glm :: dvec3 Object3D:: getUpperDirection()
{
	return ez;
}

bool Object3D::is_drawable()
{
	return ((model != nullptr) && (model->is_drawable()));
}

bool Object3D::has_textures()
{
	return ((model != nullptr) && (model->is_textures()));
}

Object3D::~Object3D()
{
}

void Object3D::setActiveTexture(int ind)
{
	model->setActiveTexture(ind);
}

void Object3D::setActiveMash(int ind)
{
	model->setActiveMash(ind);
}
