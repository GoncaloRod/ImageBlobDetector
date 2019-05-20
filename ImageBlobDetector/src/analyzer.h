#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "utils/functions.h"
#include "utils/utils.h"

void AnalyzeImage(Image* pImage, unsigned char r, unsigned char g, unsigned char b, unsigned char t, int minimum);

void FindBlob(Image *pImage, Blob *pBlob, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

void AddNeighbors(Image *pImage, Vector2IQueue *pDestination, Vector2I coord);

int PixelInRange(Pixel *pPixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

#endif