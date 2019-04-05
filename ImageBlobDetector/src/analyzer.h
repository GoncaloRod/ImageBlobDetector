#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "strucs.h"

void analyseImage(Image* image, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

void analysePizel(Pixel *pixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

#endif