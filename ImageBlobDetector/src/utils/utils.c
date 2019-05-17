#include "utils.h"

void PrintError(const char *pMessage, ...)
{
	va_list vargs;

	va_start(vargs, pMessage);

	printf("[ERROR]: ");

	vprintf(pMessage, vargs);

	printf("\n");

	va_end(vargs);
}

void PrintInfo(const char *pMessage, ...)
{
	va_list vargs;

	va_start(vargs, pMessage);

	printf("[INFO]: ");

	vprintf(pMessage, vargs);

	printf("\n");

	va_end(vargs);
}

void PrintWarning(const char* pMessage, ...)
{
	va_list vargs;

	va_start(vargs, pMessage);

	printf("[WARNING]: ");

	vprintf(pMessage, vargs);

	printf("\n");

	va_end(vargs);
}

int IsNumeric(char* pNum)
{
	int numeric = 1;

	for (int i = 0; i < (int)strlen(pNum) && numeric; ++i)
		if (pNum[i] < '0' || pNum[i] > '9')
			numeric = 0;

	return numeric;
}

int InRange(int min, int max, int value)
{
	return value >= min && value <= max;
}

double ExecutionTime(clock_t start, clock_t end)
{
	return ((double)end - (double)start) / CLOCKS_PER_SEC;
}