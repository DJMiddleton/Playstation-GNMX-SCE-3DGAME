#ifndef __PLAYER_OBJECT__
#define __PLAYER_OBJECT__

#include "PtObject.h"
#include "PtCamera.h"
#include "PtController.h"
#include "Level.h"

class PlayerObject : public PtObject
{
private:
	const float MAX_X = 7.0f;
	const float MIN_X = -7.0f;
	const float MAX_Y = 3.0f;
	const float MIN_Y = -3.0f;
	const float MAX_Z = 1.0f;
	const float MIN_Z = -2.0f;
	
	std::shared_ptr<PtController> playerController;
	std::shared_ptr<PtCamera> playerCamera;
	Level* pLevel;

public:
	PlayerObject();
	~PlayerObject();
	void initialise(std::shared_ptr<CollisionComponent> collisionComponent, PtObjectsEnum type) override;
	void update() override;
	void collide(PtObjectsEnum otherObject) override;
	void movement();
	void setCamera(std::shared_ptr<PtCamera> camera);
	void setController(std::shared_ptr<PtController> controller);
	void setLevel(Level* pLevel);
};

#endif