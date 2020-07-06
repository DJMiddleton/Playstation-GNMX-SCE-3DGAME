#ifndef __PT_OBJECT__
#define __PT_OBJECT__

#include "ptModel.h"
#include <vectormath.h>
#include <memory>
#include <gnm.h>
#include "PtMaterial.h"
#include "CollisionComponent.h"
#include "ObjectsEnum.h"

class PtObject
{
protected:
	std::shared_ptr<PtModel> pModel;
	Matrix4 modelWorldMatrix;
	Matrix4 initialTranslationMatrix;
	Matrix4 scaleMatrix;
	PtObjectsEnum type;
	float xAngle;
	float yAngle;
	std::shared_ptr<PtMaterial> pMaterial;
	std::shared_ptr<CollisionComponent> pCollisionComponent;
	bool active;

public:
	PtObject();
	virtual ~PtObject();
	virtual void initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type);
	virtual void update();
	virtual void collide(PtObjectsEnum otherObject);
	virtual void reset();
	void setInitialTranslationMatrix(Matrix4 translationMatrix);
	std::shared_ptr<PtModel> getModel();
	void setModel(std::shared_ptr<PtModel> model);
	Matrix4 getModelWorldMatrix();
	void setModelWorldMatrix(Matrix4 matrix);
	std::shared_ptr<PtMaterial> getMaterial();
	void setMaterial(std::shared_ptr<PtMaterial> newMaterial);
	void moveLeftRight(float amount);
	void moveUpDown(float amount);
	void moveForwardBack(float amount);
	void yawRotation(float amount);
	void pitchRotation(float amount);
	void rollRotation(float amount);
	void scale(Matrix4 scaleMatrix);
	void rotateX(Matrix4 rotationMatrix);
	void move(Matrix4 translationMatrix);
	Vector3 getPosition();
	PtObjectsEnum getType();
	std::shared_ptr<CollisionComponent> getCollisionComponent();
	bool getActive();
	void setActive(bool active);
};

#endif