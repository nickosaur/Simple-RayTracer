#pragma once

#include "Sample.h"
#include "Color.h"
#include <string>
#include <vector>
#include "variables.h"
#include "FreeImage.h"

using namespace std;
class Film
{
public:
	Film();
	void commit(Sample & sample, Color & color);
	void writeImage(string name);
	char convertToPixel(float x);
	FIBITMAP* img;
};
