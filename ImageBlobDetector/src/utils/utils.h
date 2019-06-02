/**
 * @file utils.h
 *
 * @brief Contains utility functions that can be used in various projects
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

/**
 * @brief Prints a message with an error format.
 *
 * @param message Message to print.
 */
void PrintError(const char* message, ...);

/**
 * @brief Prints a message with an information format.
 *
 * @param message Message to print.
 */
void PrintInfo(const char* message, ...);

/**
 * @brief Prints a message with an waring format.
 *
 * @param message Message to print.
 */
void PrintWarning(const char* message, ...);

/**
 * @brief Checks if a string contains only numbers.
 *
 * @param pNum String to validate.
 *
 * @return 1 if string is numeric. 0 if string is not numeric.
 */
int IsNumeric(char* pNum);

/**
 * @brief Checks if a number is inside a range of 2 numbers.
 *
 * @param min Minimum value.
 * @param max Maximum value.
 * @param value Value to evaluate.
 *
 * @return 1 if number is in range. 0 is number is not in range.
 */
int InRange(int min, int max, int value);

/**
 * @brief Calculates execution time of a process.
 *
 * @param start Start of the process.
 * @param end End of the process.
 *
 * @return Execution time.
 */
double ExecutionTime(clock_t start, clock_t end);

#endif