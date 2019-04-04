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

int validateArguments(int argc, char **argv,char *fileName, unsigned char *r, unsigned char *g,
					  unsigned char *b, unsigned char *t, char *mode)
{
	// Validate arguments count
	if (argc != 8) return 0;

	// Validate required 'tests' flag (doesn't really do anything but it's required by teacher)
	if (strcmp(argv[1], "tests") != 0)
		return 0;

	// Validate input file
	if (argv[2][0] == '\0')
		return 0;

	// Validate red, green, blue and tolerance values are numeric
	if (!isNumeric(argv[3]) || !isNumeric(argv[4]) || !isNumeric(argv[5]) ||
		!isNumeric(argv[6]))
	{
		return 0;
	}

	// Validate red, green, blue and tolerance values are in range of 0 to 255
	if (!inRange(0, 255, stringToInt(argv[3])) || !inRange(0, 255, stringToInt(argv[4])) ||
		!inRange(0, 255, stringToInt(argv[5])) || !inRange(0, 255, stringToInt(argv[6])))
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

Image *createImage()
{
	Image *i = (Image *)malloc(sizeof(Image));

	strcpy(i->fileName, "");
	i->width = 0;
	i->height = 0;
	i->pixels = NULL;

	return i;
}

Pixel **createPixelsMatrix(int height, int width)
{
	Pixel **pixels = (Pixel **)malloc(height * sizeof(Pixel *));

	for (int i = 0; i < height; ++i)
	{
		pixels[i] = (Pixel *)malloc(width * sizeof(Pixel));
	}

	return pixels;
}

void freePixelMatrix(Pixel **matrix, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		free(matrix[i]);
	}
	
	free(matrix);
}

void freeImage(Image *image)
{
	if (!image) return;

	// Free pixels matrix
	if (image->pixels)
		freePixelMatrix(image->pixels, image->height, image->width);
	
	// Free image structure
	free(image);
}