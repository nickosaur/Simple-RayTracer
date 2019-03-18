
#include <math.h>
#include "variables.h"
#include "Film.h"
#include "readfile.h"
#include "RayTracer.h"
#include <thread> // do it by multiples of 2s
#include <future>
#include <atomic>
using namespace std;

void init() {
	attenuation[0] = 1; attenuation[1] = 0; attenuation[2] = 0;
	ambient[0] = 0; ambient[1] = 0; ambient[2] = 0;
	shininess = 0;
	diffuse[0] = 0; diffuse[1] = 0; diffuse[2] = 0;
	specular[0] = 0; specular[1] = 0; specular[2] = 0;
	emission[0] = 0; emission[1] = 0; emission[2] = 0;
	maxdepth = 10;
	//vector<Vector> vertices;
	//vector<Light*> lights;
	//vector<Shape*> shapes;
}

int main(int argc, char * argv[]) {
	FreeImage_Initialise();
	init();
	Camera camera;

	Color* color = new Color(0.f, 0.f, 0.f);
	cout << "Reading input file" << endl;
	readfile(argv[1], &camera);

	cout << "Finish parsing" << endl;
	Film film = Film::Film();
	cout << "Generating pixels" << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Sample sample = Sample(i, j);
			Ray ray = camera.generateRay(sample);
			RayTracer::trace(ray, maxdepth, color, shapes, lights);
			film.commit(sample, *color);
		}
		cout << "Finished row " << i << endl;
	}

	outputFilename = "pupu.png";
	cout << "writing image to " << outputFilename << endl;
	film.writeImage(outputFilename);

	FreeImage_DeInitialise();
	return 0;
}