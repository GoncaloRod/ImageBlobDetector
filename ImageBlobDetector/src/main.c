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
#if 0
	// Find memory leak, set to 1 to use
	_CrtSetBreakAlloc(99);
#endif

	FILE* pInputFile;
	ImageList* pImages;
	Image* pImage;
	char fileName[50];
	unsigned char red, green, blue, tolerance;
	char mode[5];
	int memTest;

	if (!ValidateArguments(argc, argv, fileName, &red, &green, &blue, &tolerance, mode))
	{
		PrintUsageMessage(argv[0]);
		return 0;
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
			AnalyzeImage(pImage, red, green, blue, tolerance);

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

	getchar();

	_CrtDumpMemoryLeaks();
}