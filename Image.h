#ifndef __myImage_h
#define __myImage_h

#include <fstream>
#include <iostream>
#include <string.h>

class Image
{
	int w;
	int h;

	float** redChannel;
	float** greenChannel;
	float** blueChannel;

public:
	Image(int width, int height);
	Image(char* filename);

	void saveBMP(char* filename);
	void setPixel(unsigned int x,unsigned int y, float r, float g, float b);
	void addColor(unsigned int x,unsigned int y, float r, float g, float b);
	float* getPixel(unsigned int x,unsigned int y);
	inline int getWidth(){return w;}
	inline int getHeight(){return h;}
};


//#include "Image.cpp"

#endif