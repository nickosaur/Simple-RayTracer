#pragma once
#include "Shape.h"

class Sphere :
	public Shape
{
public:
	Sphere();
	Sphere(Vector & center, float radius, BRDF & brdf, Matrix & m);
	~Sphere();
	bool intersect(Ray & ray, Intersection & in);
	bool intersectP(Ray & ray);
	BRDF getBRDF();
	Vector surfaceNormal(Vector & in);
	Matrix getTransformM();
	Matrix getInvTransformM();
	
	//member variables
	Vector center;
	float radius;
	BRDF brdf;
	Matrix m, iM;
};

