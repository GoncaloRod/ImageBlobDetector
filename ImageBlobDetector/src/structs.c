#include "structs.h"

#pragma region Pixel

Pixel* createPixelMatrix(int heigth, int width)
{
	Pixel* pixels = (Pixel*)malloc(heigth * width * sizeof(Pixel));

	return pixels;
}

void freePixelMatrix(Pixel* matrix)
{
	free(matrix);
}

#pragma endregion Pixel

#pragma region Image

Image* createImage()
{
	Image* i = (Image*)malloc(sizeof(Image));

	if (!i) return NULL;

	strcpy(i->fileName, "");
	i->width = 0;
	i->height = 0;
	i->blobs = 0;
	i->pixels = NULL;

	return i;
}

void freeImage(Image* image)
{
	if (!image) return;

	if (image->pixels) freePixelMatrix(image->pixels);

	free(image);
}

#pragma endregion Image

#pragma region ImageNode

ImageNode* createImageNode()
{
	ImageNode* node = (ImageNode*)malloc(sizeof(ImageNode));

	if (!node) return NULL;

	node->next = NULL;
	node->data = NULL;

	return node;
}

void freeImageNode(ImageNode* node)
{
	if (!node) return;

	if (node->data) freeImage(node->data);

	free(node);
}

#pragma endregion ImageNode

#pragma region ImageList

ImageList* createImageList()
{
	ImageList* list = (ImageList*)malloc(sizeof(ImageList));

	if (!list) return NULL;

	list->first = NULL;
	list->count = 0;

	return list;
}

void freeImageList(ImageList* list)
{
	if (!list) return;

	ImageNode* current, * next;

	current = list->first;

	while (current)
	{
		next = current->next;

		freeImageNode(current);

		current = next;
	}

	free(list);
}

void imageListAddStart(ImageList* list, Image* image)
{
	if (!list) return;
	if (!image) return;

	ImageNode* node = createImageNode();

	if (!list->first)
	{
		list->first = list->last = node;
		list->count++;

		return;
	}

	node->next = list->first;
	list->first = node;

	list->count++;
}

void imageListAddEnd(ImageList* list, Image* image)
{
	if (!list) return;
	if (!image) return;

	if (!list->first)
	{
		imageListAddStart(list, image);
		return;
	}

	ImageNode* node = createCoordNode();

	node->data = image;

	list->last->next = node;
	list->last = node;

	list->count++;
}

#pragma endregion ImageList

#pragma region Coord

Coord* createCoord(int x, int y)
{
	Coord* coord = (Coord*)malloc(sizeof(Coord));

	if (!coord) return NULL;

	coord->x = x;
	coord->y = y;

	return coord;
}

void freeCoord(Coord* coord)
{
	if (!coord) return;

	free(coord);
}

#pragma endregion Coord

#pragma region CoordNode

CoordNode* createCoordNode()
{
	CoordNode* node = (CoordNode*)malloc(sizeof(CoordNode));

	if (!node) return NULL;

	node->next = NULL;
	node->data = NULL;

	return node;
}

void freeCoordNode(CoordNode* node)
{
	if (!node) return;

	if (node->data) freeCoord(node->data);

	free(node);
}

#pragma endregion CoordNode

#pragma region CoordQueue

CoordQueue* createCoordQueue()
{
	CoordQueue* queue = (CoordQueue*)malloc(sizeof(CoordQueue));

	if (!queue) return NULL;

	queue->first = queue->last = NULL;
	queue->count = 0;

	return queue;
}

void freeCoordQueue(CoordQueue* queue)
{
	if (!queue) return;

	for (int i = 0; i < queue->count; i++)
	{
		freeCoord(coordDequeue(queue));
	}

	free(queue);
}

void coordEnqueue(CoordQueue* queue, Coord* coord)
{
	if (!queue) return;
	if (!coord) return;

	CoordNode* node = createCoordNode();
	node->data = coord;

	if (queue->first == NULL)
	{
		queue->first = queue->last = node;
		queue->count++;

		return;
	}

	queue->last->next = node;
	queue->last = node;

	queue->count++;
}

Coord* coordDequeue(CoordQueue* queue)
{
	if (!queue) return NULL;
	if (!queue->first) return NULL;

	CoordNode* node = queue->first;
	queue->first = node->next;

	queue->count--;

	Coord* coord = node->data;

	free(node);

	return coord;
}

#pragma endregion CoordQueue

#pragma region Blob

Blob* createBlob()
{
	Blob* blob = (Blob*)malloc(sizeof(Blob));

	if (!blob) return NULL;

	blob->first = blob->last = NULL;
	blob->count = 0;

	return blob;
}

void freeBloob(Blob* blob)
{
	if (!blob) return;

	CoordNode* current, * next;

	current = blob->first;

	while (current)
	{
		next = current->next;

		freeCoordNode(current);

		current = next;
	}

	free(blob);
}

void blobAddStart(Blob* blob, Coord* coord)
{
	if (!blob) return;
	if (!coord) return;

	CoordNode* node = createCoordNode();

	node->data = coord;

	if (blob->first == NULL)
	{
		blob->first = blob->last = node;
		blob->count++;

		return;
	}

	node->next = blob->first;
	blob->first = node;

	blob->count++;
}

void blobAddEnd(Blob* blob, Coord* coord)
{
	if (!blob) return;
	if (!coord) return;

	if (blob->first == NULL)
	{
		blobAddStart(blob, coord);
		return;
	}

	CoordNode* node = createCoordNode();

	node->data = coord;

	blob->last->next = node;
	blob->last = node;

	blob->count++;
}

Coord getBlobCenter(Blob* blob)
{
	if (!blob) return;
	
	Coord coord;

	coord.x = 10;
	coord.y = 100;

	return coord;
}

#pragma endregion Blob

#pragma region BlobNode

BlobNode* createBlobNode()
{
	BlobNode* node = (BlobNode*)malloc(sizeof(BlobNode));

	if (!node) return NULL;

	node->next = NULL;
	node->data = NULL;

	return node;
}

void freeBlobNode(BlobNode* node)
{
	if (!node) return;

	freeBloob(node->data);

	free(node);
}

#pragma endregion BlobNode

#pragma region BlobList

BlobList* createBlobList()
{
	BlobList* list = (BlobList*)malloc(sizeof(BlobList));

	if (!list) return NULL;

	list->first = list->last = NULL;
	list->count = 0;

	return list;
}

void freeBlobList(BlobList* list)
{
	if (!list) return;

	BlobNode* current, * next;

	current = list->first;

	while (current)
	{
		next = current->next;

		freeBlobNode(current);

		current = next;
	}

	free(list);
}

void blobListAddStart(BlobList* list, Blob* blob) {
	if (!list) return;
	if (!blob) return;

	BlobNode* node = createBlobNode();

	node->data = blob;

	if (list->first == NULL)
	{
		list->first = list->last = node;
		list->count++;

		return;
	}

	node->next = list->first;
	list->first = node;

	list->count++;
}

void blobListAddEnd(BlobList* list, Blob* blob) {
	if (!list) return;
	if (!blob) return;

	if (list->first == NULL)
	{
		blobListAddStart(list, blob);
		return;
	}

	BlobNode* node = createBlobNode();

	node->data = blob;

	list->last->next = node;
	list->last = node;

	list->count++;
}

void blobListAddSorted(BlobList* list, Blob* blob) {
	if (!list) return;
	if (!blob) return;

	if (!list->first)
	{
		blobListAddStart(list, blob);

		return;
	}

	BlobNode* newBlob;
	BlobNode* previous = NULL;
	BlobNode* current = list->first;
	char stop = 0;

	while (current && !stop)
	{
		if (blob->count > current->data->count)
		{
			stop = 1;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}

	if (!previous)
	{
		blobListAddStart(list, blob);
	}
	else
	{
		newBlob = createBlobNode();
		newBlob->data = blob;

		newBlob->next = current;

		previous->next = newBlob;

		list->count++;
	}
}

void printBlobList(BlobList* list, Image* image)
{
	if (!list) return;
	if (!list->first) return;

	BlobNode* current = list->first;

	printInfo("%d blobs found in %s", list->count, image->fileName);

	while (current)
	{
		printf("(%d, %d) | %d pixels | Standard Deviation ( , , )\n",
			current->data->count);

		current = current->next;
	}
}

#pragma endregion BlobList
