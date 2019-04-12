#include "structs.h"

Image *createImage()
{
	Image *i = (Image *)malloc(sizeof(Image));

	strcpy(i->fileName, "");
	i->width = 0;
	i->height = 0;
	i->pixels = NULL;

	return i;
}

void freeImage(Image *image)
{
	if (!image) return;

	// Free pixels matrix
	if (image->pixels)
		freePixelMatrix(image->pixels);

	// Free image structure
	free(image);
}

Coord *createCoord(int x, int y)
{
	Coord *coord = (Coord *)malloc(sizeof(Coord));

	coord->x = x;
	coord->y = y;

	return coord;
}

void freeCoord(Coord *coord)
{
	if (!coord) return;

	free(coord);
}

CoordNode *createCoordNode()
{
	CoordNode *node = (CoordNode *)malloc(sizeof(CoordNode));

	node->next = NULL;
	node->data = NULL;

	return node;
}

void freeCoordNode(CoordNode *node)
{
	if (!node) return;

	freeCoord(node->data);

	free(node);
}

Blob *createBlob()
{
	Blob *blob = (Blob *)malloc(sizeof(Blob));

	blob->first = blob->last = NULL;
	blob->count = 0;
}

void freeBloob(Blob *blob)
{
	if (!blob) return;

	CoordNode *current, *next;

	current = blob->first;
	next = current->next;

	while (current)
	{
		freeCoordNode(current);

		current = next;
		next = current->next;
	}

	free(blob);
}

BlobNode *createBlobNode()
{
	BlobNode *node = (BlobNode *)malloc(sizeof(BlobNode));

	node->next = NULL;
	node->data = NULL;
}

void freeBlobNode(BlobNode *node)
{
	if (!node) return;

	freeBloob(node->next);

	free(node);
}

BlobList *createBlobList()
{
	BlobList *list = (BlobList *)malloc(sizeof(BlobList));

	list->first = list->last = NULL;
	list->count = 0;
}

void freeBlobList(BlobList *list)
{
	if (!list) return;

	BlobNode *current, *next;

	current = list->first;
	next = current->next;

	while (current)
	{
		freeBlobNode(current);

		current = next;
		next = current->next;
	}

	free(list);
}