#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "../structs.h"

void PrintError(const char *pMessage, ...);

void PrintInfo(const char *message, ...);

void PrintWarning(const char* message, ...);

int IsNumeric(char* pNum);

int InRange(int min, int max, int value);

double ExecutionTime(clock_t start, clock_t end);

#endif