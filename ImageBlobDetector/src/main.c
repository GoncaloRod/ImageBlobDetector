#include "main.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main(int argc, char* argv[])
{
#ifdef _DEBUG
#if 0
	// Find memory leak, set to 1 to use
	_CrtSetBreakAlloc(99);
#endif
#endif

	FILE* pInputFile;
	ImageList* pImages;
	Image* pImage;
	char fileName[50];
	unsigned char red, green, blue, tolerance;
	char mode[5];
	int minimimPixelCount = MINIMUM_PIXEL_COUNT;
	int memTest;

	// Required arguments
	if (!ValidateArguments(argc, argv, fileName, &red, &green, &blue, &tolerance, mode))
	{
		PrintUsageMessage(argv[0]);
		return 0;
	}

	// Options
	for (int i = 8; i < argc; ++i)
	{
		if (strcmp(argv[i], "-m") == 0)
		{
			if (argc < i + 2)
			{
				PrintUsageMessage(argv[0]);
				exit(EXIT_FAILURE);
			}

			if (!IsNumeric(argv[i + 1]))
			{
				PrintUsageMessage(argv[0]);
				exit(EXIT_FAILURE);
			}

			minimimPixelCount = atoi(argv[i + 1]);
			++i;

			if (minimimPixelCount <= 0)
			{
				PrintUsageMessage(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			PrintUsageMessage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	// If mode is in 'MEM' mode the program should run in infinite mode to test memory
	memTest = strcmp(mode, "MEM") == 0;

	do
	{
		pInputFile = fopen(fileName, FM_R);

		if (!pInputFile)
		{
			PrintError("File %s doesn't exist", fileName);
			return 0;
		}

		pImages = CreateImageList();

		while (!feof(pInputFile))
		{
			// Read image from file to memory
			pImage = ReadImageDefaultFormat(pInputFile);

			// Analyze image
			AnalyzeImage(pImage, red, green, blue, tolerance, minimimPixelCount);

			// Show all blobs found
			PrintImageInformation(pImage);

			// Free pixel matrix from image
			FreePixelMatrix(pImage->pPixels);
			pImage->pPixels = NULL;

			// Add image to images list
			pImageListAddEnd(pImages, pImage);
		}

		// Find image with more blobs
		pImage = GetImageMoreBlobs(pImages);
		
		if (pImage)
			PrintInfo("Image with more blobs: %s with %d blobs", pImage->fileName, pImage->pBlobs->count);
		
		// Find image with less std. deviation
		pImage = GetImageMoreBlobs(pImages);
		
		if (pImage)
			PrintInfo("Image with less std. deviation: %s | (%d, %d) | (%f, %f, %f)", pImage->fileName, pImage->minStdDeviationCenter.x, pImage->minStdDeviationCenter.y, pImage->minStdDeviation.x, pImage->minStdDeviation.y, pImage->minStdDeviation.z);

		// Free all images
		FreeImageList(pImages);

		// Close input file
		fclose(pInputFile);
	} while (memTest);

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}