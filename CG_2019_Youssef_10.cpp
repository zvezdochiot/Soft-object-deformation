//Name: Omar Youssef
//Faculty: Medical Faculty Mannheim
//Discipline: Master in Biomedical Engineering
//Student Number: 3571222


#include <iostream>
#include "Image.h"
#include <math.h>


// Defines the DeformGrid in 2D with 4x4 control points.
// The values here are force field values used for deformation

class DeformGrid
{
public:

	float** x;
	float** y;
	DeformGrid()
	{
		x = new float*[4];
		y = new float*[4];
		for (unsigned int i=0; i < 4; ++i)
		{
			x[i] = new float[4];
			y[i] = new float[4];
		}
			// set some values:
			x[0][3] = 0; x[1][3] = 0; x[2][3] = 0;   x[3][3] = 0;
			x[0][2] = 100; x[1][2] = 100; x[2][2] = 100;   x[3][2] = 100;
			x[0][1] = -100; x[1][1] = -100; x[2][1] = -100;   x[3][1] = -100;
			x[0][0] = 0; x[1][0] = 0; x[2][0] = 0;   x[3][0] = 0;


			y[0][3] = 0;  y[1][3] = 100; y[2][3] = -100; y[3][3] = 0;
			y[0][2] = 0;  y[1][2] = 100; y[2][2] = -100; y[3][2] = 0;
			y[0][1] = 0;  y[1][1] = 100; y[2][1] = -100; y[3][1] = 0;
			y[0][0] = 0;  y[1][0] = 100; y[2][0] = -100; y[3][0] = 0;
	}
};

// create a 2D image 300x300 and save it in .bmp format (3 color channels)
void createTestImage()
{
	Image img(300,300);

	// create red grid:
	for (unsigned int i=0; i < 300-1; i+=20)
	for (unsigned int j=0; j < 300; ++j)
	{
		img.setPixel(i,j, 1, 0, 0);
		img.setPixel(i+1,j, 1, 0, 0);
		img.setPixel(j,i, 1, 0, 0);
		img.setPixel(j,i+1, 1, 0, 0);
	}
	// other stuff:
	for (unsigned int i=50; i < 100; ++i)
	for (unsigned int j=100; j < 150; ++j)
		img.addColor(i,j, 0, 1, 0);
	for (unsigned int i=250; i < 300; ++i)
	for (unsigned int j=50; j < 250; ++j)
		img.addColor(i,j, 0, 1, 0);
	for (unsigned int i=160; i < 200; ++i)
	for (unsigned int j=200; j < 270; ++j)
		img.addColor(i,j, 0, 0, 1);
	for (unsigned int i=10; i < 110; ++i)
	for (unsigned int j=140; j < 190; ++j)
		img.addColor(i,j, 0, 0, 1);

	img.saveBMP("TestImage.bmp");
}

// return the cubic bezier polynoms:
// t: float value in [0 1]
// k: polynom index
float CubicBezier(float t, unsigned int k)
{
	// TODO compute and return the polynom weights

	float p, u;

	u = 1 - t;

	p = u * u * u; //first term
	if (k == 0)
		return p;

	p = 3 * u * u * t; //second term

	if (k == 1)
		return  p;

	p = 3 * u * t * t; //third term
	if (k == 2)
		return p;

	p = t * t * t; //fourth term
	if (k == 3)
		return  p;

}

// return the linear bezier polynoms:
// t: float value in [0 1]
// k: polynom index
float LinearBezier(float t, unsigned int k)
{
	// TODO compute and return the polynom weights


	float p, u;

	u = 1 - t;

	p = u; //first term
	if (k == 0)
		return p;

	p = t; //second term

	if (k == 1)
		return  p;
}


using namespace std;

int main() {

	createTestImage();
	Image img("TestImage.bmp");
	Image defImg("TestImage.bmp");
	DeformGrid grid;

	// create Bezier Spline:
	float r,g,b;
	float dx, dy;
	double u,v;

	// compute the new color values for each pixel in the deformed image.
	// You have to compute the color value for each channel red,green,blue!
 	for (unsigned int i=0; i <img.getWidth(); ++i)
	for (unsigned int j=0; j <img.getHeight(); ++j)
	{
		// compute the position u,v in [0 1] in x- and y-direction in the spline:
		u = 1.0/(img.getWidth()-1)*i;
		v = 1.0/(img.getHeight()-1)*j;

		// compute the displacements dx,dy of the voxel according to the deformation grid for the position (u,v)
		// using the cubic Bezier spline
		dx=0; dy=0;
		for (unsigned int x =0; x < 4; ++x)
		for (unsigned int y =0; y < 4; ++y)
		{
			// TODO: Please complete the code using CubicBezier function
			// HINT: sum over control points in x- and y-direction to get a surface!
			// dx +=
			// dy +=


			float tempx = grid.x[x][y];
			float tempy = grid.y[x][y];
			dx += CubicBezier(u, x) * CubicBezier(v, y) * tempx/5;
			dy += CubicBezier(v, y) * CubicBezier(u, x) * tempy/5;

		}

		// deformed position (you need unsigned int value as positions to use the img.getPixel() method!)
		float posx = i + dx;
		float posy = j + dy;



		// interpolate the voxel value from the original image using a linear spline. If the position is outside
		//   the original image set all colors to 0.0.
		if ( (posx > img.getWidth()-1) || (posy > img.getHeight()-1)
				    || (posx < 0) ||(posy < 0) )
		{
			r=0;
			g=0;
			b=0;
		}
		else // linear interpolation of the color values:
		{
			r=0; g=0; b=0;
			for (unsigned int x =0; x < 2; ++x)
			for (unsigned int y =0; y < 2; ++y)
			{
				if ((posx+x < img.getWidth()) && (posy +y < img.getHeight()))
				{
					//TODO: Please complete the code here using LinearBezier function
					//r+=
					//g+=
					//b+=

					float* temp = img.getPixel(posx + x, posy + y);
					r += LinearBezier(img.getPixel(posx, posy)[1], x);
					if(posx+x>=50 && posx+x<=100 && posy + y>=100 && posy + y <=150)
						r=0;
					if(posx+x>=250 && posx+x<=300 && posy + y>=50 && posy + y <=250)
						r=0;
					if(posx+x>=160 && posx+x<=200 && posy + y>=200 && posy + y <=270)
						r=0;
					if(posx+x>=10 && posx+x<=110 && posy + y>=140 && posy + y <=190)
						r=0;

					g += LinearBezier(u, x) * temp[1];
					b += LinearBezier(v, y) * temp[2];

				}

			}
		}
		// set the computed color values for the pixel in the deformed image
		defImg.setPixel(i,j,r,g,b);


	}
	// save deformed image:
	defImg.saveBMP("DeformedImage.bmp");

//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	return 0;
}
