/* mcs251-address-initializer.c - integers initialized with an address.

   (unsigned long) &x in a static initializer was emitted with 16 address
   bits and the region byte cleared, while the same conversion at run time
   keeps all 24 bits (bug-2031 in the large model).
 */

#include <testfwk.h>

#pragma disable_warning 322

#ifdef __SDCC_mcs251
__xdata unsigned char xv;
__code const unsigned char cv = 1;
unsigned long xl = (unsigned long) &xv;
unsigned long cl = (unsigned long) &cv;
unsigned int xi = (unsigned int) &xv;
unsigned char xc = (unsigned char) &xv;
struct
{
  unsigned char c;
  unsigned long l;
} xs = {(unsigned char) &xv, (unsigned long) &xv};
#endif

void
testAddressInitializer (void)
{
#ifdef __SDCC_mcs251
  __xdata unsigned char *xp = &xv;
  const __code unsigned char *cp = &cv;

  ASSERT (xl == (unsigned long) xp);
  ASSERT (cl == (unsigned long) cp);
  ASSERT ((cl >> 16) != 0);
  ASSERT (xi == (unsigned int) xp);
  ASSERT (xc == (unsigned char) xp);
  ASSERT (xs.c == (unsigned char) xp);
  ASSERT (xs.l == (unsigned long) xp);
#endif
}
