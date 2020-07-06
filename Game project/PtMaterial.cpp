#include "PtMaterial.h"

PtMaterial::PtMaterial()
{
	ambientColour = Vector3(0, 0, 0);
	diffuseColour = Vector3(0, 0, 0);
	specularColour = Vector3(0, 0, 0);
	pipeline = nullptr;
	textureCount = 0;
	pipelineType = PtPipelines::TDM_PIPELINE;
	loaded = false;
	textureSampler = nullptr;
	specularPower = 50;
	specularStrength = 1;

	for (int x = 0; x < PT_MAX_TEXTURES; x++)
	{
		myTextureNames[x] = PtTexturesEnum::COW_TEXTURE;
		myTextures[x] = nullptr;
	}
}

void PtMaterial::setTextureName(PtTexturesEnum texture, int index)
{
	myTextureNames[index] = texture;
}

PtTexturesEnum PtMaterial::getTextureName(int index)
{
	return myTextureNames[index];
}

void PtMaterial::setTexture(Gnm::Texture* texture, int index)
{
	myTextures[index] = texture;
}

void PtMaterial::setPipelineType(PtPipelines type, uint8_t count)
{
	pipelineType = type;
	textureCount = count;
}

void PtMaterial::setPipeline(std::shared_ptr<PtPipeline> pipeline)
{
	PtMaterial::pipeline = pipeline;
}

std::shared_ptr<PtPipeline> PtMaterial::getPipeline()
{
	return pipeline;
}

PtPipelines PtMaterial::getPipelineType()
{
	return pipelineType;
}

Gnm::Texture** PtMaterial::getMyTextures()
{
	return myTextures;
}

bool PtMaterial::getLoaded()
{
	return loaded;
}

void PtMaterial::setLoaded(bool loaded)
{
	PtMaterial::loaded = loaded;
}

uint8_t PtMaterial::getTextureCount()
{
	return textureCount;
}

void PtMaterial::setTextureSampler(Gnm::Sampler* sampler)
{
	textureSampler = sampler;
}

float PtMaterial::getSpecularPower()
{
	return specularPower;
}

void PtMaterial::setDiffuseColour(Vector3 diffuse)
{
	diffuseColour = diffuse;
}

void PtMaterial::setAmbientColour(Vector3 ambient)
{
	ambientColour = ambient;
}

float PtMaterial::getSpecularStrength()
{
	return specularStrength;
}

Gnm::Sampler* PtMaterial::getTextureSampler()
{
	return textureSampler;
}

Vector3 PtMaterial::getAmbientColour()
{
	return ambientColour;
}

Vector3 PtMaterial::getDiffuseColour()
{
	return diffuseColour;
}

void PtMaterial::setSpecularPower(float power)
{
	specularPower = power;
}

void PtMaterial::setSpecularStrength(float strength)
{
	specularStrength = strength;
}