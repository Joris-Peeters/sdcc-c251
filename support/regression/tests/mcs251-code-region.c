/* mcs251-code-region.c - __code objects outside the region the code runs in.

   __code reads used MOVC A,@A+DPTR after loading DPXL, but MOVC ignores
   DPXL and reads region FF (or the current region on some cores).  A
   __code object elsewhere, here in region FE, read the wrong bytes (the absolute
   test with __code).  Generic pointers already read code through DR56.
 */

#include <testfwk.h>

#ifdef __SDCC_mcs251
__code const unsigned char __at (0xfee000) table[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
__code const unsigned int __at (0xfee006) word = 0x1234;
#endif

static volatile unsigned char k = 4;

void
testCodeRegion (void)
{
#if defined(__SDCC_mcs251)
  const __code unsigned char *pc = table;
  const unsigned char *pg = table;
  unsigned char i, sum = 0;

  ASSERT (table[0] == 0x11);
  ASSERT (table[k] == 0x55);
  ASSERT (word == 0x1234);
  ASSERT (pc[k + 1] == 0x66);
  ASSERT (pg[k - 1] == 0x44);
  for (i = 0; i < 6; i++)
    sum += pc[i];
  ASSERT (sum == (unsigned char) (0x11 + 0x22 + 0x33 + 0x44 + 0x55 + 0x66));
#endif
}
