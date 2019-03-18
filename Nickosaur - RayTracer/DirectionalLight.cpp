#include "DirectionalLight.h"



DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(Vector & position, Color & color)
{
	this->position = position;
	this->color = color;
}


DirectionalLight::~DirectionalLight()
{
}

Color DirectionalLight::getColor()
{
	return this->color;
}

Vector DirectionalLight::getDirection(Vector & position)
{
	Vector result = this->position;
	result = result.normalize();
	return result;
}

Vector DirectionalLight::getPosition()
{
	return this->position;
}

Ray DirectionalLight::ifBlocked(Vector & vec)
{
	Vector pos = this->position;
	pos = pos.normalize();
	return Ray(vec, pos);
}

float DirectionalLight::getAttenuationColor(Vector & pos)
{
	return 1.0f;
}

float DirectionalLight::getShade(Vector & vec, Vector & normal)
{
	Vector shadow = (this->position).normalize();
	float c = shadow.dot(normal);
	if (c <= 0.0f)
		return 0.0f;
	else
		return c;
	
}

bool DirectionalLight::isPoint()
{
	return false;
}
