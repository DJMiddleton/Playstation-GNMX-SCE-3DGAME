#ifndef __LEVEL__
#define __LEVEL__

#include <memory>
#include "PtLightEnvironment.h"
#include "PtAssetManager.h"
#include "ptDrawManager.h"
#include "PtController.h"
#include "PtCamera.h"
#include "ObjectsEnum.h"
#include "GameState.h"
#include "PtHUDTextItem.h"
#include "HUDObjects.h"
#include <vector>

class Level : public GameState
{
private:
	static const int TOTAL_TIE_FIGHTERS = 15;
	static const int TIE_FIGHTER_PLAYER_DAMAGE = 15;
	static const int TIE_FIGHTER_RED_FIVE_DAMAGE = 25;
	static const int PLAYER_DEFAULT_HEALTH = 100;
	static const int RED_5_DEFAULT_HEALTH = 50;
	static const unsigned int TOTAL_CAMERAS = 2;
	static const unsigned int HUD_ITEMS = 7;
	static const unsigned int END_SEQUENCE_LENGTH = 240;

	PtLightEnvironment lights;
	std::shared_ptr<PtAssetManager> pAssetManager;
	PtDrawManager drawManager;
	std::vector<std::shared_ptr<PtObject>> pObjects;
	std::shared_ptr<PtObject> pMillenniumFalcon;
	std::shared_ptr<PtObject> pExplosion;
	std::shared_ptr<PtObject> pDeathStar;
	std::shared_ptr<PtObject> pYavinIV;
	std::shared_ptr<PtHUDTextItem> hud[HUD_OBJECTS_COUNT];
	std::shared_ptr<PtCamera> cameras[TOTAL_CAMERAS];
	std::shared_ptr<PtController> pController;
	LinearAllocator* myGarlicAllocator;
	LinearAllocator* myOnionAllocator;
	sce::Gnmx::Toolkit::Allocators* myToolkitAllocators;
	int playerHealth;
	int remainingEnemies;
	int redFiveHealth;
	int endSequenceRemaining;
	bool success;
	bool fail;
	bool cheatActive;
	unsigned int currentCameraIndex;

public:
	Level();
	~Level();
	void initialise(LinearAllocator* garlicAllocator, LinearAllocator* onionAllocator, sce::Gnmx::Toolkit::Allocators* toolkitAllocators, float aspectRatio, std::shared_ptr<PtAssetManager> pAssetManager, std::shared_ptr<PtController> pController) override;
	ScreenStates update() override;
	void draw(Gnmx::GnmxGfxContext* myGFXC) override;
	void fireBullet(Matrix4 startPosition, PtObjectsEnum owner);
	void deleteInactiveBullets();
	void deleteAllBullets();
	void setBulletsInactive();
	void enemyHit();
	void playerHit();
	void redFiveHit();
	void win();
	void loss();
	void reset();
	void extras();
};

#endif