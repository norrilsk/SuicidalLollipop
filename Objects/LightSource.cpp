#include<cmath>
#include "LightSource.hpp"
#include "../Shaders.hpp"



LightSource::LightSource()
{
}
LightSource::LightSource(const SourceType& type)
{
	setType(type);
}
void LightSource::setType(const SourceType& type)
{
	switch (type)
	{
	case CONIC:
		sourceType = 0;
		break;
	case SPHERIC:
		sourceType = 1;
		break;
	case PARALLEL:
		sourceType = 2;
		break;
	}
}
void LightSource::moveToStructure(shader_data* data, int index)
{
	data->LightPosition_worldspace[index] = glm::vec4(this->getPosition(),1);
	data->LightColor[index] = glm::vec4(LightColor, 1);
	data->LightDirection[index] = glm::vec4(this->getLookDirection(), 1);
	data->LightPower[index] = power;
	data->cos_angle[index] = (float) cos(angle);
	data->source_type[index] = (unsigned int) sourceType;
}
LightSource::~LightSource()
{
}

