#ifndef __COLLISION_COMPONENT__
#define __COLLISION_COMPONENT__

#include "3DCube.h"

class CollisionComponent
{
private:
	Cuboid3D shape;

public:
	void initialise(float height, float width, float length);
	bool checkCollision(Cuboid3D otherShape);
	void setCentrePoint(Vector3 centrePoint);
	Cuboid3D getShape();
};

#endif