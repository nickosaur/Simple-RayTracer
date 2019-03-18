#include "Vector.h"
#include <math.h>
#include <iostream>

using namespace std;

Vector::Vector()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::~Vector()
{
}

Vector Vector::operator+(Vector & v2)
{
	return Vector(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

Vector Vector::operator-(Vector & v2)
{
	return Vector(this->x - v2(0), this->y - v2(1), this->z - v2(2));
}

Vector Vector::operator*(float num)
{
	return Vector(this->x * num, this->y * num, this->z * num);
}

Vector Vector::operator/(float num)
{
	return Vector(this->x / num, this->y / num, this->z / num);
}

bool Vector::operator==(Vector & v2)
{
	float epsilon = 1e-6;
	Vector diff = *this - v2;
	float result = diff.dot(diff);
	return (result < epsilon);
}

float & Vector::operator()(const unsigned &num)
{
	switch (num) {
	case 0:
		return this->x;
	case 1:
		return this->y;
	case 2:
		return this->z;
	}
}

float Vector::magnitude(Vector & v)
{
	float _x = v.x * v.x;
	float _y = v.y * v.y;
	float _z = v.z * v.z;

	return sqrt(_x + _y + _z);
}

Vector Vector::normalize()
{
	Vector result = (*this) / magnitude((*this));
	return result;
}

float Vector::dot(Vector & rhs)
{
	return ((*this)(0) * rhs(0)) + ((*this)(1) * rhs(1)) + ((*this)(2) * rhs(2));
}

Vector Vector::cross(Vector & rhs)
{
	Vector lhs = (*this);
	Vector result = Vector();
	result(0) = (lhs(1) * rhs(2)) - (lhs(2) * rhs(1));
	result(1) = (lhs(2) * rhs(0)) - (lhs(0) * rhs(2));
	result(2) = (lhs(0) * rhs(1)) - (lhs(1) * rhs(0));

	return result;
}

Vector Vector::upvector(Vector & up, Vector & z)
{
	Vector upZ = up.cross(z);
	Vector upY = z.cross(upZ);
	return upY.normalize();
}

/*Vector operator*(float num, Vector& v1) {
	return Vector(num * v1(0), num * v1(1), num * v1(2));
}*/
