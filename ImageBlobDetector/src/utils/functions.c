#include "functions.h"

void printUsageMessage(char *programName)
{
	printf("\nUsage: %s tests input_file red green blue tolerance mode\n\n", programName);

	// TODO: Fix indentation
	printf("  input_file: File to be precessed\n");
	printf("  red: Desired red value of color to find\n");
	printf("  green: Desired green value of color to find\n");
	printf("  blue: Desired blue value of color to find\n");
	printf("  tolerance: Tolerance in red, green and blue values to find\n");
	printf("  mode: Mode in which program will execute. Can be menu, all or mem\n");
}