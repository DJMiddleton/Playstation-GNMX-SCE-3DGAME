#ifndef __PT_DRAW_MANAGER__
#define __PT_DRAW_MANAGER__

#include "ptModel.h"
#include "../../toolkit/toolkit.h"
#include <gnmx.h>
#include "PtAllShaderConstants.h"
#include "PtCamera.h"
#include "PtObject.h"
#include "PtLight.h"
#include "PtLightCount.h"
#include "PtLightEnvironment.h"
#include "PtHUDTextItem.h"
#include <memory>

class PtDrawManager
{
public:
	void draw(Gnmx::GnmxGfxContext* gfxc, std::shared_ptr<PtObject> pObject, PtLightEnvironment environment, std::shared_ptr<PtCamera> pCamera);
	void drawHUD(Gnmx::GnmxGfxContext* gfxc, std::shared_ptr<PtHUDTextItem> pItem);
};

#endif
