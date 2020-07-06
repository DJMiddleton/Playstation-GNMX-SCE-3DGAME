#include "Bullet.h"

Bullet::Bullet()
{
	pLevel = nullptr;
}

Bullet::~Bullet()
{
	pLevel = nullptr;
}

void Bullet::initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type)
{
	PtObject::initialise(collisionComponent, type);
	scaleMatrix = Matrix4::scale(Vector3(0.02, 0.02, 0.04));
}

void Bullet::update()
{
	PtObject::update();

	if (type == PtObjectsEnum::MILLENNIUM_FALCON_BULLET)
	{
		moveForwardBack(0.25);
	}
	else
	{
		moveForwardBack(-0.25);
	}

	if (modelWorldMatrix.getTranslation().getZ() < -12 || modelWorldMatrix.getTranslation().getZ() > 2)
	{
		active = false;
	}
}

void Bullet::collide(PtObjectsEnum otherObject)
{
	if (otherObject == PtObjectsEnum::MILLENNIUM_FALCON && type == PtObjectsEnum::TIE_FIGHTER_BULLET)
	{
		active = false;
	}
	else if (otherObject == PtObjectsEnum::TIE_FIGHTER && type == PtObjectsEnum::MILLENNIUM_FALCON_BULLET)
	{
		active = false;
	}
}

void Bullet::setLevel(Level* pLevel)
{
	this->pLevel = pLevel;
}