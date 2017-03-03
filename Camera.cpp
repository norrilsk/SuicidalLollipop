#include "Camera.hpp"
const double PI = 3.141592653;


Camera::Camera()
{
	x = 0;
	y = 0;
	z = 0;
	angleX = 0;
	angleY = 0;
	height = 0;
	PlayerSpeed = 0.1;
}

Camera::Camera(double x1, double y1, double z1, double height1, double PlayerSpeed1, double angleX1, double angleY1)
{
	x = x1;
	y = y1;
	z = z1;
	if (angleY1 > 89)
		angleY1 = 89;
	if (angleY1 < -89)
		angleY1 = -89;
	angleX = angleX1;
	angleY = angleY1;
	height = height1;
	PlayerSpeed = PlayerSpeed1;
}

void Camera::SetFPS(double fps)
{
	FPS = fps;
}
void Camera::Look()
{
	gluLookAt(x, y + height, z, x - sin(angleX / 180 * PI), y + height + (tan(angleY / 180 * PI)), z - cos(angleX / 180 * PI), 0, 1, 0);
	/*Первые 3 - координаты позиции глаза налюдателя, вторые 3 - координаты точки, распологающейся в центре экрана,
	третьи 3 - направление вектора, задающего поворот сцены.*/
	return;
}
void Camera::ChangePlayerSpeed(double speed)
{
	PlayerSpeed = speed;
	return;
}
void Camera::MoveForward()
{
	x -= (double)sin(angleX / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	z -= (double)cos(angleX / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	return;
}
void Camera::MoveBackward()
{
	x += (double)sin(angleX / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	z += (double)cos(angleX / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	return;
}
void Camera::MoveRight()
{
	x += (double)sin((angleX + 90) / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	z += (double)cos((angleX + 90) / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	return;
}
void Camera::MoveLeft()
{
	x += (double)sin((angleX - 90) / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	z += (double)cos((angleX - 90) / 180 * PI) * PlayerSpeed*FpsBase/FPS;
	return;
}
void Camera::RotaterRightLeft(double DeltaAngel)
{
	angleX += DeltaAngel;
	return;
}
void Camera::RotateHighDown(double DeltaAngle)
{
	angleY += DeltaAngle*FpsBase/FPS;
	//std :: cout << angleY << " !! " <<FpsBase/FPS  << " " << FPS<< std ::endl;
	if (angleY > 89)
		angleY = 89;
	if (angleY < -89)
		angleY = -89;
	return;
}


Camera::~Camera()
{
}
