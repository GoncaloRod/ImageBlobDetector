#include "files.h"

Image *readImageDefaultFormat(FILE *f)
{
	if (!f) return NULL;
	if (endOfFile(f)) return NULL;

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

			if (!inRange(0, 255, r) || !inRange(0, 255, g) || !inRange(0, 255, b))
			{
				printError("Pixel value not in range of 0 to 255 in %s", image->fileName);

				freeImage(image);

				return NULL;
			}

			image->pixels[i][j].red			= (char)r;
			image->pixels[i][j].green		= (char)g;
			image->pixels[i][j].blue		= (char)b;
			image->pixels[i][j].analysed	= 0;
		}
	}
	
	end = clock();

	// Ended loading file
	printInfo("%s readed in %f seconds", image->fileName, executionTime(start, end));

	return image;
}