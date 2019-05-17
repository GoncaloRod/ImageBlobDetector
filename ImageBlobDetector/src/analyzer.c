#include "analyzer.h"

void AnalyzeImage(Image* pImage, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	if (!pImage) return;

	Pixel* pCurrentPixel = pImage->pPixels;
	Blob* pBlob;
	clock_t start, end;

	pImage->pBlobs = createBlobList();

	PrintInfo("Analyzing %s", pImage->fileName);

	start = clock();

	// Go through pixel matrix to find blobs
	for (int i = 0; i < pImage->height; ++i)									// Lines
	{
		for (int j = 0; j < pImage->width; ++j, ++pCurrentPixel)				// Columns
		{
			// If pixels was already analyzed go to next pixel
			if (pCurrentPixel->analysed) continue;

			pCurrentPixel->analysed = 1;

			if (PixelInRange(pCurrentPixel, r, g, b, t))
			{
				pBlob = createBlob();

				blobAddEnd(pBlob, CreateVector2I(j, i));

				FindBlob(pImage, pBlob, r, g, b, t);

				// Blob needs to have at least 5 pixels to be a Blob
				if (pBlob->count < 5)				// TODO: Variable
				{
					freeBloob(pBlob);
					continue;
				}

				blobListAddSorted(pImage->pBlobs, pBlob);
			}
		}
	}

	end = clock();

	PrintInfo("%s analyzed in %f seconds", pImage->fileName, ExecutionTime(start, end));
}

void FindBlob(Image *pImage, Blob *pBlob, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	Vector2IQueue* pToAnalyse = createVector2IQueue();
	Vector2I* pCurrent = pBlob->pHead->pData;
	Pixel* pPixel;

	AddNeighbors(pImage, pToAnalyse, *pCurrent);

	while (pToAnalyse->count > 0)
	{
		pCurrent = vector2IDequeue(pToAnalyse);

		pPixel = GetPixelFromVector2I(pImage, pCurrent->x, pCurrent->y);

		if (pPixel->analysed)
		{
			FreeVector2I(pCurrent);

			continue;
		}

		pPixel->analysed = 1;

		if (PixelInRange(pPixel, r, g, b, t))
		{
			blobAddEnd(pBlob, pCurrent);

			AddNeighbors(pImage, pToAnalyse, *pCurrent);
		}
		else
		{
			FreeVector2I(pCurrent);
		}
	}

	freeVector2IQueue(pToAnalyse);
}

void AddNeighbors(Image *pImage, Vector2IQueue *pDestination, Vector2I coord)
{
	// Top
	if (coord.y > 0 && !GetPixelFromVector2I(pImage, coord.x, coord.y - 1)->analysed)
		vector2IEnqueue(pDestination, CreateVector2I(coord.x, coord.y - 1));

	// Bottom
	if (coord.y < pImage->height - 1 && !GetPixelFromVector2I(pImage, coord.x, coord.y + 1)->analysed)
		vector2IEnqueue(pDestination, CreateVector2I(coord.x, coord.y + 1));

	// Left
	if (coord.x > 0 && !GetPixelFromVector2I(pImage, coord.x - 1, coord.y)->analysed)
		vector2IEnqueue(pDestination, CreateVector2I(coord.x - 1, coord.y));

	// Right
	if (coord.x < pImage->width - 1 && !GetPixelFromVector2I(pImage, coord.x + 1, coord.y)->analysed)
		vector2IEnqueue(pDestination, CreateVector2I(coord.x + 1, coord.y));
}

int PixelInRange(Pixel *pPixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t)
{
	return InRange(r - t, r + t, pPixel->red) && InRange(g - t, g + t, pPixel->green) && InRange(b - t, b + t, pPixel->blue);
}
