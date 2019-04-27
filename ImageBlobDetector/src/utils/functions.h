#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../structs.h"
#include "utils.h"
#include "files.h"

void printUsageMessage(char *programName);

int validateArguments(int argc, char **argv, char *fileName, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *t, char *mode);

Pixel *getPixelFromCoord(Image *image, int x, int y);

void printImageInformation(Image* image);

#endif