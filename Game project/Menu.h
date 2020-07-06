#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <video_out.h>
#include "../../toolkit/toolkit.h"
#include "../../common/allocator.h"
#include "../../common/danGraphicsWrapper.h"
#include "GameState.h"
#include "PtCamera.h"
#include "PtController.h"
#include <memory>
#include "PtHUDTextItem.h"
#include "ptDrawManager.h"
#include "PtAssetManager.h"

class Menu : public GameState
{
private:
	static const unsigned int HUD_ITEMS = 4;
	PtDrawManager drawManager;
	LinearAllocator* myOnionAllocator;
	LinearAllocator* myGarlicAllocator;
	std::shared_ptr<PtController> pController;
	std::shared_ptr<PtAssetManager> pAssetManager;
	sce::Gnmx::Toolkit::Allocators* myToolkitAllocators;
	std::shared_ptr<PtHUDTextItem> pItems[HUD_ITEMS];
	ScreenStates currentState;

public:
	void initialise(LinearAllocator* garlicAllocator, LinearAllocator* onionAllocator, sce::Gnmx::Toolkit::Allocators* toolkitAllocators, float aspectRatio, std::shared_ptr<PtAssetManager> pAssetManager, std::shared_ptr<PtController> pController) override;
	ScreenStates update() override;
	void draw(Gnmx::GnmxGfxContext* myGFXC) override;
	void makeEntryMenu();
	void makeWinMenu();
	void makeLossMenu();
	void makePauseMenu();
};

#endif
