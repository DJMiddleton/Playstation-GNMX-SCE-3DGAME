#ifndef __PT_ASSET_MANAGER__
#define __PT_ASSET_MANAGER__

#include "ptModel.h"
#include "ModelsEnum.h"
#include "PtPipelineTypes.h"
#include "PtAssetTypes.h"
#include "PtTexture.h"
#include "TexturesEnum.h"
#include "PtMaterials.h"
#include "PtPipeline.h"
#include "PtMaterial.h"
#include "PtAllShaderConstants.h"
#include "../../common/danTextureLoader.h"

class PtAssetManager
{
private:
	LinearAllocator* myOnionAllocator;
	LinearAllocator* myGarlicAllocator;
	sce::Gnmx::Toolkit::Allocators* myToolkitAllocators;
	std::shared_ptr<PtPipeline> myPipelines[PtPipelines::PT_PIPELINE_COUNT];
	std::shared_ptr<PtModel> myModels[PtModelsEnum::PT_MODEL_COUNT];
	std::shared_ptr<PtTexture> myTextures[PtTexturesEnum::PT_TEXTURE_COUNT];
	std::shared_ptr<PtMaterial> myMaterials[PtMaterialsEnum::PT_MATERIALS_COUNT];
	danTextureLoader textureLoader;
	Gnm::Sampler textureSampler;

public:
	void initialise(LinearAllocator* garlicAllocator, LinearAllocator* onionAllocator, sce::Gnmx::Toolkit::Allocators* toolkitAllocators);
	std::shared_ptr<PtModel> getLoadedModel(PtModelsEnum model);
	Gnm::Texture* getTexture(PtTexturesEnum texture);
	std::shared_ptr<PtPipeline> getPipeline(PtPipelines pipeline);
	std::shared_ptr<PtMaterial> getMaterial(PtMaterialsEnum materialType);
};

#endif