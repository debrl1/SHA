
#include <stdlib.h>

#include "padding.h"
#include "parsing.h"

/*
 * Fills the bytes between element s and n (including element s) of the array
 * with zeroes.
 */
void
erase (uint8_t *array, uint64_t s, uint64_t n)
{
  for (uint64_t in = s; in < n; ++in)
    {
      array[in] = 0;
    }
}

/* 
 * This function pads a message that falls into the first category as listed
 * in 'padding.h'. In other words, the following is assumed: 
 *
 *    length % 64 + 9 <= 64
 *
 * 16 32-bit integers will be returned. These values represent the last block
 * of the message. 
 */
uint32_t *
oneblock (const uint8_t *block, uint64_t length)
{
  uint8_t *padded = malloc (sizeof (uint8_t) * 64);
  size_t  blength = length % 64;
  for (uint8_t in = 0; in < blength; ++in)
    {
      padded[in]  = block[in];
    }
  padded[blength] = 0x80;
  erase (padded, blength + 1, 64 - 8);
  length *= 8;
  for (uint8_t it = 0; it < 8; ++it)
    {
      padded[64 - 8 + it]
	= (uint8_t) (length >> 8 * (7 - it)) & 0xff;
    }
  uint32_t *p32   = malloc (sizeof (uint32_t) * 16);
  convert32 (padded, 64, p32);
  free (padded);
  return p32;
}

uint32_t *
twoblocks (const uint8_t *blocks, uint64_t length)
{
  uint8_t *padded  = malloc (sizeof (uint8_t) * 128);
  size_t  blength  = length % 64 ? length % 64 : 64;
  for (uint8_t in  = 0; in < blength; ++in)
    {
      padded[in]   = blocks[in];
    }
  padded[blength]  = 0x80;
  erase (padded, blength + 1, 128 - 8);
  length *= 8;
  for (uint32_t it = 0; it < 8; ++it)
    {
      padded[128 - 8 + it]
	= (uint8_t) (length >> 8 * (7 - it)) & 0xff;
    }
  uint32_t *p32    = malloc (sizeof (uint32_t) * 32);
  convert32 (padded, 128, p32);
  free (padded);
  return p32;
}

uint32_t *
padblock (const uint8_t *message, uint64_t length)
{
  if (length % 64 + 9 <= 64)
    {
      return oneblock (message, length);
    }
  else
    {
      return twoblocks (message, length);
    }
}
