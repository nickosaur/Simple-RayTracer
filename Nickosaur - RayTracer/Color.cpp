#include "Color.h"

Color::Color() {
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
}


Color::Color(float num) // default black
{
	this->r = num;
	this->g = num;
	this->b = num;
}

Color::Color(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

/*Color::Color(Color & c)
{
	this->r = c(0);
	this->g = c(1);
	this->b = c(2);
}*/

Color Color::operator+(Color & c)
{
	return Color((*this)(0) + c(0), (*this)(1) + c(1), (*this)(2) + c(2));
}

Color Color::operator-(Color & c)
{
	return Color((*this)(0) - c(0), (*this)(1) - c(1), (*this)(2) - c(2));
}

Color Color::operator*(float num)
{
	return Color((*this)(0) * num, (*this)(1) * num, (*this)(2) * num);
}

Color Color::operator/(float num)
{
	return Color((*this)(0) / num, (*this)(1) / num, (*this)(2) / num);
}

Color Color::operator*(Color & c)
{
	return Color(this->r * c.r, this->g * c.g, this->b * c.b);
}


float & Color::operator()(int num)
{
	// TODO: insert return statement here
	switch (num) {
	case 0: return this->r;
	case 1: return this->g;
	case 2: return this->b;
	}
}

Color::~Color()
{
}
