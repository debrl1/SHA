
/*
 * Contains the tests for functions in 'src/padding.h'. 
 *
 * Tests are done by calling the 'assert' function. Each call to this 
 * function has a unique (numeric) identifier. If the assertion fails, this 
 * integer is displayed onto the screen and I (manually) look up what went
 * wrong within the source file. 
 *
 * I have nu clue how unit testing is done in the C programming language. 
 *
 * Thijs van Esch
 * Mon 7 march 2022
 */

#include <stdio.h>

#include "../src/preprocessing/padding.h"

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

/*
 * Tests whether a block is padded properly.
 *
 *    "abc" or {0x61, 0x62, 0x63} with a message length of 3
 *
 * The expected outcome is as follows
 *
 *    {0x61, 0x62, 0x63,    -> original message
 *     0x80,                -> appending a single '1' bit
 *     ...                  -> all zeroes
 *     0x18};               -> the length of the message in bits (24) 
 *
 * but then given in 32-bit integers. 
 */
void
ca (void)
{
  uint8_t   message[] = {0x61, 0x62, 0x63};
  uint8_t   length    =  3;
  uint32_t *padded    = padblock (message, length);
  
  assert (padded[0], 0x61626380, 1);
  for (uint8_t index = 1; index < 15; ++index)
    {
      assert (padded[index], 0x00000000, 3);
    }
  assert (padded[15], 0x00000018, 4);
}

void
cb (void)
{
  uint8_t   *message = (uint8_t *)
    "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
  uint8_t   length   = 56;  
  uint32_t *padded   = padblock (message, length);

  /*
   * Please excuses this fairly long list of nearly identical function calls.
   *
   * I want to avoid errors in code that is meant to test other code, which
   * is why I decided to test the outcome of the 'padblock' function as 
   * follows.
   */
  assert (padded[0], 0x61626364, 5);
  assert (padded[1], 0x62636465, 6);
  assert (padded[2], 0x63646566, 7);
  assert (padded[3], 0x64656667, 8);
  assert (padded[4], 0x65666768, 9);
  assert (padded[5], 0x66676869, 10);
  assert (padded[6], 0x6768696a, 11);
  assert (padded[7], 0x68696a6b, 12);
  assert (padded[8], 0x696a6b6c, 13);
  assert (padded[9], 0x6a6b6c6d, 14);
  assert (padded[10], 0x6b6c6d6e, 15);
  assert (padded[11], 0x6c6d6e6f, 16);
  assert (padded[12], 0x6d6e6f70, 17);
  assert (padded[13], 0x6e6f7071, 18);
  assert (padded[14], 0x80000000, 19);

  for (uint8_t in = 15; in < 30; ++in)
    {
      assert (padded[in], 0x00000000, 20);
    }

  assert (padded[31], 0x000001c0, 21);
}

int
main (void)
{
  ca ();
  if (success)
    printf ("Padding test A ran without error\n");
  else
    {
      printf ("Padding test A failed\n");
      success = 1;
    }
  cb ();
  if (success)
    printf ("Padding test B ran without error\n");
  else
    {
      printf ("Padding test B failed\n");
      success = 1;
    }
  return 0;
}
