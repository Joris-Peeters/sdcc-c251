/* address-integer-init.c - static initializers from an address cast to an
   integer, plus a constant.

   (unsigned long) &x + 2 was emitted as x + 0: the constant was scaled by
   the size of what the cast type points to, which is 0 for an integer type.
 */

#include <testfwk.h>

char x[4];
long y[4];

unsigned long xl = (unsigned long) &x + 2;
unsigned int xi = (unsigned int) &x + 3;
unsigned long yl = (unsigned long) &y + 5;
char *xp = (char *) &y + 6;
long *yp = (long *) &y + 1;

void
testAddressIntegerInit (void)
{
  ASSERT (xl == (unsigned long) &x + 2);
  ASSERT (xi == (unsigned int) &x + 3);
  ASSERT (yl == (unsigned long) &y + 5);
  ASSERT (xp == (char *) &y + 6);
  ASSERT (yp == &y[1]);
}
