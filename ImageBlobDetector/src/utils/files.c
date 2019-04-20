#include "files.h"

Image *readImageDefaultFormat(FILE *f)
{
	if (!f) return NULL;
	if (feof(f)) return NULL;

	Pixel *pixelsMat;

	// Used to measure file loading time
	clock_t start, end;

	Image *image = createImage();

	// Read filename, height, width and channels from file
	fscanf(f, "%s\n", image->fileName);
	fscanf(f, "%d %d %d", &image->height, &image->width, &image->channels);

	// Allocate pixels matrix
	pixelsMat = image->pixels = createPixelMatrix(image->height, image->width);

	printInfo("Reading %s", image->fileName);
	
	// Start loading file
	start = clock();

	for (int i = 0; i < image->height; ++i)
	{
		for (int j = 0; j < image->width; ++j, ++pixelsMat)
		{
			// '%hhu' to read unsigned char
			fscanf(f, "%hhu\n%hhu\n%hhu\n", &pixelsMat->red, &pixelsMat->green, &pixelsMat->blue);

			pixelsMat->analysed = 0;
		}
	}
	
	end = clock();

	// Ended loading file
	printInfo("%s read in %f seconds", image->fileName, executionTime(start, end));

	return image;
}