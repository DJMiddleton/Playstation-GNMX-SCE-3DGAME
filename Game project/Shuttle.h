#ifndef __SHUTTLE__
#define __SHUTTLE__

#include "PtObject.h"

class Shuttle : public PtObject
{
private:
	float rotationAngle;
	Matrix4 starDestroyerTranslationMatrix;

public:
	Shuttle();
	void update() override;
	void reset() override;
	void setStarDestroyerTranslationMatrix(Matrix4 matrix);
};

#endif