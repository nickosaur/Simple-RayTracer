#include "BRDF.h"



BRDF::BRDF()
{
}

BRDF::BRDF(Color & ambient, Color & diffuse, Color & specular, Color & emission, float shininess)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->emission = emission;
	this->shininess = shininess;
}


BRDF::~BRDF()
{
}
