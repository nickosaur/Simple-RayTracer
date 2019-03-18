#pragma once
#include "Shape.h"
class Triangle :
	public Shape
{
public:
	Triangle();
	Triangle(Vector & A, Vector & B, Vector & C, BRDF & brdf, Matrix & m);
	bool intersect(Ray & ray, Intersection & in);
	bool intersectP(Ray & ray);
	BRDF getBRDF();
	Vector surfaceNormal(Vector & in);
	Matrix getTransformM();
	Matrix getInvTransformM();

	~Triangle();

	Vector A, B, C;
	BRDF brdf;
	Matrix m, iM;
};

