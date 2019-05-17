#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "../structs.h"
#include "utils.h"
#include "files.h"

void PrintUsageMessage(char *pProgramName);

int ValidateArguments(int argc, char **argv, char *pFileName, unsigned char *pR, unsigned char *pG, unsigned char *pB, unsigned char *pT, char *pMode);

Pixel* GetPixelFromVector2I(Image *pImage, int X, int Y);

void PrintImageInformation(Image* pImage);

Image* GetImageMoreBlobs(ImageList* pImages);

int CompareStdDeviation(Vector3F value1, Vector3F value2);

#endif