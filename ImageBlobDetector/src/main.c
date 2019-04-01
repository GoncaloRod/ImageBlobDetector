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
	_CrtSetBreakAlloc(96);
#endif

	FILE *inputFile;
	unsigned char red, green, blue, tolerance;
	char *mode;

	if (!validateArguments(argc, argv, &inputFile, &red, &green, &blue, &tolerance, &mode))
		return 0;

	fclose(inputFile);

	_CrtDumpMemoryLeaks();
}