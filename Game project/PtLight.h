#ifndef __PT_LIGHT__
#define __PT_LIGHT__

#include "../../toolkit/toolkit.h"

class PtLight
{
private:
	//Colour
	Vector3  colour;

	//direction and position
	Vector3 locationVx;
	Vector3 directionVx;

	//ADS components
	float ambientFactor;
	float diffuseFactor;
	float specularFactor;

	//Distance Attenuation
	float fixedAttenuationFactor;
	float linearAttenuationFactor;
	float quadraticAttenuationFactor;

	//angle attenuation
	float spotAngleCos;

	//flags
	bool isOn;
	bool useDistanceAttenuation;
	bool isDirectional;
	bool isInfinite;

public:
	PtLight();
	Vector3 getColour();
	Vector3 getLocationVx();
	Vector3 getDirectionVx();
	float getAmbientFactor();
	float getDiffuseFactor();
	float getSpecularFactor();
	float getFixedAttenuationFactor();
	float getLinearAttenuationFactor();
	float getQuadraticAttenuationFactor();
	float getSpotAngleCos();
	bool getIsOn();
	bool getUseDistanceAttenuation();
	bool getIsDirectional();
	bool getIsInfinite();

	void setColour(Vector3 colour);
	void setLocationVx(Vector3 location);
	void setDirectionVx(Vector3 direction);
	void setFixedAttenuationFactor(float factor);
	void setLinearAttenuationFactor(float factor);
	void setQuadraticAttenuationFactor(float factor);
	void setSpotAngleCos(float angle);
	void setIsOn(bool value);
	void setUseDistanceAttenuation(bool value);
	void setIsDirectional(bool value);
	void setIsInfinite(bool value);

};

#endif