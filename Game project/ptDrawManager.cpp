#include "ptDrawManager.h"

void PtDrawManager::draw(Gnmx::GnmxGfxContext* gfxc, std::shared_ptr<PtObject> pObject, PtLightEnvironment environment, std::shared_ptr<PtCamera> pCamera)
{
	if (pObject->getModel()->getValidData())
	{
		PtLight* pLights = environment.getLights();

		PtTDMShaderConstants* tdmShaderConstants = static_cast<PtTDMShaderConstants*>(gfxc->allocateFromCommandBuffer(sizeof(PtTDMShaderConstants), Gnm::kEmbeddedDataAlignment4));
		gfxc->setVertexBuffers(Gnm::kShaderStageVs, 0, PT_VERTEX_ELEM_COUNT, pObject->getModel()->getVertexBuffers());

		PtVVMShaderConstants* vvmShaderConstants = static_cast<PtVVMShaderConstants*>(gfxc->allocateFromCommandBuffer(sizeof(PtVVMShaderConstants), Gnm::kEmbeddedDataAlignment4));
		gfxc->setVertexBuffers(Gnm::kShaderStageVs, 0, PT_VERTEX_ELEM_COUNT, pObject->getModel()->getVertexBuffers());

		PtMMMShaderConstants* mmmShaderConstants = static_cast<PtMMMShaderConstants*>(gfxc->allocateFromCommandBuffer(sizeof(PtMMMShaderConstants), Gnm::kEmbeddedDataAlignment4));
		gfxc->setVertexBuffers(Gnm::kShaderStageVs, 0, PT_VERTEX_ELEM_COUNT, pObject->getModel()->getVertexBuffers());

		PtTDTShaderConstants* tdtShaderConstants = static_cast<PtTDTShaderConstants*>(gfxc->allocateFromCommandBuffer(sizeof(PtTDTShaderConstants), Gnm::kEmbeddedDataAlignment4));
		gfxc->setVertexBuffers(Gnm::kShaderStageVs, 0, PT_VERTEX_ELEM_COUNT, pObject->getModel()->getVertexBuffers());

		Gnm::Buffer constBuffer;

		if(pObject->getMaterial()->getPipeline()->getShaderConstant() == PtShaderConstants::TDM)
		{
			Matrix4 inverseWorldView = inverse(pCamera->getWorldViewMatrix());
			tdmShaderConstants->shc_modelProjMx = pCamera->getProjectionMatrix() * pCamera->getWorldViewMatrix() * pObject->getModelWorldMatrix();
			tdmShaderConstants->shc_normalTransMx = transpose(inverse(pObject->getModelWorldMatrix()));
			tdmShaderConstants->shc_worldViewMatrix = pCamera->getWorldViewMatrix();
			tdmShaderConstants->shc_cameraPositionWorldVx = inverseWorldView.getCol3();
			tdmShaderConstants->shc_materialSpecularPower = Vector4(0, 0, 0, 0);
			tdmShaderConstants->shc_materialSpecularStrength = Vector4(0, 0, 0, 0);
			tdmShaderConstants->shc_materialSpecularPower.x = pObject->getMaterial()->getSpecularPower();
			tdmShaderConstants->shc_materialSpecularStrength.x = pObject->getMaterial()->getSpecularStrength();

			for (int i = 0; i < PT_LIGHT_COUNT; i++)
			{
				tdmShaderConstants->shc_lightADSVx[i] = Vector4(pLights[i].getAmbientFactor(), pLights[i].getDiffuseFactor(), pLights[i].getSpecularFactor(), pLights[i].getIsOn());
				tdmShaderConstants->shc_lightAttenuationVx[i] = Vector4(pLights[i].getFixedAttenuationFactor(), pLights[i].getLinearAttenuationFactor(), pLights[i].getQuadraticAttenuationFactor(), pLights[i].getUseDistanceAttenuation());
				tdmShaderConstants->shc_lightColourVx[i] = Vector4(pLights[i].getColour(), 1.0f);
				tdmShaderConstants->shc_lightLocationVx[i] = Vector4(pLights[i].getLocationVx(), pLights[i].getIsInfinite());
				tdmShaderConstants->shc_lightSpotDirectionVx[i] = Vector4(pLights[i].getSpotAngleCos(), 1.0f, 1.0f, pLights[i].getIsDirectional());

				if (!pLights[i].getIsDirectional())
				{
					tdmShaderConstants->shc_lightSpotDirectionVx[i].w = 1.1f;
				}
			}

			constBuffer.initAsConstantBuffer(tdmShaderConstants, sizeof(PtTDMShaderConstants));
		}
		else if (pObject->getMaterial()->getPipeline()->getShaderConstant() == PtShaderConstants::VVM)
		{
			Matrix4 inverseWorldView = inverse(pCamera->getWorldViewMatrix());
			vvmShaderConstants->shc_modelProjMx = pCamera->getProjectionMatrix() * pCamera->getWorldViewMatrix() * pObject->getModelWorldMatrix();
			vvmShaderConstants->shc_normalTransMx = transpose(inverse(pObject->getModelWorldMatrix()));
			vvmShaderConstants->shc_worldViewMatrix = pCamera->getWorldViewMatrix();
			vvmShaderConstants->shc_cameraPositionWorldVx = inverseWorldView.getCol3();
			vvmShaderConstants->shc_materialSpecularPower = Vector4(0, 0, 0, 0);
			vvmShaderConstants->shc_materialSpecularStrength = Vector4(0, 0, 0, 0);
			vvmShaderConstants->shc_materialSpecularPower.x = pObject->getMaterial()->getSpecularPower();
			vvmShaderConstants->shc_materialSpecularStrength.x = pObject->getMaterial()->getSpecularStrength();
			vvmShaderConstants->shc_colour = Vector4();

			for (int i = 0; i < PT_LIGHT_COUNT; i++)
			{
				vvmShaderConstants->shc_lightADSVx[i] = Vector4(pLights[i].getAmbientFactor(), pLights[i].getDiffuseFactor(), pLights[i].getSpecularFactor(), pLights[i].getIsOn());
				vvmShaderConstants->shc_lightAttenuationVx[i] = Vector4(pLights[i].getFixedAttenuationFactor(), pLights[i].getLinearAttenuationFactor(), pLights[i].getQuadraticAttenuationFactor(), pLights[i].getUseDistanceAttenuation());
				vvmShaderConstants->shc_lightColourVx[i] = Vector4(pLights[i].getColour(), 1.0f);
				vvmShaderConstants->shc_lightLocationVx[i] = Vector4(pLights[i].getLocationVx(), pLights[i].getIsInfinite());
				vvmShaderConstants->shc_lightSpotDirectionVx[i] = Vector4(pLights[i].getSpotAngleCos(), 1.0f, 1.0f, pLights[i].getIsDirectional());

				if (!pLights[i].getIsDirectional())
				{
					vvmShaderConstants->shc_lightSpotDirectionVx[i].w = 1.1f;
				}
			}
			constBuffer.initAsConstantBuffer(vvmShaderConstants, sizeof(PtVVMShaderConstants));
		}
		else if (pObject->getMaterial()->getPipeline()->getShaderConstant() == PtShaderConstants::MMM)
		{
			Matrix4 inverseWorldView = inverse(pCamera->getWorldViewMatrix());
			mmmShaderConstants->shc_modelProjMx = pCamera->getProjectionMatrix() * pCamera->getWorldViewMatrix() * pObject->getModelWorldMatrix();
			mmmShaderConstants->shc_normalTransMx = transpose(inverse(pObject->getModelWorldMatrix()));
			mmmShaderConstants->shc_worldViewMatrix = pCamera->getWorldViewMatrix();
			mmmShaderConstants->shc_cameraPositionWorldVx = inverseWorldView.getCol3();
			mmmShaderConstants->shc_materialSpecularPower = Vector4(0, 0, 0, 0);
			mmmShaderConstants->shc_materialSpecularStrength = Vector4(0, 0, 0, 0);
			mmmShaderConstants->shc_materialAmbientColour = Vector4(0, 0, 0, 0);
			mmmShaderConstants->shc_materialDiffuseColour = Vector4(0, 0, 0, 0);
			mmmShaderConstants->shc_materialSpecularPower.x = pObject->getMaterial()->getSpecularPower();
			mmmShaderConstants->shc_materialSpecularStrength.x = pObject->getMaterial()->getSpecularStrength();
			mmmShaderConstants->shc_materialAmbientColour.x = pObject->getMaterial()->getAmbientColour().getX();
			mmmShaderConstants->shc_materialAmbientColour.y = pObject->getMaterial()->getAmbientColour().getY();
			mmmShaderConstants->shc_materialAmbientColour.z = pObject->getMaterial()->getAmbientColour().getZ();
			mmmShaderConstants->shc_materialDiffuseColour.x = pObject->getMaterial()->getDiffuseColour().getX();
			mmmShaderConstants->shc_materialDiffuseColour.y = pObject->getMaterial()->getDiffuseColour().getY();
			mmmShaderConstants->shc_materialDiffuseColour.z = pObject->getMaterial()->getDiffuseColour().getZ();

			for (int i = 0; i < PT_LIGHT_COUNT; i++)
			{
				mmmShaderConstants->shc_lightADSVx[i] = Vector4(pLights[i].getAmbientFactor(), pLights[i].getDiffuseFactor(), pLights[i].getSpecularFactor(), pLights[i].getIsOn());
				mmmShaderConstants->shc_lightAttenuationVx[i] = Vector4(pLights[i].getFixedAttenuationFactor(), pLights[i].getLinearAttenuationFactor(), pLights[i].getQuadraticAttenuationFactor(), pLights[i].getUseDistanceAttenuation());
				mmmShaderConstants->shc_lightColourVx[i] = Vector4(pLights[i].getColour(), 1.0f);
				mmmShaderConstants->shc_lightLocationVx[i] = Vector4(pLights[i].getLocationVx(), pLights[i].getIsInfinite());
				mmmShaderConstants->shc_lightSpotDirectionVx[i] = Vector4(pLights[i].getSpotAngleCos(), 1.0f, 1.0f, pLights[i].getIsDirectional());

				if (!pLights[i].getIsDirectional())
				{
					mmmShaderConstants->shc_lightSpotDirectionVx[i].w = 1.1f;
				}
			}
			constBuffer.initAsConstantBuffer(mmmShaderConstants, sizeof(PtMMMShaderConstants));
		}
		else if (pObject->getMaterial()->getPipeline()->getShaderConstant() == PtShaderConstants::TDT)
		{
			Matrix4 inverseWorldView = inverse(pCamera->getWorldViewMatrix());
			tdtShaderConstants->shc_modelProjMx = pCamera->getProjectionMatrix() * pCamera->getWorldViewMatrix() * pObject->getModelWorldMatrix();
			tdtShaderConstants->shc_normalTransMx = transpose(inverse(pObject->getModelWorldMatrix()));
			tdtShaderConstants->shc_worldViewMatrix = pCamera->getWorldViewMatrix();
			tdtShaderConstants->shc_cameraPositionWorldVx = inverseWorldView.getCol3();
			tdtShaderConstants->shc_materialSpecularPower = Vector4(0, 0, 0, 0);
			tdtShaderConstants->shc_materialSpecularStrength = Vector4(0, 0, 0, 0);
			tdtShaderConstants->shc_materialAmbientColour = Vector4(0, 0, 0, 0);
			tdtShaderConstants->shc_materialDiffuseColour = Vector4(0, 0, 0, 0);
			tdtShaderConstants->shc_materialSpecularPower.x = pObject->getMaterial()->getSpecularPower();
			tdtShaderConstants->shc_materialSpecularStrength.x = pObject->getMaterial()->getSpecularStrength();
			tdtShaderConstants->shc_materialAmbientColour.x = pObject->getMaterial()->getAmbientColour().getX();
			tdtShaderConstants->shc_materialAmbientColour.y = pObject->getMaterial()->getAmbientColour().getY();
			tdtShaderConstants->shc_materialAmbientColour.z = pObject->getMaterial()->getAmbientColour().getZ();
			tdtShaderConstants->shc_materialDiffuseColour.x = pObject->getMaterial()->getDiffuseColour().getX();
			tdtShaderConstants->shc_materialDiffuseColour.y = pObject->getMaterial()->getDiffuseColour().getY();
			tdtShaderConstants->shc_materialDiffuseColour.z = pObject->getMaterial()->getDiffuseColour().getZ();

			for (int i = 0; i < PT_LIGHT_COUNT; i++)
			{
				tdtShaderConstants->shc_lightADSVx[i] = Vector4(pLights[i].getAmbientFactor(), pLights[i].getDiffuseFactor(), pLights[i].getSpecularFactor(), pLights[i].getIsOn());
				tdtShaderConstants->shc_lightAttenuationVx[i] = Vector4(pLights[i].getFixedAttenuationFactor(), pLights[i].getLinearAttenuationFactor(), pLights[i].getQuadraticAttenuationFactor(), pLights[i].getUseDistanceAttenuation());
				tdtShaderConstants->shc_lightColourVx[i] = Vector4(pLights[i].getColour(), 1.0f);
				tdtShaderConstants->shc_lightLocationVx[i] = Vector4(pLights[i].getLocationVx(), pLights[i].getIsInfinite());
				tdtShaderConstants->shc_lightSpotDirectionVx[i] = Vector4(pLights[i].getSpotAngleCos(), 1.0f, 1.0f, pLights[i].getIsDirectional());

				if (!pLights[i].getIsDirectional())
				{
					tdtShaderConstants->shc_lightSpotDirectionVx[i].w = 1.1f;
				}
			}
			constBuffer.initAsConstantBuffer(tdtShaderConstants, sizeof(PtTDTShaderConstants));
		}

		pObject->getMaterial()->getPipeline()->use(gfxc);
	
		// assign textures 
		// Setup the texture and its sampler on the pixel shader stage
		for (int i = 0; i < pObject->getMaterial()->getTextureCount(); i++)
		{
			gfxc->setTextures(Gnm::kShaderStagePs, i, 1, pObject->getMaterial()->getMyTextures()[i]);
		}	
		gfxc->setSamplers(Gnm::kShaderStagePs, 0, 1, pObject->getMaterial()->getTextureSampler());
		
		gfxc->setConstantBuffers(Gnm::kShaderStageVs, 0, 1, &constBuffer);
		gfxc->setConstantBuffers(Gnm::kShaderStagePs, 0, 1, &constBuffer);
		gfxc->setPrimitiveType(Gnm::kPrimitiveTypeTriList);
		gfxc->setIndexSize(Gnm::kIndexSize16);
		gfxc->drawIndex(pObject->getModel()->getIndexCount(), pObject->getModel()->getGpuIndexData());
	}
}

void PtDrawManager::drawHUD(Gnmx::GnmxGfxContext* gfxc, std::shared_ptr<PtHUDTextItem> pItem)
{
	if (pItem->getValidData())
	{
		PtTDMShaderConstants *shaderConstants = static_cast<PtTDMShaderConstants*>(gfxc->allocateFromCommandBuffer(sizeof(PtTDMShaderConstants), Gnm::kEmbeddedDataAlignment4));
		gfxc->setVertexBuffers(Gnm::kShaderStageVs, 0, PT_VERTEX_ELEM_COUNT, pItem->getVertexBuffers());
		
		if (shaderConstants)
		{
			shaderConstants->shc_materialSpecularPower = Vector4(0, 0, 0, 0);
			shaderConstants->shc_materialSpecularStrength = Vector4(0, 0, 0, 0);
			shaderConstants->shc_materialSpecularPower.x = pItem->getMaterial()->getSpecularPower();
			shaderConstants->shc_materialSpecularStrength.x = pItem->getMaterial()->getSpecularStrength();
			
			pItem->getMaterial()->getPipeline()->use(gfxc);

			//assign textures 
			// Setup the texture and its sampler on the pixel shader stage
			for (int i = 0; i < pItem->getMaterial()->getTextureCount(); i++)
			{
				gfxc->setTextures(Gnm::kShaderStagePs, i, 1, pItem->getMaterial()->getMyTextures()[i]);
			}
			gfxc->setSamplers(Gnm::kShaderStagePs, 0, 1, pItem->getMaterial()->getTextureSampler());

			Gnm::Buffer constBuffer;
			constBuffer.initAsConstantBuffer(shaderConstants, sizeof(PtTDMShaderConstants));
			gfxc->setConstantBuffers(Gnm::kShaderStageVs, 0, 1, &constBuffer);
			gfxc->setConstantBuffers(Gnm::kShaderStagePs, 0, 1, &constBuffer);
			gfxc->setPrimitiveType(Gnm::kPrimitiveTypeTriList);
			gfxc->setIndexSize(Gnm::kIndexSize16);
			gfxc->drawIndex(pItem->getIndexCount(), pItem->getGpuIndexData());
		}
	}
}