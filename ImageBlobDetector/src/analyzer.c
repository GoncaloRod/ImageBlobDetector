#include "analyzer.h"

void analyseImage(Image* image, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	Pixel *pixels = image->pixels;

	for (int i = 0; i < image->height; ++i)
	{
		for (int j = 0; j < image->width; ++j, ++pixels)
		{
			if (pixels->analysed) continue;

			pixels->analysed = 1;

			if (inRange(r - t, r + t, pixels->red) && inRange(g - t, g + t, pixels->green) &&
				inRange(b - t, b + t, pixels->blue))
			{

			}
		}
	}
}
