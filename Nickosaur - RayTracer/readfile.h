#pragma once

#include <string>
#include <stack>
#include "variables.h"
#include "Camera.h"

using namespace std;

void rightMultiply(Matrix & M, stack<Matrix> & transfstack);
bool readvals(stringstream & s, const int numvals, float * values);
void readfile(const char * filename, Camera* camera);



