#ifndef __EXPLOSION_RING__
#define __EXPLOSION_RING__

#include "PtObject.h"

class ExplosionRing : public PtObject
{
private:
	Vector3 scaleMatrix;
	Vector3 colour;

public:
	ExplosionRing();
	void update() override;
	void reset() override;
};

#endif
