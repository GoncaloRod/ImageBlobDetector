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
	if (pImage->pBlobs) FreeBlobList(pImage->pBlobs);

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

Vector2IQueue* CreateVector2IQueue()
{
	Vector2IQueue* pQueue = (Vector2IQueue*)malloc(sizeof(Vector2IQueue));

	if (!pQueue)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pQueue->pHead = pQueue->pTail = NULL;
	pQueue->count = 0;

	return pQueue;
}

void FreeVector2IQueue(Vector2IQueue* pQueue)
{
	if (!pQueue) return;

	for (int i = 0; i < pQueue->count; i++)
	{
		FreeVector2I(Vector2IDequeue(pQueue));
	}

	free(pQueue);
}

void Vector2IEnqueue(Vector2IQueue* pQueue, Vector2I* pCoord)
{
	if (!pQueue) return;
	if (!pCoord) return;

	Vector2INode* node = CreateVector2INode();
	node->pData = pCoord;

	if (pQueue->pHead == NULL)
	{
		pQueue->pHead = pQueue->pTail = node;
		pQueue->count++;

		return;
	}

	pQueue->pTail->pNext = node;
	pQueue->pTail = node;

	pQueue->count++;
}

Vector2I* Vector2IDequeue(Vector2IQueue* pQueue)
{
	if (!pQueue) return NULL;
	if (!pQueue->pHead) return NULL;

	Vector2INode* node = pQueue->pHead;
	pQueue->pHead = node->pNext;

	pQueue->count--;

	Vector2I* coord = node->pData;

	free(node);

	return coord;
}

#pragma endregion Vector2IQueue

#pragma region Blob

Blob* CreateBlob()
{
	Blob* pBlob = (Blob*)malloc(sizeof(Blob));

	if (!pBlob)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pBlob->pHead = pBlob->pTail = NULL;
	pBlob->count = 0;

	return pBlob;
}

void FreeBloob(Blob* pBlob)
{
	if (!pBlob) return;

	Vector2INode* pCurrent, * pNext;

	pCurrent = pBlob->pHead;

	while (pCurrent)
	{
		pNext = pCurrent->pNext;

		FreeVector2INode(pCurrent);

		pCurrent = pNext;
	}

	free(pBlob);
}

void BlobAddStart(Blob* pBlob, Vector2I* pCoord)
{
	if (!pBlob) return;
	if (!pCoord) return;

	Vector2INode* pNode = CreateVector2INode();

	pNode->pData = pCoord;

	if (pBlob->pHead == NULL)
	{
		pBlob->pHead = pBlob->pTail = pNode;
		pBlob->count++;

		return;
	}

	pNode->pNext = pBlob->pHead;
	pBlob->pHead = pNode;

	pBlob->count++;
}

void BlobAddEnd(Blob* pBlob, Vector2I* pCoord)
{
	if (!pBlob) return;
	if (!pCoord) return;

	if (pBlob->pHead == NULL)
	{
		BlobAddStart(pBlob, pCoord);
		return;
	}

	Vector2INode* pNode = CreateVector2INode();

	pNode->pData = pCoord;

	pBlob->pTail->pNext = pNode;
	pBlob->pTail = pNode;

	pBlob->count++;
}

Vector2I GetBlobCenter(Blob* pBlob)
{
	if (!pBlob) return;
	if (!pBlob->pHead) return;

	Vector2I center;
	Vector2INode* pCurrent;
	int minX, maxX, minY, maxY;

	// Find blob boundaries
	pCurrent = pBlob->pHead;

	minX = maxX = pCurrent->pData->x;
	minY = maxY = pCurrent->pData->y;

	pCurrent = pCurrent->pNext;

	while (pCurrent)
	{
		// X boundary
		if (pCurrent->pData->x > maxX) maxX = pCurrent->pData->x;
		else if (pCurrent->pData->x < minX) minX = pCurrent->pData->x;

		// Y boundary
		if (pCurrent->pData->y > maxY) maxY = pCurrent->pData->y;
		else if (pCurrent->pData->y < minY) minY = pCurrent->pData->y;

		// Update current node
		pCurrent = pCurrent->pNext;
	}

	// Calculate center
	center.x = (minX + maxX) / 2;
	center.y = (minY + maxY) / 2;

	return center;
}

Vector3F GetBlobStdDeviation(Blob * pBlob, Image * pImage)
{
	if (!pBlob) return;
	if (!pBlob->pHead) return;

	Vector3F stdDeviation, mean;
	Pixel* pPixel;

	mean.x = mean.y = mean.z = 0;
	stdDeviation.x = stdDeviation.y = stdDeviation.z = 0;

	// Calculate blob's mean
	for (Vector2INode* pNode = pBlob->pHead; pNode; pNode = pNode->pNext)
	{
		pPixel = GetPixelFromVector2I(pImage, pNode->pData->x, pNode->pData->y);

		mean.x += pPixel->red;
		mean.y += pPixel->green;
		mean.z += pPixel->blue;
	}

	mean.x /= pBlob->count;
	mean.y /= pBlob->count;
	mean.z /= pBlob->count;

	// Calculate Std. Deviation
	for (Vector2INode* pNode = pBlob->pHead; pNode; pNode = pNode->pNext)
	{
		pPixel = GetPixelFromVector2I(pImage, pNode->pData->x, pNode->pData->y);

		stdDeviation.x += pow(pPixel->red - (double)mean.x, 2);
		stdDeviation.y += pow(pPixel->green - (double)mean.y, 2);
		stdDeviation.z += pow(pPixel->blue - (double)mean.z, 2);
	}

	stdDeviation.x = sqrt(stdDeviation.x / pBlob->count);
	stdDeviation.y = sqrt(stdDeviation.y / pBlob->count);
	stdDeviation.z = sqrt(stdDeviation.z / pBlob->count);

	return stdDeviation;
}

#pragma endregion Blob

#pragma region BlobNode

BlobNode * CreateBlobNode()
{
	BlobNode* pNode = (BlobNode*)malloc(sizeof(BlobNode));

	if (!pNode)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pNode->pNext = NULL;
	pNode->pData = NULL;

	return pNode;
}

void FreeBlobNode(BlobNode * pNode)
{
	if (!pNode) return;

	FreeBloob(pNode->pData);

	free(pNode);
}

#pragma endregion BlobNode

#pragma region BlobList

BlobList* CreateBlobList()
{
	BlobList* pList = (BlobList*)malloc(sizeof(BlobList));

	if (!pList)
	{
		PrintError("Failed to allocate memory!");

		exit(EXIT_FAILURE);
	}

	pList->pHead = pList->pTail = NULL;
	pList->count = 0;

	return pList;
}

void FreeBlobList(BlobList * pList)
{
	if (!pList) return;

	BlobNode* pCurrent, * pNext;

	pCurrent = pList->pHead;

	while (pCurrent)
	{
		pNext = pCurrent->pNext;

		FreeBlobNode(pCurrent);

		pCurrent = pNext;
	}

	free(pList);
}

void BlobListAddStart(BlobList* pList, Blob* pBlob)
{
	if (!pList) return;
	if (!pBlob) return;

	BlobNode* pNode = CreateBlobNode();

	pNode->pData = pBlob;

	if (pList->pHead == NULL)
	{
		pList->pHead = pList->pTail = pNode;
		pList->count++;

		return;
	}

	pNode->pNext = pList->pHead;
	pList->pHead = pNode;

	pList->count++;
}

void BlobListAddEnd(BlobList* pList, Blob* pBlob)
{
	if (!pList) return;
	if (!pBlob) return;

	if (pList->pHead == NULL)
	{
		BlobListAddStart(pList, pBlob);
		return;
	}

	BlobNode* pNode = CreateBlobNode();

	pNode->pData = pBlob;

	pList->pTail->pNext = pNode;
	pList->pTail = pNode;

	pList->count++;
}

void BlobListAddSorted(BlobList* pList, Blob* pBlob)
{
	if (!pList) return;
	if (!pBlob) return;

	if (!pList->pHead)
	{
		BlobListAddStart(pList, pBlob);

		return;
	}

	BlobNode* pNewBlob;
	BlobNode* pPrevious = NULL;
	BlobNode* pCurrent = pList->pHead;
	char stop = 0;

	while (pCurrent && !stop)
	{
		if (pBlob->count > pCurrent->pData->count)
		{
			stop = 1;
		}
		else
		{
			pPrevious = pCurrent;
			pCurrent = pCurrent->pNext;
		}
	}

	if (!pPrevious)
	{
		BlobListAddStart(pList, pBlob);
	}
	else
	{
		pNewBlob = CreateBlobNode();
		pNewBlob->pData = pBlob;

		pNewBlob->pNext = pCurrent;

		pPrevious->pNext = pNewBlob;

		pList->count++;
	}
}

#pragma endregion BlobList
