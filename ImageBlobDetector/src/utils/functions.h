#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "files.h"

void printUsageMessage(char *programName);

void printError(char *message);

bool isNumeric(char *num);

int stringToInt(char *num);

bool inRange(int min, int max, int value);

int validateArguments(int argc, char **argv, FILE **inputFile, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *t, char **mode);

#endif