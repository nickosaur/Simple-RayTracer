#pragma once
#include "Color.h"
#include "Vector.h"
#include "Ray.h"
class Light
{
public:
	Light();
	~Light();

	virtual Color getColor() { return Color(); };
	virtual Vector getDirection(Vector & position) {
		return Vector();
	};
	virtual Vector getPosition() { return Vector(); };
	virtual Ray ifBlocked(Vector & vec) = 0;
	virtual float getAttenuationColor(Vector & pos) { return 1.0f; };
	virtual float getShade(Vector & vec, Vector & normal) = 0;
	virtual bool isPoint() = 0;
};

