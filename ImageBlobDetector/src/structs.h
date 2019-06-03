/**
 * @file structs.h
 *
 * @brief Contains structs and functions to handle them.
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#define _CRT_SECURE_NO_WARNINGS
#define IMAGE_NAME_SIZE 50

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils/utils.h"

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

/**
 * @brief Allocates a pixel matrix.
 *
 * @param height Height of the matrix.
 * @param width Width of the matrix.
 *
 * @return Pointer to the allocated pixel matrix.
 */
Pixel* CreatePixelMatrix(int heigth, int width);

/**
 * @brief Free a previously allocated pixel matrix.
 *
 * @param matrix Pointer to the pixel matrix to free.
 */
void FreePixelMatrix(Pixel* matrix);

#pragma endregion Pixel

#pragma region Image

/**
 * @brief Allocates an image.
 *
 * @return Pointer to the allocated image.
 */
Image* CreateImage();

/**
 * @brief Free a previously allocated image.
 *
 * @param pImage Pointer to the image to free.
 */
void FreeImage(Image* pImage);

#pragma endregion Image

#pragma region ImageNode

/**
 * @brief Allocates an image node.
 *
 * @return Pointer to the allocated image node.
 */
ImageNode* CreateImageNode();

/**
 * @brief Free a previously allocated image node.
 *
 * @param pImage Pointer to the image node to free.
 */
void FreeImageNode(ImageNode* pNode);

#pragma endregion ImageNode

#pragma region ImageList

/**
 * @brief Allocates an image list.
 *
 * @return Pointer to the allocated image list.
 */
ImageList* CreateImageList();

/**
 * @brief Free a previously allocated image list.
 *
 * @return Pointer to the image list to free.
 */
void FreeImageList(ImageList* pList);

/**
 * @brief Adds an image to the head of the list.
 *
 * @param pList Pointer to the list to add the image.
 * @param pImage Pointer to the image to add to the list.
 */
void ImageListAddHead(ImageList* pList, Image* pImage);

/**
 * @brief Adds an image to the tail of the list.
 *
 * @param pList Pointer to the list to add the image.
 * @param pImage Pointer to the image to add to the list.
 */
void pImageListAddTail(ImageList* pList, Image* pImage);

#pragma endregion ImageList

#pragma region Vector2I

/**
 * @brief Allocate a 2 dimensional vector of integers.
 *
 * @param x X value of the vector.
 * @param y Y value of the vector.
 *
 * @return Pointer to the allocated vector.
 */
Vector2I* CreateVector2I(int x, int y);

/**
 * @brief Free a previously allocated vector.
 *
 * @param pVector Pointer to the vector to free.
 */
void FreeVector2I(Vector2I* pVector);

#pragma endregion Vector2I

#pragma region Vector2INode

/**
 * @brief Allocate an 2 dimensional vector of integers node.
 *
 * @return Pointer to the allocated vector node.
 */
Vector2INode* CreateVector2INode();

/**
 * @brief Free a previously allocated vector node.
 *
 * @param pVector Pointer to the vector node to free.
 */
void FreeVector2INode(Vector2INode* pNode);

#pragma endregion Vector2INode

#pragma region Vector2IQueue

/**
 * @brief Allocate a Vector2I queue.
 *
 * @return Pointer to the allocated Vector2I queue.
 */
Vector2IQueue* CreateVector2IQueue();

/**
 * @brief Free a previously allocated Vector2I queue.
 *
 * @param pQueue Pointer to the Vector2I queue to free.
 */
void FreeVector2IQueue(Vector2IQueue* pQueue);

/**
 * @brief Add a Vector2I to the queue.
 *
 * @param pQueue Pointer to the queue to add the Vector2I.
 * @param pCoord Pointer to the Vector2I to add to the Queue.
 */
void Vector2IEnqueue(Vector2IQueue* pQueue, Vector2I* pVector);

/**
 * @brief Get a Vector2I from the queue.
 *
 * @param pQueue Pointer to the queue to get a vector.
 *
 * @return Pointer to the vector extracted from the queue.
 */
Vector2I* Vector2IDequeue(Vector2IQueue* pQueue);

#pragma endregion Vector2IQueue

#pragma region Blob

/**
 * @brief Allocates a blob.
 * 
 * @return Pointer to the allocated blob.
 */
Blob* CreateBlob();

/**
 * @brief Free a previously allocated blob.
 *
 * @param pBlob Pointer to the blob to free.
 */
void FreeBloob(Blob* pBlob);

/**
 * @brief Adds a coordinate to the head of the blob.
 *
 * @param pBlob Pointer to the blob to add the coordinate.
 * @param pCoord Pointer to the coordinate to add to the blob.
 */
void BlobAddHead(Blob* pBlob, Vector2I* pCoord);

/**
 * @brief Adds a coordinate to the tail of the blob.
 *
 * @param pBlob Pointer to the blob to add the coordinate.
 * @param pCoord Pointer to the coordinate to add to the blob.
 */
void BlobAddTail(Blob* pBlob, Vector2I* pCoord);

/**
 * @brief Calculate the center of a blob.
 *
 * @param pBlob Pointer to the blob to calculate the center.
 *
 * @return 2 dimensional vector of integers with the center coordinates.
 */
Vector2I GetBlobCenter(Blob* pBlob);

/**
 * @brief Calculates blob's standard deviation.
 *
 * @param pBlob Pointer to the blob to calculate standard deviation.
 * @param pImage Pointer to the blob's image.
 *
 * @param 3 dimensional vector of floats with standard deviation value.
 */
Vector3F GetBlobStdDeviation(Blob* pBlob, Image* pImage);

#pragma endregion Blob

#pragma region BlobNode

/**
 * @brief Allocates a blob node.
 *
 * @return Pointer to the allocated blob node.
 */
BlobNode* CreateBlobNode();

/**
 * @brief Free a previously allocated blob node.
 *
 * @param pNode Pointer to the blob node to free.
 */
void FreeBlobNode(BlobNode* pNode);

#pragma endregion BlobNode

#pragma region BlobList

/**
 * @brief Allocates a blob list.
 *
 * @return Pointer to the allocated blob list.
 */
BlobList* CreateBlobList();

/**
 * @brief Free a previously allocated  blob list.
 *
 * @param pList Pointer to the blob list to free.
 */
void FreeBlobList(BlobList* pList);

/**
 * @brief Adds a blob to the head of the list.
 *
 * @param pList Pointer to the list to add the blob.
 * @param pBlob Pointer to the blob to add to the list.
 */
void BlobListAddHead(BlobList* pList, Blob* pBlob);

/**
 * @brief Adds a blob to the tail of the list.
 *
 * @param pList Pointer to the list to add the blob.
 * @param pBlob Pointer to the blob to add to the list.
 */
void BlobListAddTail(BlobList* pList, Blob* pBlob);

/**
 * @brief Adds a blob to the list with sorting.
 *
 * @param pList Pointer to the list to add the blob.
 * @param pBlob Pointer to the blob to add to the list.
 */
void BlobListAddSorted(BlobList* pList, Blob* pBlob);

#pragma endregion BlobList

#pragma endregion

#endif