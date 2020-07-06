#include "PtPipeline.h"
#include "../../toolkit/toolkit.h"
#include "../../common/shader_loader.h"

PtPipeline::PtPipeline()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
	fetchShader = nullptr;
	shaderModifier = 0;
	initialised = false;
	totalTextures = 0;
	fileName1 = nullptr;
	fileName2 = nullptr;
	type = PtAssetTypes::PIPELINE;
	shaderConstant = PtShaderConstants::NONE;
}

int PtPipeline::loadShaders(LinearAllocator* garlicAllocator, Toolkit::Allocators* toolkitAllocators)
{
	//Load the shader binaries from disk
	//These are compiled when the project is built, from the .pssl files
	vertexShader = loadShaderFromFile<VsShader>(fileName1, *toolkitAllocators);
	pixelShader = loadShaderFromFile<PsShader>(fileName2, *toolkitAllocators);

	if (!vertexShader || !pixelShader)
	{
		printf("Cannot load the shaders\n");
		return SCE_KERNEL_ERROR_EIO;
	}

	// Allocate the memory for the fetch shader
	// this is a utility shader which helps the vertex shader
	fetchShader = garlicAllocator->allocate(Gnmx::computeVsFetchShaderSize(vertexShader), Gnm::kAlignmentOfFetchShaderInBytes);
	if (!fetchShader)
	{
		printf("Cannot allocate the fetch shader memory\n");
		return SCE_KERNEL_ERROR_ENOMEM;
	}

	// Generate the fetch shader for the VS stage
	Gnm::FetchShaderInstancingMode* t_instancingData = NULL;
	Gnmx::generateVsFetchShader(fetchShader, &shaderModifier, vertexShader, t_instancingData, t_instancingData != nullptr ? 256 : 0);

	// Generate the shader input caches.
	// Using a pre-calculated shader input cache is optional with CUE but it
	// normally reduces the CPU time necessary to build the command buffers.
	Gnmx::generateInputOffsetsCache(&vSInputOffsetsCache, Gnm::kShaderStageVs, vertexShader);
	Gnmx::generateInputOffsetsCache(&pSInputOffsetsCache, Gnm::kShaderStagePs, pixelShader);

	return SCE_OK;
}

void PtPipeline::use(Gnmx::GnmxGfxContext* myGFXC)
{
	//set shaders
	myGFXC->setVsShader(vertexShader, shaderModifier, fetchShader, &vSInputOffsetsCache);
	myGFXC->setPsShader(pixelShader, &pSInputOffsetsCache);
}

int PtPipeline::getTotalTextures()
{
	return totalTextures;
}

void PtPipeline::setFileName1(const char* fileName)
{
	fileName1 = fileName;
}

void PtPipeline::setFileName2(const char* fileName)
{
	fileName2 = fileName;
}

void PtPipeline::setTotalTextures(int textures)
{
	totalTextures = textures;
}

void PtPipeline::setType(PtAssetTypes type)
{
	PtPipeline::type = type;
}

PtShaderConstants PtPipeline::getShaderConstant()
{
	return shaderConstant;
}

void PtPipeline::setShaderConstant(PtShaderConstants constant)
{
	shaderConstant = constant;
}