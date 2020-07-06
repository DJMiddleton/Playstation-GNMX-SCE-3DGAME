#include "PtCamera.h"

PtCamera::PtCamera()
{
	worldViewMatrix = Matrix4::identity();
	angle = 0;
	aspectRatio = 0;
	zNear = 0;
	zFar = 0;
}

Matrix4 PtCamera::getProjectionMatrix()
{
	return projectionMatrix;
}

void PtCamera::setProjectionMatrix(Matrix4 matrix)
{
	projectionMatrix = matrix;
}

void PtCamera::setWorldViewMatrix(Matrix4 matrix)
{
	worldViewMatrix = matrix;
}

void PtCamera::setPerspective(float angle, float aspectRatio, float zNear, float zFar)
{
	PtCamera::angle = angle;
	PtCamera::aspectRatio = aspectRatio;
	PtCamera::zNear = zNear;
	PtCamera::zFar = zFar;

	projectionMatrix = Matrix4::perspective(angle, aspectRatio, zNear, zFar);
}

void PtCamera::updateAngle(float increase)
{
	angle = angle + increase;
	setPerspective(angle, aspectRatio, zNear, zFar);
}

void PtCamera::updateAspectRatio(float increase)
{
	aspectRatio = aspectRatio + increase;
	setPerspective(angle, aspectRatio, zNear, zFar);
}

void PtCamera::updateZNear(float increase)
{
	zNear = zNear + increase;
	setPerspective(angle, aspectRatio, zNear, zFar);
}

void PtCamera::updateZFar(float increase)
{
	zFar = zFar + increase;
	setPerspective(angle, aspectRatio, zNear, zFar);
}

Matrix4 PtCamera::getWorldViewMatrix()
{
	return worldViewMatrix;
}

void PtCamera::trackLeftRight(float amount)
{
	worldViewMatrix = Matrix4::translation(Vector3(-amount, 0.0, 0.0)) * worldViewMatrix;
}

void PtCamera::trackUpDown(float amount)
{
	worldViewMatrix = Matrix4::translation(Vector3(0.0, -amount, 0.0)) * worldViewMatrix;
}

void PtCamera::trackForwardBack(float amount)
{
	worldViewMatrix = Matrix4::translation(Vector3(0.0, 0.0, -amount)) * worldViewMatrix;
}

void PtCamera::yawRotation(float amount)
{
	worldViewMatrix = Matrix4::rotationX(-amount) * worldViewMatrix;
}

void PtCamera::pitchRotation(float amount)
{
	worldViewMatrix = Matrix4::rotationY(-amount) * worldViewMatrix;
}

void PtCamera::rollRotation(float amount)
{
	worldViewMatrix = Matrix4::rotationZ(-amount) * worldViewMatrix;
}

void PtCamera::orbitalPitch(Matrix4 pointTranslation, float angle)
{
	Matrix4 orbitalRotation = Matrix4::rotationY(angle);
	worldViewMatrix = Matrix4::translation(Vector3(0, 0.2, 1)) * orbitalRotation * Matrix4::translation(Vector3(0,0,0));
}

void PtCamera::reset()
{
	worldViewMatrix = Matrix4::identity();
}