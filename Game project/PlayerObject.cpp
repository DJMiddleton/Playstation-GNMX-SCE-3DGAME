#include "PlayerObject.h"
#include <cmath>

PlayerObject::PlayerObject()
{
	playerController = nullptr;
	playerCamera = nullptr;
	pLevel = nullptr;
}

PlayerObject::~PlayerObject()
{
	playerController = nullptr;
	playerCamera = nullptr;
	pLevel = nullptr;
}

void PlayerObject::initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type)
{
	PtObject::initialise(collisionComponent, type);
	initialTranslationMatrix = Matrix4::translation(Vector3(0, -0.2, -1)) * Matrix4::rotationX(0) * Matrix4::rotationY(0) * Matrix4::rotationZ(0);
	modelWorldMatrix = initialTranslationMatrix;
}

void PlayerObject::update()
{
	PtObject::update();
	movement();

	if (playerController->r2Trigger())
	{
		pLevel->fireBullet(Matrix4::translation(modelWorldMatrix.getTranslation()), PtObjectsEnum::MILLENNIUM_FALCON_BULLET);
	}
}

void PlayerObject::collide(PtObjectsEnum otherObject)
{
	if (otherObject == PtObjectsEnum::TIE_FIGHTER_BULLET)
	{
		pLevel->playerHit();
	}
}

void PlayerObject::movement()
{
	float leftAngleY = playerController->leftStickY() / 25;
	float leftAngleX = playerController->leftStickX() / 25;

	if (playerController->r1Pressed())
	{
		if (modelWorldMatrix.getTranslation().getY().getAsFloat() < MAX_Y)
		{
			playerCamera->trackUpDown(0.05);
		}
	}
	if (playerController->l1Pressed())
	{
		if (modelWorldMatrix.getTranslation().getY().getAsFloat() > MIN_Y)
		{
			playerCamera->trackUpDown(-0.05);
		}
	}

	if (leftAngleX > 0)
	{
		if (modelWorldMatrix.getTranslation().getX().getAsFloat() < MAX_X)
		{
			playerCamera->trackLeftRight(leftAngleX);
		}
	}
	else if (leftAngleX < 0)
	{
		if (modelWorldMatrix.getTranslation().getX().getAsFloat() > MIN_X)
		{
			playerCamera->trackLeftRight(leftAngleX);
		}
	}

	if (leftAngleY > 0)
	{
		if (modelWorldMatrix.getTranslation().getZ().getAsFloat() < MAX_Z)
		{
			playerCamera->trackForwardBack(leftAngleY);
		}
	}
	else if (leftAngleY < 0)
	{
		if (modelWorldMatrix.getTranslation().getZ().getAsFloat() > MIN_Z)
		{
			playerCamera->trackForwardBack(leftAngleY);
		}
	}

	modelWorldMatrix = Matrix4::translation(Vector3(0, -0.2, -1)) * Matrix4::translation(inverse(playerCamera->getWorldViewMatrix()).getTranslation());
}

void PlayerObject::setCamera(std::shared_ptr<PtCamera> camera)
{
	playerCamera = camera;
}

void PlayerObject::setController(std::shared_ptr<PtController> controller)
{
	playerController = controller;
}

void PlayerObject::setLevel(Level* pLevel)
{
	this->pLevel = pLevel;
}