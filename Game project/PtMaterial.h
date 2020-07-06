#ifndef __PT_MATERIAL__
#define __PT_MATERIAL__
#define PT_MAX_TEXTURES 4

#include "PtTexture.h"
#include "PtPipeline.h"
#include "PtPipelineTypes.h"
#include "TexturesEnum.h"
#include <memory>

class PtMaterial
{
private:
	Vector3 ambientColour;
	Vector3 diffuseColour;
	Vector3 specularColour;
	float specularPower;
	float specularStrength;
	std::shared_ptr<PtPipeline> pipeline;
	Gnm::Texture* myTextures[PT_MAX_TEXTURES];
	Gnm::Sampler* textureSampler;
	PtTexturesEnum myTextureNames[PT_MAX_TEXTURES];
	uint8_t textureCount;
	PtPipelines pipelineType;
	bool loaded;

public:
	PtMaterial();
	void setTextureName(PtTexturesEnum texture, int index);
	PtTexturesEnum getTextureName(int index);
	void setTexture(Gnm::Texture* texture, int index);
	void setPipelineType(PtPipelines type, uint8_t count);
	void setPipeline(std::shared_ptr<PtPipeline> pipeline);
	void setTextureSampler(Gnm::Sampler* sampler);
	std::shared_ptr<PtPipeline> getPipeline();
	PtPipelines getPipelineType();
	uint8_t getTextureCount();
	Gnm::Texture** getMyTextures();
	bool getLoaded();
	void setLoaded(bool loaded);
	float getSpecularPower();
	float getSpecularStrength();
	void setAmbientColour(Vector3 ambient);
	void setDiffuseColour(Vector3 diffuse);
	Vector3 getAmbientColour();
	Vector3 getDiffuseColour();
	void setSpecularPower(float power);
	void setSpecularStrength(float strength);
	Gnm::Sampler* getTextureSampler();
};

#endif
