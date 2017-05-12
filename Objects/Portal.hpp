#ifndef _PORTAL
#define _PORTAL
#include "TrianglePortal.hpp"


class Portal
{

	std::vector <TrianglePortal> sub_portals;
	std::vector <double> portal_number;
public:
	Portal(){}
	~Portal(){}
	//если массив портальных чисел не указан все портальные числа станут 1.0
	void createPottal(int, float *, StorageIndex, double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число координат)
	void createPottal(int, double *, StorageIndex, double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число координат)
	void createPottal(int, glm::vec3 *, StorageIndex, double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число вершин)
	void createPottal(int, glm::dvec3 *, StorageIndex,double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число вершин)
	Portal(int, float *, StorageIndex, double * = NULL);
	Portal(int, double *, StorageIndex, double * = NULL);
	Portal(int, glm::vec3 *, StorageIndex, double * = NULL);
	Portal(int, glm::dvec3 *, StorageIndex,double * = NULL);
	void linkToPortal(Portal &); //присоединяем к другому порталу
};


#endif
