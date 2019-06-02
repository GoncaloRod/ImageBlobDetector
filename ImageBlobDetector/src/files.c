#include "files.h"

Image* ReadImageDefaultFormat(FILE* pFile)
{
	if (!pFile) return NULL;
	if (feof(pFile)) return NULL;

	Pixel* pPixelsMatrix;
	clock_t start, end;					// Used to measure file loading time
	Image* pImage = CreateImage();
	int red, green, blue;

	// Read filename, height, width and channels from file
	if (fscanf(pFile, "%s\n", pImage->fileName) != 1)
	{
		PrintError(FILE_INCORRECT_MESSAGE);
		exit(EXIT_FAILURE);
	}

	if (fscanf(pFile, "%d %d %d", &pImage->height, &pImage->width, &pImage->channels) != 3)
	{
		PrintError(FILE_INCORRECT_MESSAGE);
		exit(EXIT_FAILURE);
	}

	// Allocate pixels matrix
	pPixelsMatrix = pImage->pPixels = CreatePixelMatrix(pImage->height, pImage->width);

	PrintInfo("Reading %s", pImage->fileName);

	// Start loading file
	start = clock();

	for (int i = 0; i < pImage->height; ++i)
	{
		for (int j = 0; j < pImage->width; ++j, ++pPixelsMatrix)
		{
			if (fscanf(pFile, "%d\n%d\n%d\n", &red, &green, &blue) != 3)
			{
				PrintError(FILE_INCORRECT_MESSAGE);
				exit(EXIT_FAILURE);
			}

			pPixelsMatrix->red		= red;
			pPixelsMatrix->green	= green;
			pPixelsMatrix->blue		= blue;
			pPixelsMatrix->analysed = 0;
		}
	}

	end = clock();

	// Ended loading file
	PrintInfo("%s read in %f seconds", pImage->fileName, ExecutionTime(start, end));

	return pImage;
}