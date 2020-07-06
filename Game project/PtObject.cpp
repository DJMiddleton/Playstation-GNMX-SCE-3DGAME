#include "PtObject.h"

PtObject::PtObject()
{
	pCollisionComponent = nullptr;
	pModel = nullptr;
	pMaterial = nullptr;
	xAngle = 0;
	yAngle = 0;
	type = PtObjectsEnum::PT_OBJECT_COUNT;
	active = false;
}

PtObject::~PtObject()
{
	pCollisionComponent.reset();
	pCollisionComponent = nullptr;
	pModel.reset();
	pModel = nullptr;
	pMaterial.reset();
	pMaterial = nullptr;
}

std::shared_ptr<PtModel> PtObject::getModel()
{
	return pModel;
}

void PtObject::setModel(std::shared_ptr<PtModel> model)
{
	PtObject::pModel = model;
}

Matrix4 PtObject::getModelWorldMatrix()
{
	return modelWorldMatrix;
}

void PtObject::setModelWorldMatrix(Matrix4 matrix)
{
	modelWorldMatrix = matrix;
}

void PtObject::setInitialTranslationMatrix(Matrix4 translationMatrix)
{
	initialTranslationMatrix = translationMatrix;
}

std::shared_ptr<PtMaterial> PtObject::getMaterial()
{
	return pMaterial;
}

void PtObject::setMaterial(std::shared_ptr<PtMaterial> newMaterial)
{
	pMaterial = newMaterial;
}

void PtObject::moveLeftRight(float amount)
{
	modelWorldMatrix = Matrix4::translation(Vector3(-amount, 0.0, 0.0)) * modelWorldMatrix;
}

void PtObject::moveUpDown(float amount)
{
	modelWorldMatrix = Matrix4::translation(Vector3(0.0, -amount, 0.0)) * modelWorldMatrix;
}

void PtObject::moveForwardBack(float amount)
{
	modelWorldMatrix = Matrix4::translation(Vector3(0.0, 0.0, -amount)) * modelWorldMatrix;
}

void PtObject::yawRotation(float amount)
{
	modelWorldMatrix = modelWorldMatrix * Matrix4::rotationX(-amount);
}

void PtObject::pitchRotation(float amount)
{
	modelWorldMatrix = modelWorldMatrix * Matrix4::rotationY(-amount);
}

void PtObject::rollRotation(float amount)
{
	modelWorldMatrix =  modelWorldMatrix * Matrix4::rotationZ(-amount);
}

void PtObject::scale(Matrix4 scaleMatrix)
{
	modelWorldMatrix = Matrix4::translation(modelWorldMatrix.getTranslation()) * scaleMatrix;
}

void PtObject::rotateX(Matrix4 rotationMatrix)
{
	modelWorldMatrix = Matrix4::translation(modelWorldMatrix.getTranslation()) * rotationMatrix * scaleMatrix;
}

void PtObject::move(Matrix4 translationMatrix)
{
	modelWorldMatrix = translationMatrix * scaleMatrix;
}

Vector3 PtObject::getPosition()
{
	return modelWorldMatrix.getTranslation();
}

void PtObject::initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type)
{
	active = true;
	this->type = type;
	pCollisionComponent = collisionComponent;
}

std::shared_ptr<CollisionComponent> PtObject::getCollisionComponent()
{
	return pCollisionComponent;
}

void PtObject::update()
{
	pCollisionComponent->setCentrePoint(modelWorldMatrix.getTranslation());
}

PtObjectsEnum PtObject::getType()
{
	return type;
}

void PtObject::collide(PtObjectsEnum otherObject)
{

}

void PtObject::reset()
{
	active = true;
}

void PtObject::setActive(bool active)
{
	this->active = active;
}

bool PtObject::getActive()
{
	return active;
}