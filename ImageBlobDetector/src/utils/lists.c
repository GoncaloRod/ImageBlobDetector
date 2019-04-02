#include "lists.h"

ImageList *createImageList()
{
	ImageList *l = (ImageList *)malloc(sizeof(ImageList));

	l->first	= NULL;
	l->last		= NULL;
	l->count	= 0;

	return l;
}

ImageNode * createImageNode()
{
	ImageNode *n = (ImageNode *)malloc(sizeof(ImageNode));

	n->next = NULL;
	n->data = NULL;

	return n;
}

void addImageStart(ImageList *list, Image *image)
{
	if (!list) return;
	if (!image) return;

	ImageNode *node = createImageNode();

	node->data = image;
	node->next = list->first;

	if (list->first == list->last)
	{
		list->first = list->last = node;
	}
	else
	{
		list->first = node;
	}
}

void addImageList(ImageList *list, Image *image)
{
	if (!list) return;
	if (!image) return;

	if (!list->first)
	{
		addImageStart(list, image);
		return;
	}

	ImageNode *node = createImageNode();

	node->data = image;

	list->last->next = list->last = node;
}
