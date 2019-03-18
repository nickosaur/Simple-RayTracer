#pragma once
#include "Vector.h"
class Ray
{
public:
	Ray();
	Ray(Vector & position, Vector & direction, float t_min, float t_max);
	Ray(Vector & position, Vector & direction);
	~Ray();

	Vector position, direction;
	float t_min, t_max;
};

