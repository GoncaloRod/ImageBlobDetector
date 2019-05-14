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

Pixel * getPixelFromVector2I(Image *image, int x, int y)
{
	return &image->pixels[(image->width * y) + x];
}

void printImageInformation(Image* image)
{
	if (!image->blobs) return;
	if (!image->blobs->first) return;

	BlobNode* current;
	Vector2I center;
	Vector3F stdDeviation;

	printInfo("%d blobs found in %s", image->blobs->count, image->fileName);

	current = image->blobs->first;

	image->minStdDeviationCenter = getBlobCenter(current->data);
	image->minStdDeviation = getBlobStdDeviation(current->data, image);

	while (current)
	{
		center = getBlobCenter(current->data);
		stdDeviation = getBlobStdDeviation(current->data, image);

		printf("(%d, %d) | %d pixels | Standard Deviation (%f, %f, %f)\n", center.x, center.y, current->data->count, stdDeviation.x, stdDeviation.y, stdDeviation.z);

		if (compareBlobStdDeviation(stdDeviation, image->minStdDeviation) < 0)
		{
			image->minStdDeviationCenter = center;
			image->minStdDeviation = stdDeviation;
		}

		current = current->next;
	}
}

Image* getImageWithMoreBlobs(ImageList* images)
{
	if (!images) return NULL;
	if (!images->first) return NULL;

	ImageNode* topImage = images->first;

	for (ImageNode* node = images->first; node; node = node->next)
	{
		if (node->data->blobs->count > topImage->data->blobs->count)
		{
			topImage = node;
		}
	}

	return topImage->data;
}

int compareBlobStdDeviation(Vector3F value1, Vector3F value2)
{
	// TODO: Find a better way to compare std. deviation
	if (value1.x < value2.x && value1.y < value2.y && value1.z < value2.z)
		return -1;
	else if (value1.x > value2.x && value1.y > value2.y && value1.z > value2.z)
		return 1;
	else
		return 0;
}
