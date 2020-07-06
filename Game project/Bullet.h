#ifndef __BULLET__
#define __BULLET__

#include "PtObject.h"
#include "Level.h"

class Bullet : public PtObject
{
private:
	Level* pLevel;

public:
	Bullet();
	~Bullet();
	void initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type) override;
	void update() override;
	void collide(PtObjectsEnum otherObject) override;
	void setLevel(Level* pLevel);
};

#endif
