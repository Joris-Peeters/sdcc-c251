/* rtrack-div.c - register values the code generator believes it knows.

   The register tracker (rtrack.c, mcs51 and mcs251) follows literal values
   through the emitted lines and takes a register that holds a wanted
   literal instead of the literal.  DIV AB computed the remainder from the
   new A, so after 1 / 69 it took B for 0, and the zero extension of a sum
   was stored from a register holding 1 (random difftest, small model;
   mcs51 generated the same code).
 */

#include <testfwk.h>

volatile unsigned char flag = 74;
volatile unsigned long wide = 1415051924ul;
long result;

/* (wide > wide) is 0, so the code generator sees the literal 1 % 69. */
static void
remainderSum (void)
{
  result = (long)(unsigned int)((unsigned int)(((long)flag) || 0L) +
                                (unsigned int)((((long)((unsigned int)wide > (unsigned int)wide)) | 1) % 69L));
}

void
testRtrackDiv (void)
{
  remainderSum ();
  ASSERT (result == 2);
}
