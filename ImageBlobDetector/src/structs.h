#ifndef STRUCTS_H_
#define STRUCTS_H_

#define _CRT_SECURE_NO_WARNINGS
#define IMAGE_NAME_SIZE 50

#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma region Structs

typedef struct _vector3F
{
	float x, y, z;
} Vector3F;

typedef struct _vector2I
{
	int x, y;
} Vector2I;

typedef struct _vector2INode
{
	struct _vector2INode* next;
	Vector2I* data;
} Vector2INode;

typedef struct _vector2IQueue
{
	Vector2INode* first, * last;
	int count;
} Vector2IQueue;

typedef struct _blob
{
	Vector2INode* first, * last;
	Vector3F minStdDeviation;
	Vector2I minStdDeviationCenter;
	int count;
} Blob;

typedef struct _blobNode
{
	struct _blobNode* next;
	Blob* data;
} BlobNode;

typedef struct _blobList
{
	BlobNode* first, * last;
	int count;
} BlobList;

typedef struct _pixel
{
	unsigned char red, green, blue, analysed;
} Pixel;

typedef struct _image
{
	char fileName[IMAGE_NAME_SIZE];
	int width, height, channels;
	Pixel* pixels;
	BlobList* blobs;
} Image;

typedef struct _imageNode
{
	struct _imageNode* next;
	Image* data;
} ImageNode;

typedef struct _imageList
{
	ImageNode* first, * last;
	int count;
} ImageList;

#pragma endregion

#pragma region Functions

#pragma region Pixel

Pixel* createPixelMatrix(int heigth, int width);

void freePixelMatrix(Pixel* matrix);

#pragma endregion Pixel

#pragma region Image

Image* createImage();

void freeImage(Image* image);

#pragma endregion Image

#pragma region ImageNode

ImageNode* createImageNode();

void freeImageNode(ImageNode* node);

#pragma endregion ImageNode

#pragma region ImageList

ImageList* createImageList();

void freeImageList(ImageList* list);

void imageListAddStart(ImageList* list, Image* image);

void imageListAddEnd(ImageList* list, Image* image);

#pragma endregion ImageList

#pragma region Vector2I

Vector2I* createVector2I(int x, int y);

void freeVector2I(Vector2I* vector);

#pragma endregion Vector2I

#pragma region Vector2INode

Vector2INode* createVector2INode();

void freeVector2INode(Vector2INode* node);

#pragma endregion Vector2INode

#pragma region Vector2IQueue

Vector2IQueue* createVector2IQueue();

void freeVector2IQueue(Vector2IQueue* queue);

void vector2IEnqueue(Vector2IQueue* queue, Vector2I* coord);

Vector2I* vector2IDequeue(Vector2IQueue* queue);

#pragma endregion Vector2IQueue

#pragma region Blob

Blob* createBlob();

void freeBloob(Blob* blob);

void blobAddStart(Blob* blob, Vector2I* coord);

void blobAddEnd(Blob* blob, Vector2I* coord);

Vector2I getBlobCenter(Blob* blob);

Vector3F getBlobStdDeviation(Blob* blob, Image* image);

#pragma endregion Blob

#pragma region BlobNode

BlobNode* createBlobNode();

void freeBlobNode(BlobNode* node);

#pragma endregion BlobNode

#pragma region BlobList

BlobList* createBlobList();

void freeBlobList(BlobList* list);

void blobListAddStart(BlobList* list, Blob* blob);

void blobListAddEnd(BlobList* list, Blob* blob);

void blobListAddSorted(BlobList* list, Blob* blob);

#pragma endregion BlobList

#pragma endregion

#endif