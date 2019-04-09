#ifndef STRUCTS_H_
#define STRUCTS_H_

#define IMAGE_NAME_SIZE 50

typedef struct _pixel
{
	unsigned char red, green, blue, analysed;
} Pixel;

typedef struct _image
{
	char fileName[IMAGE_NAME_SIZE];
	int width, height, channels;
	Pixel *pixels;
} Image;

typedef struct _coord
{
	int x, y;
} Coord;

typedef struct _coordNode
{
	struct _coordNode *next;
	Coord *data;
} CoordNode;

typedef struct _blob
{
	CoordNode *first, *last;
	int count;
} Blob;

typedef struct _blobNode
{
	struct _blobNode *next;
	Blob *data;
} BlobNode;

typedef struct _blobList
{
	BlobNode *first, *last;
	int count;
} BlobList;

#endif