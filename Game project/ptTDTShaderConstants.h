#ifndef __PT_TDT_SHADER_CONSTANTS__
#define __PT_TDT_SHADER_CONSTANTS__

#include "../../toolkit/shader_common/shader_base.h"
#include "PtLightCount.h"

// shc_lightADSVx(x, y, z) = (ambient, diffuse, specular) intensity 0 - 1, 0 = off.w = <spare>
//shc_lightColourVx	(x,y,z) = (r,g,b)		w = on/off (1/0)
//shc_lightLocationVX	(x,y,z) = light location for positional lights, negative direction for infinite lights. w = positional/infinite (1/0)
//shc_lightSpotDirectionVx	(x,y,z) = direction for spotlights.		w = cutoff angle cosine, 1.0 or above = no cutoff cone
//shc_lightAttenuationVx	x = fixed, y = linear, z = quadratic. [attn = 1/(f + l*d + q*d*d)]	w = on/off (1/0) for attn calcs.

unistruct PtTDTShaderConstants
{
	Matrix4Unaligned shc_modelProjMx;
	Matrix4Unaligned shc_normalTransMx;
	Matrix4Unaligned shc_worldViewMatrix;
	Vector4Unaligned shc_cameraPositionWorldVx;
	Vector4Unaligned shc_lightADSVx[PT_LIGHT_COUNT];
	Vector4Unaligned shc_lightColourVx[PT_LIGHT_COUNT];
	Vector4Unaligned shc_lightLocationVx[PT_LIGHT_COUNT];
	Vector4Unaligned shc_lightSpotDirectionVx[PT_LIGHT_COUNT];
	Vector4Unaligned shc_lightAttenuationVx[PT_LIGHT_COUNT];
	Vector4Unaligned shc_materialSpecularPower;
	Vector4Unaligned shc_materialSpecularStrength;
	Vector4Unaligned shc_materialDiffuseColour;
	Vector4Unaligned shc_materialAmbientColour;
	float shc_angle;
};

#endif