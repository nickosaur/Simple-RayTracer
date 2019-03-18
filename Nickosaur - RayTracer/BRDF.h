#pragma once
#include "Color.h"
class BRDF
{
public:
	BRDF();
	BRDF(Color & ambient, Color & diffuse, Color & specular, Color & emission, float shininess);
	~BRDF();

	Color ambient, diffuse, specular, emission;
	float shininess;
};

