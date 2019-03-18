#include "Film.h"

Film::Film()
{
	img = FreeImage_Allocate(width, height, 24);
}

char Film::convertToPixel(float x) {
	if (x < 0.f) return ((unsigned char)(0.f));
	else if (x >= 1.f) return ((unsigned char)(255.f));
	else return ((unsigned char)(x * 255.f));
}

void Film::commit(Sample& sample, Color& color)
{

	RGBQUAD* pixel = new RGBQUAD();
	pixel->rgbRed = convertToPixel(color.r);
	pixel->rgbGreen = convertToPixel(color.g);
	pixel->rgbBlue = convertToPixel(color.b);
	FreeImage_SetPixelColor(img, sample.y, sample.x, pixel);


}


void Film::writeImage(string name)
{
	string output = "poopoo.png";
	FreeImage_Save(FIF_PNG, img, ("Output/" + output).c_str(), 0);
}

