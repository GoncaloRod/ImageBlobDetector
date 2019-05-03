#include "analyzer.h"

void analyzeImage(Image* image, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	if (!image) return;

	Pixel *currentPixel = image->pixels;
	Blob *blob;
	clock_t start, end;

	image->blobs = createBlobList();

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

				blobAddEnd(blob, createVector2I(j, i));

				findBlob(image, blob, r, g, b, t);

				// Blob needs to have at least 5 pixels to be a Blob
				if (blob->count < 5)				// TODO: Variable
				{
					freeBloob(blob);
					continue;
				}

				blobListAddSorted(image->blobs, blob);
			}
		}
	}

	end = clock();

	printInfo("%s analyzed in %f seconds", image->fileName, executionTime(start, end));
}

void findBlob(Image *image, Blob *blob, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	Vector2IQueue *toAnalyse = createVector2IQueue();
	Vector2I *current = blob->first->data;
	Pixel *pixel;

	addNeighbors(image, toAnalyse, *current);

	while (toAnalyse->count > 0)
	{
		current = vector2IDequeue(toAnalyse);

		pixel = getPixelFromVector2Int(image, current->x, current->y);

		if (pixel->analysed)
		{
			freeVector2I(current);

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
			freeVector2I(current);
		}
	}

	freeVector2IQueue(toAnalyse);
}

void addNeighbors(Image *image, Vector2IQueue *destination, Vector2I coord)
{
	// Top
	if (coord.y > 0 && !getPixelFromVector2Int(image, coord.x, coord.y - 1)->analysed)
		vector2IEnqueue(destination, createVector2I(coord.x, coord.y - 1));

	// Bottom
	if (coord.y < image->height - 1 && !getPixelFromVector2Int(image, coord.x, coord.y + 1)->analysed)
		vector2IEnqueue(destination, createVector2I(coord.x, coord.y + 1));

	// Left
	if (coord.x > 0 && !getPixelFromVector2Int(image, coord.x - 1, coord.y)->analysed)
		vector2IEnqueue(destination, createVector2I(coord.x - 1, coord.y));

	// Right
	if (coord.x < image->width - 1 && !getPixelFromVector2Int(image, coord.x + 1, coord.y)->analysed)
		vector2IEnqueue(destination, createVector2I(coord.x + 1, coord.y));
}

int pixelInRange(Pixel* pixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	return inRange(r - t, r + t, pixel->red) && inRange(g - t, g + t, pixel->green) && inRange(b - t, b + t, pixel->blue);
}
