#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "../structs.h"

void printError(const char *message, ...);

void printInfo(const char *message, ...);

void printDanger(const char* message, ...);

bool isNumeric(char* num);

bool inRange(int min, int max, int value);

double executionTime(clock_t start, clock_t end);

#endif