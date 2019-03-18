#include "PointLight.h"



PointLight::PointLight()
{
}

PointLight::PointLight(Vector & position, Color & color, float * attenuation)
{
	this->position = position;
	this->color = color;
	this->attenuation = attenuation;
}


PointLight::~PointLight()
{
}

Color PointLight::getColor()
{
	return this->color;
}

Vector PointLight::getDirection(Vector & position)
{
	Vector dir = this->position - position;
	return dir.normalize();
}

Vector PointLight::getPosition()
{
	return this->position;
}

Ray PointLight::ifBlocked(Vector & vec)
{
	Vector dir = this->position - vec;
	dir = dir.normalize();
	dir = dir * 0.01f;
	Vector input = dir ;
	input = input + vec;
	return Ray(input, dir);
}

float PointLight::getAttenuationColor(Vector & pos)
{
	Vector dist = this->position - pos;
	float length = dist.magnitude(dist);
	float res = attenuation[0] + attenuation[1] * length + (attenuation[2] * length * length);
	return 1.0f / res;
}

float PointLight::getShade(Vector & vec, Vector & normal)
{
	Vector shadow = this->position - vec;
	shadow = shadow.normalize();
	float c = shadow.dot(normal);
	if (c <= 0.0f)
		return 0.0f;
	else {
		return c;
	}
}

bool PointLight::isPoint()
{
	return true;
}
