#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct _pixel
{
	unsigned char red, green, blue, analized;
} Pixel;

typedef struct _image
{
	char fileName[20];
	int width, height, channels;
	Pixel **pixels;
} Image;

#endif