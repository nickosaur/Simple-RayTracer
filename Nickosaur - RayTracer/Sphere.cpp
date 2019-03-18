#include "Sphere.h"



Sphere::Sphere()
{
}

Sphere::Sphere(Vector & center, float radius, BRDF & brdf, Matrix & m)
{
	this->center = center;
	this->radius = radius;
	this->brdf = brdf;
	this->m = m;
	this->iM = m.inverse();
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Ray & ray, Intersection & in)
{
	//Ray tr = multiplyRay(this->iM, ray);
	//Ray tr = ray.transform(inverseM);
	Vector p = multiply4((this->iM), ray.position);
	Vector d = multiply3(iM, ray.direction);
	d = d.normalize();
	Ray nRay = Ray(p, d);

	Vector left = nRay.direction * 2.0f;
	Vector right = nRay.position - this->center;
	float b = left.dot(right);
	
	float a = nRay.direction.dot(nRay.direction);

	left = nRay.position - this->center;
	float c = left.dot(left);
	c = c - pow(this->radius, 2.0f);

	float delta = (b * b) - (4 * a*c);

	if (delta < 0.0f) {
		return false;
	}

	float rootA = (-b + sqrt(delta)) / (2.0f * a);
	float rootB = (-b - sqrt(delta)) / (2.0f * a);

	float t;
	
	if (max(rootA, rootB) < 0.0f) { //check if need <=
		return false;
	}

	if (min(rootA, rootB) > 0.0f) {
		t = min(rootA, rootB);
	}
	else if (rootA < rootB) {
		t = rootB;
	}
	else {
		t = rootA;
	}
	Vector dir = nRay.direction * t;
	Vector position = nRay.position + dir;
	position = multiply4(this->m, position);

	Vector normal = multiply4(this->iM, position);
	normal = normal - (this->center);
	normal = normal.normalize();
	Intersection _in = Intersection(position, normal, this);
	in = _in;
	return true;
}

bool Sphere::intersectP(Ray & ray)
{
	Ray tr = multiplyRay(this->iM, ray);

	Vector left = ray.direction * 2.0f;
	Vector right = ray.position - this->center;
	float b = left.dot(right);

	float a = ray.direction.dot(ray.direction);

	left = ray.position - this->center;
	float c = left.dot(left);
	c = c - pow(this->radius, 2.0f);

	float delta = (b * b) - (4 * a*c);

	if (delta < 0.0f) {
		return false;
	}

	float rootA = (-b + sqrt(delta)) / (2.0f * a);
	float rootB = (-b - sqrt(delta)) / (2.0f * a);

	if (max(rootA, rootB) < 0.0f) { //check if need <=
		return false;
	}

	return true;
}

BRDF Sphere::getBRDF()
{
	return this->brdf;
}

Vector Sphere::surfaceNormal(Vector & in)
{
	Matrix invM = this->iM;
	Vector invM_in = multiply4(invM, in);
	Vector normal = invM_in - this->center;
	invM = invM.transpose();
	normal = multiply3(invM, normal);
	return normal.normalize();
}

Matrix Sphere::getTransformM()
{
	return this->m;
}

Matrix Sphere::getInvTransformM()
{
	return this->iM;
}
