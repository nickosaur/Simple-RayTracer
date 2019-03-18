#pragma once
#include "Color.h"
#include "Ray.h"
#include "Intersection.h"
#include "Matrix.h"
#include "BRDF.h"
#include "Transformation.h"
#include <math.h>
#include <alg.h>
class Intersection;
class Shape
{
public:
	Shape();
	~Shape();

	Matrix m, iM;

	virtual BRDF getBRDF() = 0;
	virtual bool intersectP(Ray & ray) { return false; };
	virtual Vector surfaceNormal(Vector & in) = 0;
	virtual bool intersect(Ray & ray, Intersection & in) { return false; };
	virtual Matrix getTransformM() = 0;
	virtual Matrix getInvTransformM() = 0;
};

