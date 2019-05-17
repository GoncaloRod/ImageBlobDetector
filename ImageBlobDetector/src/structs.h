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
	struct _vector2INode* pNext;
	Vector2I* pData;
} Vector2INode;

typedef struct _vector2IQueue
{
	Vector2INode* pHead, * pTail;
	int count;
} Vector2IQueue;

typedef struct _blob
{
	Vector2INode* pHead, * pTail;
	int count;
} Blob;

typedef struct _blobNode
{
	struct _blobNode* pNext;
	Blob* pData;
} BlobNode;

typedef struct _blobList
{
	BlobNode* pHead, * pTail;
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
	Pixel* pPixels;
	BlobList* pBlobs;
	Vector3F minStdDeviation;
	Vector2I minStdDeviationCenter;
} Image;

typedef struct _imageNode
{
	struct _imageNode* pNext;
	Image* pData;
} ImageNode;

typedef struct _imageList
{
	ImageNode* pHead, * pTail;
	int count;
} ImageList;

#pragma endregion

#pragma region Functions

#pragma region Pixel

Pixel* CreatePixelMatrix(int heigth, int width);

void FreePixelMatrix(Pixel* matrix);

#pragma endregion Pixel

#pragma region Image

Image* CreateImage();

void FreeImage(Image* pImage);

#pragma endregion Image

#pragma region ImageNode

ImageNode* CreateImageNode();

void FreeImageNode(ImageNode* pNode);

#pragma endregion ImageNode

#pragma region ImageList

ImageList* CreateImageList();

void FreeImageList(ImageList* pList);

void ImageListAddStart(ImageList* pList, Image* pImage);

void pImageListAddEnd(ImageList* pList, Image* pImage);

#pragma endregion ImageList

#pragma region Vector2I

Vector2I* CreateVector2I(int x, int y);

void FreeVector2I(Vector2I* pVector);

#pragma endregion Vector2I

#pragma region Vector2INode

Vector2INode* CreateVector2INode();

void FreeVector2INode(Vector2INode* pNode);

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