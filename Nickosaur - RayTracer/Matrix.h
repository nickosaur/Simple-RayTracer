#pragma once
#include <stdlib.h>
#include "Vector.h"
class Matrix
{
public:
	Matrix();
	//Matrix(Matrix & m);
	Matrix(float num); // for identity matrix
	Matrix(float matrix[4][4]);
	virtual ~Matrix();

	//Matrix - Matrix operations
	Matrix operator*(Matrix &);
	Matrix operator+(Matrix &);
	Matrix operator-(Matrix &);

	// Matrix - Scalar operations
	Matrix operator*(float num);
	Matrix operator/(float num);

	// Matrix - Vector Operation
	Vector operator*(Vector &);

	float& operator()(const unsigned &, const unsigned &);
	float& operator()(const unsigned & val);

	Matrix inverse();
	Matrix transpose();
	float mat[4][4] = { 0 };

private:
	//member variables

};


