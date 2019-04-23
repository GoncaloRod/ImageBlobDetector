#include "main.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main(int argc, char *argv[])
{
#if 0

	// Find memory leak, set to 1 to use
	_CrtSetBreakAlloc(99);
#endif

	FILE *inputFile;
	Image *image;
	BlobList *blobs;
	clock_t analyzeStart, analyzeEnd;
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
		
		while (!feof(inputFile))
		{
			blobs = createBlobList();

			image = readImageDefaultFormat(inputFile);

			printInfo("Analyzing %s", image->fileName);

			analyzeStart = clock();

			analyseImage(image, blobs, red, green, blue, tolerance);

			analyzeEnd = clock();

			printInfo("%s analyzed in %f seconds", image->fileName, executionTime(analyzeStart, analyzeEnd));

			printBlobList(blobs);

			freeImage(image);

			freeBlobList(blobs);
		}

		fclose(inputFile);
	} while (memTest);

	getchar();
	
	_CrtDumpMemoryLeaks();
}