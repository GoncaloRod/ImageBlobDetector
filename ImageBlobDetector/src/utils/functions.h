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

Pixel *createPixelsMatrix(int heigth, int width);

// Coords
Coord *createCoord(int x, int y);
void freeCoord(Coord *coord);

// Blob Nodes
CoordNode *createCoordNode();
void freeCoordNode(CoordNode *node);

// Blobs
Blob *createBlob();
void freeBloob(Blob *blob);

// Blob Nodes
BlobNode *createBlobNode();
void freeBlobNode(BlobNode *node);

// Blob Lists
BlobList *createBlobList();
void freeBlobList(BlobList *list);

void freePixelMatrix(Pixel *matrix);

void freeImage(Image *image);

#endif