/* xor-acc-pair.c - ~ / ^ 0xff.. of a value held in A:B (mcs51, mcs251).

   A 16-bit value returned by a call (e.g. __mulint) arrives in A and B.
   XOR with 0xff in the high byte was emitted as CPL A instead of acting on
   B, so ~x only complemented the low byte.
 */

#include <testfwk.h>

static volatile unsigned int g2 = 30276u;
static volatile unsigned char g8 = 60;
static volatile unsigned int g7 = 4641;
static volatile unsigned int d = 10;

void
testXorAccPair (void)
{
  ASSERT ((unsigned long)(~(unsigned int)(g2 * g8)) == 0x480fUL);
  ASSERT ((unsigned int)~(g7 % d) == 0xfffeU);
  ASSERT ((unsigned int)((g2 * g8) ^ 0xff00U) == 0x48f0U);
}
