#include "CollisionComponent.h"

void CollisionComponent::initialise(float height, float width, float length)
{
	shape.height = height;
	shape.width = width;
	shape.length = length;
	shape.centrePoint = Vector3(0,0,0);
}

bool CollisionComponent::checkCollision(Cuboid3D otherShape)
{
	return (shape.centrePoint.getX() - shape.width / 2) <= (otherShape.centrePoint.getX() + otherShape.width / 2)
			&& (shape.centrePoint.getX() + shape.width / 2) >= (otherShape.centrePoint.getX() - otherShape.width / 2)
			&& (shape.centrePoint.getY() - shape.height / 2) <= (otherShape.centrePoint.getY() + otherShape.height / 2)
			&& (shape.centrePoint.getY() + shape.height / 2) >= (otherShape.centrePoint.getY() - otherShape.height / 2)
			&& (shape.centrePoint.getZ() - shape.length / 2) <= (otherShape.centrePoint.getZ() + otherShape.length / 2)
			&& (shape.centrePoint.getZ() + shape.length / 2) >= (otherShape.centrePoint.getZ() - otherShape.length / 2);
}


void CollisionComponent::setCentrePoint(Vector3 centrePoint)
{
	shape.centrePoint = centrePoint;
}

Cuboid3D CollisionComponent::getShape()
{
	return shape;
}