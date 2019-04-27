#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "structs.h"
#include "utils/functions.h"
#include "utils/utils.h"

void analyzeImage(Image* image, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

void findBlob(Image *image, Blob *blob, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

void addNeighbors(Image *image, CoordQueue *destination, Coord coord);

int pixelInRange(Pixel *pixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

#endif