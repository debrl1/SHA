
/*
 * Contains the declaration of all functions relating to the implementation of 
 * the SHA-256 hashing algorithm.
 *
 * Thijs J.A. van Esch
 * Wed. 9 march 2022
 */

#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>
#include <stdint.h>

/*
 * Hashes the given array of bytes using (the 'message') the SHA-256 hashing 
 * algorithm as the algorithm is defined in FIPS publication 180-4 (1).
 *
 * The length of the message has to be given in bytes.
 *
 * The message digest of a message hashed using the SHA-256 algorithm always
 * consists of 256 bits. This message digest is given back as an array of eight
 * 32-bit integers. The memory address of the first element in this array is
 * returned by the function.
 *
 *  (1) see the sources for this project in the projects README
 */
uint32_t *
sha256hash (const uint8_t *message, size_t mlength);

#endif /* SHA256_H */

