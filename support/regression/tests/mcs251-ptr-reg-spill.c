/* mcs251-ptr-reg-spill.c - spilling the users of R0 and R1.

   When a value is spilt to the stack, the live ranges holding R0 or R1 are
   spilt too.  That loop also took live ranges that had already ended: their
   register list was stale, and spilling one freed registers that a later
   long had been given, so other values were allocated over it (random
   difftest, large model with --stack-auto).
 */

#include <testfwk.h>

volatile unsigned int g1 = 50682u;
volatile long g5 = -831833084l;
volatile signed char g7 = -101;
unsigned int a0[4] = {43509u, 57463u, 2706u, 62331u};
int a1[4] = {932, -15123, 13944, -23989};
__xdata int x0[4] = {7, -4250, -26144, 20935};
const __code unsigned char c0[4] = {226, 252, 239, 161};
const __code unsigned int c1[4] = {33628u, 37102u, 23347u, 1u};
int *p0;
unsigned int *p1;
const unsigned int *p2;

void
testPtrRegSpill (void)
{
  p0 = a1;
  p1 = a0;
  p2 = c1;
  p0[((unsigned char)(long)(-1920249290l) & 3)] = ((int)((int)(unsigned char)14));
  /* The long is (unsigned long)(23347 | -101) = -69 as a long, the
     comparison (29867 % -23989 < 14) is 0, so 0 is stored in x0[0]. */
  x0[((unsigned char)(*(p0 + 0)) & 3)] = ((int)((unsigned char)(((long)(((unsigned long)(((unsigned long)((unsigned long)a1[0])) - ((unsigned long)((unsigned long)g1)))) ? ((unsigned long)(((int)(*(p2 + 2))) | ((int)g7))) : ((unsigned long)g5))) >= ((long)(((unsigned int)((((int)(unsigned long)2176545962ul) | 1) % (((int)(*(p0 + 3))) | 1))) < ((unsigned int)p0[((unsigned char)c0[0] & 3)]))))));
  ASSERT (x0[0] == 0);
}
