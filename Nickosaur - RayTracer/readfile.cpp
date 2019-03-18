#include "readfile.h"
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

vector<Light * > lights;
vector<Vector> vertices;
vector<Shape *> shapes;
Vector cameraPosition;
string outputFilename;
float ambient[3];
float diffuse[3];
float specular[3];
float emission[3];
float attenuation[3];
float shininess;
int width;
int height;
int numused = 0;
int maxdepth;
int maxVertices;
int numprimitives;

void rightMultiply(Matrix & M, stack<Matrix>& transfstack)
{
	Matrix &T = transfstack.top();
	T = T * M;
}

bool readvals(stringstream & s, const int numvals, float * values)
{
	for (int i = 0; i < numvals; i++)
	{
		s >> values[i];
		if (s.fail())
		{
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}

void readfile(const char * filename, Camera * camera)
{
	string str, cmd;

	int currVerts = 0;

	ifstream in;
	//in.open(filename);
	in.open("scene5.test");
	if (in.is_open()) {
		stack<Matrix> transfstack;
		transfstack.push(Matrix(1.0f));
		getline(in, str);	
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#'))
			{
				stringstream s(str);
				s >> cmd;
				float values[10]; // Position and color for light, colors for others
									// Up to 10 params for cameras.
				bool validinput;    // Validity of input

				if (cmd == "directional") {
					if (numused < numLights) {
						validinput = readvals(s, 6, values);
						if (validinput) {
							Vector v = Vector(values[0], values[1], values[2]);
							Color color = Color(values[3], values[4], values[5]);
							v = multiply3(transfstack.top(), v);
							DirectionalLight * light = new DirectionalLight(v, color);
							lights.push_back(light); //CHECK IF THERE'S MEMORY LEAK
							numused++;
						}
					}
				}
				else if (cmd == "point") {
					if (numused < numLights) {
						validinput = readvals(s, 6, values);
						if (validinput) {
							Vector v = Vector(values[0], values[1], values[2]);
							Color color = Color(values[3], values[4], values[5]);
							v = multiply4(transfstack.top(), v);
							PointLight * light = new PointLight(v, color, attenuation);
							lights.push_back(light);
							numused++;
						}
					}
				}
				else if (cmd == "maxdepth") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						maxdepth = values[0];
					}
				}
				else if (cmd == "output") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						s >> outputFilename;
					}
				}
				else if (cmd == "maxverts") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						maxVertices = values[0]; // ignore
						//vertices.resize(maxVertices);//maxVertices = values[0];
					}
				}
				else if (cmd == "attenuation") {
					validinput = readvals(s, 3, values); // colors 
					if (validinput) {
						attenuation[0] = values[0];
						attenuation[1] = values[1];
						attenuation[2] = values[2];
					}
				}
				else if (cmd == "ambient") {
					validinput = readvals(s, 3, values); // colors 
					if (validinput) {
						ambient[0] = values[0];
						ambient[1] = values[1];
						ambient[2] = values[2];
					}
				}
				else if (cmd == "diffuse") {
					validinput = readvals(s, 3, values); // colors 
					if (validinput) {
						diffuse[0] = values[0];
						diffuse[1] = values[1];
						diffuse[2] = values[2];
					}
				}
				else if (cmd == "specular") {
					validinput = readvals(s, 3, values); // colors 
					if (validinput) {
						specular[0] = values[0];
						specular[1] = values[1];
						specular[2] = values[2];
					}
				}
				else if (cmd == "emission") {
					validinput = readvals(s, 3, values); // colors 
					if (validinput) {
						emission[0] = values[0];
						emission[1] = values[1];
						emission[2] = values[2];
					}
				}
				else if (cmd == "shininess") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						shininess = values[0];
					}
				}
				else if (cmd == "vertex") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						Vector t = Vector(values[0], values[1], values[2]);
						vertices.push_back(t);
					}
				}
				else if (cmd == "size") {
					validinput = readvals(s, 2, values);
					if (validinput) {
						width = values[0];
						height = values[1];
					}
				}
				else if (cmd == "camera") {
					validinput = readvals(s, 10, values);
					if (validinput) {
						Vector eye = Vector(values[0], values[1], values[2]);
						cameraPosition = eye;
						Vector lookAt = Vector(values[3], values[4], values[5]);
						Vector up = Vector(values[6], values[7], values[8]);
						float fovy = values[9];
					
						*camera = Camera(eye, lookAt, up, fovy);
					}
				}
				else if (cmd == "tri") {
					validinput = readvals(s, 3, values);
					if (validinput) {
							//Shape shape = Shape()
						Vector tempA = vertices[(int)(values[0])];
						Vector A = multiply4(transfstack.top(), tempA);
						Vector tempB = vertices[(int)(values[1])];
						Vector B = multiply4(transfstack.top(), tempB);
						Vector tempC = vertices[(int)(values[2])];
						Vector C = multiply4(transfstack.top(), tempC);

						Color diffuseColor = Color(diffuse[0], diffuse[1], diffuse[2]);
						Color ambientColor = Color(ambient[0], ambient[1], ambient[2]);
						Color specularColor = Color(specular[0], specular[1], specular[2]);
						Color emissionColor = Color(emission[0], emission[1], emission[2]);
						
						BRDF brdf = BRDF(ambientColor, diffuseColor, specularColor, emissionColor, shininess);
						shapes.push_back(new Triangle(A, B, C, brdf, transfstack.top()));
					}
				}
				else if (cmd == "sphere") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						Vector center = Vector(values[0], values[1], values[2]);
						float radius = values[3];
						Color diffuseColor = Color(diffuse[0], diffuse[1], diffuse[2]);
						Color ambientColor = Color(ambient[0], ambient[1], ambient[2]);
						Color specularColor = Color(specular[0], specular[1], specular[2]);
						Color emissionColor = Color(emission[0], emission[1], emission[2]);

						BRDF brdf = BRDF(ambientColor, diffuseColor, specularColor, emissionColor, shininess);
						shapes.push_back(new Sphere(center, radius, brdf, transfstack.top()));
					}
				}
				else if (cmd == "translate") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						Matrix translateM = translate(values[0], values[1], values[2]);
						rightMultiply(translateM, transfstack);
					}
				}
				else if (cmd == "scale") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						Matrix scaleM = scale(values[0], values[1], values[2]);
						rightMultiply(scaleM, transfstack);
					}
				}
				else if (cmd == "rotate") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						Vector axis = Vector(values[0], values[1], values[2]);
						float degrees = values[3];
						Matrix rotateM = rotate(axis, degrees);
						
						rightMultiply(rotateM, transfstack);
					}
				}
				else if (cmd == "pushTransform") {
					transfstack.push(transfstack.top());
				}
				else if (cmd == "popTransform") {
					transfstack.pop();
				}
				else {
					cerr << "Error: " << cmd << " is not an option \n Skipping \n";
				}
			}
			getline(in, str);
		}
	} // else : todo transformations
}
