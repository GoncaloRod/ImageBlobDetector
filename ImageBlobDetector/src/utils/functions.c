#include "functions.h"

void printUsageMessage(char *programName)
{
	printf("\nUsage: %s tests input_file red green blue tolerance mode\n\n", programName);

	// TODO: Fix indentation
	printf("  input_file: File to be precessed\n");
	printf("  red: Desired red value of color to find\n");
	printf("  green: Desired green value of color to find\n");
	printf("  blue: Desired blue value of color to find\n");
	printf("  tolerance: Tolerance in red, green and blue values to find\n");
	printf("  mode: Mode in which program will execute. Can be menu, all or mem\n");
}

void printError(char *message)
{
	printf("ERROR: %s\n\n", message);
}

bool isNumeric(char *num)
{
	bool numeric = true;

	for (size_t i = 0; i < strlen(num) && numeric; ++i)
		if (num[i] < '0' || num[i] > '9')
			numeric = false;

	return numeric;
}

int stringToInt(char *num)
{
	int value = 0;

	for (size_t i = 0; i < strlen(num); ++i)
	{
		value *= 10;
		value += num[i] - '0';
	}

	return value;
}

bool inRange(int min, int max, int value)
{
	return value >= min && value <= max;
}

int validateArguments(int argc, char **argv,  FILE **inputFile, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *t, char **mode)
{
	if (argc != 8 || strcmp(argv[1], "tests") != 0)
	{
		printUsageMessage(argv[0]);
		return 0;
	}

	*inputFile = fopen(argv[2], FM_R);

	if (inputFile == NULL)
	{
		printError("Failed to open input file");
		return 0;
	}

	if (!isNumeric(argv[3]) || !isNumeric(argv[4]) || !isNumeric(argv[5]) || !isNumeric(argv[6]))
	{
		printError("Red, Green, Blue and Tolerance must be numeric");
		return 0;
	}

	if (!inRange(0, 255, stringToInt(argv[3])) || !inRange(0, 255, stringToInt(argv[4])) || !inRange(0, 255, stringToInt(argv[5])) || !inRange(0, 255, stringToInt(argv[6])))
	{
		printError("Red, Green, Blue and Tolerance values must be in range from 0 to 255");
		return 0;
	}

	*r = (unsigned char)stringToInt(argv[3]);
	*g = (unsigned char)stringToInt(argv[4]);
	*b = (unsigned char)stringToInt(argv[5]);
	*t = (unsigned char)stringToInt(argv[6]);

	if (strcmp(argv[7], "MENUS") != 0 || strcmp(argv[7], "ALL") != 0 || strcmp(argv[7], "MEM") != 0)
	{
		printUsageMessage(argv[0]);
		return 0;
	}

	strcpy(mode, argv[7]);

	return 1;
}
