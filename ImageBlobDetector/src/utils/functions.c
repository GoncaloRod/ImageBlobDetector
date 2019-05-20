#include "functions.h"

void PrintUsageMessage(char *pProgramName)
{
	printf("\nUsage: %s tests input_file red green blue tolerance mode [-m count]\n\n", pProgramName);
	
	printf("    %-15sFile to be precessed\n", "input_file:");
	printf("    %-15sDesired red value of color to find\n", "red:");
	printf("    %-15sDesired green value of color to find\n", "green:");
	printf("    %-15sDesired blue value of color to find\n", "blue:");
	printf("    %-15sTolerance in red, green and blue values to find\n", "tolerance:");
	printf("    %-15sMode in which program will execute. Can be MENU, ALL or MEM\n", "mode:");

	printf("\nOptions:\n");
	printf("    %-15sMinimum number of pixels to be considered blob. Should be a number greater than 0\n", "-m count");
}

int ValidateArguments(int argc, char **argv,char *pFileName, unsigned char *pR, unsigned char *pG, unsigned char *pB, unsigned char *pT, char *pMode)
{
	// Validate arguments count
	if (argc < 8) return 0;

	// Validate required 'tests' flag (doesn't really do anything but it's required by teacher)
	if (strcmp(argv[1], "tests") != 0)
		return 0;

	// Validate input file
	if (argv[2][0] == '\0')
		return 0;

	strcpy(pFileName, argv[2]);

	// Validate red, green, blue and tolerance values are numeric
	if (!IsNumeric(argv[3]) || !IsNumeric(argv[4]) || !IsNumeric(argv[5]) || !IsNumeric(argv[6]))
	{
		return 0;
	}

	// Validate red, green, blue and tolerance values are in range of 0 to 255
	if (!InRange(0, 255, atoi(argv[3])) || !InRange(0, 255, atoi(argv[4])) || !InRange(0, 255, atoi(argv[5])) || !InRange(0, 255, atoi(argv[6])))
	{
		return 0;
	}

	*pR = (unsigned char)atoi(argv[3]);
	*pG = (unsigned char)atoi(argv[4]);
	*pB = (unsigned char)atoi(argv[5]);
	*pT = (unsigned char)atoi(argv[6]);
	
	// Validate mode
	if (strcmp(argv[7], "MENU") != 0 && strcmp(argv[7], "ALL") != 0 && strcmp(argv[7], "MEM") != 0)
	{
		PrintUsageMessage(argv[0]);
		return 0;
	}

	strcpy(pMode, argv[7]);

	return 1;
}

Pixel* GetPixelFromVector2I(Image *pImage, int x, int y)
{
	return &pImage->pPixels[(pImage->width * y) + x];
}

void PrintImageInformation(Image* pImage)
{
	if (!pImage->pBlobs) return;
	if (!pImage->pBlobs->pHead) return;

	Vector2I center;
	Vector3F stdDeviation;

	// Print image's blob count
	PrintInfo("%d blobs found in %s", pImage->pBlobs->count, pImage->fileName);

	pImage->minStdDeviationCenter = GetBlobCenter(pImage->pBlobs->pHead->pData);
	pImage->minStdDeviation = GetBlobStdDeviation(pImage->pBlobs->pHead->pData, pImage);

	// Print center, pixel count and std.deviation for every pixel
	for (BlobNode* pNode = pImage->pBlobs->pHead; pNode; pNode = pNode->pNext)
	{
		center = GetBlobCenter(pNode->pData);
		stdDeviation = GetBlobStdDeviation(pNode->pData, pImage);

		printf("(%d, %d) | %d pixels | Standard Deviation (%f, %f, %f)\n", center.x, center.y, pNode->pData->count, stdDeviation.x, stdDeviation.y, stdDeviation.z);

		// Update image's less std.deviation blob
		if (CompareStdDeviation(stdDeviation, pImage->minStdDeviation) < 0)
		{
			pImage->minStdDeviationCenter = center;
			pImage->minStdDeviation = stdDeviation;
		}
	}
}

Image* GetImageMoreBlobs(ImageList* pImages)
{
	if (!pImages) return NULL;
	if (!pImages->pHead) return NULL;

	ImageNode* pTopNode = pImages->pHead;

	for (ImageNode* pNode = pTopNode->pNext; pNode; pNode = pNode->pNext)
	{
		if (pNode->pData->pBlobs->count > pTopNode->pData->pBlobs->count)
		{
			pTopNode = pNode;
		}
	}

	return pTopNode->pData;
}

Image* GetImageLessStdDeviation(ImageList* pImages)
{
	if (!pImages) return NULL;
	if (!pImages->pHead) return NULL;

	ImageNode* pTopNode = pImages->pHead;

	for (ImageNode* pNode = pTopNode->pNext; pNode; pNode = pNode->pNext)
	{
		if (CompareStdDeviation(pNode->pData->minStdDeviation, pTopNode->pData->minStdDeviation) < 0)
		{
			pTopNode = pNode;
		}
	}

	return pTopNode->pData;
}

int CompareStdDeviation(Vector3F value1, Vector3F value2)
{
	float real1, real2;

	real1 = sqrt(pow(value1.x, 2) + pow(value1.y, 2) + pow(value1.z, 2));
	real2 = sqrt(pow(value2.x, 2) + pow(value2.y, 2) + pow(value2.z, 2));

	if (real1 > real2)
		return 1;
	else if (real1 < real2)
		return -1;
	else
		return 0;
}
