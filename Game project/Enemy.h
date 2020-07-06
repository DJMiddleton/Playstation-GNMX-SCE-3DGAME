#ifndef __ENEMY__
#define __ENEMY__

#include "PtObject.h"
#include "Level.h"
#include "TieFighterTargets.h"

class Enemy : public PtObject
{
private:
	constexpr static float Z_MOVEMENT = 0.002f;
	const static int FIRE_CHANCE = 75;
	int steps;
	float xMovement;
	TieFighterTargets target;
	Level* pLevel;
	bool hitRedFive;

public:
	Enemy();
	void initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type) override;
	void update() override;
	void collide(PtObjectsEnum otherObject) override;
	void reset() override;
	void setLevel(Level* level);
	void setTieFighterTarget(TieFighterTargets target);
};

#endif
