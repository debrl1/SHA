
#include <stdlib.h>

#include "math/constants.h"
#include "math/math32.h"
#include "preprocessing/padding.h"
#include "preprocessing/parsing.h"

#include "../include/sha256.h"

int count = 0;

/*
 * For all SHA algorithm, each block is processed in order. This function takes
 * the hash value and the current block as arguments in order to hash the block
 * and update the hash value accordingly.
 *
 * The method assumes that a hash value has already been set. In other words,
 * the initial hash values have to be copied before the hashing of blocks is
 * started.
 *
 * The block also has to be given as an array of 32-bit integers, which means
 * the input to the 'sha256hash' function has to be converted before this
 * function is called.
 */
void
hashblock (uint32_t *hashvalues, const uint32_t *block)
{
  uint32_t *ms   = malloc (sizeof (uint32_t) * 64);
  for (uint8_t t = 0; t < 64; ++t)
    {
      if (t < 16)
	ms[t] = block[t];
      else
	ms[t] = Sig1(ms[t - 2]) + ms[t - 7]
	      + Sig0(ms[t - 15])  + ms[t - 16];
    }
  uint32_t * wv = malloc (sizeof (uint32_t) * 8);
  for (uint8_t in = 0; in < 8; ++in) /* Setting the working variables */
    {
      wv[in] = hashvalues[in];
    }
  for (uint8_t it = 0; it < 64; ++it)
    {
      uint32_t t1, t2; /* Tempory variables */
      t1    = wv[7];
      t1   += SIG1(wv[4]);
      t1   += Ch(wv[4], wv[5], wv[6]);
      t1   += K256[it];
      t1   += ms[it];
      t2    = SIG0 (wv[0]);
      t2   += Maj (wv[0], wv[1], wv[2]);
      wv[7] = wv[6];
      wv[6] = wv[5];
      wv[5] = wv[4];
      wv[4] = wv[3] + t1;
      wv[3] = wv[2];
      wv[2] = wv[1];
      wv[1] = wv[0];
      wv[0] = t1 + t2;
    }
  for (uint8_t in = 0; in < 8; ++in)
    {
      hashvalues[in] = wv[in] + hashvalues[in];
    }
  free (ms);
  free (wv);
}

uint32_t *
sha256hash (const uint8_t *message, size_t mlength)
{
  const uint8_t *block = message;
  size_t fbc = mlength / 64;
  size_t r = mlength % 64 > 55 ? 2 : 1;
  uint32_t *hv = malloc (sizeof (uint32_t) * 8);
  for (uint8_t in = 0l; in < 8; ++in)
    {
      hv[in] = INIT256[in];
    }
  uint32_t *block32 = malloc (sizeof (uint32_t) * 16);
  for (size_t it = 0; it < fbc; ++it)
    {
      convert32 (block, 64, block32);
      hashblock (hv, block32);
      block = block + 64; 
    }
  free (block32);
  uint32_t *remainder = padblock (message + (64 * fbc), mlength);
  hashblock (hv, remainder);
  if (r != 1)
    {
      hashblock (hv, remainder + 16);
    }
  free (remainder);
  return hv;
}
