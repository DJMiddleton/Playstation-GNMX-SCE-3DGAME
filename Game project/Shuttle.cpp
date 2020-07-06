#include "Shuttle.h"

Shuttle::Shuttle()
{
	rotationAngle = 0;
}

void Shuttle::update()
{
	PtObject::update();

	rotationAngle = rotationAngle + 0.001;
	Matrix4 orbitalRotation = Matrix4::rotationY(rotationAngle);
	modelWorldMatrix = orbitalRotation * starDestroyerTranslationMatrix * initialTranslationMatrix;
}

void Shuttle::setStarDestroyerTranslationMatrix(Matrix4 matrix)
{
	starDestroyerTranslationMatrix = matrix;
}

void Shuttle::reset()
{
	PtObject::reset();
	rotationAngle = 0;
	modelWorldMatrix = Matrix4::translation(Vector3(-17, 0, -20));
}