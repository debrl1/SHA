
/* 
 * Contains the declaration of the function that can pad a 512-bit message 
 * block.
 *
 * Thijs J.A. van Esch
 * Mon. 7 march 2022
 */

#ifndef PADDING_H
#define PADDING_H

#include <stdint.h>

/*
 * Pads the given message block.
 *
 * The length of the message also has to be given in bytes.
 *
 * The method returns the address of the first 32-bit integer in an array of
 * 16 or 32 SHA words that represent the padded block.
 *
 * Note the following:
 *
 * There are two types of messages when it comes to padding:
 *
 *  1. the ones that can be padded only using the last block of the message (
 *     no new block has to be appended to the message), or
 *  2. the ones that need another block to be appended to the message in 
 *     order for the message to be properly padded.
 * 
 * A message is of the first category if there are 9 or more unused bytes in
 * the last message block. If this is the case, the 'padblock' function will
 * return 16 32-bit integers (a.k.a. 16 'words'). 
 * 
 * If this is not the case, the function will return 32 words, representing
 * the last two blocks of the message. It is up to the caller of the function
 * to determine the type of message that is being dealt with.
 */ 
uint32_t *
padblock (const uint8_t *block, uint64_t length);

#endif /* PADDING_H */
