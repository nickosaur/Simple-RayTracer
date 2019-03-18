#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(Vector & position, Color & color);
	~DirectionalLight();

	Color getColor();
	Vector getDirection(Vector & position);
	Vector getPosition();
	Ray ifBlocked(Vector & vec);
	float getAttenuationColor(Vector & pos);
	float getShade(Vector & vec, Vector & normal);
	bool isPoint();

protected:
	Vector position;
	Color color;
};

