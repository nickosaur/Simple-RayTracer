#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(Vector & position, Color & color, float * attenuation);
	virtual ~PointLight();
	Color getColor();
	Vector getDirection(Vector & position);
	Vector getPosition();
	Ray ifBlocked(Vector & vec);
	float getAttenuationColor(Vector & pos);
	float getShade(Vector & vec, Vector & normal);
	bool isPoint();

	Vector position;
	Color color;
	float * attenuation;
};

