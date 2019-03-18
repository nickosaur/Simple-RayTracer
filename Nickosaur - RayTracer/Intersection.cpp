#include "Intersection.h"



Intersection::Intersection()
{
}

Intersection::Intersection(Vector & position, Vector & normal, Shape * shape)
{
	this->position = position;
	this->normal = normal;
	this->shape = shape;
}


Intersection::~Intersection()
{
}
