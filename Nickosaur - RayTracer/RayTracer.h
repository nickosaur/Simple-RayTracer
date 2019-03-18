#include "variables.h"
#include "glm/glm.hpp"

class RayTracer
{
public:
	RayTracer();
	static void checkHit(Ray & r, float * thit, vector<Shape*> shapes, Light * light, Vector & input);
	static Color computeLight(Intersection in, vector<Light*> lights, Shape * geom, vector<Shape*> shapes);
	static void trace(Ray & ray, int depth, Color * color, vector<Shape*> shapes, vector<Light*> lights);
	~RayTracer();
};
