/**
 * @file analyzer.h
 *
 * @brief Contains functions related to image analysis.
 */

#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "functions.h"
#include "utils/utils.h"

/**
 * @brief Analyzes an image and searches for blobs.
 *
 * @param pImage Pointer to the image to analyze.
 * @param r Red value of a color to search for.
 * @param g Green value of a color to search for.
 * @param b Blue value of a color to search for.
 * @param t Tolerance value when comparing color values.
 * @param minimum Minimum amount of pixels for a blob to be considered blob.
 */
void AnalyzeImage(Image* pImage, unsigned char r, unsigned char g, unsigned char b, unsigned char t, int minimum);

/**
 * @brief Explores a possible blob when a valid pixel is found.
 *
 * @param pImage Pointer to the image.
 * @param pBlob Pointer to the blob.
 * @param r Red value of a color to search for.
 * @param g Green value of a color to search for.
 * @param b Blue value of a color to search for.
 * @param t Tolerance value when comparing color values.
 */
void FindBlob(Image* pImage, Blob* pBlob, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

/**
 * @brief Adds all neighbors from a pixel to a queue.
 *
 * @param pImage Pointer to the image.
 * @param pDestination Queue where all the neighbors will be stored.
 * @param coord Coordinate of the master pixel.
 */
void AddNeighbors(Image* pImage, Vector2IQueue* pDestination, Vector2I coord);

/**
 * @brief Evaluates if a pixel is considered valid.
 *
 * @param Pointer to the pixel to evaluate.
 * @param r Red value of a color to search for.
 * @param g Green value of a color to search for.
 * @param b Blue value of a color to search for.
 * @param t Tolerance value when comparing color values.
 */
int PixelInRange(Pixel* pPixel, unsigned char r, unsigned char g, unsigned char b, unsigned char t);

#endif