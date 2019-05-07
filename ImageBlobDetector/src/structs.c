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
	i->pixels = NULL;
	i->blobs = NULL;

	return i;
}

void freeImage(Image* image)
{
	if (!image) return;

	if (image->pixels) freePixelMatrix(image->pixels);
	if (image->blobs) freeBlobList(image->blobs);

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

	ImageNode* node = createVector2INode();

	node->data = image;

	list->last->next = node;
	list->last = node;

	list->count++;
}

#pragma endregion ImageList

#pragma region Vector2I

Vector2I* createVector2I(int x, int y)
{
	Vector2I* coord = (Vector2I*)malloc(sizeof(Vector2I));

	if (!coord) return NULL;

	coord->x = x;
	coord->y = y;

	return coord;
}

void freeVector2I(Vector2I* vector)
{
	if (!vector) return;

	free(vector);
}

#pragma endregion Vector2I

#pragma region Vector2IdNode

Vector2INode* createVector2INode()
{
	Vector2INode* node = (Vector2INode*)malloc(sizeof(Vector2INode));

	if (!node) return NULL;

	node->next = NULL;
	node->data = NULL;

	return node;
}

void freeVector2INode(Vector2INode* node)
{
	if (!node) return;

	if (node->data) freeVector2I(node->data);

	free(node);
}

#pragma endregion Vector2INode

#pragma region Vector2IQueue

Vector2IQueue* createVector2IQueue()
{
	Vector2IQueue* queue = (Vector2IQueue*)malloc(sizeof(Vector2IQueue));

	if (!queue) return NULL;

	queue->first = queue->last = NULL;
	queue->count = 0;

	return queue;
}

void freeVector2IQueue(Vector2IQueue* queue)
{
	if (!queue) return;

	for (int i = 0; i < queue->count; i++)
	{
		freeVector2I(vector2IDequeue(queue));
	}

	free(queue);
}

void vector2IEnqueue(Vector2IQueue* queue, Vector2I* coord)
{
	if (!queue) return;
	if (!coord) return;

	Vector2INode* node = createVector2INode();
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

Vector2I* vector2IDequeue(Vector2IQueue* queue)
{
	if (!queue) return NULL;
	if (!queue->first) return NULL;

	Vector2INode* node = queue->first;
	queue->first = node->next;

	queue->count--;

	Vector2I* coord = node->data;

	free(node);

	return coord;
}

#pragma endregion Vector2IQueue

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

	Vector2INode* current, * next;

	current = blob->first;

	while (current)
	{
		next = current->next;

		freeVector2INode(current);

		current = next;
	}

	free(blob);
}

void blobAddStart(Blob* blob, Vector2I* coord)
{
	if (!blob) return;
	if (!coord) return;

	Vector2INode* node = createVector2INode();

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

void blobAddEnd(Blob* blob, Vector2I* coord)
{
	if (!blob) return;
	if (!coord) return;

	if (blob->first == NULL)
	{
		blobAddStart(blob, coord);
		return;
	}

	Vector2INode* node = createVector2INode();

	node->data = coord;

	blob->last->next = node;
	blob->last = node;

	blob->count++;
}

Vector2I getBlobCenter(Blob* blob)
{
	if (!blob) return;
	if (!blob->first) return;

	Vector2I center;
	Vector2INode* current;
	int minX, maxX, minY, maxY;

	// Find blob boundaries
	current = blob->first;

	minX = maxX = current->data->x;
	minY = maxY = current->data->y;

	current = current->next;

	while (current)
	{
		// X boundary
		if (current->data->x > maxX) maxX = current->data->x;
		else if (current->data->x < minX) minX = current->data->x;

		// Y boundary
		if (current->data->y > maxY) maxY = current->data->y;
		else if (current->data->y < minY) minY = current->data->y;

		// Update current node
		current = current->next;
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
	if (!blob->first) return;

	Vector3F stdDeviation, mean;
	Pixel* pixel;

	mean.x = mean.y = mean.z = 0;
	stdDeviation.x = stdDeviation.y = stdDeviation.z = 0;
	
	// Calculate blob's mean
	for (Vector2INode* node = blob->first; node; node = node->next)
	{
		pixel = getPixelFromVector2Int(image, node->data->x, node->data->y);
		
		mean.x += pixel->red;
		mean.y += pixel->green;
		mean.z += pixel->blue;
	}

	mean.x /= blob->count;
	mean.y /= blob->count;
	mean.z /= blob->count;

	// Calculate Std. Deviation
	for (Vector2INode* node = blob->first; node; node = node->next)
	{
		pixel = getPixelFromVector2Int(image, node->data->x, node->data->y);

		stdDeviation.x += pow(pixel->red - (double)mean.x, 2);
		stdDeviation.y += pow(pixel->green - (double)mean.y, 2);
		stdDeviation.z += pow(pixel->blue - (double)mean.z, 2);
	}

	stdDeviation.x = sqrt(stdDeviation.x / blob->count);
	stdDeviation.y = sqrt(stdDeviation.y / blob->count);
	stdDeviation.z = sqrt(stdDeviation.z / blob->count);

	// TODO: Currently we have a very small difference in comparison to original project. Why?

	return stdDeviation;
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

#pragma endregion BlobList
