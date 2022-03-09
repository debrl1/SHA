
/*
 * This file contains the declaration of the function that is used to convert
 * sequences of bytes into sequences of 32-bit integers while preserving the
 * original order of the bytes.
 *
 * Thijs van Esch
 * Wed. 9 march 2022
 */

#ifndef PREPROCESSING_PARSING_H
#define PREPROCESSING_PARSING_H

#include <stdint.h>

/*
 * Converts the given array of bytes into an array of 32-bit integers while
 * preserving the byte-order of the original array.
 * 
 * The size of the original array has to be given in bytes. 
 */
void
convert32 (const uint8_t *original, uint64_t size, uint32_t *array32);

#endif /* PREPROCESSING_PARSING_H */

