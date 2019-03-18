#pragma once
class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);

	virtual ~Vector();

	// Binary operations
	Vector operator+(Vector & v2); // vector addition
	Vector operator-(Vector & v2); // vector subtraction
	Vector operator*(float num); // scalar multiplication
	Vector operator/(float num); // scalar division
	bool operator==(Vector & v2);

	// class functions
	float& operator()(const unsigned &);
	float magnitude(Vector & v);
	Vector normalize();
	float dot(Vector & rhs);
	Vector cross(Vector & rhs);
	static Vector upvector(Vector & up, Vector & z);


	//member variables
	float x, y, z;


protected:
};
