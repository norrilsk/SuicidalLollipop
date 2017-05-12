#include "PhysicalEngine.hpp"
#include"Objects/Room.hpp"
#include"Objects/MovableObject.hpp"
#include "Objects/Object3D.hpp"
#include<glm/glm.hpp>
#include<cmath>
glm::dvec3 Magik(glm::dvec3 A, glm::dvec3 B, glm::dvec3 C, glm::dvec3 O, double R);
//TODO:: Написать столкновение типа коробка-коробка
void PhysicalEngine::ApplyPhysics(double dt)
{
	if (!room)
		return;
	agents.resize(room->numberOfMovableObjects());
	targets.resize(room->numberOfObjects());

	room->getAllMovablObjects(agents.data());
	room->getAllObjects(targets.data());
	CheckCollisions();
	
}
void PhysicalEngine::CheckCollisions()
{
	for (auto target : targets)
	{
		target->physicalProperties().ambient_power = 0.07;
	}
	for (int i = 0; i < targets.size(); i++)
	{
		if (targets[i]->physicalProperties().m == DBL_MAX)
			continue;
		for (int j = i+1; j < targets.size(); j++)
		{
			
			glm::dmat4 Mati = targets[i]->ModelMat(), Matj = targets[j]->ModelMat();
			glm::dvec3 Oi = glm::dvec3(Mati*glm::dvec4(targets[i]->getSphereCenter(), 1));
			glm::dvec3 Oj = glm::dvec3(Matj*glm::dvec4(targets[j]->getSphereCenter(), 1));

			double dist = glm::length(Oi-Oj);
			glm::dvec3 MovementVector = normalize (Oj - Oi);
			if ( dist > (targets[i]->getR() + targets[j]->getR())) // проверили 2 сферы
				continue;
			double ModeMV = targets[i]->getR() + targets[j]->getR() - dist;

			MovementVector*= ModeMV;
			glm::dvec3 box1[8],box2[8];
			
			for (int k = 0; k < 8; k++)
			{
				box1[k] = glm::dvec3(Mati*targets[i]->getBox()[k]);
				box2[k] = glm::dvec3(Matj*targets[j]->getBox()[k]);
			}
			glm::dvec3 tmp;

			if ((tmp  = box_sphere(box1, Oj,targets[j]->getR()))  ==  glm::dvec3(0))
				continue;
			if (glm::length(tmp) < ModeMV)
			{
				ModeMV = glm::length(tmp);
				MovementVector = tmp;
			}
			if ((tmp = box_sphere(box2,Oi , targets[i]->getR())) == glm::dvec3(0))
				continue;
			if (glm::length(tmp) < ModeMV)
			{
				ModeMV = glm::length(tmp);
				MovementVector = -tmp;
			}
			MovableObject*agent = (MovableObject*)targets[i];
			if (targets[j]->physicalProperties().m > 100000000.0*targets[i]->physicalProperties().m) //TODO:: написать чтото более физичное
			{
				agent->moveAbsolute(-MovementVector);
			}
			else
			{
				MovableObject*target = (MovableObject*)targets[j];
				double distA = -ModeMV *(agent->physicalProperties().m / (agent->physicalProperties().m + target->physicalProperties().m));
				double distB = distA + ModeMV;
				MovementVector = glm::normalize(MovementVector);
				agent->moveAbsolute(distA*MovementVector);
				target->moveAbsolute(distB*MovementVector);
			}
			
			// теперь раздвинем обЪекты
			

			
				

			//targets[i]->physicalProperties().ambient_power = 1;
			//targets[j]->physicalProperties().ambient_power = 1;


		}
	}
}

PhysicalEngine::PhysicalEngine()
{
}


PhysicalEngine::~PhysicalEngine()
{
}

glm::dvec3 PhysicalEngine::box_sphere(glm::dvec3* box,  glm::dvec3 O, double R)// чекаем коробку из 8 вершин и сферку
{
	glm::dvec3 A, B, C;
	glm::dvec3 ret;
	// ГРАНЬ 1
	A = box[0];
	B = box[2];
	C = box[3];
	if ((ret = Magik(A, B, C, O, R)) != glm::dvec3(0))
		return ret;
	// ГРАНЬ 2
	A = box[5];
	B = box[6];
	C = box[0];
	if ((ret = Magik(A, B, C, O, R)) != glm::dvec3(0))
		return ret;
	// ГРАНЬ 3
	A = box[7];
	B = box[1];
	C = box[5];
	if ((ret = Magik(A, B, C, O, R)) != glm::dvec3(0))
		return ret;
	// ГРАНЬ 4
	A = box[3];
	B = box[4];
	C = box[7];
	if ((ret = Magik(A, B, C, O, R)) != glm::dvec3(0))
		return ret;
	// ГРАНЬ 5
	A = box[7];
	B = box[5];
	C = box[3];
	if ((ret = Magik(A, B, C, O, R)) != glm::dvec3(0))
		return ret;
	// ГРАНЬ 5
	A = box[2];
	B = box[6];
	C = box[4];
	if ((ret = Magik(A, B, C, O, R)) != glm::dvec3(0))
		return ret;
	return glm::dvec3(0);

}
glm::dvec3 Magik(glm::dvec3 A, glm::dvec3 B, glm::dvec3 C, glm::dvec3 O,double R)
{
	glm::dvec3 e1, e2, n, l;
	double h, r, a_b, a_c;
	double x, y;
	e1 = glm::normalize(B - A);
	e2 = glm::normalize(C - A);
	n = glm::cross(e1, e2);
	l = O - A;
	h = glm::dot(n, l);// расстояние от точки О до точки пересечения с плоскостью грани (номер выше)
	if (h < R)
	{
		r = sqrt(R*R - h*h);
		a_b = glm::length(A - B);
		a_c = glm::length(A - C);
		x = (glm::dot(e2, l));
		y = (glm::dot(e1, l));
		if ((y > 0) && (y < (a_b)))
		{
			if ((x > -r) && (x < (a_c + r)))
			{
				return  n*(R - h);
			}

		}
		if ((y < 0) && (y > -r))
		{
			if ((x > 0) && (x < (a_c)))
			{
				return  n*(R - h);
			}
			if ((x > -r) && (x < 0) && ((x*x + y*y) < r*r))
			{
				return  n*(R - h);
			}
			if ((x > a_c) && (x < a_c + r) && (((x - a_c)*(x - a_c) + y*y) < r*r))
			{
				return  n*(R - h);
			}
		}
		if ((y < a_b + r) && (y > a_b))
		{
			if ((x > 0) && (x < (a_c)))
			{
				return  n*(R - h);
			}
			if ((x > -r) && (x < 0) && ((x*x + (y - a_b)*(y - a_b)) < r*r))
			{
				return  n*(R - h);
			}
			if ((x > a_c) && (x < a_c + r) && (((x - a_c)*(x - a_c) + (y - a_b)*(y - a_b)) < r*r))
			{
				return  n*(R - h);
			}
		}
	}
	return glm::dvec3(0);
}