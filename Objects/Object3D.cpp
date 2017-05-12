#include <iostream>
#include "Object3D.hpp"
#include "../Error.hpp"

Object3D::Object3D()
{
}
Object3D::Object3D(Model * modell)
{
	model = modell;
}
Object3D::Object3D(const Object3D & obj)
{
	physical_properties = obj.physical_properties;
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

double Object3D::getR()
{
	if (!model)
		throw(newError(OBJ));
	return model->getR();
}

glm::dvec4 Object3D::getMaxBoxVertex()
{
	if (!model)
		throw(newError(OBJ));
	return model->getMaxBoxVertex();
}

glm::dvec4 Object3D::getMinBoxVertex()
{
	if (!model)
		throw(newError(OBJ));
	return model->getMinBoxVertex();
}

glm::dvec3 Object3D::getSphereCenter()
{

	if (!model)
		throw(newError(OBJ));
	return model->getSphereCenter();
}
PhysicalProperties::PhysicalProperties()
{
	m = 25.0;
	conservedEnergy = 0.8;
	ambient_power = 0.07;
	velocity = glm::dvec3(0.0, 0.0, 0.0);
	J = glm::dmat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	MassCenter = glm::dvec3(0, 0, 1);
	omega = glm::dvec3(0, 0, 0);
}