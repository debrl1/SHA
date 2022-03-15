
/*
 * Contains the tests for the 'sha256hash' function in  'src/padding.h'. 
 *
 * Tests are done by calling the 'assert' function. Each call to this 
 * function has a unique (numeric) identifier. If the assertion fails, this 
 * integer is displayed onto the screen and I (manually) look up what went
 * wrong within the source file. 
 *
 * Thijs van Esch
 * Wed. 7 march 2022 (last modified on Fri. 11 march 2022)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/sha256.h"

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
check (const uint32_t *result, const uint32_t *expected, uint8_t offset)
{
  for (uint8_t in = 0; in < 8; ++in)
    {
      assert (result[in], expected[in], in + offset);
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
  check (result, expected, 0);
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
  check (result, expected, 8);
}

void
cc ()
{
  uint8_t *message /* This message consists of one million 'a's  */
     = malloc (sizeof (uint8_t) * 1000000);
  uint64_t  mlength    = 1000000;
  memset (message, 'a', mlength);
  uint32_t *result     = sha256hash (message, mlength);
  uint32_t  expected[] = {0xcdc76e5c, 0x9914fb92, 0x81a1c7e2, 0x84d73e67,
                          0xf1809a48, 0xa497200e, 0x046d39cc, 0xc7112cd0};
  check (result, expected, 16);
}

void
cd ()
{
  uint8_t *message    = (uint8_t *) "";
  uint64_t mlength    = 0;
  uint32_t *result    = sha256hash (message, mlength);
  uint32_t expected[] = {0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924,
                         0x27ae41e4, 0x649b934c, 0xa495991b, 0x7852b855};
  check (result, expected, 24);
}

void
ce ()
{
  uint8_t *message    = (uint8_t *) "This is a really long message, containing "
                                    "a lot of characters in order to test the "
                                    "hashing of multi-block messages.";
  uint64_t mlength    = 115;
  uint32_t *result    = sha256hash (message, mlength);
  uint32_t expected[] = {0x4745ecea, 0xa45fd629, 0x86e68cfd, 0x90b8cd34,
                         0x8a1a381e, 0x0ea4755a, 0xbae9fd5d, 0x05baf10b};
  check (result, expected, 32);
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
  cc ();
  if (success)
    printf ("SHA256 test C ran without error\n");
  else
    {
      printf ("SHA256 test C failed\n");
      success = 1;
    }
  cd ();
  if (success)
    printf ("SHA256 test D ran without error\n");
  else
    {
      printf ("SHA256 test D failed\n");
      success = 1;
    }
  ce ();
  if (success)
    printf ("SHA256 test E ran without error\n");
  else
    {
      printf ("SHA256 test E failed\n");
      success = 1;
    }
  return 0;
}

