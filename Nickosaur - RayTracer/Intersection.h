#pragma once
#include "Vector.h"
#include "Shape.h"
class Shape;
class Intersection
{
public:
	Intersection();
	Intersection(Vector & position, Vector & normal, Shape * shape);
	~Intersection();

	Vector position, normal;
	Shape * shape;
};

