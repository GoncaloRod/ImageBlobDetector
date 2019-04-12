#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "structs.h"
#include "utils/functions.h"

void analyseImage(Image* image, BlobList *blobls, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

void findBlob(Image *image, Blob *blob, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

#endif