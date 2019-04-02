#ifndef LISTS_H_
#define LISTS_H_

#include <stdio.h>
#include <stdlib.h>

#include "../strucs.h"

ImageList *createImageList();

ImageNode *createImageNode();

void addImageStart(ImageList *list, Image *image);

void addImageList(ImageList *list, Image *image);

#endif // LISTS_H_
