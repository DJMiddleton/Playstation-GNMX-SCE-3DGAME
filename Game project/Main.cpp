/* SIE CONFIDENTIAL
PlayStation(R)4 Programmer Tool Runtime Library Release 04.008.061
* Copyright (C) 2015 Sony Interactive Entertainment Inc.
* All Rights Reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <scebase.h>
#include <kernel.h>
#include <gnmx.h>
#include <video_out.h>
#include "../../toolkit/toolkit.h"
#include "../../common/allocator.h"
#include "../../common/danGraphicsWrapper.h"
#include "PtController.h"
#include "PtAssetManager.h"
#include <vector>
#include "Level.h"
#include "GameState.h"
#include "Menu.h"
#include <ctime>

using namespace sce;
using namespace sce::Gnmx;

int main(int _argc, const char* _argv[])
{
	//define the size of our memory heaps
	static const size_t sc_onionMemorySize				= 16 * 1024 * 1024;
	static const size_t sc_garlicMemorySize				= 64 * 4 * 1024 * 1024;

	//just a little check to see if things are working
	printf("Hello World!\n");
	
	//utility for error messages
	int l_error = 0;

	// there are several types of memory access available, but we need to do our own memory management
	// the three main types are "CPU" (which is used automatically) "Onion" for larger CPU use and "Garlic" for GPU use
	// Initialize the WB_ONION memory allocator
	LinearAllocator myOnionAllocator;
	l_error = myOnionAllocator.initialize(sc_onionMemorySize, SCE_KERNEL_WB_ONION, SCE_KERNEL_PROT_CPU_RW | SCE_KERNEL_PROT_GPU_ALL);
	if (l_error != SCE_OK) 
	{ 
		printf("Onion allocator failed to initialise: 0x%08X\n", l_error); 
		return l_error; 
	}

	// Initialize the WC_GARLIC memory allocator
	// NOTE: CPU reads from GARLIC write-combined memory have a very low
	//       bandwidth so they are disabled for safety in this sample
	LinearAllocator myGarlicAllocator;
	l_error = myGarlicAllocator.initialize(sc_garlicMemorySize, SCE_KERNEL_WC_GARLIC, SCE_KERNEL_PROT_CPU_WRITE | SCE_KERNEL_PROT_GPU_ALL);
	if (l_error != SCE_OK)
	{ 
		printf("Garlic allocator failed to initialise: 0x%08X\n", l_error); 
		return l_error; 
	}

	// We are using three wrappers to the hardware provided by Sony
	// "Gnm" is their low-level graphics API
	// On top of this they provide "Gnmx" with higher level functionality
	// Both Gnm and Gnmx are accessed through libraries and are part of the standard SCE API
	// There is also "toolkit" which was developed for their sample programs
	// This adds yet more abstraction above Gnm and Gnmx
	// However, it is not part of the standard API and so including it in projects is a little cumbersome
	// Sony advise it is not fit for use in release mode games.

	// Initialize the Toolkit module
	sce::Gnmx::Toolkit::Allocators myToolkitAllocators;
	myOnionAllocator.getIAllocator(myToolkitAllocators.m_onion);
	myGarlicAllocator.getIAllocator(myToolkitAllocators.m_garlic);
	Toolkit::initializeWithAllocators(&myToolkitAllocators);

	// Finally, there is a fourth layer of wrapper, the danGraphicsWrapper
	// this is provided by Dan Hodgson for use for students with his tutor series
	// It abstracts away a whole load of hardware stuff including render contexts, video surfaces and concurrency
	danGraphicsWrapper myGraphicsWrapper;
	l_error = myGraphicsWrapper.init(&myOnionAllocator, &myGarlicAllocator);
	if (l_error != SCE_OK)
	{ 
		printf("Graphics Wrapper failed to init: 0x%08X\n", l_error);  
		return l_error; 
	}

	srand((unsigned int)time(NULL));
	const float t_aspectRatio = float(myGraphicsWrapper.getBufferWidth()) / float(myGraphicsWrapper.getBufferHeight());

	std::shared_ptr<PtAssetManager> pAssetManager = std::make_shared<PtAssetManager>();
	pAssetManager->initialise(&myGarlicAllocator, &myOnionAllocator, &myToolkitAllocators);

	std::shared_ptr<PtController> pController = std::make_shared<PtController>();
	pController->initialise();

	Level* pLevel = new Level();
	pLevel->initialise(&myGarlicAllocator, &myOnionAllocator, &myToolkitAllocators, t_aspectRatio, pAssetManager, pController);

	Menu* pMenu = new Menu(); 
	pMenu->initialise(&myGarlicAllocator, &myOnionAllocator, &myToolkitAllocators, t_aspectRatio, pAssetManager, pController);

	GameState* pCurrentState = pMenu;
	ScreenStates screen = ScreenStates::REMAIN;

	//main draw loop
	while (screen != ScreenStates::EXIT)
	{
		//required to set states ready for draw commands
		myGraphicsWrapper.preDraw();

		//Grab a pointer to the current graphics context, to give us direct access
		Gnmx::GnmxGfxContext* myGFXC = myGraphicsWrapper.getRenderContext();
	
		if (pCurrentState)
		{
			pController->update();
			screen = pCurrentState->update();
			pCurrentState->draw(myGFXC);

			if (screen == ScreenStates::NEW_GAME)
			{
				pLevel->reset();
				pCurrentState = pLevel;
			}
			else if (screen == ScreenStates::RESUME_GAME)
			{
				pCurrentState = pLevel;
			}
			else if (screen == ScreenStates::ENTRY_MENU)
			{
				pCurrentState = pMenu;
				pMenu->makeEntryMenu();
			}
			else if (screen == ScreenStates::WIN_MENU)
			{
				pCurrentState = pMenu;
				pMenu->makeWinMenu();
			}
			else if (screen == ScreenStates::LOSS_MENU)
			{
				pCurrentState = pMenu;
				pMenu->makeLossMenu();
			}
			else if (screen == ScreenStates::PAUSE_MENU)
			{
				pCurrentState = pMenu;
				pMenu->makePauseMenu();
			}
		}

		//and this neeeds to be done after all draw calls, to end the frame.
		myGraphicsWrapper.postDraw();
	}// main loop

	delete pLevel;
	delete pMenu;
	pCurrentState = nullptr;
	pLevel = nullptr;
	pMenu = nullptr;

	//tidy up
	myGraphicsWrapper.release();

	// Releasing manually each allocated resource is not necessary as we are
	// terminating the linear allocators for ONION and GARLIC here.
	//myOnionAllocator.terminate();
	//myGarlicAllocator.terminate();

	return 0;
}//main()
