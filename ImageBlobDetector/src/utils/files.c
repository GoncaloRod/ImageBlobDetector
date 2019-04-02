#include "files.h"

Image *readImageDefaultFormat(FILE *f)
{
	if (!f) return NULL;

	// Check if file is not empty
	fseek(f, SEEK_END, 0);

	long fEnd = ftell(f);

	fseek(f, SEEK_SET, 0);

	if (ftell(f) == fEnd) return NULL;

	clock_t start, end;

	Image *image;
	char fileName[20];
	int height, width, channels;
	Pixel **pixels;

	int r, g, b;

	fscanf(f, "%s\n", fileName);
	fscanf(f, "%d %d %d", &height, &width, &channels);

	pixels = (Pixel **)malloc(height * sizeof(Pixel *));
	
	for (size_t i = 0; i < height; ++i)
	{
		pixels[i] = (Pixel *)malloc(width * sizeof(Pixel));
	}

	printInfo("Reading %s", fileName);

	start = clock();

	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			if (ftell(f) == fEnd)
			{
				printError("Missing pixel in %s", fileName);

				free(pixels);

				return;
			}

			fscanf(f, "%d\n%d\n%d\n", &r, &g, &b);

			if (!inRange(0, 255, r) || !inRange(0, 255, g) || !inRange(0, 255, b))
			{
				printError("Pixel value not in range of 0 to 255 in %s", fileName);

				free(pixels);

				return;
			}

			pixels[i][j].red		= (char)r;
			pixels[i][j].green		= (char)g;
			pixels[i][j].blue		= (char)b;
			pixels[i][j].analized	= 0;
		}
	}

	end = clock();

	printInfo("%s readed in %f seconds", executionTime(start, end));

	image = createImage();

	strcpy(image->fileName, fileName);
	
	image->width = width;
	image->height = height;
	image->channels = channels;

	image->pixels = pixels;

	return image;
}