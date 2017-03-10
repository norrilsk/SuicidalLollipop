#ifndef _MOUSE
#define _MOUSE
#include <utility>
#include <glm/glm.hpp>
class Mouse
{
	int X, Y; 
	double sensity; // Координаты положения мыши, чувствительность

public:
	std :: pair <int, int>  getPosition(); //абсолютные координаты курсора
	glm :: dvec2 getMovement(); // движение мыши с момента последнего вызова getMovement() или getPosition()
	void ChangeSensity(double sens); // Изменить чувствительность
	void centre();  //центрирует курсор
	Mouse();
	
	~Mouse();
};
#endif
