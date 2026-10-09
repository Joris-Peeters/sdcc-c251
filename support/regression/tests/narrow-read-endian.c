/* narrow-read-endian.c - narrowing a value read through a pointer.

   (unsigned char)p[i] may be done as a 1-byte read; on a big-endian target
   that byte is at the end of the object, not at its address.  sdcc-c251
   read the high byte.
 */

#include <testfwk.h>
#include <stdint.h>

static const uint16_t table[5] = {0x00f7, 0x038f, 0x0039, 0x030f, 0x0079};
static uint16_t words[3] = {0x1234, 0x5678, 0x9abc};
static const uint32_t longs[2] = {0x11223344UL, 0x55667788UL};
static volatile unsigned char k = 3;

void
testNarrowRead (void)
{
  unsigned char i;

  for (i = 0; i < 5; i++)
    ASSERT ((unsigned char)table[i] == (table[i] & 0xff));
  ASSERT ((unsigned char)table[k] == 0x0f);
  ASSERT ((unsigned char)words[k - 2] == 0x78);
  ASSERT ((unsigned char)longs[k - 2] == 0x88);
  ASSERT ((uint16_t)longs[k - 3] == 0x3344);
}
