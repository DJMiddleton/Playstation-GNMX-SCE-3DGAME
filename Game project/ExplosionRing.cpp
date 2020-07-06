#include "ExplosionRing.h"

ExplosionRing::ExplosionRing()
{
	scaleMatrix = Vector3(1.0f, 1.0f, 1.0f);
	colour = Vector3(1.0f, 0.5f, 0.0f);
}

void ExplosionRing::update()
{
	PtObject::update();

	scale(Matrix4::scale(scaleMatrix));
	scaleMatrix.setX(scaleMatrix.getX().getAsFloat() + 0.25);
	scaleMatrix.setZ(scaleMatrix.getZ().getAsFloat() + 0.25);

	colour.setX(colour.getX().getAsFloat() - 0.005);
	colour.setY(colour.getY().getAsFloat() - 0.0025);

	if (colour.getY().getAsFloat() < 0)
	{
		colour.setY(0);
	}

	if (colour.getX().getAsFloat() < 0)
	{
		pMaterial->setSpecularPower(0);
		pMaterial->setSpecularStrength(0);
		colour.setX(0);
	}

	pMaterial->setAmbientColour(colour);
	pMaterial->setDiffuseColour(colour);
}

void ExplosionRing::reset()
{
	PtObject::reset();

	active = false;
	scaleMatrix = Vector3(1.0f, 1.0f, 1.0f);
	scale(Matrix4::scale(scaleMatrix));

	colour = Vector3(1.0f, 0.5f, 0.0f);
	pMaterial->setAmbientColour(colour);
	pMaterial->setDiffuseColour(colour);
}