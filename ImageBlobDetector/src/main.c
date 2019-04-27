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

	FILE* inputFile;
	ImageList* images;
	Image* image;
	char fileName[50];
	unsigned char red, green, blue, tolerance;
	char mode[5];
	bool memTest;

	if (!validateArguments(argc, argv, fileName, &red, &green, &blue, &tolerance, mode))
	{
		printUsageMessage(argv[0]);
		return 0;
	}

	// If mode is in 'MEM' mode the program should run in infinite mode to test memory
	memTest = strcmp(mode, "MEM") == 0;

	do
	{
		inputFile = fopen(fileName, FM_R);

		if (!inputFile)
		{
			printError("File %s doesn't exist", fileName);
			return 0;
		}

		images = createImageList();

		while (!feof(inputFile))
		{
			// Read image from file to memory
			image = readImageDefaultFormat(inputFile);

			// Analyze image
			analyzeImage(image, red, green, blue, tolerance);

			// Show all blobs found
			printImageInformation(image);

			// Free pixel matrix from image
			freePixelMatrix(image->pixels);
			image->pixels = NULL;

			// Add image to images list
			imageListAddEnd(images, image);
		}

		// Free all images
		freeImageList(images);

		// Close input file
		fclose(inputFile);
	} while (memTest);

	getchar();

	_CrtDumpMemoryLeaks();
}