
/*
 * Contains the tests for the 'sha256hash' function in  'src/padding.h'. 
 *
 * Tests are done by calling the 'assert' function. Each call to this 
 * function has a unique (numeric) identifier. If the assertion fails, this 
 * integer is displayed onto the screen and I (manually) look up what went
 * wrong within the source file. 
 *
 * Thijs van Esch
 * Wed. 7 march 2022
 */


#include <stdio.h>

#include "../src/sha256.h"

uint8_t success = 1;

void
assert (uint32_t value, uint32_t expected, uint32_t test)
{
  if (value != expected)
    {
      printf ("Test no. %d failed:\n", test);
      printf ("\texpected outcome: 0x%08x\n", expected);
      printf ("\tactual outcome: 0x%08x\n", value);
      success = 0; 
    }
}

void
ca ()
{
  uint8_t  *message    = (uint8_t *) "abc";
  uint64_t  mlength    = 3;
  uint32_t *result     = sha256hash (message, mlength);
  uint32_t  expected[] = {0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223,
                          0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad};
  for (uint8_t in = 0; in < 8; ++in)
    {
      assert (result[in], expected[in], in);
    }
}

void
cb ()
{
  uint8_t  *message    = (uint8_t *) "abcdbcdecdefdefgefghfghighijhij"
                                     "kijkljklmklmnlmnomnopnopq";
  uint64_t  mlength    = 56;
  uint32_t *result     = sha256hash (message, mlength);
  uint32_t  expected[] = {0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039,
                          0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1};

  for (uint8_t in = 0; in < 8; ++in)
    {
      assert (result[in], expected[in], in + 8);
    }
}

int
main(void)
{
  
  ca ();
  if (success)
    printf ("SHA256 test A ran without error\n");
  else
    {
      printf ("SHA256 test A failed\n");
      success = 1;
    }
  cb ();
  if (success)
    printf ("SHA256 test B ran without error\n");
  else
    {
      printf ("SHA256 test B failed\n");
      success = 1;
    }
  return 0;
}

