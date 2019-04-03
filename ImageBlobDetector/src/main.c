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
	_CrtSetBreakAlloc(75);
#endif

	FILE *inputFile;
	Image *image;
	unsigned char red, green, blue, tolerance;
	char mode[5];

	if (!validateArguments(argc, argv, &inputFile, &red, &green, &blue, &tolerance, mode))
	{
		printUsageMessage(argv[0]);
		return 0;
	}

	image = readImageDefaultFormat(inputFile);

	freeImage(image);

	fclose(inputFile);

	getchar();

	_CrtDumpMemoryLeaks();
}