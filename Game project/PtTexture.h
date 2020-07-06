#ifndef __PT_TEXTURE__
#define __PT_TEXTURE__

#include <gnmx.h>
#include "PtAssetTypes.h"
using namespace sce;

struct PtTexture
{
public:
	Gnm::Texture texture;
	const char* filename = nullptr;
	PtAssetTypes assetType = PtAssetTypes::TEXTURE_GNF;
	bool validData = false;
	uint8_t index = 0;
};

#endif