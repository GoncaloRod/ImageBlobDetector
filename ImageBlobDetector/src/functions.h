/**
 * @file functions.h
 *
 * @brief Contains some random functions to do random things.
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "utils/utils.h"
#include "files.h"

/**
 * @brief Function to print usage message.
 *
 * @param pProgramName String with the executable name to display in usage message.
 */
void PrintUsageMessage(char* pProgramName);

/**
 * @brief Validates required command line arguments.
 *
 * @param argc Number of arguments passed in the command line.
 * @param argv Every string passed in the command line.
 * @param pFileName Pointer to the variable where the input file name will be stored.
 * @param pR Pointer to the variable where the desired Red amount will be stored.
 * @param pG Pointer to the variable where the desired Green amount will be stored.
 * @param pB Pointer to the variable where the desired Blue amount will be stored.
 * @param pT Pointer to the variable where the desired Tolerance amount will be stored.
 * @param pMode Pointer to the variable where the mode name will be stored.
 *
 * @return 1 if the arguments are valid. 0 If the arguments are invalid.
 */
int ValidateArguments(int argc, char** argv, char* pFileName, unsigned char* pR, unsigned char* pG, unsigned char* pB, unsigned char* pT, char* pMode);

/**
 * @brief Get a pointer to a pixel from a given coordinate.
 *
 * @param pImage Pointer to the Image structure.
 * @param X X value from coordinate.
 * @param Y Y value from coordinate.
 *
 * @return Pointer to the pixel.
 */
Pixel* GetPixelFromVector2I(Image* pImage, int X, int Y);

/**
 * @brief Prints all image's information.
 *
 * @param pImage Pointer to the image to print the information.
 */
void PrintImageInformation(Image* pImage);

/**
 * @brief Gets the image with more blobs.
 *
 * @param pImages Pointer to a list of images.
 *
 * @return Pointer to the image with more blobs.
 */
Image* GetImageMoreBlobs(ImageList* pImages);

/**
 * @brief Compare to Standard Deviation values.
 *
 * @param value1 Value 1 to compare.
 * @param value1 Value 2 to compare.
 *
 * @return -1 if value 1 is less then value 2. 0 if the values are equal. 1 if value 1 is grater then value 2.
 */
int CompareStdDeviation(Vector3F value1, Vector3F value2);

#endif