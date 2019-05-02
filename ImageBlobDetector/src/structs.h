#ifndef STRUCTS_H_
#define STRUCTS_H_

#define _CRT_SECURE_NO_WARNINGS
#define IMAGE_NAME_SIZE 50

#include <stdlib.h>
#include <string.h>

#pragma region Structs

typedef struct _vector2Int
{
	int x, y;
} Vector2Int;

typedef struct _vector2IntNode
{
	struct _vector2IntNode* next;
	Vector2Int* data;
} Vector2IntNode;

typedef struct _vector2IntQueue
{
	Vector2IntNode* first, * last;
	int count;
} Vector2IntQueue;

typedef struct _blob
{
	Vector2IntNode* first, * last;
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

#pragma region Vector2Int

Vector2Int* createVector2Int(int x, int y);

void freeVector2Int(Vector2Int* vector);

#pragma endregion Vector2Int

#pragma region Vector2IntNode

Vector2IntNode* createVector2IntNode();

void freeVector2IntNode(Vector2IntNode* node);

#pragma endregion Vector2IntNode

#pragma region Vector2IntQueue

Vector2IntQueue* createVector2IntQueue();

void freeVector2IntQueue(Vector2IntQueue* queue);

void vector2IntEnqueue(Vector2IntQueue* queue, Vector2Int* coord);

Vector2Int* vector2IntDequeue(Vector2IntQueue* queue);

#pragma endregion Vector2IntQueue

#pragma region Blob

Blob* createBlob();

void freeBloob(Blob* blob);

void blobAddStart(Blob* blob, Vector2Int* coord);

void blobAddEnd(Blob* blob, Vector2Int* coord);

Vector2Int getBlobCenter(Blob* blob);

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