#ifndef _PORTAL
#define _PORTAL
#include "TrianglePortal.hpp"


class Portal
{
	StorageIndex current_room = 0;
	StorageIndex target_room = 0;
	std::vector <TrianglePortal> sub_portals;
	bool linked = false;
	glm::dvec3 main_vector;//вектор портала (направление)
	glm::dvec3 second_vector;//вектор портала (поворрот)
	glm::dmat4 M;//матрица перехода
	glm::dvec3 O;//цетр портала
public:
	Portal(){}
	~Portal(){}
	//если массив портальных чисел не указан все портальные числа станут 1.0
	void createPottal(int, float *, StorageIndex);//создаем порталы из массива вершин, указываем комнату (указывается число координат)
	void createPottal(int, double *, StorageIndex);//создаем порталы из массива вершин, указываем комнату (указывается число координат)
	void createPottal(int, glm::vec3 *, StorageIndex);//создаем порталы из массива вершин, указываем комнату (указывается число вершин)
	void createPottal(int, glm::dvec3 *, StorageIndex);//создаем порталы из массива вершин, указываем комнату (указывается число вершин)
	void setRoom(StorageIndex);//какая комната?
	void setVectors(glm::dvec3,glm::dvec3);
	void setVectors(double, double, double, double, double, double);
	StorageIndex getRoom();
	StorageIndex getTarget();
	Portal(int, float *, StorageIndex);
	Portal(int, double *, StorageIndex);
	Portal(int, glm::vec3 *, StorageIndex);
	Portal(int, glm::dvec3 *, StorageIndex);
	glm::dmat4 Matrix();
	size_t numberOfSubportals();                                //число суброрталов
	TrianglePortal& operator [](int);                           //доступ к порталам
	void linkToPortal(Portal &); //присоединяем к другому порталу
	bool is_linked() { return linked;}//слинкован ли портал
};


#endif
