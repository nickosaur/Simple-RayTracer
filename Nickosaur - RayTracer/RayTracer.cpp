#include "RayTracer.h"
#include <algorithm>



RayTracer::RayTracer()
{
}

void RayTracer::checkHit(Ray & r, float * thit, vector<Shape *> shapes, Light * light, Vector & input)
{
	float t = -1;
	for (int i = 0; i < shapes.size(); i++) {
		Intersection in;
		if (shapes[i]->intersect(r, in)) {
			Vector dist = r.position - in.position;
			float distance = dist.magnitude(dist);
			if (t < 0 || distance < t) {
				t = distance;
			}
		}
	}

	*thit = t;

	if (light->isPoint()) {
		Vector light_Pos = light->getPosition();
		Vector difference = input - light_Pos;
		float distance = difference.magnitude(difference);
		if (t < distance) {
			*thit = t;
		}
		else {
			*thit = -1;
		}
	}

	
}

Color RayTracer::computeLight(Intersection in, vector<Light*> lights, Shape * geom, vector<Shape*> shapes)
{
	Color temp = Color(0.0f);
	BRDF brdf = geom->getBRDF();
	for (int i = 0; i < lights.size(); i++) {
		Vector in_pos = in.position; // remove
		//in_pos = in_pos * 0.01f;//remove
		Ray ray = lights[i]->ifBlocked(in_pos); 
		//do closest hit
		float t;
		checkHit(ray, &t, shapes, lights[i], in_pos);
		if (t < 0) {
			// do it
			Color light_Color = lights[i]->getColor(); // maybe remove
			Vector eyeDir = cameraPosition - in_pos;
			eyeDir = eyeDir.normalize();

			Vector lightDir = lights[i]->getDirection(in_pos);

			Vector half0 = eyeDir + lightDir;
			half0 = half0.normalize();

			float kd = lights[i]->getShade(in_pos, in.normal);
			Color diff = brdf.diffuse;
			Color lambert = diff * kd;
			lambert = lambert * light_Color;

			float nDotH = max((in.normal).dot(half0), 0.0f);
			float shininess = brdf.shininess;
			Color spec = brdf.specular;
			Color phong = spec * pow(nDotH, shininess);
			
			phong = phong * light_Color; // maybe remove
			float atten = lights[i]->getAttenuationColor(in_pos);
			temp = temp + lambert;
			temp = temp + phong;
			temp = temp * atten;
		}
		/*checkHit(ray, &t, shapes, lights[i], in.position);
		if (t < 0) {
			// do it
			Vector eyeDir = cameraPosition - in.position;
			eyeDir = eyeDir.normalize();
			
			Vector lightDir = lights[i]->getDirection(in.position);

			Vector half0 = eyeDir + lightDir;
			half0 = half0.normalize();

			float kd = lights[i]->getShade(in.position, in.normal);
			Color diff = brdf.diffuse;
			Color lambert = diff * kd;

			float nDotH = max((in.normal).dot(half0), 0.0f);
			float shininess = brdf.shininess;
			Color spec = brdf.specular;
			Color phong = spec * pow(nDotH, shininess);
			Color light_Color = lights[i]->getColor(); // maybe remove
			phong = phong * light_Color; // maybe remove
			float atten = lights[i]->getAttenuationColor(in.position);
			temp = temp + lambert;
			temp = temp + phong;
			temp = temp * atten;
		}*/
	}
	Color finalColor = temp + brdf.ambient;
		finalColor = finalColor + brdf.emission;
	return finalColor;
}

void RayTracer::trace(Ray & ray, int depth, Color * color, vector<Shape*> shapes, vector<Light*> lights)
{
	if (depth <= 0) {
		*color = Color(0.0f);
		return;
	}

	float close = -1.f;
	Intersection finalIn;
	Intersection in;
	Shape * shape = NULL;

	for (int i = 0; i < shapes.size(); i++) {

		if (shapes[i]->intersect(ray, in)) {
			//Vector RI = in.position - ray.position;
			Vector RI = ray.position - in.position;
			float distance = RI.magnitude(RI);
			if (close < 0 || distance < close) {
				close = distance;
				finalIn = in;
				shape = shapes[i];
			}
		}
	}

	if (shape) {
		BRDF brdf = shape->getBRDF();


		Vector norml = shape->surfaceNormal(finalIn.position);
		Vector rayDir = (ray.direction).normalize();
		Vector ortho = norml * (norml.dot(rayDir));
		Vector inRefl = ortho * 2.0f;
		Vector reflect = (ray.direction * 1.01f - inRefl).normalize();
		Vector reflect2 = reflect * 1.0f;
		Color finalColor = computeLight(finalIn, lights, shape, shapes);

		Color cTrace;
		
		Vector rayPos = finalIn.position + reflect2;
		Ray rTrace = Ray(rayPos, reflect);
		trace(rTrace, depth - 1, &cTrace, shapes, lights);

		cTrace = cTrace * brdf.specular;
		finalColor = finalColor + cTrace;
		*color = finalColor;
		return;
	}
	*color = Color(0.0f);
}


RayTracer::~RayTracer()
{
}
