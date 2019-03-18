#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Camera.h"
#include "Vector.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Triangle.h"
#include "Sphere.h"
using namespace std;

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif 

#ifdef MAINPROGRAM
int width = 600, height = 400; // width and height
float shininess;
float ambient[3];
float diffuse[3];
float specular[3];
float emission[3];
float attenuation[3];
#else
EXTERN int width, height;
EXTERN float ambient[3];
EXTERN float diffuse[3];
EXTERN float specular[3];
EXTERN float emission[3];
EXTERN float attenuation[3];
EXTERN float shininess;
#endif 

EXTERN string outputFilename;

EXTERN int maxVertices;
EXTERN vector<Vector> vertices;
const int numLights = 100;
EXTERN vector<Light*> lights;
EXTERN vector<Shape*> shapes;
EXTERN int numused;

const int maxprimitives = 1001;
//EXTERN GeometricPrimitive* geometricPrimitives[maxprimitives];
EXTERN int numprimitives;

EXTERN int maxdepth;
EXTERN Vector cameraPosition;

#endif