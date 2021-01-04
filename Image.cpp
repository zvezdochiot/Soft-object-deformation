#include "Image.h"

Image::Image(int width, int height): w(width), h(height)
{
	redChannel = new float*[w];
	greenChannel = new float*[w];
	blueChannel = new float*[w];
	for (unsigned int i=0; i < w; ++i)
	{
		redChannel[i] =  new float[h];
		greenChannel[i] =  new float[h];
		blueChannel[i] =  new float[h];
		for (unsigned int j=0; j < h; ++j)
		{
			redChannel[i][j] = 1;
			greenChannel[i][j] = 1;
			blueChannel[i][j] = 1;
		}
	}
}

Image::Image(char* filename)
{
	FILE * f;
	long lSize;
	unsigned char * buffer;
	size_t result;

	f = fopen ( filename, "rb" );
	if (f==NULL) {fputs ("File error",stderr); exit (1);}

	// obtain file size:
	fseek (f , 0 , SEEK_END);
	lSize = ftell (f);
	rewind (f);

	// allocate memory to contain the whole file:
	buffer = (unsigned char*) malloc (sizeof(unsigned char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	// copy the file into the buffer:
	result = fread (buffer,1,lSize,f);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

	/* the whole file is now loaded in the memory buffer. */
	w = 0;
	h = 0;

	w += (unsigned int)buffer[14+4]; 
	w += (unsigned int)buffer[14+5] << 8; 
	w += (unsigned int)buffer[14+6] << 16; 
	w += (unsigned int)buffer[14+7] << 24; 

	h += (unsigned int)buffer[14+8]; 
	h += (unsigned int)buffer[14+9] << 8; 
	h += (unsigned int)buffer[14+10] << 16; 
	h += (unsigned int)buffer[14+11] << 24; 

	/*std::cout << "Size: " << lSize << "\n";
	std::cout << "w: " << w << "\n";
	std::cout << "h: " << h << "\n";
*/
	redChannel = new float*[w];
	greenChannel = new float*[w];
	blueChannel = new float*[w];
	for (unsigned int i=0; i < w; ++i)
	{
		redChannel[i] =  new float[h];
		greenChannel[i] =  new float[h];
		blueChannel[i] =  new float[h];
	}

	int x,y;
	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			x=i; y=j;
			
			redChannel[i][j] = (unsigned int)buffer[(x+y*w)*3+2 + 54]/255;
			greenChannel[i][j] = (unsigned int)buffer[(x+y*w)*3+1 + 54]/255;
			blueChannel[i][j] = (unsigned int)buffer[(x+y*w)*3 + 54]/255;
		}
	}
	// terminate
	fclose (f);
	free (buffer);
}

void Image::saveBMP(char* filename)
{
	unsigned char *img = NULL;
	int filesize = 54 + 3*w*h; 
	if( img ) free( img );
	img = (unsigned char *)malloc(3*w*h);
	memset(img,0,sizeof(img));
	int x,y,r,g,b;
	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			x=i; y=(h-1)-j;
			r = redChannel[i][j]*255;
			g = greenChannel[i][j]*255;
			b = blueChannel[i][j]*255;
			if (r > 255) r=255;
			if (g > 255) g=255;
			if (b > 255) b=255;
			img[(x+y*w)*3+2] = (unsigned char)(r);
			img[(x+y*w)*3+1] = (unsigned char)(g);
			img[(x+y*w)*3+0] = (unsigned char)(b);
		}
	}

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);


	FILE *f;

	f = fopen(filename,"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(unsigned int i=0; i<h; i++)
	{
		fwrite(img+(w*(h-i-1)*3),3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	fclose(f);
}

// no range checking!
void Image::setPixel(unsigned int x,unsigned int y, float r, float g, float b)
{
	redChannel[x][y] = r;
	greenChannel[x][y] = g;
	blueChannel[x][y] = b;
}

void Image::addColor(unsigned int x,unsigned int y, float r, float g, float b)
{
	redChannel[x][y]   = 0.5* (redChannel[x][y]+r);
	greenChannel[x][y] = 0.5* (greenChannel[x][y]+g);
	blueChannel[x][y]  = 0.5* (blueChannel[x][y]+b);
}

float* Image::getPixel(unsigned int x,unsigned int y)
{
	float* pixel =  new float[3];
	pixel[0] = redChannel[x][y];
	pixel[1] = greenChannel[x][y];
	pixel[2] = blueChannel[x][y];
	return pixel;
}