#include "PtAssetManager.h"

void PtAssetManager::initialise(LinearAllocator* garlicAllocator, LinearAllocator* onionAllocator, sce::Gnmx::Toolkit::Allocators* toolkitAllocators)
{
	textureSampler.init();
	textureSampler.setMipFilterMode(Gnm::kMipFilterModeNone);
	textureSampler.setXyFilterMode(Gnm::kFilterModeBilinear, Gnm::kFilterModeBilinear);

	myOnionAllocator = onionAllocator;
	myGarlicAllocator = garlicAllocator;
	myToolkitAllocators = toolkitAllocators;

	myModels[PtModelsEnum::FALCON_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::FALCON_MODEL]->setFilename("/app0/assets/models/obj/Millennium Falcon white.obj");
	myModels[PtModelsEnum::FALCON_MODEL]->setAssetType(PtAssetTypes::MODEL_OBJ);

	myModels[PtModelsEnum::SPHERE_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::SPHERE_MODEL]->setFilename("/app0/assets/models/ptm/sphere.ptm");
	myModels[PtModelsEnum::SPHERE_MODEL]->setAssetType(PtAssetTypes::MODEL_PTM);

	myModels[PtModelsEnum::TIE_FIGHTER_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::TIE_FIGHTER_MODEL]->setFilename("/app0/assets/models/obj/TIE Fighter no textures.obj");
	myModels[PtModelsEnum::TIE_FIGHTER_MODEL]->setAssetType(PtAssetTypes::MODEL_OBJ);

	myModels[PtModelsEnum::CUBE_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::CUBE_MODEL]->setFilename("/app0/assets/models/ptm/CubeSplitFace.ptm");
	myModels[PtModelsEnum::CUBE_MODEL]->setAssetType(PtAssetTypes::MODEL_PTM);

	myModels[PtModelsEnum::FLOOR_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::FLOOR_MODEL]->setFilename("/app0/assets/models/ptm/floor.ptm");
	myModels[PtModelsEnum::FLOOR_MODEL]->setAssetType(PtAssetTypes::MODEL_PTM);

	myModels[PtModelsEnum::STAR_DESTROYER_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::STAR_DESTROYER_MODEL]->setFilename("/app0/assets/models/obj/Star Destroyer.obj");
	myModels[PtModelsEnum::STAR_DESTROYER_MODEL]->setAssetType(PtAssetTypes::MODEL_OBJ);

	myModels[PtModelsEnum::PYRAMID_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::PYRAMID_MODEL]->setFilename("/app0/assets/models/PTM/pyramid.ptm");
	myModels[PtModelsEnum::PYRAMID_MODEL]->setAssetType(PtAssetTypes::MODEL_PTM);

	myModels[PtModelsEnum::RING_MODEL] = std::make_shared<PtModel>();
	myModels[PtModelsEnum::RING_MODEL]->setFilename("/app0/assets/models/obj/Ring.obj");
	myModels[PtModelsEnum::RING_MODEL]->setAssetType(PtAssetTypes::MODEL_OBJ);

	myTextures[PtTexturesEnum::FALCON_TEXTURE_WHITE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::FALCON_TEXTURE_WHITE]->filename = "/app0/assets/textures/Millennium Falcon Texture white.gnf";
	myTextures[PtTexturesEnum::FALCON_TEXTURE_WHITE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::FALCON_TEXTURE_BLACK] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::FALCON_TEXTURE_BLACK]->filename = "/app0/assets/textures/Millennium Falcon Texture black.gnf";
	myTextures[PtTexturesEnum::FALCON_TEXTURE_BLACK]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::TIE_FIGHTER_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::TIE_FIGHTER_TEXTURE]->filename = "/app0/assets/textures/Tie Fighter texture.gnf";
	myTextures[PtTexturesEnum::TIE_FIGHTER_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::COW_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::COW_TEXTURE]->filename = "/app0/assets/textures/cow.gnf";
	myTextures[PtTexturesEnum::COW_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::PLANET_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::PLANET_TEXTURE]->filename = "/app0/assets/textures/Endor.gnf";
	myTextures[PtTexturesEnum::PLANET_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::TEDDY_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::TEDDY_TEXTURE]->filename = "/app0/assets/textures/TeddyTexture.gnf";
	myTextures[PtTexturesEnum::TEDDY_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::FONT_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::FONT_TEXTURE]->filename = "/app0/assets/textures/font.gnf";
	myTextures[PtTexturesEnum::FONT_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::EARTH_GLOSS_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::EARTH_GLOSS_TEXTURE]->filename = "/app0/assets/textures/earthGloss.gnf";
	myTextures[PtTexturesEnum::EARTH_GLOSS_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::DEATH_STAR_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::DEATH_STAR_TEXTURE]->filename = "/app0/assets/textures/Death Star.gnf";
	myTextures[PtTexturesEnum::DEATH_STAR_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::RED_BEAM_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::RED_BEAM_TEXTURE]->filename = "/app0/assets/textures/Red Beam.gnf";
	myTextures[PtTexturesEnum::RED_BEAM_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myTextures[PtTexturesEnum::GREEN_BEAM_TEXTURE] = std::make_shared<PtTexture>();
	myTextures[PtTexturesEnum::GREEN_BEAM_TEXTURE]->filename = "/app0/assets/textures/Green.gnf";
	myTextures[PtTexturesEnum::GREEN_BEAM_TEXTURE]->assetType = PtAssetTypes::TEXTURE_GNF;

	myPipelines[PtPipelines::TDM_PIPELINE] = std::make_shared<PtPipeline>();
	myPipelines[PtPipelines::TDM_PIPELINE]->setTotalTextures(1);
	myPipelines[PtPipelines::TDM_PIPELINE]->setShaderConstant(PtShaderConstants::TDM);
	myPipelines[PtPipelines::TDM_PIPELINE]->setFileName1("/app0/ptTDMShader_vv.sb");
	myPipelines[PtPipelines::TDM_PIPELINE]->setFileName2("/app0/ptTDMShader_p.sb");
	myPipelines[PtPipelines::TDM_PIPELINE]->loadShaders(garlicAllocator, toolkitAllocators);

	myPipelines[PtPipelines::VVM_PIPELINE] = std::make_shared<PtPipeline>();
	myPipelines[PtPipelines::VVM_PIPELINE]->setTotalTextures(0);
	myPipelines[PtPipelines::VVM_PIPELINE]->setShaderConstant(PtShaderConstants::VVM);
	myPipelines[PtPipelines::VVM_PIPELINE]->setFileName1("/app0/ptVVMShader_vv.sb");
	myPipelines[PtPipelines::VVM_PIPELINE]->setFileName2("/app0/ptVVMShader_p.sb");
	myPipelines[PtPipelines::VVM_PIPELINE]->loadShaders(garlicAllocator, toolkitAllocators);

	myPipelines[PtPipelines::MMM_PIPELINE] = std::make_shared<PtPipeline>();
	myPipelines[PtPipelines::MMM_PIPELINE]->setTotalTextures(0);
	myPipelines[PtPipelines::MMM_PIPELINE]->setShaderConstant(PtShaderConstants::MMM);
	myPipelines[PtPipelines::MMM_PIPELINE]->setFileName1("/app0/ptMMMShader_vv.sb");
	myPipelines[PtPipelines::MMM_PIPELINE]->setFileName2("/app0/ptMMMShader_p.sb");
	myPipelines[PtPipelines::MMM_PIPELINE]->loadShaders(garlicAllocator, toolkitAllocators);

	myPipelines[PtPipelines::TDT_PIPELINE] = std::make_shared<PtPipeline>();
	myPipelines[PtPipelines::TDT_PIPELINE]->setTotalTextures(2);
	myPipelines[PtPipelines::TDT_PIPELINE]->setShaderConstant(PtShaderConstants::TDT);
	myPipelines[PtPipelines::TDT_PIPELINE]->setFileName1("/app0/ptTDTShader_vv.sb");
	myPipelines[PtPipelines::TDT_PIPELINE]->setFileName2("/app0/ptTDTShader_p.sb");
	myPipelines[PtPipelines::TDT_PIPELINE]->loadShaders(garlicAllocator, toolkitAllocators);

	myPipelines[PtPipelines::HUD_PIPELINE] = std::make_shared<PtPipeline>();
	myPipelines[PtPipelines::HUD_PIPELINE]->setTotalTextures(1);
	myPipelines[PtPipelines::HUD_PIPELINE]->setShaderConstant(PtShaderConstants::TDM);
	myPipelines[PtPipelines::HUD_PIPELINE]->setFileName1("/app0/ptHUDShader_vv.sb");
	myPipelines[PtPipelines::HUD_PIPELINE]->setFileName2("/app0/ptHUDShader_p.sb");
	myPipelines[PtPipelines::HUD_PIPELINE]->loadShaders(garlicAllocator, toolkitAllocators);

	myMaterials[PtMaterialsEnum::FALCON_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::FALCON_MATERIAL]->setTextureName(PtTexturesEnum::FALCON_TEXTURE_WHITE, 0);
	myMaterials[PtMaterialsEnum::FALCON_MATERIAL]->setTextureName(PtTexturesEnum::FALCON_TEXTURE_BLACK, 1);
	myMaterials[PtMaterialsEnum::FALCON_MATERIAL]->setPipelineType(PtPipelines::TDT_PIPELINE, myPipelines[PtPipelines::TDT_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::FALCON_MATERIAL]->setSpecularPower(50);
	myMaterials[PtMaterialsEnum::FALCON_MATERIAL]->setSpecularStrength(50);

	myMaterials[PtMaterialsEnum::TIE_FIGHTER_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::TIE_FIGHTER_MATERIAL]->setTextureName(PtTexturesEnum::TIE_FIGHTER_TEXTURE, 0);
	myMaterials[PtMaterialsEnum::TIE_FIGHTER_MATERIAL]->setPipelineType(PtPipelines::TDM_PIPELINE, myPipelines[PtPipelines::TDM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::TIE_FIGHTER_MATERIAL]->setSpecularPower(0);
	myMaterials[PtMaterialsEnum::TIE_FIGHTER_MATERIAL]->setSpecularStrength(0);

	myMaterials[PtMaterialsEnum::STAR_DESTROYER_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::STAR_DESTROYER_MATERIAL]->setTextureName(PtTexturesEnum::DEATH_STAR_TEXTURE, 0);
	myMaterials[PtMaterialsEnum::STAR_DESTROYER_MATERIAL]->setPipelineType(PtPipelines::TDM_PIPELINE, myPipelines[PtPipelines::TDM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::STAR_DESTROYER_MATERIAL]->setSpecularPower(0);
	myMaterials[PtMaterialsEnum::STAR_DESTROYER_MATERIAL]->setSpecularStrength(0);

	myMaterials[PtMaterialsEnum::PLANET_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::PLANET_MATERIAL]->setTextureName(PtTexturesEnum::PLANET_TEXTURE, 0);
	myMaterials[PtMaterialsEnum::PLANET_MATERIAL]->setPipelineType(PtPipelines::TDM_PIPELINE, myPipelines[PtPipelines::TDM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::PLANET_MATERIAL]->setSpecularStrength(0);
	myMaterials[PtMaterialsEnum::PLANET_MATERIAL]->setSpecularPower(0);

	myMaterials[PtMaterialsEnum::DEATH_STAR_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::DEATH_STAR_MATERIAL]->setTextureName(PtTexturesEnum::DEATH_STAR_TEXTURE, 0);
	myMaterials[PtMaterialsEnum::DEATH_STAR_MATERIAL]->setPipelineType(PtPipelines::TDM_PIPELINE, myPipelines[PtPipelines::TDM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::DEATH_STAR_MATERIAL]->setSpecularStrength(0);
	myMaterials[PtMaterialsEnum::DEATH_STAR_MATERIAL]->setSpecularPower(0);

	myMaterials[PtMaterialsEnum::PLASTIC_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::PLASTIC_MATERIAL]->setTextureName(PtTexturesEnum::COW_TEXTURE, 0);
	myMaterials[PtMaterialsEnum::PLASTIC_MATERIAL]->setPipelineType(PtPipelines::TDM_PIPELINE, myPipelines[PtPipelines::TDM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::PLASTIC_MATERIAL]->setAmbientColour(Vector3(0.5, 0.5, 0.5));
	myMaterials[PtMaterialsEnum::PLASTIC_MATERIAL]->setDiffuseColour(Vector3(0.5, 0.5, 0.5));
	myMaterials[PtMaterialsEnum::PLASTIC_MATERIAL]->setSpecularStrength(0);
	myMaterials[PtMaterialsEnum::PLASTIC_MATERIAL]->setSpecularPower(0);

	myMaterials[PtMaterialsEnum::FONT_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::FONT_MATERIAL]->setTextureName(PtTexturesEnum::FONT_TEXTURE, 0);
	myMaterials[PtMaterialsEnum::FONT_MATERIAL]->setPipelineType(PtPipelines::HUD_PIPELINE, myPipelines[PtPipelines::HUD_PIPELINE]->getTotalTextures());

	myMaterials[PtMaterialsEnum::RED_BEAM_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::RED_BEAM_MATERIAL]->setPipelineType(PtPipelines::MMM_PIPELINE, myPipelines[PtPipelines::MMM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::RED_BEAM_MATERIAL]->setAmbientColour(Vector3(1, 0, 0));
	myMaterials[PtMaterialsEnum::RED_BEAM_MATERIAL]->setDiffuseColour(Vector3(1, 0, 0));
	myMaterials[PtMaterialsEnum::RED_BEAM_MATERIAL]->setSpecularStrength(50);
	myMaterials[PtMaterialsEnum::RED_BEAM_MATERIAL]->setSpecularPower(50);

	myMaterials[PtMaterialsEnum::GREEN_BEAM_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::GREEN_BEAM_MATERIAL]->setPipelineType(PtPipelines::MMM_PIPELINE, myPipelines[PtPipelines::MMM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::GREEN_BEAM_MATERIAL]->setAmbientColour(Vector3(0, 1, 0));
	myMaterials[PtMaterialsEnum::GREEN_BEAM_MATERIAL]->setDiffuseColour(Vector3(0, 1, 0));
	myMaterials[PtMaterialsEnum::GREEN_BEAM_MATERIAL]->setSpecularStrength(50);
	myMaterials[PtMaterialsEnum::GREEN_BEAM_MATERIAL]->setSpecularPower(50);

	myMaterials[PtMaterialsEnum::PYRAMID_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::PYRAMID_MATERIAL]->setPipelineType(PtPipelines::VVM_PIPELINE, myPipelines[PtPipelines::VVM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::PYRAMID_MATERIAL]->setSpecularStrength(0);
	myMaterials[PtMaterialsEnum::PYRAMID_MATERIAL]->setSpecularPower(0);

	myMaterials[PtMaterialsEnum::RING_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::RING_MATERIAL]->setPipelineType(PtPipelines::MMM_PIPELINE, myPipelines[PtPipelines::MMM_PIPELINE]->getTotalTextures());
	myMaterials[PtMaterialsEnum::RING_MATERIAL]->setAmbientColour(Vector3(1, 0.5, 0));
	myMaterials[PtMaterialsEnum::RING_MATERIAL]->setDiffuseColour(Vector3(1, 0.5, 0));
	myMaterials[PtMaterialsEnum::RING_MATERIAL]->setSpecularStrength(50);
	myMaterials[PtMaterialsEnum::RING_MATERIAL]->setSpecularPower(50);

	myMaterials[PtMaterialsEnum::DOUBLE_EARTH_MATERIAL] = std::make_shared<PtMaterial>();
	myMaterials[PtMaterialsEnum::DOUBLE_EARTH_MATERIAL]->setTextureName(PtTexturesEnum::PLANET_TEXTURE, 0);
	myMaterials[PtMaterialsEnum::DOUBLE_EARTH_MATERIAL]->setTextureName(PtTexturesEnum::EARTH_GLOSS_TEXTURE, 1);
	myMaterials[PtMaterialsEnum::DOUBLE_EARTH_MATERIAL]->setPipelineType(PtPipelines::TDT_PIPELINE, myPipelines[PtPipelines::TDT_PIPELINE]->getTotalTextures());
}

std::shared_ptr<PtModel> PtAssetManager::getLoadedModel(PtModelsEnum model)
{
	std::shared_ptr<PtModel> requestedModel = myModels[(int)model];

	if (!requestedModel->getValidData())
	{
		if (requestedModel->getAssetType() == PtAssetTypes::MODEL_OBJ)
		{
			requestedModel->loadModelOBJ(myGarlicAllocator);
		}
		else if (requestedModel->getAssetType() == PtAssetTypes::MODEL_PTM)
		{
			requestedModel->loadModelPTM(myGarlicAllocator);
		}
	}

	return requestedModel;
}

Gnm::Texture* PtAssetManager::getTexture(PtTexturesEnum texture)
{
	if (!myTextures[texture]->validData)
	{
		int error = textureLoader.loadTextureFromGnf(myTextures[texture]->filename, myTextures[texture]->index, myToolkitAllocators, myTextures[texture]->texture);

		if (error == SCE_OK)
		{
			myTextures[texture]->validData = true;
		}
	}

	return &myTextures[texture]->texture;
}

std::shared_ptr<PtPipeline> PtAssetManager::getPipeline(PtPipelines pipeline)
{
	return myPipelines[pipeline];
}

std::shared_ptr<PtMaterial> PtAssetManager::getMaterial(PtMaterialsEnum materialType)
{
	std::shared_ptr<PtMaterial> material = myMaterials[materialType];

	if (!material->getLoaded())
	{
		material->setPipeline(getPipeline(material->getPipelineType()));

		for (int x = 0; x < material->getTextureCount(); x++)
		{
			material->setTexture(getTexture(material->getTextureName(x)), x);
		}
		material->setTextureSampler(&textureSampler);
		material->setLoaded(true);
	}

	return material;
}