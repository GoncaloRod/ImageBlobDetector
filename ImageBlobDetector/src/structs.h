#ifndef STRUCTS_H_
#define STRUCTS_H_

#define _CRT_SECURE_NO_WARNINGS
#define IMAGE_NAME_SIZE 50

#include <stdlib.h>
#include <string.h>

#pragma region Structs

typedef struct _pixel
{
	unsigned char red, green, blue, analysed;
} Pixel;

typedef struct _image
{
	char fileName[IMAGE_NAME_SIZE];
	int width, height, channels;
	Pixel *pixels;
} Image;

typedef struct _coord
{
	int x, y;
} Coord;

typedef struct _coordNode
{
	struct _coordNode *next;
	Coord *data;
} CoordNode;

typedef struct _coordQueue
{
	CoordNode *first, *last;
	int count;
} CoordQueue;

typedef struct _blob
{
	CoordNode *first, *last;
	int count;
} Blob;

typedef struct _blobNode
{
	struct _blobNode *next;
	Blob *data;
} BlobNode;

typedef struct _blobList
{
	BlobNode *first, *last;
	int count;
} BlobList;

#pragma endregion

#pragma region Functions

// Images
Image *createImage();

void freeImage(Image *image);

// Coords
Coord *createCoord(int x, int y);

void freeCoord(Coord *coord);

// Coord Nodes
CoordNode *createCoordNode();

void freeCoordNode(CoordNode *node);

// Coord Queue
CoordQueue *createCoordQueue();

void freeCoordQueue(CoordQueue *queue);

void coordEnqueue(CoordQueue *queue, Coord* coord);

Coord *coordDequeue(CoordQueue *queue);

// Blobs
Blob *createBlob();

void freeBloob(Blob *blob);

void blobAddStart(Blob *blob, Coord *coord);

void blobAddEnd(Blob *blob, Coord *coord);

// Blob Nodes
BlobNode *createBlobNode();

void freeBlobNode(BlobNode *node);

// Blob Lists
BlobList *createBlobList();

void freeBlobList(BlobList *list);

#pragma endregion

#endif