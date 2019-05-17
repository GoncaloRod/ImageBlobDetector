#include "structs.h"

#pragma region Pixel

Pixel* CreatePixelMatrix(int heigth, int width)
{
	Pixel* pPixels = (Pixel*)malloc(heigth * width * sizeof(Pixel));

	return pPixels;
}

void FreePixelMatrix(Pixel* pMatrix)
{
	free(pMatrix);
}

#pragma endregion Pixel

#pragma region Image

Image* CreateImage()
{
	Image* pImage = (Image*)malloc(sizeof(Image));

	if (!pImage)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	strcpy(pImage->fileName, "");
	pImage->width = 0;
	pImage->height = 0;
	pImage->pPixels = NULL;
	pImage->pBlobs = NULL;
	pImage->minStdDeviation.x = pImage->minStdDeviation.y = pImage->minStdDeviation.z = 0;
	pImage->minStdDeviationCenter.x = pImage->minStdDeviationCenter.y = 0;

	return pImage;
}

void FreeImage(Image* pImage)
{
	if (!pImage) return;

	if (pImage->pPixels) FreePixelMatrix(pImage->pPixels);
	if (pImage->pBlobs) freeBlobList(pImage->pBlobs);

	free(pImage);
}

#pragma endregion Image

#pragma region ImageNode

ImageNode* CreateImageNode()
{
	ImageNode* pNode = (ImageNode*)malloc(sizeof(ImageNode));

	if (!pNode)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pNode->pNext = NULL;
	pNode->pData = NULL;

	return pNode;
}

void FreeImageNode(ImageNode* pNode)
{
	if (!pNode) return;

	if (pNode->pData) FreeImage(pNode->pData);

	free(pNode);
}

#pragma endregion ImageNode

#pragma region ImageList

ImageList* CreateImageList()
{
	ImageList* pList = (ImageList*)malloc(sizeof(ImageList));

	if (!pList)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pList->pHead = NULL;
	pList->count = 0;

	return pList;
}

void FreeImageList(ImageList* pList)
{
	if (!pList) return;

	ImageNode* pCurrent, * pNext;

	pCurrent = pList->pHead;

	while (pCurrent)
	{
		pNext = pCurrent->pNext;

		FreeImageNode(pCurrent);

		pCurrent = pNext;
	}

	free(pList);
}

void ImageListAddStart(ImageList* pList, Image* pImage)
{
	if (!pList) return;
	if (!pImage) return;

	ImageNode* pNode = CreateImageNode();

	pNode->pData = pImage;

	if (!pList->pHead)
	{
		pList->pHead = pList->pTail = pNode;
		pList->count++;

		return;
	}

	pNode->pNext = pList->pHead;
	pList->pHead = pNode;

	pList->count++;
}

void pImageListAddEnd(ImageList* pList, Image* pImage)
{
	if (!pList) return;
	if (!pImage) return;

	if (!pList->pHead)
	{
		ImageListAddStart(pList, pImage);
		return;
	}

	ImageNode* pNode = CreateImageNode();

	pNode->pData = pImage;

	pList->pTail->pNext = pNode;
	pList->pTail = pNode;

	pList->count++;
}

#pragma endregion ImageList

#pragma region Vector2I

Vector2I* CreateVector2I(int x, int y)
{
	Vector2I* pVector = (Vector2I*)malloc(sizeof(Vector2I));

	if (!pVector)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pVector->x = x;
	pVector->y = y;

	return pVector;
}

void FreeVector2I(Vector2I* pVector)
{
	if (!pVector) return;

	free(pVector);
}

#pragma endregion Vector2I

#pragma region Vector2IdNode

Vector2INode* CreateVector2INode()
{
	Vector2INode* pNode = (Vector2INode*)malloc(sizeof(Vector2INode));

	if (!pNode)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pNode->pNext = NULL;
	pNode->pData = NULL;

	return pNode;
}

void FreeVector2INode(Vector2INode* pNode)
{
	if (!pNode) return;

	if (pNode->pData) FreeVector2I(pNode->pData);

	free(pNode);
}

#pragma endregion Vector2INode

#pragma region Vector2IQueue

Vector2IQueue* createVector2IQueue()
{
	Vector2IQueue* queue = (Vector2IQueue*)malloc(sizeof(Vector2IQueue));

	if (!queue) return NULL;

	queue->pHead = queue->pTail = NULL;
	queue->count = 0;

	return queue;
}

void freeVector2IQueue(Vector2IQueue* queue)
{
	if (!queue) return;

	for (int i = 0; i < queue->count; i++)
	{
		FreeVector2I(vector2IDequeue(queue));
	}

	free(queue);
}

void vector2IEnqueue(Vector2IQueue* queue, Vector2I* coord)
{
	if (!queue) return;
	if (!coord) return;

	Vector2INode* node = CreateVector2INode();
	node->pData = coord;

	if (queue->pHead == NULL)
	{
		queue->pHead = queue->pTail = node;
		queue->count++;

		return;
	}

	queue->pTail->pNext = node;
	queue->pTail = node;

	queue->count++;
}

Vector2I* vector2IDequeue(Vector2IQueue* queue)
{
	if (!queue) return NULL;
	if (!queue->pHead) return NULL;

	Vector2INode* node = queue->pHead;
	queue->pHead = node->pNext;

	queue->count--;

	Vector2I* coord = node->pData;

	free(node);

	return coord;
}

#pragma endregion Vector2IQueue

#pragma region Blob

Blob* createBlob()
{
	Blob* blob = (Blob*)malloc(sizeof(Blob));

	if (!blob) return NULL;

	blob->pHead = blob->pTail = NULL;
	blob->count = 0;

	return blob;
}

void freeBloob(Blob* blob)
{
	if (!blob) return;

	Vector2INode* current, * next;

	current = blob->pHead;

	while (current)
	{
		next = current->pNext;

		FreeVector2INode(current);

		current = next;
	}

	free(blob);
}

void blobAddStart(Blob* blob, Vector2I* coord)
{
	if (!blob) return;
	if (!coord) return;

	Vector2INode* node = CreateVector2INode();

	node->pData = coord;

	if (blob->pHead == NULL)
	{
		blob->pHead = blob->pTail = node;
		blob->count++;

		return;
	}

	node->pNext = blob->pHead;
	blob->pHead = node;

	blob->count++;
}

void blobAddEnd(Blob* blob, Vector2I* coord)
{
	if (!blob) return;
	if (!coord) return;

	if (blob->pHead == NULL)
	{
		blobAddStart(blob, coord);
		return;
	}

	Vector2INode* node = CreateVector2INode();

	node->pData = coord;

	blob->pTail->pNext = node;
	blob->pTail = node;

	blob->count++;
}

Vector2I getBlobCenter(Blob* blob)
{
	if (!blob) return;
	if (!blob->pHead) return;

	Vector2I center;
	Vector2INode* current;
	int minX, maxX, minY, maxY;

	// Find blob boundaries
	current = blob->pHead;

	minX = maxX = current->pData->x;
	minY = maxY = current->pData->y;

	current = current->pNext;

	while (current)
	{
		// X boundary
		if (current->pData->x > maxX) maxX = current->pData->x;
		else if (current->pData->x < minX) minX = current->pData->x;

		// Y boundary
		if (current->pData->y > maxY) maxY = current->pData->y;
		else if (current->pData->y < minY) minY = current->pData->y;

		// Update current node
		current = current->pNext;
	}

	// Calculate center
	// TODO: Find right way to round the center
	center.x = (minX + maxX) / 2;
	center.y = (minY + maxY) / 2;

	return center;
}

Vector3F getBlobStdDeviation(Blob* blob, Image* image)
{
	if (!blob) return;
	if (!blob->pHead) return;

	Vector3F stdDeviation, mean;
	Pixel* pixel;

	mean.x = mean.y = mean.z = 0;
	stdDeviation.x = stdDeviation.y = stdDeviation.z = 0;
	
	// Calculate blob's mean
	for (Vector2INode* node = blob->pHead; node; node = node->pNext)
	{
		pixel = GetPixelFromVector2I(image, node->pData->x, node->pData->y);
		
		mean.x += pixel->red;
		mean.y += pixel->green;
		mean.z += pixel->blue;
	}

	mean.x /= blob->count;
	mean.y /= blob->count;
	mean.z /= blob->count;

	// Calculate Std. Deviation
	for (Vector2INode* node = blob->pHead; node; node = node->pNext)
	{
		pixel = GetPixelFromVector2I(image, node->pData->x, node->pData->y);

		stdDeviation.x += pow(pixel->red - (double)mean.x, 2);
		stdDeviation.y += pow(pixel->green - (double)mean.y, 2);
		stdDeviation.z += pow(pixel->blue - (double)mean.z, 2);
	}

	stdDeviation.x = sqrt(stdDeviation.x / blob->count);
	stdDeviation.y = sqrt(stdDeviation.y / blob->count);
	stdDeviation.z = sqrt(stdDeviation.z / blob->count);

	// TODO: Currently we have a very small difference in comparison to original project. Why? Is this a problem?

	return stdDeviation;
}

#pragma endregion Blob

#pragma region BlobNode

BlobNode* createBlobNode()
{
	BlobNode* node = (BlobNode*)malloc(sizeof(BlobNode));

	if (!node) return NULL;

	node->pNext = NULL;
	node->pData = NULL;

	return node;
}

void freeBlobNode(BlobNode* node)
{
	if (!node) return;

	freeBloob(node->pData);

	free(node);
}

#pragma endregion BlobNode

#pragma region BlobList

BlobList* createBlobList()
{
	BlobList* list = (BlobList*)malloc(sizeof(BlobList));

	if (!list) return NULL;

	list->pHead = list->pTail = NULL;
	list->count = 0;

	return list;
}

void freeBlobList(BlobList* list)
{
	if (!list) return;

	BlobNode* current, * next;

	current = list->pHead;

	while (current)
	{
		next = current->pNext;

		freeBlobNode(current);

		current = next;
	}

	free(list);
}

void blobListAddStart(BlobList* list, Blob* blob) {
	if (!list) return;
	if (!blob) return;

	BlobNode* node = createBlobNode();

	node->pData = blob;

	if (list->pHead == NULL)
	{
		list->pHead = list->pTail = node;
		list->count++;

		return;
	}

	node->pNext = list->pHead;
	list->pHead = node;

	list->count++;
}

void blobListAddEnd(BlobList* list, Blob* blob) {
	if (!list) return;
	if (!blob) return;

	if (list->pHead == NULL)
	{
		blobListAddStart(list, blob);
		return;
	}

	BlobNode* node = createBlobNode();

	node->pData = blob;

	list->pTail->pNext = node;
	list->pTail = node;

	list->count++;
}

void blobListAddSorted(BlobList* list, Blob* blob) {
	if (!list) return;
	if (!blob) return;

	if (!list->pHead)
	{
		blobListAddStart(list, blob);

		return;
	}

	BlobNode* newBlob;
	BlobNode* previous = NULL;
	BlobNode* current = list->pHead;
	char stop = 0;

	while (current && !stop)
	{
		if (blob->count > current->pData->count)
		{
			stop = 1;
		}
		else
		{
			previous = current;
			current = current->pNext;
		}
	}

	if (!previous)
	{
		blobListAddStart(list, blob);
	}
	else
	{
		newBlob = createBlobNode();
		newBlob->pData = blob;

		newBlob->pNext = current;

		previous->pNext = newBlob;

		list->count++;
	}
}

#pragma endregion BlobList
