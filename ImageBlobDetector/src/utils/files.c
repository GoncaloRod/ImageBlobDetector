#include "files.h"

Image *readImageDefaultFormat(FILE *f)
{
	if (!f) return NULL;
	if (feof(f)) return NULL;

	// Used to measure file loading time
	clock_t start, end;

	Image *image = createImage();

	int r, g, b;

	// Read filename, height, width and channels from file
	fscanf(f, "%s\n", image->fileName);
	fscanf(f, "%d %d %d", &image->height, &image->width, &image->channels);

	// Allocate pixels matrix
	image->pixels = createPixelsMatrix(image->height, image->width);

	printInfo("Reading %s", image->fileName);
	
	// Start loading file
	start = clock();

	for (int i = 0; i < image->height; ++i)
	{
		for (int j = 0; j < image->width; ++j)
		{
			fscanf(f, "%d\n%d\n%d\n", &r, &g, &b);

			image->pixels[i][j].red			= (char)r;
			image->pixels[i][j].green		= (char)g;
			image->pixels[i][j].blue		= (char)b;
			image->pixels[i][j].analysed	= 0;
		}
	}
	
	end = clock();

	// Ended loading file
	printInfo("%s read in %f seconds", image->fileName, executionTime(start, end));

	return image;
}