#ifndef __3D_CUBE__
#define __3D_CUBE__

#include "../../toolkit/toolkit.h"

struct Cuboid3D
{
public:
	float height = 0;
	float width = 0;
	float length = 0;
	Vector3 centrePoint;
};

#endif