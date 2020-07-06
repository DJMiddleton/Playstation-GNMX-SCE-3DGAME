#include"PtLightEnvironment.h"

PtLight* PtLightEnvironment::getLights()
{
	return lights;
}

PtLight* PtLightEnvironment::getLight(unsigned int index)
{
	return &lights[index];
}