#include "analyzer.h"

void analyseImage(Image* image, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	Pixel *pixels = image->pixels;

	for (int i = 0; i < image->height; ++i)
	{
		for (int j = 0; j < image->height; ++j, ++pixels)
		{
			if (pixels->analysed) continue;


		}
	}
}

void analysePizel(Pixel *pixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	if ((pixel->red <= r + t && pixel->red <= r - t) &&
		(pixel->green <= g + t && pixel->green <= g - t) &&
		(pixel->blue <= b + t && pixel->blue <= b - t))
	{

	}
}
