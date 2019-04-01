#include "main.h"

int main(int argc, char *argv[])
{
	if (argc != 8 || !strcmp(argv[1], "tests"))
	{
		printUsageMessage(argv[0]);

		return 0;
	}

	FILE *inputFile = fopen(argv[2], FM_R);

	if (inputFile == NULL)
	{
		// TODO: Error message

		return 0;
	}
}