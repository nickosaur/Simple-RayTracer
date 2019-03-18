#pragma once
#include "Matrix.h"
#include "Vector.h"
#include "Ray.h"
#define _USE_MATH_DEFINES
#include <math.h>
class Transformation
{
public:
	Transformation();
	//Transformation(Matrix & mat);
	~Transformation();

protected:
	//Matrix m;
	//Matrix minvt;
};

Vector multiply4(Matrix & m, Vector & v);
Vector multiply3(Matrix & m, Vector & v);
Ray multiplyRay(Matrix & m, Ray & r);
Matrix rotate(Vector & axis, float degrees);
Matrix scale(float sx, float sy, float sz);
Matrix translate(float tx, float ty, float tz);

