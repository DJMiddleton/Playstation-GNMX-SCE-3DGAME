#include "Enemy.h"

Enemy::Enemy()
{
	steps = 0;
	xMovement = 0.02;
	hitRedFive = false;
}

void Enemy::initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type)
{
	PtObject::initialise(collisionComponent, type);
	scaleMatrix = Matrix4::scale(Vector3(0.4, 0.5, 0.5));
	scale(scaleMatrix);
}

void Enemy::update()
{
	PtObject::update();

	if (target == TieFighterTargets::RED_FIVE)
	{
		if (modelWorldMatrix.getTranslation().getY().getAsFloat() > -3)
		{
			moveUpDown(Z_MOVEMENT);
		}
		else
		{
			if (!hitRedFive)
			{
				pLevel->redFiveHit();
				hitRedFive = true;
			}
		}
	}
	else
	{
		moveLeftRight(xMovement);
		steps++;

		if (rand() % FIRE_CHANCE == 0)
		{
			pLevel->fireBullet(Matrix4::translation(modelWorldMatrix.getTranslation()), PtObjectsEnum::TIE_FIGHTER_BULLET);
		}

		if (steps > 250)
		{
			xMovement = xMovement * -1;
			steps = 0;

			if (modelWorldMatrix.getTranslation().getZ() < -3)
			{
				moveForwardBack(-0.25);
			}
		}
	}
}

void Enemy::collide(PtObjectsEnum otherObject)
{
	if (otherObject == PtObjectsEnum::MILLENNIUM_FALCON_BULLET)
	{
		pLevel->enemyHit();
		active = false;
	}
}

void Enemy::reset()
{
	PtObject::reset();
	steps = 0;
	xMovement = 0.02;
	hitRedFive = false;
	move(initialTranslationMatrix);
}

void Enemy::setLevel(Level* level)
{
	pLevel = level;
}

void Enemy::setTieFighterTarget(TieFighterTargets target)
{
	this->target = target;
}