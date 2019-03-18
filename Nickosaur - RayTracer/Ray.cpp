#include "Ray.h"
#include <float.h>

Ray::Ray()
{
}

Ray::Ray(Vector & position, Vector & direction, float t_min, float t_max)
{
	this->position = position;
	this->direction = direction;
	this->t_min = t_min;
	this->t_max = t_max;
}

Ray::Ray(Vector & position, Vector & direction)
{
	this->position = position;
	this->direction = direction;
	this->t_min = 0.0f;
	this->t_max = FLT_MAX;
}


Ray::~Ray()
{
}
