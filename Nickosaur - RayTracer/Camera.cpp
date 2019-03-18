#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(Vector & eye, Vector & lookAt, Vector & up, float fovy)
{
	this->eye = eye;
	this->lookAt = lookAt;
	this->up = up;
	this->fovy = fovy;

	this->w = this->eye - this->lookAt;
	this->w = (this->w).normalize();
	Vector wUp = (this->w).cross(this->up);
	this->u = wUp.normalize();
	this->v = w.cross(u);

	this->fovy = fovy * M_PI / 180.0f;
	
	float z = tan(this->fovy / 2.0f);
	z = (1.0f / z) * height / 2.0f;
	this->fovx = 2.0f * atan((width / 2.0f) / z);
}

Ray Camera::generateRay(Sample s)
{
	float _h = (float)height;
	float _w = (float)width;

	float x = ((float) s.x) + 0.5f;
	float y = ((float) s.y) + 0.5f;

	float alpha = -tan(fovx / 2.0f) * (y - (_w / 2.0f)) / (_w / 2.0f);
	float beta = tan(fovy / 2.0f) * ((_h / 2.0f) - x) / (_h / 2.0f);

	Vector alpha_u = this->u * alpha;
	Vector beta_v = this->v * beta;
	Vector dir = alpha_u + beta_v - w;
	dir = dir.normalize();
	return Ray(this->eye, dir);
}


Camera::~Camera()
{
}
