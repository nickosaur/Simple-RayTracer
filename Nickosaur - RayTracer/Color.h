#pragma once
class Color
{
public:
	Color();
	Color(float r, float g, float b);
	Color(float num);

	//Color(Color & c);
	//operator overloading
	Color operator+(Color & c);
	Color operator-(Color & c);
	Color operator*(float num);
	Color operator/(float num);
	Color operator*(Color & c);

	float & operator()(int num);
	float r, g, b;

	~Color();

private:
};

