/* narrow-op-net-uses.c - narrowing an operation net with a stale use.

   Generalized constant propagation narrows operations whose result is only
   used narrowly.  An earlier pass leaves a use of an operand that no longer
   exists; for mcs51 that was accepted in the large and huge models only, so
   this expression stopped the small model with an internal error (random
   difftest, mcs251 and mcs51 alike).
 */

#include <testfwk.h>

#if defined(__SDCC_mcs51) || defined(__SDCC_mcs251) /* other ports do not accept the stale use */
volatile int g4 = 0;
volatile unsigned long g5 = 3574445849ul;
volatile signed char g6 = -53;
volatile unsigned long g7 = 3945284281ul;
unsigned long x0[4] = {7ul, 1919455630ul, 2122297309ul, 2808385977ul};
const long c0[4] = {79292141l, 943285565l, -1820094445l, 275687834l};
volatile unsigned char k = 1;

/* (long)g7 < -53 is 1, the right side (1 >> 1) is 0, so 1 > 0. */
static void
narrowed (void)
{
  g5 = ((unsigned int)(k ? ((unsigned long)(((long)g7) < ((long)g6))) : ((unsigned long)(x0[0] ? ((int)g4) : 1)))) >
       ((unsigned int)(((unsigned int)(((int)g5) || ((int)c0[0]))) >> 1));
}
#endif

void
testNarrowOpNetUses (void)
{
#if defined(__SDCC_mcs51) || defined(__SDCC_mcs251)
  narrowed ();
  ASSERT (g5 == 1);
#endif
}
