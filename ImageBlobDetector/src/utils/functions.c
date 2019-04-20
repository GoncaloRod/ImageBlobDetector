#include "functions.h"

void printUsageMessage(char *programName)
{
	printf("\nUsage: %s tests input_file red green blue tolerance mode\n\n", programName);
	
	// TODO: Better formating
	printf("\tinput_file:\t\tFile to be precessed\n");
	printf("\tred:\t\t\tDesired red value of color to find\n");
	printf("\tgreen:\t\t\tDesired green value of color to find\n");
	printf("\tblue:\t\t\tDesired blue value of color to find\n");
	printf("\ttolerance:\t\tTolerance in red, green and blue values to find\n");
	printf("\tmode:\t\t\tMode in which program will execute. Can be MENU, ALL or MEM\n");
}

int validateArguments(int argc, char **argv,char *fileName, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *t, char *mode)
{
	// Validate arguments count
	if (argc != 8) return 0;

	// Validate required 'tests' flag (doesn't really do anything but it's required by teacher)
	if (strcmp(argv[1], "tests") != 0)
		return 0;

	// Validate input file
	if (argv[2][0] == '\0')
		return 0;

	strcpy(fileName, argv[2]);

	// Validate red, green, blue and tolerance values are numeric
	if (!isNumeric(argv[3]) || !isNumeric(argv[4]) || !isNumeric(argv[5]) || !isNumeric(argv[6]))
	{
		return 0;
	}

	// Validate red, green, blue and tolerance values are in range of 0 to 255
	if (!inRange(0, 255, stringToInt(argv[3])) || !inRange(0, 255, stringToInt(argv[4])) || !inRange(0, 255, stringToInt(argv[5])) || !inRange(0, 255, stringToInt(argv[6])))
	{
		return 0;
	}

	*r = (unsigned char)stringToInt(argv[3]);
	*g = (unsigned char)stringToInt(argv[4]);
	*b = (unsigned char)stringToInt(argv[5]);
	*t = (unsigned char)stringToInt(argv[6]);
	
	// Validate mode
	if (strcmp(argv[7], "MENU") != 0 && strcmp(argv[7], "ALL") != 0 && strcmp(argv[7], "MEM") != 0)
	{
		printUsageMessage(argv[0]);
		return 0;
	}

	strcpy(mode, argv[7]);

	return 1;
}

Pixel *getPixelFromCoord(Image *image, int x, int y)
{
	return &image->pixels[(image->width * y) + x];
}