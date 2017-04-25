#ifndef _LIGHTSOURCE
#define _LIGHTSOURCE
#include "MovableObject.hpp"
struct shader_data;
enum SourceType: int
{
	CONIC,
	SPHERIC,
	PARALLEL

};
class LightSource :public MovableObject
{
	glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);// ���� ���������
	float power = 0; // �������� ���������
	float sourceType = 1; // ��� ���������
	float angle = 0.524; // ���� ���������
public:
	void setAngle(float _angle) { angle = _angle; } // ���������� ����
	void setPower(float _power) { power = _power; } //���������� ��������
	void setColor(glm::vec3 color) { LightColor = color; }// ���������� ����
	void setType(const SourceType& type);// ���������� ��� ���������
	void moveToStructure(shader_data* data, int index);// �������� �������� � ��������� � ��������� ������
	LightSource(const SourceType& type);//
	LightSource();
	~LightSource();
};
#endif