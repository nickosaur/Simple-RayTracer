#include "Matrix.h"
#include <vector>
#include <tuple>
#define SIZE 4

Matrix::Matrix()
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->mat[i][j] = 0.0f;
		}
	}
}

/*Matrix::Matrix(Matrix & m)
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->mat[i][j] = m(i,j);
		}
	}
}*/

Matrix::Matrix(float num)
{
	for (int i = 0; i < SIZE; i++) {
		this->mat[i][i] = num;
	}
}

Matrix::Matrix(float matrix[4][4])
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			this->mat[i][j] = matrix[i][j];
		}
	}
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator*(Matrix &m)
{
	Matrix result = Matrix();
	float temp = 0.0f;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			temp = 0.0f;
			for (int k = 0; k < SIZE; k++) {
				temp += mat[i][k] * m(k, j);
			}
			result(i, j) = temp;
		}
	}
	return result;
}

Matrix Matrix::operator+(Matrix &m)
{
	Matrix sum = Matrix();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			sum(i, j) = (*this)(i, j) + m(i, j);
		}
	}
	return sum;
}

Matrix Matrix::operator-(Matrix &m)
{
	Matrix diff = Matrix();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			diff(i, j) = (*this)(i, j) - m(i, j);
		}
	}
	return diff;
}

Matrix Matrix::operator*(float num)
{
	Matrix mult = Matrix();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			mult(i, j) = (*this)(i, j) * num;
		}
	}
	return mult;
}

Matrix Matrix::operator/(float num)
{
	Matrix div = Matrix();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			div(i, j) = (*this)(i, j) / num;
		}
	}
	return div;
}

Vector Matrix::operator*(Vector &v)
{
	Vector result = Vector();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result(i) += (*this)(i, j) * v(j);
		}
	}
	return result;
}

float & Matrix::operator()(const unsigned &row, const unsigned &col)
{
	return this->mat[row][col];
}

float & Matrix::operator()(const unsigned & val)
{
	// row major 
	/*
		[0 1 2 3
		 4 5 6 7
		 8 9 10 11
		 12 13 14 15]
	*/
	int row = val / 4;
	int col = val % 4;
	return (*this)(row, col);

}

Matrix Matrix::inverse()
{
	Matrix inv = Matrix();
	float det;
	int i;

	inv(0) = (*this)(5) * (*this)(10) * (*this)(15) -
		(*this)(5)* (*this)(11)* (*this)(14) -
		(*this)(9)* (*this)(6)* (*this)(15) +
		(*this)(9)* (*this)(7)* (*this)(14) +
		(*this)(13)* (*this)(6)* (*this)(11) -
		(*this)(13)* (*this)(7)* (*this)(10);

	inv(4) = -(*this)(4)* (*this)(10)* (*this)(15) +
		(*this)(4)* (*this)(11)* (*this)(14) +
		(*this)(8)* (*this)(6)* (*this)(15) -
		(*this)(8)* (*this)(7)* (*this)(14) -
		(*this)(12)* (*this)(6)* (*this)(11) +
		(*this)(12)* (*this)(7)* (*this)(10);

	inv(8) = (*this)(4)* (*this)(9)* (*this)(15) -
		(*this)(4)* (*this)(11)* (*this)(13) -
		(*this)(8)* (*this)(5)* (*this)(15) +
		(*this)(8)* (*this)(7)* (*this)(13) +
		(*this)(12)* (*this)(5)* (*this)(11) -
		(*this)(12)* (*this)(7)* (*this)(9);

	inv(12) = -(*this)(4)* (*this)(9)* (*this)(14) +
		(*this)(4)* (*this)(10)* (*this)(13) +
		(*this)(8)* (*this)(5)* (*this)(14) -
		(*this)(8)* (*this)(6)* (*this)(13) -
		(*this)(12)* (*this)(5)* (*this)(10) +
		(*this)(12)* (*this)(6)* (*this)(9);

	inv(1) = -(*this)(1)* (*this)(10)* (*this)(15) +
		(*this)(1)* (*this)(11)* (*this)(14) +
		(*this)(9)* (*this)(2)* (*this)(15) -
		(*this)(9)* (*this)(3)* (*this)(14) -
		(*this)(13)* (*this)(2)* (*this)(11) +
		(*this)(13)* (*this)(3)* (*this)(10);

	inv(5) = (*this)(0)* (*this)(10)* (*this)(15) -
		(*this)(0)* (*this)(11)* (*this)(14) -
		(*this)(8)* (*this)(2)* (*this)(15) +
		(*this)(8)* (*this)(3)* (*this)(14) +
		(*this)(12)* (*this)(2)* (*this)(11) -
		(*this)(12)* (*this)(3)* (*this)(10);

	inv(9) = -(*this)(0)* (*this)(9)* (*this)(15) +
		(*this)(0)* (*this)(11)* (*this)(13) +
		(*this)(8)* (*this)(1)* (*this)(15) -
		(*this)(8)* (*this)(3)* (*this)(13) -
		(*this)(12)* (*this)(1)* (*this)(11) +
		(*this)(12)* (*this)(3)* (*this)(9);

	inv(13) = (*this)(0)* (*this)(9)* (*this)(14) -
		(*this)(0)* (*this)(10)* (*this)(13) -
		(*this)(8)* (*this)(1)* (*this)(14) +
		(*this)(8)* (*this)(2)* (*this)(13) +
		(*this)(12)* (*this)(1)* (*this)(10) -
		(*this)(12)* (*this)(2)* (*this)(9);

	inv(2) = (*this)(1)* (*this)(6)* (*this)(15) -
		(*this)(1)* (*this)(7)* (*this)(14) -
		(*this)(5)* (*this)(2)* (*this)(15) +
		(*this)(5)* (*this)(3)* (*this)(14) +
		(*this)(13)* (*this)(2)* (*this)(7) -
		(*this)(13)* (*this)(3)* (*this)(6);

	inv(6) = -(*this)(0)* (*this)(6)* (*this)(15) +
		(*this)(0)* (*this)(7)* (*this)(14) +
		(*this)(4)* (*this)(2)* (*this)(15) -
		(*this)(4)* (*this)(3)* (*this)(14) -
		(*this)(12)* (*this)(2)* (*this)(7) +
		(*this)(12)* (*this)(3)* (*this)(6);

	inv(10) = (*this)(0)* (*this)(5)* (*this)(15) -
		(*this)(0)* (*this)(7)* (*this)(13) -
		(*this)(4)* (*this)(1)* (*this)(15) +
		(*this)(4)* (*this)(3)* (*this)(13) +
		(*this)(12)* (*this)(1)* (*this)(7) -
		(*this)(12)* (*this)(3)* (*this)(5);

	inv(14) = -(*this)(0)* (*this)(5)* (*this)(14) +
		(*this)(0)* (*this)(6)* (*this)(13) +
		(*this)(4)* (*this)(1)* (*this)(14) -
		(*this)(4)* (*this)(2)* (*this)(13) -
		(*this)(12)* (*this)(1)* (*this)(6) +
		(*this)(12)* (*this)(2)* (*this)(5);

	inv(3) = -(*this)(1)* (*this)(6)* (*this)(11) +
		(*this)(1)* (*this)(7)* (*this)(10) +
		(*this)(5)* (*this)(2)* (*this)(11) -
		(*this)(5)* (*this)(3)* (*this)(10) -
		(*this)(9)* (*this)(2)* (*this)(7) +
		(*this)(9)* (*this)(3)* (*this)(6);

	inv(7) = (*this)(0)* (*this)(6)* (*this)(11) -
		(*this)(0)* (*this)(7)* (*this)(10) -
		(*this)(4)* (*this)(2)* (*this)(11) +
		(*this)(4)* (*this)(3)* (*this)(10) +
		(*this)(8)* (*this)(2)* (*this)(7) -
		(*this)(8)* (*this)(3)* (*this)(6);

	inv(11) = -(*this)(0)* (*this)(5)* (*this)(11) +
		(*this)(0)* (*this)(7)* (*this)(9) +
		(*this)(4)* (*this)(1)* (*this)(11) -
		(*this)(4)* (*this)(3)* (*this)(9) -
		(*this)(8)* (*this)(1)* (*this)(7) +
		(*this)(8)* (*this)(3)* (*this)(5);

	inv(15) = (*this)(0)* (*this)(5)* (*this)(10) -
		(*this)(0)* (*this)(6)* (*this)(9) -
		(*this)(4)* (*this)(1)* (*this)(10) +
		(*this)(4)* (*this)(2)* (*this)(9) +
		(*this)(8)* (*this)(1)* (*this)(6) -
		(*this)(8)* (*this)(2)* (*this)(5);

	det = (*this)(0)* inv(0) + (*this)(1)* inv(4) + (*this)(2)* inv(8) + (*this)(3)* inv(12);

	/*if (det == 0)
		return false;*/

	det = 1.0f / det;

	Matrix invOut = Matrix();
	for (i = 0; i < 16; i++)
		invOut(i) = inv(i) * det;

	return invOut;
}

Matrix Matrix::transpose()
{
	Matrix res = Matrix();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			res(i, j) = (*this)(j, i);
		}
	}
	return res;
}
