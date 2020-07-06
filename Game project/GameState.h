#ifndef __GAME_STATE__
#define __GAME_STATE__

#include <memory>
#include "PtAssetManager.h"
#include "ScreenStates.h"
#include "PtController.h"

class GameState
{
public:
	virtual ~GameState() {};
	virtual	void initialise(LinearAllocator* garlicAllocator, LinearAllocator* onionAllocator, sce::Gnmx::Toolkit::Allocators* toolkitAllocators, float aspectRatio, std::shared_ptr<PtAssetManager> pAssetManager, std::shared_ptr<PtController> pController) = 0;
	virtual ScreenStates update() = 0;
	virtual void draw(Gnmx::GnmxGfxContext* myGFXC) = 0;
};

#endif
