#include "files.h"

ImageList *readDefaultFormat(FILE *f)
{
	if (!f) return NULL;

	// Check if file is not empty
	fseek(f, SEEK_END, 0);

	long end = ftell(f);

	fseek(f, SEEK_SET, 0);

	if (ftell(f) == end) return NULL;

	ImageList *list = createImageList();

	while (ftell(f) != end)
	{
		
	}

	return list;
}