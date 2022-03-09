
#include "parsing.h"

void
convert32 (const uint8_t *original, uint64_t size, uint32_t *array32)
{
  for (uint64_t in = 0; in < size; in = in + 4)
    {
      array32[in / 4] =
	  (original[in]     << 24)
	| (original[in + 1] << 16)
	| (original[in + 2] << 8)
	| (original[in + 3]);
    }
}
