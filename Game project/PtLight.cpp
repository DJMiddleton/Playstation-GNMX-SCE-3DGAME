#include "PtLight.h"

PtLight::PtLight()
{
	colour = Vector3(1.0, 1.0, 1.0);
	locationVx = Vector3(-1.0, 0.0, 0.0);
	directionVx = Vector3(-1, 0, 0);
	ambientFactor = 0.02;
	diffuseFactor = 1.0;
	specularFactor = 1.0;
	fixedAttenuationFactor = 0;
	linearAttenuationFactor = 0;
	quadraticAttenuationFactor = 0.25f;
	spotAngleCos = 0.174;
	isDirectional = false;
	isInfinite = true;
	isOn = true;
	useDistanceAttenuation = false;
}

Vector3 PtLight::getColour()
{
	return colour;
}

Vector3 PtLight::getLocationVx()
{
	return locationVx;
}

Vector3 PtLight::getDirectionVx()
{
	return directionVx;
}

float PtLight::getAmbientFactor()
{
	return ambientFactor;
}

float PtLight::getDiffuseFactor()
{
	return diffuseFactor;
}

float PtLight::getSpecularFactor()
{
	return specularFactor;
}

float PtLight::getFixedAttenuationFactor()
{
	return fixedAttenuationFactor;
}

float PtLight::getLinearAttenuationFactor()
{
	return linearAttenuationFactor;
}

float PtLight::getQuadraticAttenuationFactor()
{
	return quadraticAttenuationFactor;
}

float PtLight::getSpotAngleCos()
{
	return spotAngleCos;
}

bool PtLight::getIsOn()
{
	return isOn;
}

bool PtLight::getUseDistanceAttenuation()
{
	return useDistanceAttenuation;
}

bool PtLight::getIsDirectional()
{
	return isDirectional;
}

bool PtLight::getIsInfinite()
{
	return isInfinite;
}

void PtLight::setColour(Vector3 colour)
{
	PtLight::colour = colour;
}

void PtLight::setLocationVx(Vector3 location)
{
	locationVx = location;
}

void PtLight::setDirectionVx(Vector3 direction)
{
	directionVx = direction;
}

void PtLight::setFixedAttenuationFactor(float factor)
{
	fixedAttenuationFactor = factor;
}

void PtLight::setLinearAttenuationFactor(float factor)
{
	linearAttenuationFactor = factor;
}

void PtLight::setQuadraticAttenuationFactor(float factor)
{
	quadraticAttenuationFactor = factor;
}

void PtLight::setSpotAngleCos(float angle)
{
	spotAngleCos = angle;
}

void PtLight::setIsOn(bool value)
{
	isOn = value;
}

void PtLight::setUseDistanceAttenuation(bool value)
{
	useDistanceAttenuation = value;
}

void PtLight::setIsDirectional(bool value)
{
	isDirectional = value;
}

void PtLight::setIsInfinite(bool value)
{
	isInfinite = value;
}