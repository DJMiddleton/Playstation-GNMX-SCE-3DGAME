#ifndef __PT_PIPELINE__
#define __PT_PIPELINE__

#include <scebase.h>
#include <kernel.h>
#include <gnmx.h>
#include "../../common/allocator.h"
#include "PtAssetTypes.h"
#include "PtAllShaderConstants.h"

using namespace sce;
using namespace sce::Gnmx;

class PtPipeline
{
private:
	//shader stuff
	VsShader* vertexShader;
	PsShader* pixelShader;
	void* fetchShader;
	Gnmx::InputOffsetsCache vSInputOffsetsCache;
	Gnmx::InputOffsetsCache	pSInputOffsetsCache;
	uint32_t shaderModifier;
	bool initialised;
	int totalTextures;
	const char* fileName1;
	const char* fileName2;
	PtAssetTypes type;
	PtShaderConstants shaderConstant;

public:
	PtPipeline();
	int loadShaders(LinearAllocator* garlicAllocator, Toolkit::Allocators* toolkitAllocators);
	void use(Gnmx::GnmxGfxContext* myGFXC);
	void setFileName1(const char* fileName);
	void setFileName2(const char* fileName);
	void setTotalTextures(int textures);
	void setType(PtAssetTypes type);
	PtShaderConstants getShaderConstant();
	int getTotalTextures();
	void setShaderConstant(PtShaderConstants constant);
};

#endif