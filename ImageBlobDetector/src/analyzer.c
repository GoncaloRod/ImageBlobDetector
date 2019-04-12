#include "analyzer.h"

void analyseImage(Image* image, BlobList *blobls, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	Pixel *pixels = image->pixels;
	Blob *blob;

	for (int i = 0; i < image->height; ++i)
	{
		for (int j = 0; j < image->width; ++j, ++pixels)
		{
			if (pixels->analysed) continue;

			pixels->analysed = 1;

			if (inRange(r - t, r + t, pixels->red) && inRange(g - t, g + t, pixels->green) &&
				inRange(b - t, b + t, pixels->blue))
			{
				blob = createBlob();

				blobAddEnd(blob, createCoord(j, i));

				findBlob(image, blob, r, g, b, t);

				if (blob->count < 5)		// TODO: variable
				{
					freeBloob(blob);
					continue;
				}

				// TODO: Add to blob list
			}
		}
	}
}

void findBlob(Image *image, Blob *blob, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	CoordQueue *toAnalyse = createCoordQueue();
	Coord *current = blob->first;

	// TODO: Function
	// Top
	if (current->y > 0) coordEnqueue(blob, createCoord(current->x, current->y - 1));

	// Bottom
	if (current->y < image->height - 1) coordEnqueue(blob, createCoord(current->x, current->y + 1));

	// Left
	if (current->x > 0) coordEnqueue(blob, createCoord(current->x - 1, current->y));

	// Right
	if (current->x < image->width - 1) coordEnqueue(blob, createCoord(current->x + 1, current->y));

	while (toAnalyse->count > 0)
	{
		// TODO: Analyse
	}
}
