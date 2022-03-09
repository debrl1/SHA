
/*
 * This file contains all function macros and the declaration of  actual 
 * functions that relate to the hashing process and operate on 32-bit words.
 */

#ifndef MATH_MATH32_H
#define MATH_MATH32_H

/*
 * 'Ch' stands for 'choose' (see source number 2 in SOURCES.md). The X input
 * 'chooses' is input Y or Z should be used.
 */
#define Ch(X, Y, Z) ((X) & (Y)) ^ (~(X) & (Z))

/*
 * 'Maj' stands for 'Majority' (see source number 2 in SOURCES.md). For each
 * bit, the resulting bit is the bit this is most common in the three inputs.
 */
#define Maj(X, Y, Z) (((X) & (Y)) ^ ((X) & (Z)) ^ ((Y) & (Z)))

/*
 * Calculates the result of the circular right shift operation where X is a
 * 32-bit integer and N is an integer with 0 <= n < 32.
 */
#define ROTR(X, N) (((X) >> (N)) | ((X) << (32 - (N))))

/*
 * Shifts the X input to the right by N bits. 
 * 
 * This macro is solely defined in order for the algorithm syntax to sort of
 * match the one used in FIPS publication 180-4.
 */
#define SHR(X, N) ((X) >> (N))

/*
 * SHA-256 uses four function that are difficult to mention by name. 
 * 
 * I have decided to name equations 4.4, 4.5, 4.6, 4.7 as follows:
 *     SIG0
 *     SIG1
 *     Sig0
 *     Sig1
 *
 * Their definitions are as follows: 
 */

#define SIG0(X) ((ROTR((X), 2))  ^ (ROTR((X), 13)) ^ (ROTR((X), 22)))

#define SIG1(X) ((ROTR((X), 6))  ^ (ROTR((X), 11)) ^ (ROTR((X), 25)))

#define Sig0(X) ((ROTR((X), 7))  ^ (ROTR((X), 18)) ^ (SHR((X), 3)))

#define Sig1(X) ((ROTR((X), 17)) ^ (ROTR((X), 19)) ^ (SHR((X), 10)))

#endif /* MATH_MATH32_H */

