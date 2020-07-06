#ifndef __PT_CAMERA__
#define __PT_CAMERA__

#include <vectormath.h>
#include "../../common/danGraphicsWrapper.h"

class PtCamera
{
private:
	Matrix4 projectionMatrix;
	Matrix4 worldViewMatrix;
	float angle;
	float aspectRatio;
	float zNear;
	float zFar;

public:
	PtCamera();
	Matrix4 getProjectionMatrix();
	Matrix4 getWorldViewMatrix();
	void setWorldViewMatrix(Matrix4 matrix);
	void setProjectionMatrix(Matrix4 matrix);
	void setPerspective(float angle, float aspectRatio, float zNear, float zFar);
	void updateAngle(float increase);
	void updateAspectRatio(float increase);
	void updateZNear(float increase);
	void updateZFar(float increase);
	void trackLeftRight(float amount);
	void trackUpDown(float amount);
	void trackForwardBack(float amount);
	void yawRotation(float amount);
	void pitchRotation(float amount);
	void rollRotation(float amount);
	void orbitalPitch(Matrix4 pointTranslation, float angle);
	void reset();
};

#endif