#include "utils.h"

void printError(const char *message, ...)
{
	va_list vargs;

	va_start(vargs, message);

	printf("[ERROR]: ");

	vprintf(message, vargs);

	printf("\n");

	va_end(vargs);
}

void printInfo(const char *message, ...)
{
	va_list vargs;

	va_start(vargs, message);

	printf("[INFO]: ");

	vprintf(message, vargs);

	printf("\n");

	va_end(vargs);
}

bool isNumeric(char *num)
{
	bool numeric = true;

	for (int i = 0; i < (int)strlen(num) && numeric; ++i)
		if (num[i] < '0' || num[i] > '9')
			numeric = false;

	return numeric;
}

int stringToInt(char *num)
{
	int value = 0;

	for (int i = 0; i < (int)strlen(num); ++i)
	{
		value *= 10;
		value += num[i] - '0';
	}

	return value;
}

bool inRange(int min, int max, int value)
{
	return value >= min && value <= max;
}

double executionTime(clock_t start, clock_t end)
{
	return ((double)(end - start)) / CLOCKS_PER_SEC;
}