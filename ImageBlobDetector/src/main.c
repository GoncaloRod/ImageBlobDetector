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
	char FileName[50];
	unsigned char Red, Green, Blue, Tolerance;
	char Mode[5];
	unsigned char MemTest;

	if (!validateArguments(argc, argv, FileName, &Red, &Green, &Blue, &Tolerance, Mode))
	{
		printUsageMessage(argv[0]);
		return 0;
	}

	// If mode is in 'MEM' mode the program should run in infinite mode to test memory
	MemTest = strcmp(Mode, "MEM") == 0;

	do
	{
		pInputFile = fopen(FileName, FM_R);

		if (!pInputFile)
		{
			printError("File %s doesn't exist", FileName);
			return 0;
		}

		pImages = createImageList();

		while (!feof(pInputFile))
		{
			// Read image from file to memory
			pImage = readImageDefaultFormat(pInputFile);

			// Analyze image
			analyzeImage(pImage, Red, Green, Blue, Tolerance);

			// Show all blobs found
			printImageInformation(pImage);

			// Free pixel matrix from image
			freePixelMatrix(pImage->pixels);
			pImage->pixels = NULL;

			// Add image to images list
			imageListAddEnd(pImages, pImage);
		}

		// Find image with more blobs
		pImage = getImageWithMoreBlobs(pImages);
		
		if (pImage)
			printInfo("Image with more blobs: %s with %d blobs", pImage->fileName, pImage->blobs->count);
		
		// Find image with less std. deviation
		pImage = getImageWithMoreBlobs(pImages);
		
		if (pImage)
			printInfo("Image with less std. deviation: %s | (%d, %d) | (%f, %f, %f)", pImage->fileName, pImage->minStdDeviationCenter.x, pImage->minStdDeviationCenter.y, pImage->minStdDeviation.x, pImage->minStdDeviation.y, pImage->minStdDeviation.z);

		// Free all images
		freeImageList(pImages);

		// Close input file
		fclose(pInputFile);
	} while (MemTest);

	getchar();

	_CrtDumpMemoryLeaks();
}