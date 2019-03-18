#pragma once
#include "Vector.h"
#include "Ray.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "variables.h"
#include "Sample.h"
class Camera
{
public:
	Camera();
	Camera(Vector & eye, Vector & lookAt, Vector & up, float fovy);
	Ray generateRay(Sample s);
	~Camera();

	Vector eye, lookAt, up, u, v, w;
	float fovx, fovy;
};

