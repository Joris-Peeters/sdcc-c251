/* getword-signed.c - the upper word of a long, as a signed int.

   (int)(ul >> 16) is a GETWORD node.  It was typed int, so the cast to int
   looked redundant and was dropped, while the iCode gives the word an
   unsigned type: the comparison with a negative int was then unsigned.
 */

#include <testfwk.h>

volatile unsigned long ul = 0x0001ffffUL;
volatile unsigned long uh = 0xffd40000UL;
volatile int neg = -44;
volatile unsigned int big = 65492u;

static int
le (void)
{
  return (int)(ul >> 16) <= neg;
}

static int
ge (void)
{
  return (int)(uh >> 16) >= 0;
}

static int
divided (void)
{
  return (int)(ul >> 16) <= (int)(big / 1u);
}

void
testGetwordSigned (void)
{
  ASSERT (!le ());
  ASSERT (!ge ());
  ASSERT (!divided ());
  ASSERT ((int)(uh >> 16) == -44);
}
