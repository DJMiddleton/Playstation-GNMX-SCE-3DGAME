#ifndef __PT_LIGHT_ENVIRONMENT__
#define __PT_LIGHT_ENVIRONMENT__

#include "PtLight.h"
#include "PtLightCount.h"

class PtLightEnvironment
{
private:
	PtLight lights[PT_LIGHT_COUNT];

public:
	PtLight* getLights();
	PtLight* getLight(unsigned int index);
};

#endif
