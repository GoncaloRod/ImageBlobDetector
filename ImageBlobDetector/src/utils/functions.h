#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "../strucs.h"
#include "files.h"

void printUsageMessage(char *programName);

void printError(const char *message, ...);

void printInfo(const char *message, ...);

bool isNumeric(char *num);

int stringToInt(char *num);

bool inRange(int min, int max, int value);

int validateArguments(int argc, char **argv, FILE **inputFile, unsigned char *r,
					  unsigned char *g, unsigned char *b, unsigned char *t, char *mode);

Image *createImage();

double executionTime(clock_t start, clock_t end);

#endif