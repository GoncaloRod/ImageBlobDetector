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

#endif