#include "analyzer.h"

void analyseImage(Image* image, BlobList *blobls, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	Pixel *currentPixel = image->pixels;
	Blob *blob;
	clock_t start, end;

	printInfo("Analyzing %s", image->fileName);

	start = clock();

	// Go through pixel matrix to find blobs
	for (int i = 0; i < image->height; ++i)									// Lines
	{
		for (int j = 0; j < image->width; ++j, ++currentPixel)				// Columns
		{
			// If pixels was already analyzed go to next pixel
			if (currentPixel->analysed) continue;

			currentPixel->analysed = 1;

			if (pixelInRange(currentPixel, r, g, b, t))
			{
				blob = createBlob();

				blobAddEnd(blob, createCoord(j, i));

				findBlob(image, blob, r, g, b, t);

				// Blob needs to have at least 5 pixels to be a Blob
				if (blob->count < 5)				// TODO: Variable
				{
					freeBloob(blob);
					continue;
				}

				blobListAddSorted(blobls, blob);
			}
		}
	}

	end = clock();

	printInfo("%s analyzed in %f seconds", image->fileName, executionTime(start, end));
}

void findBlob(Image *image, Blob *blob, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	CoordQueue *toAnalyse = createCoordQueue();
	Coord *current = blob->first->data;
	Pixel *pixel;

	addNeighbors(image, toAnalyse, *current);

	while (toAnalyse->count > 0)
	{
		current = coordDequeue(toAnalyse);

		pixel = getPixelFromCoord(image, current->x, current->y);

		if (pixel->analysed)
		{
			freeCoord(current);

			continue;
		}

		pixel->analysed = 1;

		if (pixelInRange(pixel, r, g, b, t))
		{
			blobAddEnd(blob, current);

			addNeighbors(image, toAnalyse, *current);
		}
		else
		{
			freeCoord(current);
		}
	}

	freeCoordQueue(toAnalyse);
}

void addNeighbors(Image *image, CoordQueue *destination, Coord coord)
{
	// Top
	if (coord.y > 0 && !getPixelFromCoord(image, coord.x, coord.y - 1)->analysed)
		coordEnqueue(destination, createCoord(coord.x, coord.y - 1));

	// Bottom
	if (coord.y < image->height - 1 && !getPixelFromCoord(image, coord.x, coord.y + 1)->analysed)
		coordEnqueue(destination, createCoord(coord.x, coord.y + 1));

	// Left
	if (coord.x > 0 && !getPixelFromCoord(image, coord.x - 1, coord.y)->analysed)
		coordEnqueue(destination, createCoord(coord.x - 1, coord.y));

	// Right
	if (coord.x < image->width - 1 && !getPixelFromCoord(image, coord.x + 1, coord.y)->analysed)
		coordEnqueue(destination, createCoord(coord.x + 1, coord.y));
}

int pixelInRange(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	return inRange(r - t, r + t, pixel->red) && inRange(g - t, g + t, pixel->green) && inRange(b - t, b + t, pixel->blue);
}
