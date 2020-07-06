#include "Level.h"
#include "PlayerObject.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Shuttle.h"
#include "ExplosionRing.h"
#include <algorithm>

Level::Level()
{
	myGarlicAllocator = nullptr;
	myOnionAllocator = nullptr;
	myToolkitAllocators = nullptr;
	pDeathStar = nullptr;
	pYavinIV = nullptr;
	pExplosion = nullptr;
	pMillenniumFalcon = nullptr;
	fail = false;
	success = false;
	cheatActive = false;
	playerHealth = PLAYER_DEFAULT_HEALTH;
	redFiveHealth = RED_5_DEFAULT_HEALTH;
	currentCameraIndex = 0;
	endSequenceRemaining = END_SEQUENCE_LENGTH;
}

Level::~Level()
{
	myGarlicAllocator = nullptr;
	myOnionAllocator = nullptr;
	myToolkitAllocators = nullptr;
	pDeathStar = nullptr;
	pYavinIV = nullptr;
	pExplosion = nullptr;
	pMillenniumFalcon = nullptr;
}

void Level::initialise(LinearAllocator* garlicAllocator, LinearAllocator* onionAllocator, sce::Gnmx::Toolkit::Allocators* toolkitAllocators, float aspectRatio, std::shared_ptr<PtAssetManager> pAssetManager, std::shared_ptr<PtController> pController)
{
	myGarlicAllocator = garlicAllocator;
	myOnionAllocator = onionAllocator;
	myToolkitAllocators = toolkitAllocators;
	this->pAssetManager = pAssetManager;

	lights.getLight(0)->setLocationVx(Vector3(0, -10, -10));
	lights.getLight(1)->setLocationVx(Vector3(-2, 0, 2));

	for (int i = 0; i < TOTAL_CAMERAS; i++)
	{
		cameras[i] = std::make_shared<PtCamera>();
		cameras[i]->setPerspective(1.57f, aspectRatio, 0.001f, 100.0f);
	}

	remainingEnemies = TOTAL_TIE_FIGHTERS;

	this->pController = pController;
	
	std::shared_ptr<CollisionComponent> pPlayerCollisionComponent = std::make_shared<CollisionComponent>();
	pPlayerCollisionComponent->initialise(0.3f, 1.0f, 0.5f);

	std::shared_ptr<PlayerObject> pPlayer = std::make_shared<PlayerObject>();
	pPlayer->initialise(pPlayerCollisionComponent, PtObjectsEnum::MILLENNIUM_FALCON);
	pPlayer->setCamera(cameras[0]);
	pPlayer->setController(this->pController);
	pPlayer->setLevel(this);
	pPlayer->setModel(pAssetManager->getLoadedModel(PtModelsEnum::FALCON_MODEL));
	pPlayer->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FALCON_MATERIAL));
	pObjects.push_back(pPlayer);
	pMillenniumFalcon = pPlayer;

	pPlayerCollisionComponent->setCentrePoint(pPlayer->getPosition());

	std::shared_ptr<CollisionComponent> pGenericCollision = std::make_shared<CollisionComponent>();
	pGenericCollision->initialise(1, 1, 1);

	std::shared_ptr<PtObject> pDeathStar = std::make_shared<PtObject>();
	pDeathStar->setModelWorldMatrix(Matrix4::translation(Vector3(0, -43, -10)));
	pDeathStar->setInitialTranslationMatrix(Matrix4::translation(Vector3(0, -43, -10)));
	pDeathStar->scale(Matrix4::scale(Vector3(40, 40, 40)));
	pDeathStar->setModel(pAssetManager->getLoadedModel(PtModelsEnum::SPHERE_MODEL));
	pDeathStar->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::DEATH_STAR_MATERIAL));
	pDeathStar->getModel()->setDefaultColour(Vector3(0.5, 0.5 ,0.5));
	pObjects.push_back(pDeathStar);
	this->pDeathStar = pDeathStar;

	pDeathStar->initialise(pGenericCollision, PtObjectsEnum::DEATH_STAR);
	pGenericCollision->setCentrePoint(pDeathStar->getPosition());

	Vector3 squad1Position(-2, -1, -9);
	Vector3 squad2Position(-4, 0, -10);
	for (int i = 0; i < TOTAL_TIE_FIGHTERS; i++)
	{
		std::shared_ptr<CollisionComponent> pEnemyCollisionComponent = std::make_shared<CollisionComponent>();
		pEnemyCollisionComponent->initialise(0.4, 0.4, 0.35);

		std::shared_ptr<Enemy> pTieFighter = std::make_shared<Enemy>();
		pTieFighter->initialise(pEnemyCollisionComponent, PtObjectsEnum::TIE_FIGHTER);
		pTieFighter->setModel(pAssetManager->getLoadedModel(PtModelsEnum::TIE_FIGHTER_MODEL));
		pTieFighter->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::TIE_FIGHTER_MATERIAL));
		pTieFighter->setLevel(this);
		pObjects.push_back(pTieFighter);

		if (i > 9)
		{
			pTieFighter->move(Matrix4::translation(squad2Position));
			pTieFighter->setInitialTranslationMatrix(Matrix4::translation(squad2Position));
			pTieFighter->setTieFighterTarget(TieFighterTargets::RED_FIVE);
			pTieFighter->rotateX(Matrix4::rotationX(1.57));
			squad2Position.setX(squad2Position.getX() + 1.5);
			squad2Position.setY(squad2Position.getY() + 1.5);
		}
		else
		{
			pTieFighter->move(Matrix4::translation(squad1Position));
			pTieFighter->setInitialTranslationMatrix(Matrix4::translation(squad1Position));
			pTieFighter->setTieFighterTarget(TieFighterTargets::MILLENNIUM_FALCON);

			if (i == 4)
			{
				squad1Position.setX(-2);
				squad1Position.setY(1);
			}
			else
			{
				squad1Position.setX(squad1Position.getX() + 1);
			}
		}
	}

	std::shared_ptr<CollisionComponent> pStarDestroyerCollision = std::make_shared<CollisionComponent>();
	pStarDestroyerCollision->initialise(1, 1, 1);
	std::shared_ptr<PtObject> pStarDestroyer = std::make_shared<PtObject>();
	pStarDestroyer->setModelWorldMatrix(Matrix4::translation(Vector3(-15, 2, -15)));
	pStarDestroyer->setInitialTranslationMatrix(Matrix4::translation(Vector3(-15, 2, -15)));
	pStarDestroyer->scale(Matrix4::scale(Vector3(5, 5, 5)));
	pStarDestroyer->setModel(pAssetManager->getLoadedModel(PtModelsEnum::STAR_DESTROYER_MODEL));
	pStarDestroyer->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::STAR_DESTROYER_MATERIAL));
	pObjects.push_back(pStarDestroyer);
	pStarDestroyer->initialise(pStarDestroyerCollision, PtObjectsEnum::STAR_DESTROYER);

	std::shared_ptr<CollisionComponent> pPlanetCollision = std::make_shared<CollisionComponent>();
	pPlanetCollision->initialise(1, 1, 1);
	std::shared_ptr<PtObject> pPlanet = std::make_shared<PtObject>();
	pPlanet->setModelWorldMatrix(Matrix4::translation(Vector3(10, 10, -50)));
	pPlanet->setInitialTranslationMatrix(Matrix4::translation(Vector3(10, 10, -50)));
	pPlanet->scale(Matrix4::scale(Vector3(6, 6, 6)));
	pPlanet->setModel(pAssetManager->getLoadedModel(PtModelsEnum::SPHERE_MODEL));
	pPlanet->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::PLANET_MATERIAL));
	pObjects.push_back(pPlanet);
	pPlanet->initialise(pPlanetCollision, PtObjectsEnum::PLANET);
	pYavinIV = pPlanet;

	std::shared_ptr<CollisionComponent> pPyramidCollision = std::make_shared<CollisionComponent>();
	pPyramidCollision->initialise(1, 1, 1);
	std::shared_ptr<Shuttle> pPyramid = std::make_shared<Shuttle>();
	pPyramid->setInitialTranslationMatrix(Matrix4::translation(Vector3(-17, 0, -20)));
	pPyramid->setModelWorldMatrix(Matrix4::translation(Vector3(-17, 0, -20)));
	pPyramid->setModel(pAssetManager->getLoadedModel(PtModelsEnum::PYRAMID_MODEL));
	pPyramid->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::PYRAMID_MATERIAL));
	pObjects.push_back(pPyramid);
	pPyramid->initialise(pPyramidCollision, PtObjectsEnum::SHUTTLE);
	pPyramid->setStarDestroyerTranslationMatrix(Matrix4::translation(Vector3(-15, 2, -15)));

	std::shared_ptr<CollisionComponent> pRingCollision = std::make_shared<CollisionComponent>();
	pRingCollision->initialise(1, 1, 1);
	std::shared_ptr<ExplosionRing> pRing = std::make_shared<ExplosionRing>();
	pRing->setInitialTranslationMatrix(Matrix4::translation(Vector3(0, -10, -20)));
	pRing->setModelWorldMatrix(Matrix4::translation(Vector3(0, -10, -20)));
	pRing->setModel(pAssetManager->getLoadedModel(PtModelsEnum::RING_MODEL));
	pRing->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::RING_MATERIAL));
	pObjects.push_back(pRing);
	pRing->initialise(pRingCollision, PtObjectsEnum::RING);
	pRing->setActive(false);
	pExplosion = pRing;

	hud[HEALTH_TEXT] = std::make_shared<PtHUDTextItem>();
	hud[HEALTH_TEXT]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	hud[HEALTH_TEXT]->initialise(myGarlicAllocator, "Health:", 1.5, -0.95, 0.95);

	hud[HEALTH_VALUE] = std::make_shared<PtHUDTextItem>();
	hud[HEALTH_VALUE]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	hud[HEALTH_VALUE]->initialise(myGarlicAllocator, playerHealth, 1.5, -0.83, 0.95, 3);

	hud[RED_FIVE_HEALTH_TEXT] = std::make_shared<PtHUDTextItem>();
	hud[RED_FIVE_HEALTH_TEXT]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	hud[RED_FIVE_HEALTH_TEXT]->initialise(myGarlicAllocator, "Red 5 Health:", 1.5, -0.95, 0.9);

	hud[RED_FIVE_HEALTH_VALUE] = std::make_shared<PtHUDTextItem>();
	hud[RED_FIVE_HEALTH_VALUE]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	hud[RED_FIVE_HEALTH_VALUE]->initialise(myGarlicAllocator, redFiveHealth, 1.5, -0.75, 0.9, 3);

	hud[TIE_FIGHTERS_TEXT] = std::make_shared<PtHUDTextItem>();
	hud[TIE_FIGHTERS_TEXT]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	hud[TIE_FIGHTERS_TEXT]->initialise(myGarlicAllocator, "TIE Fighters:", 1.5, -0.95, 0.85);

	hud[TIE_FIGHTERS_VALUE] = std::make_shared<PtHUDTextItem>();
	hud[TIE_FIGHTERS_VALUE]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	hud[TIE_FIGHTERS_VALUE]->initialise(myGarlicAllocator, remainingEnemies, 1.5, -0.75, 0.85, 2);

	hud[CHEAT_TEXT] = std::make_shared<PtHUDTextItem>();
	hud[CHEAT_TEXT]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	hud[CHEAT_TEXT]->initialise(myGarlicAllocator, "Cheat Inactive", 1.5, -0.95, 0.8);
}

ScreenStates Level::update()
{
	unsigned int size = pObjects.size();
	for (int i = 0; i < size; i++)
	{
		if (pObjects[i]->getActive())
		{
			pObjects[i]->update();
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int c = i; c < size; c++)
		{
			if (c != i)
			{
				if(pObjects[i]->getActive() && pObjects[c]->getActive())
				{
					if (pObjects[i]->getCollisionComponent()->checkCollision(pObjects[c]->getCollisionComponent()->getShape()))
					{
						pObjects[i]->collide(pObjects[c]->getType());
						pObjects[c]->collide(pObjects[i]->getType());
					}
				}
			}
		}
	}

	if (success || fail)
	{
		endSequenceRemaining--;
	}

	pObjects[1]->pitchRotation(0.0005);
	deleteInactiveBullets();

	if (pController->optionsTrigger())
	{
		return ScreenStates::PAUSE_MENU;
	}

	extras();

	if (fail && endSequenceRemaining == 0)
	{
		return ScreenStates::LOSS_MENU;
	}
	else if (success && endSequenceRemaining == 0)
	{
		return ScreenStates::WIN_MENU;
	}
	else
	{
		return ScreenStates::REMAIN;
	}
}

void Level::extras()
{
	if (pController->triangleTrigger())
	{
		if (pController->toggleTriangle())
		{
			hud[CHEAT_TEXT]->updateText(myGarlicAllocator, "Cheat Active");
			cheatActive = true;
		}
		else
		{
			hud[CHEAT_TEXT]->updateText(myGarlicAllocator, "Cheat Inactive");
			cheatActive = false;
		}
	}

	if (pController->squareTrigger())
	{
		if (currentCameraIndex == 0)
		{
			currentCameraIndex = 1;
		}
		else
		{
			currentCameraIndex = 0;
		}
	}

	if (pController->circleTrigger())
	{
		if (lights.getLight(0)->getIsOn())
		{
			lights.getLight(0)->setIsOn(false);
		}
		else
		{
			lights.getLight(0)->setIsOn(true);
		}
	}

	if (pController->crossTrigger())
	{
		if (lights.getLight(1)->getIsOn())
		{
			lights.getLight(1)->setIsOn(false);
		}
		else
		{
			lights.getLight(1)->setIsOn(true);
		}
	}

	cameras[1]->yawRotation(pController->rightStickY() / -50);
	cameras[1]->pitchRotation(pController->rightStickX() / -50);

	if (pController->upPressed())
	{
		cameras[1]->trackUpDown(0.06);
	}
	if (pController->downPressed())
	{
		cameras[1]->trackUpDown(-0.06);
	}
	if (pController->rightPressed())
	{
		cameras[1]->trackLeftRight(0.06);
	}
	if (pController->leftPressed())
	{
		cameras[1]->trackLeftRight(-0.06);
	}
}

void Level::draw(Gnmx::GnmxGfxContext* myGFXC)
{
	unsigned int size = pObjects.size();
	for (int i = 0; i < size; i++)
	{
		if (pObjects[i]->getActive())
		{
			drawManager.draw(myGFXC, pObjects[i], lights, cameras[currentCameraIndex]);
		}
	}

	for (int i = 0; i < HUD_ITEMS; i++)
	{
		drawManager.drawHUD(myGFXC, hud[i]);
	}
}

void Level::fireBullet(Matrix4 startPosition, PtObjectsEnum owner)
{
	if (!fail)
	{
		std::shared_ptr<CollisionComponent> pBulletCollision = std::make_shared<CollisionComponent>();
		pBulletCollision->initialise(0.1f, 0.1f, 0.1f);

		std::shared_ptr<Bullet> pBullet = std::make_shared<Bullet>();
		pBullet->initialise(pBulletCollision, owner);
		pBullet->move(startPosition);
		pBullet->setModel(pAssetManager->getLoadedModel(PtModelsEnum::SPHERE_MODEL));

		if (owner == PtObjectsEnum::MILLENNIUM_FALCON_BULLET)
		{
			pBullet->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::RED_BEAM_MATERIAL));
		}
		else
		{
			pBullet->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::GREEN_BEAM_MATERIAL));
		}

		pBullet->setLevel(this);
		pObjects.push_back(pBullet);
	}
}

void Level::deleteInactiveBullets()
{
	for (std::shared_ptr<PtObject>& pObject : pObjects)
	{
		if (pObject)
		{
			if (pObject->getActive() == false)
			{
				if (pObject->getType() == PtObjectsEnum::MILLENNIUM_FALCON_BULLET || pObject->getType() == PtObjectsEnum::TIE_FIGHTER_BULLET)
				{
					pObject.reset();
					pObject = nullptr;
				}
			}
		}
	}

	std::vector<std::shared_ptr<PtObject>>::iterator iterator = std::remove(pObjects.begin(), pObjects.end(), nullptr);
	pObjects.erase(iterator, pObjects.end());
}

void Level::deleteAllBullets()
{
	for (std::shared_ptr<PtObject>& pObject : pObjects)
	{
		if (pObject)
		{
			if (pObject->getType() == PtObjectsEnum::MILLENNIUM_FALCON_BULLET || pObject->getType() == PtObjectsEnum::TIE_FIGHTER_BULLET)
			{
				pObject.reset();
				pObject = nullptr;
			}
		}
	}

	std::vector<std::shared_ptr<PtObject>>::iterator iterator = std::remove(pObjects.begin(), pObjects.end(), nullptr);
	pObjects.erase(iterator, pObjects.end());
}

void Level::setBulletsInactive()
{
	for (std::shared_ptr<PtObject>& pObject : pObjects)
	{
		if (pObject)
		{
			if (pObject->getType() == PtObjectsEnum::MILLENNIUM_FALCON_BULLET || pObject->getType() == PtObjectsEnum::TIE_FIGHTER_BULLET)
			{
				pObject->setActive(false);
			}
		}
	}
}

void Level::enemyHit()
{
	remainingEnemies--;
	hud[TIE_FIGHTERS_VALUE]->updateNumber(myGarlicAllocator, remainingEnemies);

	if (remainingEnemies == 0)
	{
		win();
	}
}

void Level::playerHit()
{
	if (!cheatActive)
	{
		playerHealth = playerHealth - TIE_FIGHTER_PLAYER_DAMAGE;
		hud[HEALTH_VALUE]->updateNumber(myGarlicAllocator, playerHealth);

		if (playerHealth <= 0)
		{
			hud[HEALTH_VALUE]->updateNumber(myGarlicAllocator, 0);
			pMillenniumFalcon->setActive(false);
			loss();
		}
	}
}

void Level::redFiveHit()
{
	if (!cheatActive)
	{
		redFiveHealth = redFiveHealth - TIE_FIGHTER_RED_FIVE_DAMAGE;
		hud[RED_FIVE_HEALTH_VALUE]->updateNumber(myGarlicAllocator, redFiveHealth);

		if (redFiveHealth <= 0)
		{
			hud[RED_FIVE_HEALTH_VALUE]->updateNumber(myGarlicAllocator, 0);
			loss();
		}
	}
}

void Level::win()
{
	success = true;
	setBulletsInactive();
	pDeathStar->setActive(false);
	pExplosion->setActive(true);
	pExplosion->setModelWorldMatrix(Matrix4::translation(Vector3(0, -10, -20)));
}

void Level::loss()
{
	if (!fail)
	{
		fail = true;
		pYavinIV->setActive(false);
		pExplosion->setActive(true);
		pExplosion->setModelWorldMatrix(Matrix4::translation(Vector3(10, 10, -50)));
	}
}

void Level::reset()
{
	if (cheatActive)
	{
		pController->toggleTriangle();
	}

	for (int i = 0; i < PT_LIGHT_COUNT; i++)
	{
		lights.getLight(i)->setIsOn(true);
	}

	endSequenceRemaining = END_SEQUENCE_LENGTH;
	fail = false;
	success = false;
	cheatActive = false;
	playerHealth = PLAYER_DEFAULT_HEALTH;
	redFiveHealth = RED_5_DEFAULT_HEALTH;
	currentCameraIndex = 0;
	remainingEnemies = TOTAL_TIE_FIGHTERS;
	deleteAllBullets();

	for (int c = 0; c < TOTAL_CAMERAS; c++)
	{
		cameras[c]->reset();
	}

	unsigned int size = pObjects.size();
	for (int c = 0; c < size; c++)
	{
		pObjects[c]->reset();
	}

	hud[RED_FIVE_HEALTH_VALUE]->updateNumber(myGarlicAllocator, redFiveHealth);
	hud[HEALTH_VALUE]->updateNumber(myGarlicAllocator, playerHealth);
	hud[TIE_FIGHTERS_VALUE]->updateNumber(myGarlicAllocator, remainingEnemies);
	hud[CHEAT_TEXT]->updateText(myGarlicAllocator, "Cheat Inactive");
}