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

#pragma region Pixel

Pixel *createPixelMatrix(int heigth, int width);

void freePixelMatrix(Pixel* matrix);

#pragma endregion Pixel

#pragma region Image

Image *createImage();

void freeImage(Image* image);

#pragma endregion Image

#pragma region Coord

Coord *createCoord(int x, int y);

void freeCoord(Coord *coord);

#pragma endregion Coord

#pragma region CoordNode

CoordNode *createCoordNode();

void freeCoordNode(CoordNode *node);

#pragma endregion CoordNode

#pragma region CoordQueue

CoordQueue *createCoordQueue();

void freeCoordQueue(CoordQueue *queue);

void coordEnqueue(CoordQueue *queue, Coord* coord);

Coord *coordDequeue(CoordQueue *queue);

#pragma endregion CoordQueue

#pragma region Blob

Blob *createBlob();

void freeBloob(Blob *blob);

void blobAddStart(Blob *blob, Coord *coord);

void blobAddEnd(Blob *blob, Coord *coord);

#pragma endregion Blob

#pragma region BlobNode

BlobNode *createBlobNode();

void freeBlobNode(BlobNode *node);

#pragma endregion BlobNode

#pragma region BlobList

BlobList *createBlobList();

void freeBlobList(BlobList *list);

void blobListAddStart(BlobList *list, Blob *blob);

void blobListAddEnd(BlobList *list, Blob *blob);

void blobListAddSorted(BlobList *list, Blob *blob);

void printBlobList(BlobList *list);

#pragma endregion BlobList

#pragma endregion

#endif