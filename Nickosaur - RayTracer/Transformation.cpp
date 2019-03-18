#include "Transformation.h"



Transformation::Transformation()
{
}

Transformation::~Transformation()
{
}

Vector multiply4(Matrix & m, Vector & v)
{
	Vector result = Vector();
	result(0) = m(0, 0) * v(0) + m(0, 1) * v(1) + m(0, 2) * v(2) + m(0, 3);
	result(1) = m(1, 0) * v(0) + m(1, 1) * v(1) + m(1, 2) * v(2) + m(1, 3);
	result(2) = m(2, 0) * v(0) + m(2, 1) * v(1) + m(2, 2) * v(2) + m(2, 3);
	return result;
}

Vector multiply3(Matrix & m, Vector & v)
{
	Vector result = Vector();
	result(0) = m(0, 0) * v(0) + m(0, 1) * v(1) + m(0, 2) * v(2);
	result(1) = m(1, 0) * v(0) + m(1, 1) * v(1) + m(1, 2) * v(2);
	result(2) = m(2, 0) * v(0) + m(2, 1) * v(1) + m(2, 2) * v(2);
	return result;
}

Ray multiplyRay(Matrix & m, Ray & r)
{
	Vector pos = Vector(r.position.x, r.position.y, r.position.z);
	Vector p = multiply4(m, pos);
	Vector d = multiply3(m, r.direction);
	Ray ret = Ray(p, d);
	return ret;
}

Matrix rotate(Vector & axis, float degrees)
{
	float rad = degrees * M_PI / 180.0f;
	Vector normAxis = axis.normalize();

	Matrix aCos = Matrix(0.0f);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			aCos(i, j) = normAxis(i) * normAxis(j);
		}
	}
	aCos(3, 3) = 0;

	float mat[4][4] = {
		0, -normAxis(2), normAxis(1), 0,
		normAxis(2), 0, -normAxis(0), 0,
		-normAxis(1), normAxis(0), 0, 0,
		0, 0, 0, 0
	};
	Matrix aStar = Matrix(mat);
	Matrix I = Matrix(1.0f);
	I(3, 3) = 0;
	I = I * (cos(rad));
	aCos = aCos * (1 - cos(rad));
	aStar = aStar * (sin(rad));

	Matrix ret = I + aCos + aStar;
	ret(3, 3) = 1;
	return ret;
}

Matrix scale(float sx, float sy, float sz)
{
	Matrix mat = Matrix(1.0f);
	mat(0, 0) = sx;
	mat(1, 1) = sy;
	mat(2, 2) = sz;
	return mat;
}

Matrix translate(float tx, float ty, float tz)
{
	Matrix tr = Matrix(1.0f);
	tr(0, 3) = tx;
	tr(1, 3) = ty;
	tr(2, 3) = tz;
	return tr;
}

/*int main() {
	Matrix m = Matrix(1.0f);
	Transformation T(m);
	Matrix p = Matrix(1.0f);
	return 0;
}*/