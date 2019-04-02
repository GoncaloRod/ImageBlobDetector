#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct _pixel
{
	unsigned char red, green, blue, analized;
} Pixel;

typedef struct _image
{
	char fileName[20];
	int width, height;
	Pixel **pixels;
} Image;

typedef struct _imageNode
{
	struct _imageNode *next;
	Image *data;
} ImageNode;

typedef struct _imageList
{
	ImageNode *first, *last;
	int count;
} ImageList;

#endif