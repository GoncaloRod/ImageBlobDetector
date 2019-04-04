#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../strucs.h"
#include "utils.h"
#include "files.h"

void printUsageMessage(char *programName);

int validateArguments(int argc, char **argv, char *fileName, unsigned char *r, unsigned char *g,
					  unsigned char *b, unsigned char *t, char *mode);

Image *createImage();

Pixel **createPixelsMatrix(int heigth, int width);

void freePixelMatrix(Pixel **matrix, int height, int width);

void freeImage(Image *image);

#endif