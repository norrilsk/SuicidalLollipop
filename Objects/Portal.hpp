#ifndef _PORTAL
#define _PORTAL
#include "TrianglePortal.hpp"


class Portal
{
	StorageIndex current_room = 0;
	StorageIndex target_room = 0;
	std::vector <TrianglePortal> sub_portals;
	bool linked = false;
public:
	Portal(){}
	~Portal(){}
	//если массив портальных чисел не указан все портальные числа станут 1.0
	void createPottal(int, float *, StorageIndex, double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число координат)
	void createPottal(int, double *, StorageIndex, double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число координат)
	void createPottal(int, glm::vec3 *, StorageIndex, double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число вершин)
	void createPottal(int, glm::dvec3 *, StorageIndex,double * = NULL);//создаем порталы из массива вершин, указываем комнату (указывается число вершин)
	void setRoom(StorageIndex);//какая комната?
	StorageIndex getRoom();
	StorageIndex getTarget();
	Portal(int, float *, StorageIndex, double * = NULL);
	Portal(int, double *, StorageIndex, double * = NULL);
	Portal(int, glm::vec3 *, StorageIndex, double * = NULL);
	Portal(int, glm::dvec3 *, StorageIndex,double * = NULL);
	size_t numberOfSubportals();                                //число суброрталов
	TrianglePortal& operator [](int);                           //доступ к порталам
	void linkToPortal(Portal &); //присоединяем к другому порталу
	bool is_linked() { return linked;}//слинкован ли портал
};


#endif
