#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(Vector & A, Vector & B, Vector & C, BRDF & brdf, Matrix & m)
{
	this->A = A;
	this->B = B;
	this->C = C;
	this->brdf = brdf;
	this->m = m;
	this->iM = m.inverse();
}

bool Triangle::intersect(Ray & ray, Intersection & in)
{
	Vector AB = this->B - this->A;
	Vector AC = this->C - this->A;
	Vector BC = this->C - this->B;
	Vector CA = this->A - this->C;
	Vector normal = AB.cross(AC);
	normal = normal.normalize();

	Vector a_p = ray.position - A;
	float t = - (normal.dot(a_p)) / (normal.dot(ray.direction));
	if (t < 0.0) {
		return false;
	}
	Vector p1_t = ray.direction * t;
	Vector pos = ray.position + p1_t;
	Vector AP = pos - this->A;
	Vector BP = pos - this->B;
	Vector CP = pos - this->C;
	
	float inside1 = (AB.cross(AP)).dot(normal);
	float inside2 = (BC.cross(BP)).dot(normal);
	float inside3 = (CA.cross(CP)).dot(normal);
	if (inside1 >= 0 && inside2 >= 0 && inside3 >= 0) {
		in.position = pos;
		in.normal = normal;
		in.shape = this;
		return true;
	}
	return false;
}

bool Triangle::intersectP(Ray & ray)
{
	Vector AB = this->B - this->A;
	Vector AC = this->C - this->A;
	Vector BC = this->C - this->B;
	Vector CA = this->A - this->C;
	Vector normal = AB.cross(AC);
	normal = normal.normalize();

	Vector a_p = ray.position - A;
	float t = -(normal.dot(a_p)) / (normal.dot(ray.direction));
	if (t < 0.0) {
		return false;
	}
	Vector p1_t = ray.direction * t;
	Vector pos = ray.position + p1_t;
	Vector AP = pos - this->A;
	Vector BP = pos - this->B;
	Vector CP = pos - this->C;

	float inside1 = (AB.cross(AP)).dot(normal);
	float inside2 = (BC.cross(BP)).dot(normal);
	float inside3 = (CA.cross(CP)).dot(normal);
	if (inside1 >= 0 && inside2 >= 0 && inside3 >= 0) {
		return true;
	}
	return false;
}

BRDF Triangle::getBRDF()
{
	return this->brdf;
}

Vector Triangle::surfaceNormal(Vector & in)
{
	Vector AB = this->B - this->A;
	Vector AC = this->C - this->A;
	Vector sNormal = AB.cross(AC);
	return sNormal.normalize();
}

Matrix Triangle::getTransformM()
{
	return this->m;
}

Matrix Triangle::getInvTransformM()
{
	return this->iM;
}


Triangle::~Triangle()
{
}
