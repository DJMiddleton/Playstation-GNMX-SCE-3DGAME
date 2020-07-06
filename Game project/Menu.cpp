#include "Menu.h"

void Menu::initialise(LinearAllocator* garlicAllocator, LinearAllocator* onionAllocator, sce::Gnmx::Toolkit::Allocators* toolkitAllocators, float aspectRatio, std::shared_ptr<PtAssetManager> pAssetManager, std::shared_ptr<PtController> pController)
{
	myGarlicAllocator = garlicAllocator;
	myOnionAllocator = onionAllocator;
	myToolkitAllocators = toolkitAllocators;
	this->pAssetManager = pAssetManager;
	this->pController = pController;
	currentState = ScreenStates::ENTRY_MENU;
	
	pItems[0] = std::make_shared<PtHUDTextItem>();
	pItems[0]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	pItems[0]->initialise(myGarlicAllocator, "Trench Run            ", 4, -0.3, 0.85);

	pItems[1] = std::make_shared<PtHUDTextItem>();
	pItems[1]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	pItems[1]->initialise(myGarlicAllocator, "Red Five has started his attack on the Death Star. Your task is protect him while he makes the trench run. To do this, you must pilot the Millennium Falcon and destroy all TIE fighters you see", 1, -0.95, 0.7);

	pItems[2] = std::make_shared<PtHUDTextItem>();
	pItems[2]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	pItems[2]->initialise(myGarlicAllocator, "Some TIE Fighters will attack you and some will attack Red Five. You must stop stop them from killing you while also stopping them from getting too close to Red Five on the Death Star surface", 1, -0.95, 0.65);

	pItems[3] = std::make_shared<PtHUDTextItem>();
	pItems[3]->setMaterial(pAssetManager->getMaterial(PtMaterialsEnum::FONT_MATERIAL));
	pItems[3]->initialise(myGarlicAllocator, "Press Options to start game. Press Circle to exit. Left stick controls forward/back and left/right movement. R1 to move up. L1 to move down", 1, -0.95, 0.6);
}

void Menu::draw(Gnmx::GnmxGfxContext* myGFXC)
{
	for (int i = 0; i < HUD_ITEMS; i++)
	{
		if (pItems[i])
		{
			drawManager.drawHUD(myGFXC, pItems[i]);
		}
	}
}

ScreenStates Menu::update()
{
	if (pController->optionsTrigger())
	{
		if (currentState == ScreenStates::ENTRY_MENU)
		{
			return ScreenStates::NEW_GAME;
		}
		else if (currentState == ScreenStates::PAUSE_MENU)
		{
			return ScreenStates::RESUME_GAME;
		}
		else
		{
			return ScreenStates::ENTRY_MENU;
		}
	}
	else if (pController->circleTrigger())
	{
		return ScreenStates::EXIT;
	}
	else if (pController->squareTrigger() && currentState == ScreenStates::PAUSE_MENU)
	{
		return ScreenStates::ENTRY_MENU;
	}
	else
	{
		return ScreenStates::REMAIN;
	}
}

void Menu::makeEntryMenu()
{
	pItems[0]->updateText(myGarlicAllocator, "Trench Run");
	pItems[1]->updateText(myGarlicAllocator, "Red Five has started his attack on the Death Star. Your task is protect him while he makes the trench run. To do this, you must pilot the Millennium Falcon and destroy all TIE fighters you see");
	pItems[2]->updateText(myGarlicAllocator, "Some TIE Fighters will attack you and some will attack Red Five. You must stop stop them from killing you while also stopping them from getting too close to Red Five on the Death Star surface");
	pItems[3]->updateText(myGarlicAllocator, "Press Options to start game. Press Circle to exit. Left stick controls forward/back and left/right movement. R1 to move up. L1 to move down. R2 to Fire. Triangle turns cheat On/Off");
	currentState = ScreenStates::ENTRY_MENU;
}

void Menu::makeWinMenu()
{
	pItems[0]->updateText(myGarlicAllocator, "You Have Succeeded");
	pItems[1]->updateText(myGarlicAllocator, "The Death Star has been destroyed. The Rebellion has defeated the Empire");
	pItems[2]->updateText(myGarlicAllocator, "The galaxy is safe again");
	pItems[3]->updateText(myGarlicAllocator, "Press Options to restart. Press Circle to exit");
	currentState = ScreenStates::WIN_MENU;
}

void Menu::makeLossMenu()
{
	pItems[0]->updateText(myGarlicAllocator, "You Have Failed");
	pItems[1]->updateText(myGarlicAllocator, "You Are Beaten, It Is Useless To Resist, The Death Star has not been destroyed. The Rebellion has been crushed. It's Over");
	pItems[2]->updateText(myGarlicAllocator, "The Empire will continue to control the galaxy");
	pItems[3]->updateText(myGarlicAllocator, "Press Options to restart. Press Circle to exit");
	currentState = ScreenStates::LOSS_MENU;
}

void Menu::makePauseMenu()
{
	pItems[0]->updateText(myGarlicAllocator, "Pause");
	pItems[1]->updateText(myGarlicAllocator, "Press Options to resume");
	pItems[2]->updateText(myGarlicAllocator, "Press Circle to exit");
	pItems[3]->updateText(myGarlicAllocator, "Press Square to Restart");
	currentState = ScreenStates::PAUSE_MENU;
}